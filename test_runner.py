import subprocess
import os
import difflib
from typing import Tuple, Optional
from colorama import Fore, Style, init


class DualLogger:
    def __init__(self, file_path: str):
        self.terminal = sys.stdout
        self.log = open(file_path, "w", encoding="utf-8")

    def write(self, message: str):
        self.terminal.write(message)
        self.log.write(message)

    def flush(self):
        self.terminal.flush()
        self.log.flush()

    def close(self):
        self.log.close()


init(autoreset=True)

CASES_DIR = "tests/cases"    # Directory containing test case source files
OUTPUTS_DIR = "tests/outputs" # Directory where output files will be saved
BIN_OUTPUT = "output"         # Name of the binary that is run after compilation

# Compile the IR from a given source file
def compile_ir(src_file: str) -> None:
    subprocess.run(["make", "run_code", f"TEST_FILE={src_file}"], check=True)


# (TODO: Možná se zamyslet na spojením do jednoho příkazu v makefile code_run)
def compile_and_run_binary() -> str:
    subprocess.run(["make", "run"], check=True)
    result = subprocess.run([f"./{BIN_OUTPUT}"], capture_output=True, text=True)
    return result.stdout.strip()

# Save the program output into a text file
def save_output(test_name: str, output_text: str) -> None:
    output_path = os.path.join(OUTPUTS_DIR, f"{test_name}.out.txt")
    with open(output_path, "w") as f:
        f.write(output_text)

# Compare the expected and actual output files line-by-line
def compare_outputs(expected_file: str, output_file: str) -> Tuple[bool, list[str], list[str]]:
    with open(expected_file) as f:
        expected_lines = f.read().strip().splitlines()

    with open(output_file) as f:
        output_lines = f.read().strip().splitlines()

    return expected_lines == output_lines, expected_lines, output_lines

# Run a single test case
def run_test(src_file: str, only_compare: bool = False) -> Optional[bool]:
    # Extract test name (without the .pl extension)
    test_name = os.path.basename(src_file)[:-3]  
    expected_file = os.path.join(CASES_DIR, f"{test_name}_expected.txt")
    output_file = os.path.join(OUTPUTS_DIR, f"{test_name}.out.txt")

    if not only_compare:
        # Compile IR and run the binary
        compile_ir(src_file)
        output_text = compile_and_run_binary()
        save_output(test_name, output_text)

    # If no expected output is found, warn and skip
    if not os.path.exists(expected_file):
        print(f"{Fore.YELLOW}⚠️ No expected file for {test_name}{Style.RESET_ALL}")
        return None
    if not os.path.exists(output_file):
        print(f"{Fore.YELLOW}⚠️ No output file for {test_name}{Style.RESET_ALL}")
        return None

    # Compare actual output to expected output
    passed, expected_lines, output_lines = compare_outputs(expected_file, output_file)

    if passed:
        print(f"{Fore.GREEN}✅ {test_name} passed{Style.RESET_ALL}")
        return True
    else:
        print(f"{Fore.RED}❌ {test_name} failed{Style.RESET_ALL}")
        # If failed, show the difference line-by-line
        diff = difflib.unified_diff(expected_lines, output_lines, fromfile="expected", tofile="actual", lineterm="")
        for line in diff:
            if line.startswith('+') and not line.startswith('+++'):
                print(Fore.GREEN + line)
            elif line.startswith('-') and not line.startswith('---'):
                print(Fore.RED + line)
            else:
                print(line)
        return False

import datetime

def main(only_compare: bool = False) -> None:
    os.makedirs(OUTPUTS_DIR, exist_ok=True)

    now = datetime.datetime.now().isoformat(timespec="seconds").replace(":", "-")
    report_filename = f"report_{now}.txt"
    report_path = os.path.join(OUTPUTS_DIR, report_filename)

    logger = DualLogger(report_path)
    sys.stdout = logger  # Redirect all prints to both console and file

    print(f"Test Report - {datetime.datetime.now().isoformat()}")
    print("=" * 30)

    passed = 0
    failed = 0
    skipped = 0

    for filename in sorted(os.listdir(CASES_DIR)):
        if filename.endswith(".pl"):
            src_path = os.path.join(CASES_DIR, filename)
            result = run_test(src_path, only_compare=only_compare)
            if result is True:
                passed += 1
            elif result is False:
                failed += 1
            else:
                skipped += 1

    print("\n" + "="*30)
    print(f"Summary: {Fore.GREEN}{passed} passed{Style.RESET_ALL}, {Fore.RED}{failed} failed{Style.RESET_ALL}, {Fore.YELLOW}{skipped} skipped{Style.RESET_ALL}")

    sys.stdout = logger.terminal  # Restore normal print behavior
    logger.close()
    print(f"Report saved to ./tests/{report_path}")

if __name__ == "__main__":
    import sys
    # PROTOŽE JSEM ČURÁK, CO TO DĚLÁ NA ARMU ALE NAPSAL COMPILER PRO X86
    # TAK JE TU FLAG NA POROVNÁNÍ VÝSTUPŮ BEZ KOMPILACE
    only_compare = "--only-compare" in sys.argv 
    main(only_compare=only_compare)
