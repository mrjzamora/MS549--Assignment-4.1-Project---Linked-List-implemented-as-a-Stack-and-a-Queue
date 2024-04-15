#include <iostream>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <iomanip>

struct Node {
    int data;
    Node* prev;
    Node* next;
    Node(int data) : data(data), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
protected:
    Node* head;
    Node* tail;
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}
    virtual void insert(int data) = 0;
    virtual void remove(int data) = 0;

    void printContents() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

class Stack : public DoublyLinkedList {
public:
    void insert(int data) override {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void remove(int data) override {
        Node* temp = head;
        while (temp != nullptr && temp->data != data) {
            temp = temp->next;
        }
        if (temp == nullptr) return;
        if (temp == head) {
            head = head->next;
            if (head) head->prev = nullptr;
        }
        else if (temp == tail) {
            tail = tail->prev;
            if (tail) tail->next = nullptr;
        }
        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
        delete temp;
    }
};

class Queue : public DoublyLinkedList {
public:
    void insert(int data) override {
        Node* newNode = new Node(data);
        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void remove(int data) override {
        Node* temp = head;
        while (temp != nullptr && temp->data != data) {
            temp = temp->next;
        }
        if (temp == nullptr) return;
        if (temp == head) {
            head = head->next;
            if (head) head->prev = nullptr;
        }
        else if (temp == tail) {
            tail = tail->prev;
            if (tail) tail->next = nullptr;
        }
        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
        delete temp;
    }
};

void performanceTest(DoublyLinkedList& obj, const std::string& name, const std::vector<int>& sizes) {
    std::vector<long long> insertionTimes;
    std::vector<long long> deletionTimes;

    for (int n : sizes) {
        std::vector<int> data(n);
        for (int i = 0; i < n; ++i) {
            data[i] = std::rand() % 100000;
        }

        // Timing insert operations
        auto start = std::chrono::high_resolution_clock::now();
        for (int num : data) {
            obj.insert(num);
        }
        auto end = std::chrono::high_resolution_clock::now();
        insertionTimes.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

        // Timing remove operations
        start = std::chrono::high_resolution_clock::now();
        for (int num : data) {
            obj.remove(num);
        }
        end = std::chrono::high_resolution_clock::now();
        deletionTimes.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
    }

    // Printing the timing results
    std::cout << "Performance Results for " << name << ":\n";
    std::cout << "Operation\t\t100\t\t1000\t\t10000\n";
    std::cout << "Insert (ms)\t\t" << insertionTimes[0] << "\t\t"
        << insertionTimes[1] << "\t\t" << insertionTimes[2] << "\n";
    std::cout << "Delete (ms)\t\t" << deletionTimes[0] << "\t\t"
        << deletionTimes[1] << "\t\t" << deletionTimes[2] << "\n";
}

int main() {
    Stack myStack;
    Queue myQueue;
    std::vector<int> testSizes = { 100, 1000, 10000 };

    std::cout << "Stack operations:\n";
    myStack.insert(10);
    myStack.insert(20);
    myStack.insert(30);
    std::cout << "Stack contents after inserts: ";
    myStack.printContents();
    myStack.remove(20);
    std::cout << "Stack contents after removing 20: ";
    myStack.printContents();

    std::cout << "\nQueue operations:\n";
    myQueue.insert(10);
    myQueue.insert(20);
    myQueue.insert(30);
    std::cout << "Queue contents after inserts: ";
    myQueue.printContents();
    myQueue.remove(30);
    std::cout << "Queue contents after removing 30: ";
    myQueue.printContents();

    // Performance Testing
    std::cout << "\nPerformance Measurements:\n";
    performanceTest(myStack, "Stack", testSizes);
    performanceTest(myQueue, "Queue", testSizes);

    return 0;
}