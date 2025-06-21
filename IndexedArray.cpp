#include "LinearDataStructure.hpp"

template <typename T>
class IndexedArray : public LinearDataStructure<T> {
 private:
  std::unique_ptr<T[]> data;
  size_t capacity;

 public:
  IndexedArray(size_t capacity = 100)
      : LinearDataStructure<T>(),
        capacity(capacity),
        data(std::make_unique<T[]>(capacity)) {}

  IndexedArray(std::initializer_list<T> init)
      : LinearDataStructure<T>(),
        capacity(init.size()),
        data(std::make_unique<T[]>(init.size())) {
    for (size_t i = 0; i < init.size(); i++) {
      data[i] = *(init.begin() + i);
    }
    this->size = init.size();
  }

  bool isEmpty() const override { return this->size == 0; }

  bool isFull() const override { return this->size == capacity; }

  size_t length() const override { return this->size; }

  T &operator[](size_t pos) {
    if (pos >= this->size) {
      throw std::out_of_range("Index fora dos limites");
    }
    return data[pos];
  }

  void insertAtPosition(size_t pos, const T &value) override {
    if (isFull()) {
      throw std::overflow_error("O array esta cheio");
    }
    if (pos > this->size) {
      throw std::out_of_range("Posição fora dos limites");
    }

    for (size_t i = this->size; i > pos; i--) {
      data[i] = data[i - 1];
    }

    data[pos] = value;
    this->size++;
  }

  T removeFromPosition(size_t pos) override {
    if (isEmpty()) {
      throw std::underflow_error("Array esta vazio");
    }
    if (pos >= this->size) {
      throw std::out_of_range("Posição fora dos limites");
    }

    T value = data[pos];

    for (size_t i = pos; i < this->size - 1; i++) {
      data[i] = data[i + 1];
    }

    this->size--;
    return value;
  }

  T &getAtPosition(size_t pos) const override {
    if (pos >= this->size) {
      throw std::out_of_range("Index fora dos limites");
    }
    return data[pos];
  }

  void resize(size_t newCapacity) {
    if (newCapacity < this->size) {
      throw std::invalid_argument(
          "Nova capacidade é menor que o atual tamanho");
    }

    auto newData = std::make_unique<T[]>(newCapacity);
    for (size_t i = 0; i < this->size; i++) {
      newData[i] = data[i];
    }

    data = std::move(newData);
    capacity = newCapacity;
  }

  virtual void sort() {
    for (size_t i = 0; i < this->size - 1; i++) {
      for (size_t j = 0; j < this->size - i - 1; j++) {
        if (getAtPosition(j) > getAtPosition(j + 1)) {
          swap(j, j + 1);
        }
      }
    }
  }
};