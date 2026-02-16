CXX = g++
CXXFLAGS = -Wall -Wextra -O2
TARGET = main

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp

main_reference: main_reference.cpp
	$(CXX) $(CXXFLAGS) -g -o main_reference main_reference.cpp

main_pointer: main_pointer.cpp
	$(CXX) $(CXXFLAGS) -g -o main_pointer main_pointer.cpp

test_pointer_vs_value: test_pointer_vs_value.cpp
	$(CXX) $(CXXFLAGS) -o test_pointer_vs_value test_pointer_vs_value.cpp

clean:
	rm -f $(TARGET) main_pointer main_reference test_pointer_vs_value

.PHONY: clean
