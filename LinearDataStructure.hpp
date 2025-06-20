#include <initializer_list>
#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T>
class LinearDataStructure {
 protected:
  size_t size;

 public:
  LinearDataStructure() : size(0) {}
  virtual ~LinearDataStructure() = default;

  virtual bool isEmpty() const = 0;
  virtual bool isFull() const = 0;
  virtual size_t length() const = 0;

  virtual void insertAtStart(const T &value) {
    throw std::runtime_error(
        "Operação não suportada por essa estrutura de dados");
  }
  virtual void insertAtEnd(const T &value) {
    throw std::runtime_error(
        "Operação não suportada por essa estrutura de dados");
  }
  virtual void insertAtPosition(size_t pos, const T &value) {
    throw std::runtime_error(
        "Operação não suportada por essa estrutura de dados");
  }

  virtual T removeFromStart() {
    throw std::runtime_error(
        "Operação não suportada por essa estrutura de dados");
  }
  virtual T removeFromEnd() {
    throw std::runtime_error(
        "Operação não suportada por essa estrutura de dados");
  }
  virtual T removeFromPosition(size_t pos) {
    throw std::runtime_error(
        "Operação não suportada por essa estrutura de dados");
  }

  virtual T &getFirst() const {
    throw std::runtime_error(
        "Operação não suportada por essa estrutura de dados");
  }
  virtual T &getLast() const {
    throw std::runtime_error(
        "Operação não suportada por essa estrutura de dados");
  }
  virtual T &getAtPosition(size_t pos) const {
    throw std::runtime_error(
        "Operação não suportada por essa estrutura de dados");
  }

  virtual T &operator[](size_t pos) const { return getAtPosition(pos); }

  virtual void swap(size_t pos1, size_t pos2) {
    if (pos1 >= size || pos2 >= size) {
      throw std::out_of_range("Index out of bounds");
    }
    T temp = getAtPosition(pos1);
    getAtPosition(pos1) = getAtPosition(pos2);
    getAtPosition(pos2) = temp;
  }

  virtual void sort() {
    for (size_t i = 0; i < size - 1; i++) {
      for (size_t j = 0; j < size - i - 1; j++) {
        if (getAtPosition(j) > getAtPosition(j + 1)) {
          swap(j, j + 1);
        }
      }
    }
  }
};