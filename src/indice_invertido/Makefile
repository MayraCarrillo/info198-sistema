BIN = ../../bin
SRC = indice_invertido.cpp ../common/util.cpp ../common/indice_invert.cpp
OUT = $(BIN)/indice_invertido

all: $(OUT)

$(BIN):
	mkdir -p $(BIN)

$(OUT): $(SRC) | $(BIN)
	g++ -std=c++17 $(SRC) -I../include -o $(OUT)
