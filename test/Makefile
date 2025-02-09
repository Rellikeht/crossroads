BUILD_DIR = build
SRC = ../src

.PHONY: obj clean tests run road_test run_road_test

# test: obj
# 	gcc -Og -g -o $(BUILD_DIR)/test $(BUILD_DIR)/crossroads.o test.c

tests: road_test

run: run_road_test

road_test:
	gcc -Og -g -D ROAD_LENGTH=10000000 -o $(BUILD_DIR)/road_test $(SRC)/crossroads.c road_test.c

run_road_test: road_test
	$(BUILD_DIR)/road_test

obj:
	mkdir -p $(BUILD_DIR)
	make -C $(SRC) obj-debug
	cp $(SRC)/build/crossroads.o $(BUILD_DIR)

clean:
	rm -fr $(BUILD_DIR)/*
