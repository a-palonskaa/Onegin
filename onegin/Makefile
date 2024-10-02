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

BUILD_DIR = ../build/onegin
EXECUTABLE = ../build/executable/onegin
INCLUDE_DIR = include
SOURCE_DIR  = src

SOURCES = main.cpp print_results.cpp sort_and_print.cpp string_functions.cpp onegin_argparser.cpp

SOURCES := $(addprefix $(SOURCE_DIR)/, $(SOURCES))
OBJECTS += $(addprefix $(BUILD_DIR)/, $(SOURCES:%.cpp=%.o))
DEPS = $(OBJECTS:%.o=%.d)

INCLUDES = include logger parse_arguments sort text_lib
INCLUDES := $(addprefix ../common/,$(INCLUDES))

CFLAGS += -I$(INCLUDE_DIR) $(addprefix -I,$(INCLUDES))

LIB_DIR = ../build/common
LDFLAGS = -L$(LIB_DIR) -lcommon

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@$(CC) $(LDFLAGS) $^ -o $@

$(OBJECTS): $(BUILD_DIR)/%.o:%.cpp
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -MP -MMD -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(DEPS)

NODEPS = clean

ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
-include $(DEPS)
endif
