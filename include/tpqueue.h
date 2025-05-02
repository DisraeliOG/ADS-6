// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <cstddef>
#include <stdexcept>

struct SYM {
    char ch;
    int prior;
};

template <typename T>
class TPQueue {
 private:
  struct Node {
    T data;
    Node* next;
    explicit Node(const T& d) : data(d), next(nullptr) {}
  };

  Node* head;
  std::size_t count;

 public:
  TPQueue() : head(nullptr), count(0) {}

  ~TPQueue() {
    clear();
  }

  // Disable copy semantics
  TPQueue(const TPQueue&) = delete;
  TPQueue& operator=(const TPQueue&) = delete;

  // Check if the queue is empty
  bool empty() const {
    return head == nullptr;
  }

  // Return number of elements
  std::size_t size() const {
    return count;
  }

  // Insert element into the queue based on its priority
  void push(const T& value) {
    Node* node = new Node(value);
    // If empty or higher priority than head, insert at front
    if (!head || value.prior > head->data.prior) {
      node->next = head;
      head = node;
    } else {
      // Traverse to find insertion point
      Node* current = head;
      while (current->next && current->next->data.prior >= value.prior) {
        current = current->next;
      }
      node->next = current->next;
      current->next = node;
    }
    ++count;
  }

  T pop() {
    if (empty()) {
      throw std::out_of_range("Pop from empty TPQueue");
    }
    Node* node = head;
    T value = node->data;
    head = head->next;
    delete node;
    --count;
    return value;
  }

  const T& top() const {
    if (empty()) {
      throw std::out_of_range("Top from empty TPQueue");
    }
    return head->data;
  }

  void clear() {
    while (head) {
      Node* tmp = head;
      head = head->next;
      delete tmp;
    }
    count = 0;
  }
};

#endif  // INCLUDE_TPQUEUE_H_

