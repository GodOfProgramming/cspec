CXX		:= g++
CXX_FLAGS 	:= -Wall -Wextra -std=c++17 -O3 -fPIC

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

STATIC_LIBRARY	:= libcspec.a
SHARED_LIBRARY	:= libcspec.so
EXECUTABLE	:= spec

SHARED_LIBS	:= -lcspec
STATIC_LIBS	:= $(STATIC_LIBRARY)

LIB_DIRS	:= -L./

all: make_dirs $(SHARED_LIBRARY) $(STATIC_LIBRARY) $(BIN)/$(EXECUTABLE).shared $(BIN)/$(EXECUTABLE).static

$(SHARED_LIBRARY): $(OBJ_FILES)
	$(CXX) -shared -o $@ $^

$(STATIC_LIBRARY): $(OBJ_FILES)
	$(AR) $(AR_FLAGS) $@ $^

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXX_FLAGS) -c $(INCLUDE_DIRS) $< -o $@

$(BIN)/$(EXECUTABLE).shared: $(EXAMPLES)/*.spec.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE_DIRS) -I$(EXAMPLES) $(STATIC_LIBS) $^ -o $@

$(BIN)/$(EXECUTABLE).static: $(EXAMPLES)/*.spec.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE_DIRS) -I$(EXAMPLES) $(LIB_DIRS) $^ -o $@ $(SHARED_LIBS)

make_dirs:
	-@mkdir -p $(BIN) $(OBJ)

clean:
	-@rm -f $(BIN)/* $(OBJ)/*

