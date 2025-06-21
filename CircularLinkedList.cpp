template <typename T>
class CircularLinkedList : public LinearDataStructure<T> {
 private:
  struct Node {
    T data;
    std::unique_ptr<Node> next;
    Node(const T& data) : data(data), next(nullptr) {}
  };

  std::unique_ptr<Node> head;
  Node* tail;

 public:
  CircularLinkedList()
      : LinearDataStructure<T>(), head(nullptr), tail(nullptr) {}

  CircularLinkedList(std::initializer_list<T> init) : CircularLinkedList() {
    for (const auto& item : init) {
      insertAtEnd(item);
    }
  }

  ~CircularLinkedList() override {
    if (tail) {
      tail->next = nullptr;
    }
  }

  Node* getNode(size_t pos) const {
    if (pos >= this->size) {
      throw std::out_of_range("Index fora dos limites");
    }
    Node* current = head.get();
    for (size_t i = 0; i < pos; i++) {
      current = current->next.get();
    }
    return current;
  }

  bool isEmpty() const override { return this->size == 0; }

  bool isFull() const override { return false; }

  size_t length() const override { return this->size; }

  void insertAtStart(const T& value) override {
    auto newNode = std::make_unique<Node>(value);
    if (isEmpty()) {
      head = std::move(newNode);
      tail = head.get();
      tail->next = std::move(head);
    } else {
      newNode->next = std::move(head)
    }
    this->size++;
  }

  void insertAtEnd(const T& value) override {
    auto newNode = std::make_unique<Node>(value);
    if (isEmpty()) {
      insertAtStart(value);
    } else {
      newNode->next = std::move(tail->next);
      tail->next = std::move(newNode);
      tail = tail->next.get();
      tail->next = std::move(head);
      this->size++;
    }
  }

  void insertAtPosition(size_t pos, const T& value) override {
    if (pos > this->size) {
      throw std::out_of_range("Posição fora dos limites");
    }

    if (pos == 0) {
      insertAtStart(value);
    } else if (pos == this->size) {
      insertAtEnd(value);
    } else {
      auto newNode = std::make_unique<Node>(value);
      Node* current = head.get();
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
      throw std::underflow_error("Lista está vazia");
    }

    T value = head->data;
    if (this->size == 1) {
      head = nullptr;
      tail = nullptr;
    } else {
      head = std::move(head->next);
      tail->next = std::move(head);
    }
    this->size--;

    return value;
  }

  T removeFromEnd() override {
    if (isEmpty()) {
      throw std::underflow_error("Lista está vazia");
    }

    if (this->size == 1) {
      return removeFromStart();
    }

    Node* current = head.get();
    while (current->next.get() != tail) {
      current = current->next.get();
    }

    T value = tail->data;
    current->next = std::move(tail->next);
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
      Node* current = head.get();
      for (size_t i = 1; i < pos; i++) {
        current = current->next.get();
      }

      T value = current->next->data;
      current->next = std::move(current->next->next);
      this->size--;

      return value;
    }
  }

  T& getFirst() const override {
    if (isEmpty()) {
      throw std::underflow_error("Lista está vazia");
    }
    return head->data;
  }

  T& getLast() const override {
    if (isEmpty()) {
      throw std::underflow_error("Lista está vazia");
    }
    return tail->data;
  }

  T& getAtPosition(size_t pos) const override {
    if (pos >= this->size) {
      throw std::out_of_range("Index fora dos limites");
    }

    Node* current = head.get();
    for (size_t i = 0; i < pos; i++) {
      current = current->next.get();
    }

    return current->data;
  }

  void rotate() {
    if (!isEmpty() && this->size > 1) {
      tail = head.get();
      head = std::move(head->next);
      tail->next = std::move(head);
    }
  }

  void display() const {
    if (isEmpty()) {
      std::cout << "Lista vazia" << std::endl;
      return;
    }

    Node* current = head.get();
    std::cout << "Lista Circular: ";

    for (size_t i = 0; i < this->size; i++) {
      std::cout << current->data << " ";
      current = current->next.get();
    }
    std::cout << std::endl;
  }
};