CXX		:= g++
CXX_FLAGS 	:= -Wall -Wextra -std=c++17 -O3
MULTI_FLAGS	:= -f -c -f -Wall -f -Wextra -f -std=c++17

AR		:= ar
AR_FLAGS	:= rvs

BIN		:= bin
OUT		:= out

SRC		:= src
INCLUDE		:= include
EXAMPLES	:= examples

MULTI_INCLUDE	:= -i include

LIBRARIES	:=
STATIC_LIBS	:= libcspec.a
MULTI_STATIC	:= -s libcspec.a

EXECUTABLE	:= spec

ARCHIVE_OBJECTS	:= \
    $(OUT)/spec.o \
    $(OUT)/test_block.o \
    $(OUT)/describe_block.o \
    $(OUT)/context_block.o \
    $(OUT)/it_block.o \
    $(OUT)/console.o

libcspec.a: $(ARCHIVE_OBJECTS)
	$(AR) $(AR_FLAGS) $@ $^

$(OUT)/spec.o: $(SRC)/spec.cpp
	$(CXX) $(CXX_FLAGS) -c -I$(INCLUDE) $^ -o $@

$(OUT)/test_block.o: $(SRC)/test_block.cpp
	$(CXX) $(CXX_FLAGS) -c -I$(INCLUDE) $^ -o $@

$(OUT)/describe_block.o: $(SRC)/describe_block.cpp
	$(CXX) $(CXX_FLAGS) -c -I$(INCLUDE) $^ -o $@

$(OUT)/context_block.o: $(SRC)/context_block.cpp
	$(CXX) $(CXX_FLAGS) -c -I$(INCLUDE) $^ -o $@

$(OUT)/it_block.o: $(SRC)/it_block.cpp
	$(CXX) $(CXX_FLAGS) -c -I$(INCLUDE) $^ -o $@

$(OUT)/console.o: $(SRC)/console.cpp
	$(CXX) $(CXX_FLAGS) -c -I$(INCLUDE) $^ -o $@

multicompilation: $(SRC)/*.cpp
	@multi-compile.rb $(CXX) $^ $(MULTI_FLAGS) $(MULTI_INCLUDE)

example: $(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(EXAMPLES)/*.spec.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $(STATIC_LIBS) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/* $(OUT)/*

FORCE:

