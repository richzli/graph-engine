# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -g
ifeq ($(OS),Windows_NT)
	LDFLAGS = -lglfw3 -lopengl32 -lgdi32
else
	LDFLAGS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
endif

# Sources and output
SRCS = src/glad.c $(wildcard src/*.cpp)
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

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

clean:
	rm -f $(OBJS) $(EXEC)