BUILD_DIR_EXECUTABLE = build/executable
EXECUTABLE_ONEGIN = $(BUILD_DIR_EXECUTABLE)/onegin
EXECUTABLE_HEADER_SORT = $(BUILD_DIR_EXECUTABLE)/header_sort

CC = g++
CFLAGS =
BUILD_DIR = build
SOURCES_ONEGIN =
SOURCES_HEADER_SORT =
OBJECTS_ONEGIN =
OBJECTS_HEADER_SORT =
DEPS_ONEGIN =
DEPS_HEADER_SORT =

-include common/config.mk

all: onegin

-include onegin/config.mk
-include header_sort/config.mk

onegin: $(EXECUTABLE_ONEGIN)

$(EXECUTABLE_ONEGIN): $(OBJECTS_ONEGIN)
	@$(CC) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

header_sort: $(EXECUTABLE_HEADER_SORT)

$(EXECUTABLE_HEADER_SORT): $(OBJECTS_HEADER_SORT)
	@$(CC) $(LDFLAGS) $^ -o $@

.PHONY: clean
clean:
	@rm -f $(OBJECTS_ONEGIN) $(OBJECTS_HEADER_SORT) $(EXECUTABLE_ONEGIN) $(EXECUTABLE_HEADER_SORT)

echo:
	@echo $(OBJECTS_ONEGIN)
