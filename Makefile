SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Default target
all: $(BUILD_DIR)/output $(BUILD_DIR)/test_collisions $(BUILD_DIR)/test_distribution $(BUILD_DIR)/test_performance $(BUILD_DIR)/test_correctness

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile source files
$(BUILD_DIR)/linkedlist.o: $(SRC_DIR)/linkedlist.cpp $(SRC_DIR)/linkedlist.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/hashtable.o: $(SRC_DIR)/hashtable.cpp $(SRC_DIR)/hashtable.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/hashtable.h $(SRC_DIR)/linkedlist.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile test files
$(BUILD_DIR)/test_collisions.o: $(TEST_DIR)/test_collisions.cpp $(SRC_DIR)/hashtable.h $(SRC_DIR)/linkedlist.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/test_distribution.o: $(TEST_DIR)/test_distribution.cpp $(SRC_DIR)/hashtable.h $(SRC_DIR)/linkedlist.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/test_performance.o: $(TEST_DIR)/test_performance.cpp $(SRC_DIR)/hashtable.h $(SRC_DIR)/linkedlist.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/test_correctness.o: $(TEST_DIR)/test_correctness.cpp $(SRC_DIR)/hashtable.h $(SRC_DIR)/linkedlist.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link the final executable
$(BUILD_DIR)/output: $(BUILD_DIR)/main.o $(BUILD_DIR)/linkedlist.o $(BUILD_DIR)/hashtable.o
	$(CXX) $(CXXFLAGS) $^ -o $@

# Link test executables
$(BUILD_DIR)/test_collisions: $(BUILD_DIR)/test_collisions.o $(BUILD_DIR)/hashtable.o $(BUILD_DIR)/linkedlist.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/test_distribution: $(BUILD_DIR)/test_distribution.o $(BUILD_DIR)/hashtable.o $(BUILD_DIR)/linkedlist.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/test_performance: $(BUILD_DIR)/test_performance.o $(BUILD_DIR)/hashtable.o $(BUILD_DIR)/linkedlist.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/test_correctness: $(BUILD_DIR)/test_correctness.o $(BUILD_DIR)/hashtable.o $(BUILD_DIR)/linkedlist.o
	$(CXX) $(CXXFLAGS) $^ -o $@

# Clean build
clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/output $(BUILD_DIR)/test_*

# Force rebuild
rebuild: clean all
