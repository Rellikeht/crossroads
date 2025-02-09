BUILD_DIR = build
SRC = ../src

.PHONY: obj clean tests run road_test run_road_test simulation_test run_simulation_test

tests: road_test simulation_test

run: run_road_test run_simulation_test

road_test:
	gcc -Og -g -D ROAD_LENGTH=1000001 -o $(BUILD_DIR)/road_test $(SRC)/crossroads.c road_test.c

run_road_test: road_test
	$(BUILD_DIR)/road_test

simulation_test: obj
	gcc -Og -g -o $(BUILD_DIR)/simulation_test $(BUILD_DIR)/crossroads.o simulation_test.c

run_simulation_test: simulation_test
	$(BUILD_DIR)/simulation_test

obj:
	mkdir -p $(BUILD_DIR)
	make -C $(SRC) obj-debug
	cp $(SRC)/build/crossroads.o $(BUILD_DIR)

clean:
	rm -fr $(BUILD_DIR)/*
