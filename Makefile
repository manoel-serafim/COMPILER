CC = gcc
CFLAGS = -I include
SRC_DIR = src
BUILD_DIR = build

all: bin/cmc

bin/cmc: main.c $(BUILD_DIR)/lexer.o $(BUILD_DIR)/buffer.o
	$(CC) -g -o $@ $< $(BUILD_DIR)/lexer.o $(BUILD_DIR)/buffer.o

$(BUILD_DIR)/lexer.o: $(SRC_DIR)/lexer.c
	$(CC) -g -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/buffer.o: $(SRC_DIR)/buffer.c
	$(CC) -g -c $< -o $@ $(CFLAGS)

clean:
	rm -f cmc $(BUILD_DIR)/*.o
