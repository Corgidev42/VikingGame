#INCLUDES = -I /opt/homebrew/include/ 
#LINKLIB = /opt/homebrew/lib/libraylib.dylib

# Makefile for VikingGame
# Compiler
CXX = g++
# Executable name
EXEC = VikingGame
# Source files
SRC = $(wildcard *.cpp)
# Object files
OBJ = $(SRC:.cpp=.o)
# Compiler flags
CXXFLAGS = -I /opt/homebrew/include/
# Linker flags
LDFLAGS = /opt/homebrew/lib/libraylib.dylib
# Zip command
ZIP = zip -r

all: $(EXEC) 

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^ 

zip:
	$(ZIP) VikingGame.zip *

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC) VikingGame.zip
