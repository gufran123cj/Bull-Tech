CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++17
TARGET = line_count

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -pthread -o $(TARGET) main.cpp

clean:
	rm -f $(TARGET)

.PHONY: clean
