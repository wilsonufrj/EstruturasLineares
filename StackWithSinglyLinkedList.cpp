template <typename T>
class StackWithSinglyLinkedList : public LinearDataStructure<T> {
 private:
  SinglyLinkedList<T> list;

 public:
  StackWithSinglyLinkedList() : LinearDataStructure<T>(), list() {}

  StackWithSinglyLinkedList(std::initializer_list<T> init)
      : StackWithSinglyLinkedList() {
    for (const auto &item : init) {
      push(item);
    }
  }

  bool isEmpty() const override { return list.isEmpty(); }

  bool isFull() const override { return false; }

  size_t length() const override { return list.length(); }

  void push(const T &value) { list.insertAtStart(value); }

  T pop() { return list.removeFromStart(); }

  T &peek() const { return list.getFirst(); }

  void insertAtStart(const T &value) override { push(value); }

  T removeFromStart() override { return pop(); }

  T &getFirst() const override { return peek(); }

  void clear() {
    while (!isEmpty()) {
      pop();
    }
  }
};