# PainLang Compiler

Cílem je vytvořit takový základ jazyka, abych mohl vzít ten jazyk a vytvořit v něm překladač pro tento jazyk. 

## Testování
Je nutné nejdříve vyčistit projekt a zkompilovat parser.
```bash
make clean
make parser
python3 test_runner.py
```

## Použití

```bash
# Zkompilování projektu
make parser

# Získání output.asm ze zdrojáku
./bin/painlang_parser -i input_file [-o output-file] [-O] [-m ir_file] 
```

Překladač zatím umí pouze `x86_64` pro získání executable a následné spuštění je nutné spustit tento příkaz:

```bash
nasm -f elf64 output.asm -o output.o && gcc -no-pie output.o -o output && ./output
```