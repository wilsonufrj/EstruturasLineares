#include <initializer_list>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "DoublyLinkedList.cpp"
#include "IndexedArray.cpp"
#include "Queue.cpp"
#include "SinglyLinkedList.cpp"
#include "Stack.cpp"

void testDataStructures() {
  // Teste da Pilha
  Stack<int> stack;
  stack.push(1);
  stack.push(2);
  stack.push(3);

  std::cout << "Stack: ";
  while (!stack.isEmpty()) {
    std::cout << stack.pop() << " ";
  }
  std::cout << std::endl;

  // Teste da Fila
  Queue<std::string> queue;
  queue.enqueue("first");
  queue.enqueue("second");
  queue.enqueue("third");

  std::cout << "Queue: ";
  while (!queue.isEmpty()) {
    std::cout << queue.dequeue() << " ";
  }
  std::cout << std::endl;

  IndexedArray<double> array = {1.1, 2.2, 3.3, 4.4};
  array.insertAtPosition(2, 2.5);

  std::cout << "Array: ";
  for (size_t i = 0; i < array.length(); i++) {
    std::cout << array[i] << " ";
  }
  std::cout << std::endl;

  SinglyLinkedList<char> sll = {'a', 'b', 'd'};
  sll.insertAtPosition(2, 'c');

  std::cout << "Singly Linked List: ";
  for (size_t i = 0; i < sll.length(); i++) {
    std::cout << sll[i] << " ";
  }
  std::cout << std::endl;

  DoublyLinkedList<int> dll = {10, 20, 30, 40};
  dll.insertAtPosition(2, 25);
  dll.removeFromEnd();

  std::cout << "Doubly Linked List: ";
  for (size_t i = 0; i < dll.length(); i++) {
    std::cout << dll[i] << " ";
  }
  std::cout << std::endl;

  IndexedArray<int> nums = {5, 3, 8, 1, 2};
  nums.sort();

  std::cout << "Sorted Array: ";
  for (size_t i = 0; i < nums.length(); i++) {
    std::cout << nums[i] << " ";
  }
  std::cout << std::endl;
}

int main() {
  try {
    testDataStructures();
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}