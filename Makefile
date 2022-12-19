CXX       := gcc
CXX_FLAGS := -ggdb -lncurses

BIN     := bin
SRC     := src
INCLUDE := /usr/include/

LIBRARIES   := 
EXECUTABLE  := tetris


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.c
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*
