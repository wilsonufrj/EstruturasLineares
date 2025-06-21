#include <initializer_list>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "DoublyLinkedList.cpp"

template <typename T>
class PriorityQueue {
 private:
  DoublyLinkedList<T> list;

 public:
  PriorityQueue() = default;

  PriorityQueue(std::initializer_list<T> init) : list(init) {}

  void enqueue(const T& item) { list.insertSorted(item); }

  T dequeue() {
    if (isEmpty()) {
      throw std::underflow_error(
          "PriorityQueue underflow: cannot dequeue from an empty queue.");
    }
    return list.removeFromEnd();
  }

  T peek() const {
    if (isEmpty()) {
      throw std::underflow_error("PriorityQueue is empty.");
    }
    return list.getLast();
  }

  bool isEmpty() const { return list.isEmpty(); }

  size_t size() const { return list.length(); }

  void display() const {
    std::cout << "PriorityQueue (highest priority last): ";
    for (size_t i = 0; i < list.length(); ++i) {
      std::cout << list[i] << " ";
    }
    std::cout << std::endl;
  }
};