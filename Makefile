
TARGET_EXEC=a

SRC_DIR = src
LIB_DIR = lib
BIN_DIR = bin
DBG_DIR = dbg
DEP_DIR = dep

LD=g++
CC=gcc
CXX=g++
CCFLAGS:=-I$(SRC_DIR) -I$(LIB_DIR)
DBG_CCFLAGS=-DDEBUG -g
RLS_CCFLAGS=-O3
LDFLAGS=

BIN_EXEC = $(BIN_DIR)/$(TARGET_EXEC).exe
DBG_EXEC = $(DBG_DIR)/$(TARGET_EXEC).exe

BASE := $(patsubst ./%,%,$(basename $(shell cd $(SRC_DIR); /usr/bin/find -name '*.c' -or -name '*.cpp')))
OBJS := $(BASE:%=$(BIN_DIR)/%.o)
DBGS := $(BASE:%=$(DBG_DIR)/%.o)
DEPS := $(BASE:%=$(DEP_DIR)/%.d)

$(DBG_EXEC): $(DBGS)
	$(LD) $^ -o $@ $(CCFLAGS) $(DBG_CCFLAGS) $(LDFLAGS)

$(BIN_EXEC): $(OBJS)
	$(LD) $^ -o $@ $(CCFLAGS) $(RLS_CCFLAGS) $(LDFLAGS)

$(DBG_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@) $(patsubst $(DBG_DIR)/%,$(DEP_DIR)/%,$(dir $@))
	$(CC) $< -c -o $@ $(CCFLAGS) $(DBG_CCFLAGS) -MMD -MP -MF $(patsubst $(SRC_DIR)/%.c,$(DEP_DIR)/%.d,$<)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@) $(patsubst $(BIN_DIR)/%,$(DEP_DIR)/%,$(dir $@))
	$(CC) $< -c -o $@ $(CCFLAGS) $(RLS_CCFLAGS) -MMD -MP -MF $(patsubst $(SRC_DIR)/%.c,$(DEP_DIR)/%.d,$<)

$(DBG_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@) $(patsubst $(DBG_DIR)/%,$(DEP_DIR)/%,$(dir $@))
	$(CXX) $< -c -o $@ $(CCFLAGS) $(DBG_CCFLAGS) -MMD -MP -MF $(patsubst $(SRC_DIR)/%.cpp,$(DEP_DIR)/%.d,$<)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@) $(patsubst $(BIN_DIR)/%,$(DEP_DIR)/%,$(dir $@))
	$(CXX) $< -c -o $@ $(CCFLAGS) $(RLS_CCFLAGS) -MMD -MP -MF $(patsubst $(SRC_DIR)/%.cpp,$(DEP_DIR)/%.d,$<)

debug: $(DBG_EXEC)
release: $(BIN_EXEC)
clean:
	rm $(BIN_DIR) $(DBG_DIR) $(DEP_DIR) -rf

.PHONY: debug release clean

-include $(DEPS)
