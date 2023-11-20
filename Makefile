# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++17
SFML_INCLUDE = -I/opt/homebrew/Cellar/sfml/2.6.1/include
SFML_LIBS = -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-audio -lsfml-system

# Source files and output executable
SRCS = src/main.cpp src/commands.cpp src/music.cpp src/instrument.cpp
EXECUTABLE = MainTest src/*.o

# Build rule
all: $(EXECUTABLE)

$(EXECUTABLE): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SFML_INCLUDE) $^ -o $@ $(SFML_LIBS)

clean:
	rm -f $(EXECUTABLE)
