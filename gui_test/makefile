
SRC := myGui.c
BIN := myGui
DIR := release

GTK := pkg-config --cflags --libs gtk+-2.0

all: $(DIR)/$(BIN)

$(DIR)/$(BIN): $(SRC) | $(DIR)
	gcc -o $(DIR)/$(BIN) $(SRC) `$(GTK)`

$(DIR):
	mkdir $@

clean:
	rm $(DIR)/$(BIN)
