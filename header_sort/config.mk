HEADER_INCLUDE_DIR = header_sort/include
SOURCE_DIR  = header_sort/src

SOURCES_HEADER = main.cpp includes_sort.cpp
SOURCES_HEADER_BUILD = $(addprefix $(SOURCE_DIR)/, $(SOURCES_HEADER))
OBJECTS_HEADER = $(addprefix $(BUILD_DIR)/, $(SOURCES_HEADER_BUILD:%.cpp=%.o))

SOURCES_HEADER_SORT += $(addprefix $(SOURCE_DIR)/, $(SOURCES_HEADER))
OBJECTS_HEADER_SORT += $(addprefix $(BUILD_DIR)/, $(SOURCES_HEADER_BUILD:%.cpp=%.o))
DEPS_HEADER_SORT	+= $(OBJECTS_HEADER:.o=.d)

CFLAGS += -I$(HEADER_INCLUDE_DIR)
