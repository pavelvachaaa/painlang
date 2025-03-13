# Kámo tak makefile je hustá věc třeba
MAKE=make
GCC=gcc

FILENAME=pl
PRINT_OUTPUT="y"

PARSER_BIN="painlang_parser"

ROOT_DIR=$(shell pwd)
INCDIR=$(ROOT_DIR)/inc
INCFILES := $(shell find $(INCDIR) -type f -name "*.c")
#LIBOBJS = $(wildcard $(LIBDIR)/*.o)
#LIBNAMES = $(shell basename -s ".o" $(LIBOBJS))
#LIBS = $(addprefix -l, $(LIBNAMES))

BINDIR="./bin"
TESTDIR="./tests"
TEST_OK_FILE="valid_01.painlang"
TEST_NOOK_FILE="invalid_01.painlang"

.PHONY: parser test_ok test_nook subclean clean all

all: clean parser test_ok test_nook
	@if [ $(PRINT_OUTPUT) ]; then cat $(BINDIR)/$(TEST_OK_FILE).report; fi
	@if [ $(PRINT_OUTPUT) ]; then cat $(BINDIR)/$(TEST_NOOK_FILE).report; fi

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


test_ok:
	@./$(BINDIR)/$(PARSER_BIN) $(TESTDIR)/$(TEST_OK_FILE) >$(BINDIR)/$(TEST_OK_FILE).report
test_nook:
	@./$(BINDIR)/$(PARSER_BIN) $(TESTDIR)/$(TEST_NOOK_FILE) >$(BINDIR)/$(TEST_NOOK_FILE).report

subclean:
	@rm -rf lex.yy.c
	@rm -rf y.tab.h y.tab.c

clean: subclean
	@rm -rf $(BINDIR)/* *.o

