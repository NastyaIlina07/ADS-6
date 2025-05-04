// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <stdexcept>
template<typename T>
class TPQueue {
 private:
  struct Node {
    T data;
    Node* next;
    explicit Node(const T& data, Node* next = nullptr) : data(data), next(next) {}
  };

  Node* head;
  Node* tail;
  int size;

 public:
  TPQueue() : head(nullptr), tail(nullptr), size(0) {}

  ~TPQueue() { clear(); }

  void push(const T& item) {
    Node* newNode = new Node(item);

    if (!head || item.prior > head->data.prior) {
      newNode->next = head;
      head = newNode;
      if (!tail) tail = head;
      size++;
      return;
    }

    Node* current = head;
    while (current->next && current->next->data.prior >= item.prior) {
      current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;

    if (!newNode->next) {
      tail = newNode;
    }

    size++;
  }

  T pop() {
    if (empty()) {
      throw std::underflow_error("TPQueue is empty");
    }

    Node* temp = head;
    T data = head->data;
    head = head->next;

    if (!head) {
      tail = nullptr;
    }

    delete temp;
    size--;
    return data;
  }

  const T& front() const {
    if (empty()) {
      throw std::underflow_error("TPQueue is empty");
    }
    return head->data;
  }

  const T& back() const {
    if (empty()) {
      throw std::underflow_error("TPQueue is empty");
    }
    return tail->data;
  }

  bool empty() const { return head == nullptr; }

  int getSize() const { return size; }

  void clear() {
    while (head) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
    tail = nullptr;
    size = 0;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
