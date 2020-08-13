#################
### Variables ###
#################

CXX									:= g++
CXX_FLAGS 					:= -Wall -Wextra -std=c++17 -O3 -funroll-loops

AR									:= ar
AR_ARGS							:= rvs

BIN									:= bin
OBJ									:= obj

SRC									:= src
INCLUDE							:= include
EXAMPLES						:= examples

LIB_INSTALL_DIR			:= /usr/local/lib
INCLUDE_INSTALL_DIR := /usr/local/include

LIB_NAME						:= libcspec
STATIC_LIBRARY			:= $(LIB_NAME).a
SHARED_LIBRARY			:= $(LIB_NAME).so

EXECUTABLE					:= spec
EXE_STATIC					:= $(EXECUTABLE).static
EXE_SHARED					:= $(EXECUTABLE).shared

SRC_FILES						:= $(wildcard $(SRC)/*.cpp)
OBJ_FILES						:= $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRC_FILES))
DEP_FILES						:= $(patsubst $(SRC)/%.cpp, $(OBJ)/%.d, $(SRC_FILES))

EXAMPLE_SRC_FILES		:= $(wildcard $(EXAMPLES)/*.cpp)
EXAMPLE_OBJ_FILES		:= $(patsubst $(EXAMPLES)/%.cpp, $(OBJ)/%.o, $(EXAMPLE_SRC_FILES))
EXAMPLE_DEP_FILES 	:= $(patsubst $(EXAMPLES)/%.cpp, $(OBJ)/%.d, $(EXAMPLE_SRC_FILES))

OBJECTS							:= $(OBJ_FILES) $(EXAMPLE_OBJ_FILES)
DEPENDENCIES				:= $(DEP_FILES) $(EXAMPLE_DEP_FILES)

LIB_DIRS						:= -L./bin

################
### Targets  ###
################

.PHONY: all
all: $(BIN) $(OBJ) $(BIN)/$(STATIC_LIBRARY) $(BIN)/$(SHARED_LIBRARY)

.PHONY: examples
examples: all $(BIN)/$(EXE_STATIC) $(BIN)/$(EXE_SHARED)

.PHONY: install
install: $(INSTALL_DIR) all
	@install.sh $(SHARED_LIBRARY) $(STATIC_LIBRARY) $(LIB_INSTALL_DIR) $(INCLUDE_INSTALL_DIR)

.PHONY: uninstall
uninstall:
	-@rm $(LIB_INSTALL_DIR)/$(SHARED_LIBRARY)
	-@rm $(LIB_INSTALL_DIR)/$(STATIC_LIBRARY)
	-@rm -rf $(INCLUDE_INSTALL_DIR)/cspec

.PHONY: check
check: test-static test-shared

.PHONY: test-static
test-static: $(BIN)/$(EXE_STATIC)
	@echo "Testing static..." && $< && echo "Passed!"

.PHONY: test-shared
test-shared: $(BIN)/$(EXE_SHARED)
	@echo "Testing shared..." && $< && echo "Passed!"

.PHONY: force
force: clean all

.PHONY: clean
clean:
	-@rm -f $(SHARED_LIBRARY) $(STATIC_LIBRARY) $(OBJECTS) $(DEPENDENCIES)

.PHONY: ci
ci: install
	@$(MAKE) check

-include $(DEPENDENCIES)

####################
### Common Tasks ###
####################

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXX_FLAGS) -c -fPIC -MMD -MP -I$(INCLUDE) $< -o $@

$(OBJ)/%.o: $(EXAMPLES)/%.cpp
	$(CXX) $(CXX_FLAGS) -c -MMD -MP -I$(INCLUDE) $< -o $@

######################
### Static Library ###
######################

$(BIN)/$(STATIC_LIBRARY): $(OBJ_FILES)
	$(AR) $(AR_ARGS) $@ $^

$(BIN)/$(EXE_STATIC): $(EXAMPLE_OBJ_FILES)
	$(CXX) $(CXX_FLAGS) -o $@ -I$(INCLUDE) -I$(EXAMPLES) $(LIB_DIRS) $^ -Wl,-Bstatic -lcspec -Wl,-Bdynamic

######################
### Shared Library ###
######################

$(BIN)/$(SHARED_LIBRARY): $(OBJ_FILES)
	$(CXX) -shared -o $@ $^

$(BIN)/$(EXE_SHARED): $(EXAMPLE_OBJ_FILES)
	$(CXX) $(CXX_FLAGS) -o $@ -I$(INCLUDE) -I$(EXAMPLES) $(LIB_DIRS) $^ -Wl,-Bdynamic -lcspec

###############
### Utility ###
###############

$(BIN):
	-@mkdir -p $@

$(OBJ):
	-@mkdir -p $@

$(INSTALL_DIR):
	-@mkdir -p $@
