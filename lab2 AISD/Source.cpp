#include <iostream>
#include <cstdlib> 
#include <algorithm>
#include <clocale>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* _head;

public:
    // Конструктор по умолчанию.
    LinkedList() : _head(nullptr) {}

    // Конструктор копирования.
    LinkedList(const LinkedList& other) : _head(nullptr) {
        Node<T>* otherCurrent = other._head;
        while (otherCurrent) {
            push_tail(otherCurrent->data);
            otherCurrent = otherCurrent->next;
        }
    }

    // Конструктор, заполняющий список случайными значениями согласно заданию.
    LinkedList(int size) : _head(nullptr) {
        for (int i = 0; i < size; ++i) {
            push_tail(rand() % 100); // случайные значения от 0 до 99
        }
    }

    // Деструктор.
    ~LinkedList() {
        Node<T>* current = _head;
        while (current) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        _head = nullptr;
    }

    // Операция присваивания.
    LinkedList& operator=(const LinkedList& other) {
        LinkedList temp(other);
        swap(temp);
        return *this;
    }

    // Добавление элемента в конец списка — push_tail.
    void push_tail(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (!_head) {
            _head = newNode;
        }
        else {
            Node<T>* current = _head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // Добавление другого списка LinkedList в конец списка — push_tail (перегруженный метод).
    void push_tail(const LinkedList& other) {
        Node<T>* otherCurrent = other._head;
        while (otherCurrent) {
            push_tail(otherCurrent->data);
            otherCurrent = otherCurrent->next;
        }
    }

    // Добавление элемента в начало списка — push_head.
    void push_head(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = _head;
        _head = newNode;
    }

    // Добавление списка LinkedList в начало списка — push_head (перегруженный метод).
    void push_head(const LinkedList& other) {
        LinkedList temp(other);
        temp.reverse();
        Node<T>* otherCurrent = temp._head;
        while (otherCurrent) {
            push_head(otherCurrent->data);
            otherCurrent = otherCurrent->next;
        }
    }


    // Удаление элемента из начала списка — pop_head.
    void pop_head() {
        if (!_head) {
            return;
        }
        Node<T>* temp = _head;
        _head = _head->next;
        delete temp;
    }

    // Удаление элемента из конца списка — pop_tail.
    void pop_tail() {
        if (!_head) {
            return;
        }
        if (!_head->next) {
            delete _head;
            _head = nullptr;
            return;
        }
        Node<T>* current = _head;
        while (current->next->next) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }

    // Удаление всех элементов Node с информационным полем, равным переданному — delete_node.
    void delete_node(const T& value) {
        while (_head && _head->data == value) {
            pop_head();
        }
        if (!_head) {
            return;
        }
        Node<T>* current = _head;
        while (current->next) {
            if (current->next->data == value) {
                Node<T>* temp = current->next;
                current->next = current->next->next;
                delete temp;
            }
            else {
                current = current->next;
            }
        }
    }

    // Операция доступа по индексу (в двух вариантах: для чтения/записи).
    T& operator[](int index) {
        Node<T>* current = _head;
        for (int i = 0; i < index; ++i) {
            if (!current) {
                throw out_of_range("Index out of range");
            }
            current = current->next;
        }
        if (!current) {
            throw out_of_range("Index out of range");
        }
        return current->data;
    }

    const T& operator[](int index) const {
        Node<T>* current = _head;
        for (int i = 0; i < index; ++i) {
            if (!current) {
                throw out_of_range("Index out of range");
            }
            current = current->next;
        }
        if (!current) {
            throw out_of_range("Index out of range");
        }
        return current->data;
    }

    void printLuckyNumbers() {
        Node<T>* current = _head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    bool find(const T& value) const {
        Node<T>* current = _head;
        while (current) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void findNumbers(int N) {
        LinkedList<int> list1;
        for (int i = 1; i <= N; ++i) {
            list1.push_tail(i);
        }

        LinkedList<int> list2;
        Node<int>* current = list1._head;
        while (current) {
            if (current->data % 2 != 0) {
                list2.push_tail(current->data);
            }
            current = current->next;
        }

        LinkedList<int> list3;
        Node<int>* current2 = list2._head;
        int count2 = 0;
        while (current2) {
            ++count2;
            if (count2 % 3 != 0) {
                list3.push_tail(current2->data);
            }
            current2 = current2->next;
        }

        LinkedList<int> list4;
        Node<int>* current3 = list3._head;
        int count3 = 0;
        while (current3) {
            ++count3;
            if (count3 % 7 != 0) {
                list4.push_tail(current3->data);
            }
            current3 = current3->next;
        }

        // Вывод результатов
        std::cout << "Исходный список:" << std::endl;
        list1.printLuckyNumbers();
        std::cout << "Список счасливых чисел:" << std::endl;
        list4.printLuckyNumbers();
        std::cout << "Список несчастливых чисел:" << std::endl;
        printUnluckyNumbers(list1, list4);
    }

    void printUnluckyNumbers(LinkedList<int> list, LinkedList<int> exclusionList) {
        Node<int>* current = list._head;
        while (current) {
            if (!exclusionList.find(current->data)) {
                std::cout << current->data << " ";
            }
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    LinkedList<int> list1;
    list1.findNumbers(26);
    return 0;
}