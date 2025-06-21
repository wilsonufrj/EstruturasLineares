template <typename T>
class DoublyLinkedList : public LinearDataStructure<T> {
 private:
  struct Node {
    T data;
    std::unique_ptr<Node> next;
    Node* prev;

    Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}
  };

  std::unique_ptr<Node> head;
  Node* tail;

  void bubbleSort() {
    if (!head || !head->next) return;

    bool swapped;
    Node* current;
    Node* lastSorted = nullptr;

    do {
      swapped = false;
      current = head.get();

      while (current->next.get() != lastSorted) {
        if (current->data > current->next->data) {
          std::swap(current->data, current->next->data);
          swapped = true;
        }
        current = current->next.get();
      }
      lastSorted = current;
    } while (swapped);
  }

  Node* findInsertPosition(const T& value) const {
    Node* current = head.get();
    while (current && current->data < value) {
      current = current->next.get();
    }
    return current;
  }

 public:
  DoublyLinkedList() : LinearDataStructure<T>(), head(nullptr), tail(nullptr) {}

  DoublyLinkedList(std::initializer_list<T> init) : DoublyLinkedList() {
    for (const auto& item : init) {
      insertAtEnd(item);
    }
    bubbleSort();
  }

  template <typename InputIt>
  DoublyLinkedList(InputIt first, InputIt last) : DoublyLinkedList() {
    for (auto it = first; it != last; ++it) {
      insertAtEnd(*it);
    }
    bubbleSort();
  }

  bool isEmpty() const override { return this->size == 0; }

  bool isFull() const override { return false; }

  size_t length() const override { return this->size; }

  void insertSorted(const T& value) {
    if (isEmpty() || value <= head->data) {
      insertAtStart(value);
    } else if (value >= tail->data) {
      insertAtEnd(value);
    } else {
      Node* position = findInsertPosition(value);
      insertBeforeNode(position, value);
    }
  }

  void insertAtStart(const T& value) override {
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

  void insertAtEnd(const T& value) override {
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

  void insertBeforeNode(Node* node, const T& value) {
    auto newNode = std::make_unique<Node>(value);
    newNode->prev = node->prev;
    newNode->next = std::move(node->prev->next);
    node->prev = newNode.get();
    newNode->prev->next = std::move(newNode);
    this->size++;
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

  bool contains(const T& value) const {
    Node* current = head.get();
    while (current && current->data <= value) {
      if (current->data == value) return true;
      current = current->next.get();
    }
    return false;
  }

  T& getFirst() const override {
    if (isEmpty()) {
      throw std::underflow_error("Lista esta vazia");
    }
    return head->data;
  }

  T& getLast() const override {
    if (isEmpty()) {
      throw std::underflow_error("Lista esta vazia");
    }
    return tail->data;
  }

  void print() const {
    Node* current = head.get();
    while (current) {
      std::cout << current->data << " ";
      current = current->next.get();
    }
    std::cout << std::endl;
  }
};