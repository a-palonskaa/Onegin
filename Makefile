CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Weffc++ -Wc++14-compat -Wmissing-declarations         \
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
		 -fPIE -Werror=vla -Wimplicit-fallthrough
LDFLAGS =

SOURCE_DIR  = src
BUILD_DIR   = build

SOURCES = main.cpp sort_and_print.cpp string_functions.cpp print_results.cpp sort.cpp text_t_lib.cpp arg_parser.cpp logger.cpp includes_sort.cpp
SOURCES := $(addprefix $(SOURCE_DIR)/, $(SOURCES))

OBJECTS = $(addprefix $(BUILD_DIR)/, $(SOURCES:%.cpp=%.o))

EXECUTABLE = $(BUILD_DIR)/meow

.PHONY: all

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@$(CC) $(LDFLAGS) $^ -o $@

$(OBJECTS): $(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean #псевдоцель(не привязана к файлуб таргет который не файл)
clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
