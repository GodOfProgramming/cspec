CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BIN		:= bin
SRC		:= src
INCLUDE		:= include
LIB		:= lib

MYLIB		:= $(ONEOFFS_REPO)/c++/tools

LIBRARIES	:=
STATIC_LIBS	:= libconsole.a
EXECUTABLE	:= spec 

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -I$(MYLIB) $^ -L$(LIB) $(STATIC_LIBS) -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*

