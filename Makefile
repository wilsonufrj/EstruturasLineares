CXX = g++

CXXFLAGS = -std=c++17 -Wall -fpermissive -I.

SRCS = CircularLinkedList.cpp DoublyLinkedList.cpp IndexedArray.cpp PriorityQueue.cpp Queue.cpp SinglyLinkedList.cpp Stack.cpp StackWithSinglyLinkedList.cpp UsuarioBandeijao.cpp

OBJS = $(SRCS:.cpp=.o)

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp LinearDataStructure.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
