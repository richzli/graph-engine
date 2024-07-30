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
OBJS = $(patsubst %.cpp,%.o,$(SRCS:.c=.o))
DEPS = $(patsubst %.cpp,%.d,$(SRCS:.c=.d))
ifeq ($(OS),Windows_NT)
	EXEC = app.exe
else
	EXEC = app
endif

# Compilation rules
.PHONY: all clean

all: $(EXEC)

-include $(DEPS)

%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

%.o: %.c
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@
# Surely using g++ to compile C code can't go wrong

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

clean:
	rm -f $(OBJS) $(EXEC) $(DEPS)