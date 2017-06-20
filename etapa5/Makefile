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

etapa5: lex.yy.o y.tab.o hash.o main.o ast.o semantic.o tacs.o
	gcc -o etapa5 lex.yy.o main.o hash.o y.tab.o ast.o semantic.o tacs.o
y.tab.o: y.tab.c
	gcc -c y.tab.c
y.tab.c: parser.y
	yacc -d parser.y
main.o: main.c y.tab.c
	gcc -c main.c 
hash.o: hash.c
	gcc -c hash.c
ast.o: ast.c
	gcc -c ast.c
semantic.o: semantic.c
	gcc -c semantic.c
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: scanner.l y.tab.c
	flex --header-file=lex.yy.h scanner.l
clean:
	rm *.o lex.yy.* etapa5 y.tab.*

