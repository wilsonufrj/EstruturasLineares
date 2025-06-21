#include "LinearDataStructure.hpp"

template <typename T>
class Queue : public LinearDataStructure<T> {
 private:
  struct Node {
    T data;
    std::unique_ptr<Node> next;
    Node(const T& data) : data(data), next(nullptr) {}
  };

  std::unique_ptr<Node> front;
  Node* rear;

 public:
  Queue() : LinearDataStructure<T>(), front(nullptr), rear(nullptr) {}

  Queue(std::initializer_list<T> init) : Queue() {
    for (const auto& item : init) {
      enqueue(item);
    }
  }

  bool isEmpty() const override { return this->size == 0; }

  bool isFull() const override { return false; }

  size_t length() const override { return this->size; }

  void enqueue(const T& value) {
    auto newNode = std::make_unique<Node>(value);
    if (isEmpty()) {
      front = std::move(newNode);
      rear = front.get();
    } else {
      rear->next = std::move(newNode);
      rear = rear->next.get();
    }
    this->size++;
  }

  T dequeue() {
    if (isEmpty()) {
      throw std::underflow_error("Fila underflow");
    }
    T value = front->data;
    front = std::move(front->next);
    this->size--;
    if (isEmpty()) {
      rear = nullptr;
    }
    return value;
  }

  T& peek() const {
    if (isEmpty()) {
      throw std::underflow_error("Fila esta vazia");
    }
    return front->data;
  }

  void insertAtEnd(const T& value) override { enqueue(value); }
  T removeFromStart() override { return dequeue(); }
  T& getFirst() const override { return peek(); }
};