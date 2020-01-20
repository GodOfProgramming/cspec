CXX		:= g++
CXX_FLAGS 	:= -Wall -Wextra -std=c++17 -O3

AR		:= ar
AR_FLAGS	:= rvs

BIN		:= bin
OBJ		:= obj

SRC		:= src
INCLUDE		:= include
EXAMPLES	:= examples

INCLUDE_DIRS	:= -I$(INCLUDE) -I$(DASH_INCLUDE) -I$(FIBER_INCLUDE)

SRC_FILES	:= $(wildcard $(SRC)/*.cpp)
OBJ_FILES	:= $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRC_FILES))

LIBRARY		:= libcspec.a
EXECUTABLE	:= spec

STATIC_LIBS	:= $(LIBRARY)

all: make_dirs $(LIBRARY)

$(LIBRARY): $(OBJ_FILES)
	$(AR) $(AR_FLAGS) $@ $^

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXX_FLAGS) -c $(INCLUDE_DIRS) $< -o $@

$(BIN)/$(EXECUTABLE): $(EXAMPLES)/*.spec.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE_DIRS) -I$(EXAMPLES) $(STATIC_LIBS) $^ -o $@

example: $(BIN)/$(EXECUTABLE)

run: example
	$(BIN)/$(EXECUTABLE)

make_dirs:
	-@mkdir -p $(BIN) $(OBJ)

clean:
	-@rm -f $(BIN)/* $(OBJ)/*

