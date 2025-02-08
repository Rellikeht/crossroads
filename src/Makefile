BUILD_DIR = build
TEST_DIR = ../test

.PHONY: exe obj clean test run_tests run

exe: obj
	gcc -o $(BUILD_DIR)/main $(BUILD_DIR)/crossroads.o main.c

obj:
	mkdir -p $(BUILD_DIR)
	gcc -c -o $(BUILD_DIR)/crossroads.o crossroads.c

clean:
	rm -fr $(BUILD_DIR)/*

tests:
	make -C $(TEST_DIR)

run_tests:
	make -C $(TEST_DIR) run
