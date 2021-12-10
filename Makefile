# A simple Makefile
# <Aarshad Mahi and G-00975690>
# CS 262, Lab Section 221
# Lab9

TARGET = conversion
PATH = ./out/

CC = gcc
ERROR = -pedantic-errors
CFLAGS = -g -Wall ${ERROR} -o
OUT = out

all: ${TARGET}.c 
	${CC} ${CFLAGS} ${PATH}${TARGET} ${TARGET}.c
clean:
	rm ${PATH}${TARGET}
	rm -r ./.vscode
run:
	${CC} ${CFLAGS} ${PATH}${TARGET} ${TARGET}.c
	${PATH}${TARGET}
	