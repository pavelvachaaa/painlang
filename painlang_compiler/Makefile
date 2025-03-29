# Kámo tak makefile je hustá věc třeba
MAKE=make
GCC=gcc

CFLAGS=-no-pie

DEFAULT_TEST_FILE="./tests/valid_01.painlang"

FILENAME=pl
PRINT_OUTPUT="y"

PARSER_BIN="painlang_parser"
PARSER_OUTPUT="output"

ROOT_DIR=$(shell pwd)
INCDIR=$(ROOT_DIR)/inc
INCFILES := $(shell find $(INCDIR) -type f -name "*.c")

BINDIR="./bin"
TESTDIR="./tests"

test:
	echo $(ROOT_DIR)
	echo $(LIBOBJS)
	echo $(LIBNAMES)
	echo $(LIBS)

#-p abychom vytvořili /bin když neexistuje
parser:
	@mkdir -p $(BINDIR) 
	yacc -d $(FILENAME).y 
	flex $(FILENAME).l
	$(GCC) -I$(INCDIR) -c $(INCFILES) lex.yy.c y.tab.c
	$(GCC) -o $(PARSER_BIN) *.o
	@mv $(PARSER_BIN) $(BINDIR)/
	@mv *.o $(BINDIR) 

# Intermidiate kód
run_ir:
	$(BINDIR)/$(PARSER_BIN)  -i $(DEFAULT_TEST_FILE) -O

# Tvorba binárky a spuštění
run:
	nasm -f elf64 $(PARSER_OUTPUT).asm -o $(PARSER_OUTPUT).o && $(GCC) $(CFLAGS) $(PARSER_OUTPUT).o -o $(PARSER_OUTPUT) && ./$(PARSER_OUTPUT)

run_full:
	make clean
	make parser
	make run_ir
	make run

debug:
	clear
	make clean
	make parser
	make run_ir


subclean:
	@rm -rf lex.yy.c
	@rm -rf y.tab.h y.tab.c

.PHONY: clean

clean: subclean
	@rm -rf $(BINDIR)/* *.o
