BUILD_DIR = build
SRC = ../src
CFLAGS = -Wall -Wextra -pedantic

.PHONY: obj clean tests run road_test run_road_test simulation_test run_simulation_test test_simulations

tests: road_test simulation_test

run: run_road_test run_simulation_test

road_test:
	gcc $(CFLAGS) -Og -g -D ROAD_LENGTH=100001 -D INT_TYPE="long long" \
		-o $(BUILD_DIR)/road_test $(SRC)/crossroads.c road_test.c

run_road_test: road_test
	$(BUILD_DIR)/road_test

simulation_test:
	@make -C $(SRC) exe
	@cp $(SRC)/build/main $(BUILD_DIR)/simulation

run_simulation_test: simulation_test
	@./simulation_test.py

test_simulations: simulation_test
	@./test_simulations.py

obj:
	@mkdir -p $(BUILD_DIR)
	@make -C $(SRC) obj-debug
	@cp $(SRC)/build/crossroads.o $(BUILD_DIR)

clean:
	rm -fr $(BUILD_DIR)/*
