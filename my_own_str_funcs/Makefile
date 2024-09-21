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
SOURCES_MY_FUNCS = test_str_functions.cpp str_functions.cpp
OBJECTS_MY_FUNCS = $(SOURCES_MY_FUNCS:.cpp=.o)
EXECUTABLE_MY_FUNCS = mine

all: $(EXECUTABLE_MY_FUNCS)

$(EXECUTABLE_MY_FUNCS): $(OBJECTS_MY_FUNCS)
	$(CC) $(LDFLAGS) $(OBJECTS_MY_FUNCS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE_MY_FUNCS) $(OBJECTS_MY_FUNCS)

