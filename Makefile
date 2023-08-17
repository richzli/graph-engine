# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror
ifeq ($(OS),Windows_NT)
	LDFLAGS = -lglfw3 -lopengl32 -lgdi32
else
	LDFLAGS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
endif

# Sources and output
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
EXEC = app

# Compilation rules
all: $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

clean:
	rm -f $(OBJS) $(EXEC)