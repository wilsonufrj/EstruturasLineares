template <typename T>
class DoublyLinkedList : public LinearDataStructure<T> {
 private:
  struct Node {
    T data;
    std::unique_ptr<Node> next;
    Node *prev;

    Node(const T &data) : data(data), next(nullptr), prev(nullptr) {}
  };

  std::unique_ptr<Node> head;
  Node *tail;

 public:
  DoublyLinkedList() : LinearDataStructure<T>(), head(nullptr), tail(nullptr) {}

  DoublyLinkedList(std::initializer_list<T> init) : DoublyLinkedList() {
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
      newNode->next->prev = newNode.get();
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
      newNode->prev = tail;
      tail->next = std::move(newNode);
      tail = tail->next.get();
    }
    this->size++;
  }

  void insertAtPosition(size_t pos, const T &value) override {
    if (pos > this->size) {
      throw std::out_of_range("Posição fora dos limites");
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
      newNode->prev = current;
      newNode->next->prev = newNode.get();
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
    } else {
      head->prev = nullptr;
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

    T value = tail->data;
    tail = tail->prev;
    tail->next = nullptr;
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
      for (size_t i = 0; i < pos; i++) {
        current = current->next.get();
      }

      T value = current->data;
      current->prev->next = std::move(current->next);
      current->next->prev = current->prev;
      this->size--;

      return value;
    }
  }

  T &getFirst() const override {
    if (isEmpty()) {
      throw std::underflow_error("Lista esta vazia");
    }
    return head->data;
  }

  T &getLast() const override {
    if (isEmpty()) {
      throw std::underflow_error("Lista esta vazia");
    }
    return tail->data;
  }

  T &getAtPosition(size_t pos) const override {
    if (pos >= this->size) {
      throw std::out_of_range("Index fora dos limites");
    }

    if (pos < this->size / 2) {
      Node *current = head.get();
      for (size_t i = 0; i < pos; i++) {
        current = current->next.get();
      }
      return current->data;
    } else {
      Node *current = tail;
      for (size_t i = this->size - 1; i > pos; i--) {
        current = current->prev;
      }
      return current->data;
    }
  }

  T &operator[](size_t pos) {
    if (pos >= this->size) {
      throw std::out_of_range("Posição fora dos limites");
    }

    if (pos < this->size / 2) {
      Node *current = head.get();
      for (size_t i = 0; i < pos; i++) {
        current = current->next.get();
      }
      return current->data;
    } else {
      Node *current = tail;
      for (size_t i = this->size - 1; i > pos; i--) {
        current = current->prev;
      }
      return current->data;
    }
  }
};
