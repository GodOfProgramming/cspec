CXX		:= g++
CXX_FLAGS 	:= -Wall -Wextra -std=c++17 -O3 

AR		:= ar
AR_ARGS		:= rvs

BIN		:= bin
OBJ		:= obj

SRC		:= src
INCLUDE		:= include
EXAMPLES	:= examples

SRC_FILES	:= $(wildcard $(SRC)/*.cpp)
OBJ_FILES	:= $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRC_FILES))

EXAMPLE_SRC_FILES	:= $(wildcard $(EXAMPLES)/*.cpp)
EXAMPLE_OBJ_FILES 	:= $(patsubst $(EXAMPLES)/%.cpp, $(OBJ)/%.o, $(EXAMPLE_SRC_FILES))

STATIC_LIBRARY	:= libcspec.a
SHARED_LIBRARY	:= libcspec.so
EXECUTABLE	:= spec

SHARED_LIBS	:= -lcspec
STATIC_LIBS	:= $(STATIC_LIBRARY)

LIB_DIRS	:= -L./

all: 				\
    make_dirs 			\
    $(STATIC_LIBRARY) 		\
    $(SHARED_LIBRARY)		\
    $(BIN)/$(EXECUTABLE).static \
    $(BIN)/$(EXECUTABLE).shared

####################
### Common Tasks ###
####################

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXX_FLAGS) -c -fPIC -I$(INCLUDE) $< -o $@

$(OBJ)/%.spec.o: $(EXAMPLES)/%.spec.cpp
	$(CXX) $(CXX_FLAGS) -c -I$(INCLUDE) $< -o $@

######################
### Static Library ###
######################

$(STATIC_LIBRARY): $(OBJ_FILES)
	$(AR) $(AR_ARGS) $@ $^

$(BIN)/$(EXECUTABLE).static: $(EXAMPLE_OBJ_FILES)
	$(CXX) $(CXX_FLAGS) -o $@ -I$(INCLUDE) -I$(EXAMPLES) $(STATIC_LIBS) $^

######################
### Shared Library ###
######################

$(SHARED_LIBRARY): $(OBJ_FILES)
	$(CXX) -shared -o $@ $^

$(BIN)/$(EXECUTABLE).shared: $(EXAMPLE_OBJ_FILES)
	$(CXX) $(CXX_FLAGS) -o $@ -I$(INCLUDE) -I$(EXAMPLES) $(LIB_DIRS) $^ $(SHARED_LIBS)

###############
### Utility ###
###############

make_dirs:
	-@mkdir -p $(BIN) $(OBJ)

clean:
	-@rm -f $(SHARED_LIBRARY) $(STATIC_LIBRARY) $(BIN)/* $(OBJ)/*

