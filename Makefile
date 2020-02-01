#################
### Variables ###
#################

CXX		:= g++
CXX_FLAGS 	:= -Wall -Wextra -std=c++17 -O3 -funroll-loops

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
EXE_STATIC	:= $(EXECUTABLE).static
EXE_SHARED	:= $(EXECUTABLE).shared

SHARED_LIBS	:= -lcspec
STATIC_LIBS	:= $(STATIC_LIBRARY)

LIB_DIRS	:= -L.

INSTALL_DIR	:= /usr/local/lib64

################
### Targets  ###
################

.PHONY: all
all: setup			\
    $(STATIC_LIBRARY) 		\
    $(SHARED_LIBRARY)		\
    $(BIN)/$(EXE_STATIC) 	\
    $(BIN)/$(EXE_SHARED)

.PHONY: setup
setup: $(BIN) $(OBJ)

.PHONY: install
install: $(INSTALL_DIR) all
	@SHARED_LIBRARY="$(SHARED_LIBRARY)" INSTALL_DIR="$(INSTALL_DIR)" /bin/bash install.sh

.PHONY: uninstall
uninstall:
	-@rm $(INSTALL_DIR)/$(SHARED_LIBRARY)

.PHONY: check
check: test-static test-shared

.PHONY: test-static
test-static: $(BIN)/$(EXECUTABLE).static
	@echo "Testing static..." && $< > /dev/null && echo "Passed!"

.PHONY: test-shared
test-shared: $(BIN)/$(EXECUTABLE).shared
	@echo "Testing shared..." && $< > /dev/null && echo "Passed!"

.PHONY: force
force: clean all

.PHONY: clean
clean:
	-@rm -rf $(SHARED_LIBRARY) $(STATIC_LIBRARY) $(BIN) $(OBJ)

.PHONY: ci
ci: install
	@make check LD_LIBRARY_PATH="$(LD_LIBRARY_PATH):$(INSTALL_DIR)"

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

$(BIN)/$(EXE_STATIC): $(EXAMPLE_OBJ_FILES)
	$(CXX) $(CXX_FLAGS) -o $@ -I$(INCLUDE) -I$(EXAMPLES) $(STATIC_LIBS) $^

######################
### Shared Library ###
######################

$(SHARED_LIBRARY): $(OBJ_FILES)
	$(CXX) -shared -o $@ $^

$(BIN)/$(EXE_SHARED): $(EXAMPLE_OBJ_FILES)
	$(CXX) $(CXX_FLAGS) -o $@ -I$(INCLUDE) -I$(EXAMPLES) $(LIB_DIRS) $^ $(SHARED_LIBS)

###############
### Utility ###
###############

$(BIN):
	-@mkdir -p $@

$(OBJ):
	-@mkdir -p $@

$(INSTALL_DIR):
	-@mkdir -p $@

