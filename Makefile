# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -g
ifeq ($(OS),Windows_NT)
	LDFLAGS = -lglfw3 -lopengl32 -lgdi32
else
	LDFLAGS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
endif

# Sources and output
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
SRCS = $(call rwildcard,src,*.cpp *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS:.cpp=.o))
ifeq ($(OS),Windows_NT)
	EXEC = app.exe
else
	EXEC = app
endif

# Compilation rules
all: $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@
# Surely using g++ to compile C code can't go wrong

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

clean:
	rm -f $(OBJS) $(EXEC)