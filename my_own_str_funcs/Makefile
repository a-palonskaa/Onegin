CC = g++
CFLAGS += -Wall -std=c++17 -Wall -Wextra -Weffc++ -Wc++14-compat -Wmissing-declarations   \
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
LDFLAGS =

BUILD_DIR = build
MY_FUNCS_DIR = str_functions
MY_GETLINE_DIR = getline

SOURCES_MY_FUNCS = test_str_functions.cpp str_functions.cpp
SOURCES_MY_FUNCS := $(addprefix $(MY_FUNCS_DIR)/, $(SOURCES_MY_FUNCS))
SOURCES_MY_GETLINE = get_line_v1.cpp get_line_v2.cpp test_get_line.cpp
SOURCES_MY_GETLINE := $(addprefix $(MY_GETLINE_DIR)/, $(SOURCES_MY_GETLINE))

OBJECTS_MY_GETLINE = $(SOURCES_MY_GETLINE:.cpp=.o)
OBJECTS_MY_GETLINE := $(addprefix $(BUILD_DIR)/, $(OBJECTS_MY_GETLINE))

OBJECTS_MY_FUNCS = $(SOURCES_MY_FUNCS:.cpp=.o)
OBJECTS_MY_FUNCS := $(addprefix $(BUILD_DIR)/, $(OBJECTS_MY_FUNCS))

EXECUTABLE_MY_FUNCS = mine
EXECUTABLE_MY_FUNCS:= $(addprefix $(BUILD_DIR)/, $(EXECUTABLE_MY_FUNCS))

EXECUTABLE_MY_GETLINE = get_line
EXECUTABLE_MY_GETLINE:= $(addprefix $(BUILD_DIR)/, $(EXECUTABLE_MY_GETLINE))

all: my_func

my_func: $(EXECUTABLE_MY_FUNCS)

$(EXECUTABLE_MY_FUNCS): $(OBJECTS_MY_FUNCS)
	$(CC) $(LDFLAGS) $(OBJECTS_MY_FUNCS) -o $@

my_get_line: $(EXECUTABLE_MY_GETLINE)

$(EXECUTABLE_MY_GETLINE): $(OBJECTS_MY_GETLINE)
	$(CC) $(LDFLAGS) $(OBJECTS_MY_GETLINE) -o $@

$(BUILD_DIR)/%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE_MY_FUNCS) $(EXECUTABLE_MY_GETLINE) $(OBJECTS_MY_FUNCS) $(OBJECTS_MY_GETLINE)

echo:
	echo $(OBJECTS_MY_GETLINE)
