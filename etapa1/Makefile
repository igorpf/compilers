#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 1
#
# Makefile for three compiler calls
# Read the comments on Makefile2. All of them apply here too.
# But now the hash table is compiled in a separate gcc call
# Therefore, there must be a header of it to be included in scanner.l
#

etapa1: lex.yy.c
	gcc -o etapa1 lex.yy.c
lex.yy.c: scanner.l
	lex scanner.l

clean:
	rm *.o lex.yy.c lex.yy.h etapa1