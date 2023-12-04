CC = gcc
CFLAGS = -g -I include
SRC_DIR = src
BISON_DIR = utils/bison
BUILD_DIR = build
SAMPLE_DIR= utils/samples

all: bin/cmc

bin/cmc: main.c $(BUILD_DIR)/lexer.o $(BUILD_DIR)/buffer.o $(BUILD_DIR)/parser.tab.o
	$(CC) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/parser.tab.o: $(BISON_DIR)/parser.tab.c
	$(CC) -c $< -o $@ $(CFLAGS) 

clean:
	rm -f bin/cmc $(BUILD_DIR)/*.o 

test: $(wildcard utils/samples/*)
	@echo "Running tests..."
	@for file in $^; do \
		echo "Testing $$file"; \
		./bin/cmc "$$file"; \
	done
	@echo "All tests completed."

