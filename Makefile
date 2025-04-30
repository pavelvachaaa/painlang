MAKE=make
GCC=gcc

CFLAGS=-no-pie

# Use ?= so the default is used only if TEST_FILE is not provided in the command
TEST_FILE ?= ./tests/valid_01.pl

FILENAME=pl
PRINT_OUTPUT="y"

PARSER_BIN="painlang_parser"
PARSER_OUTPUT="output"

ROOT_DIR=$(shell pwd)
INCDIR=$(ROOT_DIR)/inc
INCFILES := $(shell find $(INCDIR) -type f -name "*.c")

BINDIR=./bin
TESTDIR=./tests

test:
	make clean
	make parser
	python3 test_runner.py

# -p to create /bin if it doesn't exist
parser:
	@mkdir -p $(BINDIR)
	yacc -d $(FILENAME).y
	flex $(FILENAME).l
	$(GCC) -I$(INCDIR) -c $(INCFILES) lex.yy.c y.tab.c
	$(GCC) -o $(PARSER_BIN) *.o
	@mv $(PARSER_BIN) $(BINDIR)/
	@mv *.o $(BINDIR)

# Intermediate representation generation
run_ir:
	$(BINDIR)/$(PARSER_BIN) -i $(TEST_FILE) -O

# Compile ASM to binary and run it
run:
	nasm -f elf64 $(PARSER_OUTPUT).asm -o $(PARSER_OUTPUT).o && $(GCC) $(CFLAGS) $(PARSER_OUTPUT).o -o $(PARSER_OUTPUT) && ./$(PARSER_OUTPUT)

# Clean, build, run IR and execute
run_full:
	make clean
	make parser
	make run_ir TEST_FILE=$(TEST_FILE)
	make run

# Just IR and run
run_code:
	make run_ir TEST_FILE=$(TEST_FILE)
	make run

debug:
	clear
	make clean
	make parser
	make run_ir TEST_FILE=$(TEST_FILE)

subclean:
	@rm -rf lex.yy.c
	@rm -rf y.tab.h y.tab.c

.PHONY: clean

clean: subclean
	@rm -rf $(BINDIR)/* *.o