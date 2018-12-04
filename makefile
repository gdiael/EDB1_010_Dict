# https://github.com/gdiael/EDB1_010_Dict.git
#
# $@ = nome da regra de compilação
# $^ = lista de depedências da regra
# $< = primeira dependência da regra

CC = g++ -g

INC = ./include
SRC = ./src
OBJ = ./build
BIN = ./bin

PROG = $(BIN)/dict

FLAGS = -Wall -pedantic -std=c++11 -I$(INC)

OBJLIS = $(OBJ)/HashTable.o $(OBJ)/TestTable.o $(OBJ)/main.o

all: mkdirs $(PROG)

mkdirs:
	mkdir -p $(BIN)
	mkdir -p $(OBJ)

$(PROG): $(OBJLIS)
	$(CC) $(FLAGS) -o $@ $^

$(OBJ)/HashTable.o: $(SRC)/HashTable.cpp $(INC)/HashTable.h $(INC)/HashEntry.h
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ)/TestTable.o: $(SRC)/TestTable.cpp $(INC)/TestTable.h $(INC)/HashTable.h
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/TestTable.h
	$(CC) $(FLAGS) -c $< -o $@

clean: 
	rm -f $(BIN)/*
	rm -f $(OBJ)/*

run:
	$(PROG)

# propriedades para serem usadas ao compilar no windows com o MinGW com gcc e gdb
# não usar o comando Make e sim o executável: mingw32-make.exe

mkdirswin:
	if not exist $(BIN) mkdir "$(BIN)
	if not exist $(OBJ) mkdir "$(OBJ)

runwin: mkdirswin $(PROG)
	chcp 65001
	$(PROG)

cleanwin: 
	del /q "$(BIN)\*
	del /q "$(OBJ)\*