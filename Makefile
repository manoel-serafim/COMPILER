CC = gcc
CFLAGS = -g -I include
SRC_DIR = src
BISON_DIR = utils/bison
BUILD_DIR = build
SAMPLE_DIR= utils/samples

all: bin/cmc

bin/cmc: main.c $(BUILD_DIR)/lexer.o $(BUILD_DIR)/buffer.o $(BUILD_DIR)/parser.tab.o $(BUILD_DIR)/parser.o $(BUILD_DIR)/contextualizer.o $(BUILD_DIR)/generator.o
	$(CC) -g -o $@ $^

$(BUILD_DIR)/buffer.o: $(SRC_DIR)/buffer.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/lexer.o: $(SRC_DIR)/lexer.c $(BUILD_DIR)/parser.tab.o
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/parser.tab.o: $(BISON_DIR)/parser.tab.c 
	$(CC) -c $< -o $@ $(CFLAGS) 

$(BUILD_DIR)/parser.o: $(SRC_DIR)/parser.c $(BUILD_DIR)/parser.tab.o
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/contextualizer.o: $(SRC_DIR)/contextualizer.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/generator.o: $(SRC_DIR)/generator.c
	$(CC) -c $< -o $@ $(CFLAGS)


bison:
	cd $(BISON_DIR) && bison -d parser.y	

clean:
	rm -f bin/cmc $(BUILD_DIR)/*.o $(BISON_DIR)/parser.tab.* $(BISON_DIR)/parse.output

test: $(wildcard utils/samples/*)
	@echo "Running tests..."
	@for file in $^; do \
		echo "\n\n ";\
		echo "Testing $$file"; \
		./bin/cmc "$$file"; \
	done
	@echo "All tests completed."

