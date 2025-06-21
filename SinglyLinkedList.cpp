#include "LinearDataStructure.hpp"

template <typename T>
class SinglyLinkedList : public LinearDataStructure<T> {
 private:
  struct Node {
    T data;
    std::unique_ptr<Node> next;
    Node(const T &data) : data(data), next(nullptr) {}
  };

  std::unique_ptr<Node> head;
  Node *tail;

 public:
  SinglyLinkedList() : LinearDataStructure<T>(), head(nullptr), tail(nullptr) {}

  SinglyLinkedList(std::initializer_list<T> init) : SinglyLinkedList() {
    for (const auto &item : init) {
      insertAtEnd(item);
    }
  }

  bool isEmpty() const override { return this->size == 0; }

  bool isFull() const override { return false; }

  size_t length() const override { return this->size; }

  void insertAtStart(const T &value) override {
    auto newNode = std::make_unique<Node>(value);
    if (isEmpty()) {
      head = std::move(newNode);
      tail = head.get();
    } else {
      newNode->next = std::move(head);
      head = std::move(newNode);
    }
    this->size++;
  }

  void insertAtEnd(const T &value) override {
    auto newNode = std::make_unique<Node>(value);
    if (isEmpty()) {
      head = std::move(newNode);
      tail = head.get();
    } else {
      tail->next = std::move(newNode);
      tail = tail->next.get();
    }
    this->size++;
  }

  void insertAtPosition(size_t pos, const T &value) override {
    if (pos > this->size) {
      throw std::out_of_range("Posição bora dos limites");
    }

    if (pos == 0) {
      insertAtStart(value);
    } else if (pos == this->size) {
      insertAtEnd(value);
    } else {
      auto newNode = std::make_unique<Node>(value);
      Node *current = head.get();
      for (size_t i = 1; i < pos; i++) {
        current = current->next.get();
      }
      newNode->next = std::move(current->next);
      current->next = std::move(newNode);
      this->size++;
    }
  }

  T removeFromStart() override {
    if (isEmpty()) {
      throw std::underflow_error("Lista esta vazia");
    }

    T value = head->data;
    head = std::move(head->next);
    this->size--;

    if (isEmpty()) {
      tail = nullptr;
    }

    return value;
  }

  T removeFromEnd() override {
    if (isEmpty()) {
      throw std::underflow_error("Lista esta vazia");
    }

    if (this->size == 1) {
      return removeFromStart();
    }

    Node *current = head.get();
    while (current->next->next != nullptr) {
      current = current->next.get();
    }

    T value = current->next->data;
    current->next = nullptr;
    tail = current;
    this->size--;

    return value;
  }

  T removeFromPosition(size_t pos) override {
    if (pos >= this->size) {
      throw std::out_of_range("Posição fora dos limites");
    }

    if (pos == 0) {
      return removeFromStart();
    } else if (pos == this->size - 1) {
      return removeFromEnd();
    } else {
      Node *current = head.get();
      for (size_t i = 1; i < pos; i++) {
        current = current->next.get();
      }

      T value = current->next->data;
      current->next = std::move(current->next->next);
      this->size--;

      return value;
    }
  }

  T &getFirst() const override {
    if (isEmpty()) {
      throw std::underflow_error("List is empty");
    }
    return head->data;
  }

  T &getLast() const override {
    if (isEmpty()) {
      throw std::underflow_error("List is empty");
    }
    return tail->data;
  }

  T &getAtPosition(size_t pos) const override {
    if (pos >= this->size) {
      throw std::out_of_range("Index out of bounds");
    }

    Node *current = head.get();
    for (size_t i = 0; i < pos; i++) {
      current = current->next.get();
    }

    return current->data;
  }

  const T &operator[](size_t pos) const {
    if (pos >= this->size) {
      throw std::out_of_range("Index fora dos limites");
    }

    Node *current = head.get();
    for (size_t i = 0; i < pos; i++) {
      current = current->next.get();
    }

    return current->data;
  }
};