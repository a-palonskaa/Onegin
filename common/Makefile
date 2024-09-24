CC = g++
CFLAGS = -Wall -std=c++17 -Wall -Wextra -Weffc++ -Wc++14-compat -Wmissing-declarations   \
		 -Wcast-align -Wcast-qual -Wchar-subscripts -Wconversion -Wctor-dtor-privacy     \
		 -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat=2     \
		 -Winline -Wnon-virtual-dtor -Woverloaded-virtual -Wpacked -Wpointer-arith       \
		 -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo           \
		 -Wstrict-overflow=2 -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef   \
		 -Wunreachable-code -Wunused -Wvariadic-macros -Wno-literal-range 			     \
		 -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast 			 \
		 -Wno-varargs -Wstack-protector -Wsuggest-override -Wbounds-attributes-redundant \
		 -Wlong-long -Wopenmp -fcheck-new -fsized-deallocation -fstack-protector 		 \
		 -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-protector  \
		 -fPIE -Werror=vla

OUT = ../build/common/libcommon.a
BUILD_DIR = ../build/common
INCLUDE_DIR_COMMON = include
LOGGER_DIR  = logger
PARSE_ARGUMENTS_DIR = parse_arguments
SORT_DIR = sort
TEXT_T_LIB_DIR = text_t_lib

SRC_LOGGER = logger.cpp
SRC_PARSE_ARGUMENTS = parse_arguments.cpp
SRC_SORT = sort.cpp
SRC_TEXT_T_LIB = text_t_lib.cpp

SRC_LOGGER := $(addprefix $(LOGGER_DIR)/, $(SRC_LOGGER))
SRC_PARSE_ARGUMENTS := $(addprefix $(PARSE_ARGUMENTS_DIR)/, $(SRC_PARSE_ARGUMENTS))
SRC_SORT := $(addprefix $(SORT_DIR)/, $(SRC_SORT))
SRC_TEXT_T_LIB := $(addprefix $(TEXT_T_LIB_DIR)/, $(SRC_TEXT_T_LIB))

SOURCES = $(SRC_PARSE_ARGUMENTS) $(SRC_SORT) $(SRC_TEXT_T_LIB) $(SRC_LOGGER)

OBJECTS = $(addprefix $(BUILD_DIR)/, $(SOURCES:%.cpp=%.o))
DEPS = $(OBJECTS:%.o=%.d)

CFLAGS += -I$(INCLUDE_DIR_COMMON) -I$(LOGGER_DIR) -I$(PARSE_ARGUMENTS_DIR) -I$(SORT_DIR) -I$(TEXT_T_LIB_DIR)
.SUFFIXES:.cpp

all: $(OUT)

$(OBJECTS):$(BUILD_DIR)/%.o:%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MP -MMD -c $< -o $@

$(OUT):$(OBJECTS)
	ar rcs $(OUT) $(OBJECTS)

clean:
	rm -f $(OUT) $(OBJECTS) $(DEPS)

NODEPS = clean

ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
-include $(DEPS)
endif
