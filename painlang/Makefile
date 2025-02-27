# Kámo tak makefile je hustá věc třeba
hello:
	lex pl.l
	yacc -d pl.y
	cc lex.yy.c y.tab.c -o pavel1 

clean:
	rm ./pavel1
