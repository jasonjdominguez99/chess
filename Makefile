CXX       := /usr/bin/g++
CXX_FLAGS := -std=c++17 -fdiagnostics-color=always -ggdb

BIN     := bin
SRC     := src
INCLUDE := include

LIBRARIES   :=
EXECUTABLE  := main.exe


all: $(BIN)/$(EXECUTABLE)
	echo "Now run!"
	$(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp main.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)
	echo "Compilation successful!"

clean:
	-rm $(BIN)/*