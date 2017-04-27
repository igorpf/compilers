#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 1
#
# Makefile for three compiler calls
# Read the comments on Makefile2. All of them apply here too.
# But now the hash table is compiled in a separate gcc call
# Therefore, there must be a header of it to be included in scanner.l
#

#etapa1: lex.yy.c
#	gcc -o etapa1 lex.yy.c
#lex.yy.c: scanner.l
#	lex scanner.l

#clean:
#	rm *.o lex.yy.c lex.yy.h etapa1

etapa2: lex.yy.o y.tab.o hash.o main.o
	gcc -o etapa2 lex.yy.o main.o hash.o y.tab.o
y.tab.o: y.tab.c
	gcc -c y.tab.c
y.tab.c: parser.y
	yacc -d parser.y -v
main.o: main.c y.tab.c
	gcc -c main.c 
hash.o: hash.c
	gcc -c hash.c
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: scanner.l y.tab.c
	flex --header-file=lex.yy.h scanner.l
clean:
	rm main.o hash.o lex.yy.* etapa2 y.tab.*

