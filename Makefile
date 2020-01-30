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

LIB_NAME	:= libcspec
STATIC_LIBRARY	:= $(LIB_NAME).a
SHARED_LIBRARY	:= $(LIB_NAME).so
EXECUTABLE	:= spec

SHARED_LIBS	:= -lcspec
STATIC_LIBS	:= $(STATIC_LIBRARY)

LIB_DIRS	:= -L.

INSTALL_DIR	:= /usr/local/lib64

all: 				\
    $(BIN)			\
    $(OBJ)			\
    $(STATIC_LIBRARY) 		\
    $(SHARED_LIBRARY)		\
    $(BIN)/$(EXECUTABLE).static \
    $(BIN)/$(EXECUTABLE).shared

install: all
	@if [ -d $(INSTALL_DIR) ]; then 			\
	    echo "Installing into $(INSTALL_DIR)"; 		\
	    cp $(SHARED_LIBRARY) $(INSTALL_DIR);		\
	    chmod 755 $(INSTALL_DIR)/$(SHARED_LIBRARY);		\
	else 							\
	    echo "'$(INSTALL_DIR)' does not exist, exiting"; 	\
	fi

.PHONY: force
force: clean all

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

$(BIN):
	-@mkdir -p $@

$(OBJ):
	-@mkdir -p $@

.PHONY: clean
clean:
	-@rm -rf $(SHARED_LIBRARY) $(STATIC_LIBRARY) $(BIN) $(OBJ)

