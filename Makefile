CXX		:= g++
CXX_FLAGS 	:= -Wall -Wextra -std=c++17

AR		:= ar
AR_FLAGS	:= rvs

BIN		:= bin
OUT		:= out
SRC		:= src
INCLUDE		:= include
EXAMPLES	:= examples
LIB		:= lib

MYLIB		:= $(ONEOFFS_REPO)/c++/tools

LIBRARIES	:=
STATIC_LIBS	:= libcspec.a libconsole.a
EXECUTABLE	:= spec

$(BIN)/$(EXECUTABLE): $(EXAMPLES)/*.spec.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -I$(MYLIB) $^ -L$(LIB) $(STATIC_LIBS) -o $@ $(LIBRARIES)

libcspec.a: $(OUT)/spec.o $(OUT)/test_block.o $(OUT)/describe_block.o $(OUT)/context_block.o $(OUT)/it_block.o
	$(AR) $(AR_FLAGS) $@ $^

$(OUT)/spec.o: $(SRC)/spec.cpp
	$(CXX) $(CXX_FLAGS) -c -I$(INCLUDE) -I$(MYLIB) $^ -L$(LIB) -o $@ $(LIBRARIES)

$(OUT)/test_block.o: $(SRC)/test_block.cpp
	$(CXX) $(CXX_FLAGS) -c -I$(INCLUDE) -I$(MYLIB) $^ -L$(LIB) -o $@ $(LIBRARIES)

$(OUT)/describe_block.o: $(SRC)/describe_block.cpp
	$(CXX) $(CXX_FLAGS) -c -I$(INCLUDE) -I$(MYLIB) $^ -L$(LIB) -o $@ $(LIBRARIES)

$(OUT)/context_block.o: $(SRC)/context_block.cpp
	$(CXX) $(CXX_FLAGS) -c -I$(INCLUDE) -I$(MYLIB) $^ -L$(LIB) -o $@ $(LIBRARIES)

$(OUT)/it_block.o: $(SRC)/it_block.cpp
	$(CXX) $(CXX_FLAGS) -c -I$(INCLUDE) -I$(MYLIB) $^ -L$(LIB) -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/* $(OUT)/*

FORCE:



