ONEGIN_INCLUDE_DIR = onegin/include
ONEGIN_SOURCE_DIR  = onegin/src

SRC_ONEGIN = main.cpp print_results.cpp sort_and_print.cpp string_functions.cpp

SOURCES_ONEGIN += $(addprefix $(ONEGIN_SOURCE_DIR)/, $(SRC_ONEGIN))
SOURCES_ONEGIN_NEW = $(addprefix $(ONEGIN_SOURCE_DIR)/, $(SRC_ONEGIN))
OBJECTS_ONEGIN_NEW = $(addprefix $(BUILD_DIR)/, $(SOURCES_ONEGIN_NEW:%.cpp=%.o))
OBJECTS_ONEGIN += $(addprefix $(BUILD_DIR)/, $(SOURCES_ONEGIN_NEW:%.cpp=%.o))
DEPS += $(OBJECTS_ONEGIN_NEW:.o=.d)

CFLAGS += -I$(ONEGIN_INCLUDE_DIR)
