#!/bin/bash
lex scanner.l
gcc lex.yy.c
./a.out