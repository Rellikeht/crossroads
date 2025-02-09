BUILD_DIR = build
TEST_DIR = ../test
CFLAGS = -Wall -Wextra -pedantic

.PHONY: exe obj clean test run_tests run

exe: obj
	gcc $(CFLAGS) -o $(BUILD_DIR)/main $(BUILD_DIR)/crossroads.o main.c

obj-dir:
	@mkdir -p $(BUILD_DIR)

obj: obj-dir
	gcc $(CFLAGS) -c -o $(BUILD_DIR)/crossroads.o crossroads.c

obj-debug: obj-dir
	gcc $(CFLAGS) -c -Og -g -o $(BUILD_DIR)/crossroads.o crossroads.c

clean:
	rm -fr $(BUILD_DIR)/*

tests:
	@make -C $(TEST_DIR)

run_tests:
	@make -C $(TEST_DIR) run
