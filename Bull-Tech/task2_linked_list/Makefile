CXX = g++
CXXFLAGS = -Wall -Wextra -O2
TARGET = main

$(TARGET): main.cpp linked_list.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp linked_list.cpp

clean:
	rm -f $(TARGET)

.PHONY: clean
