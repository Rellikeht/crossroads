BUILD_DIR = build
SRC = ../src

.PHONY: obj clean test run

test: obj
	gcc -o $(BUILD_DIR)/test $(BUILD_DIR)/crossroads.o test.c

obj:
	mkdir -p $(BUILD_DIR)
	make -C $(SRC) obj
	cp $(SRC)/build/crossroads.o $(BUILD_DIR)

clean:
	rm -fr $(BUILD_DIR)/*

run: test
	$(BUILD_DIR)/test
