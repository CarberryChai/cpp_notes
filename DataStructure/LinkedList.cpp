#include <iostream>

template <typename T> struct Node {
  T value;
  Node<T> *next;
};

template <typename T> class LinkedList {
public:
  LinkedList() = default;
  LinkedList(int s) : _size(s) {}
  LinkedList(LinkedList &&) = default;
  LinkedList(const LinkedList &) = default;
  LinkedList &operator=(LinkedList &&) = default;
  LinkedList &operator=(const LinkedList &) = default;
  ~LinkedList() = default;

  int size() const { return _size; }

  Node<T> *head() const { return _head; }

  Node<T> *tril() const { return _tril; }

private:
  int _size = 0;
  Node<T> *_head;
  Node<T> *_tril;
};

int main(int argc, char *argv[]) {
  LinkedList<int> list;
  std::cout << list.size() << std::endl;
  return 0;
}
