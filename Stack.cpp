#include "LinearDataStructure.hpp"

template <typename T>
class Stack : public LinearDataStructure<T> {
 private:
  struct Node {
    T data;
    std::unique_ptr<Node> next;
    Node(const T &data) : data(data), next(nullptr) {}
  };

  std::unique_ptr<Node> top;

 public:
  Stack() : LinearDataStructure<T>(), top(nullptr) {}

  Stack(std::initializer_list<T> init) : Stack() {
    for (const auto &item : init) {
      push(item);
    }
  }

  bool isEmpty() const override { return this->size == 0; }

  bool isFull() const override { return false; }

  size_t length() const override { return this->size; }

  void push(const T &value) {
    auto newNode = std::make_unique<Node>(value);
    newNode->next = std::move(top);
    top = std::move(newNode);
    this->size++;
  }

  T pop() {
    if (isEmpty()) {
      throw std::underflow_error("Stack underflow");
    }
    T value = top->data;
    top = std::move(top->next);
    this->size--;
    return value;
  }

  T &peek() const {
    if (isEmpty()) {
      throw std::underflow_error("Stack is empty");
    }
    return top->data;
  }

  void insertAtStart(const T &value) override { push(value); }
  T removeFromStart() override { return pop(); }
  T &getFirst() const override { return peek(); }
};
