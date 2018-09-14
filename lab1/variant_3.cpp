//
// Created by Антон Донской on 06/09/2018.
//

#include <iostream>

template<class T>
class Node {
public:
    Node *_prev = nullptr;
    Node *_next = nullptr;
    T _data;


};

template<class T>
class List {
private:
    size_t _size;

public:
    Node<T> *_head;

    List() {
        _size = 0;
    }

    ~List() {
        Node<T> *current = _head;
        while (_size) {
            pop_front();
        }
    }

    void push_back(T data) {
        Node<T> *newNode = new Node<T>;
        newNode->_data = data;
        if (_size == 0) {
            _head = newNode;
        } else {
            Node<T> *current = _head;

            while (current != nullptr) {
                if (current->_next == nullptr) {
                    current->_next = newNode;
                    current->_next->_prev = current;
                    break;
                }
                current = current->_next;
            }
        }
        _size++;
    }

    void pop_back() {
        if (_size == 0) {
            throw ("Nothing to pop");
        } else {
            Node<T> *last = _head;
            while (last->_next != nullptr) {
                last = last->_next;
            }
            Node<T> *pre_last = last->_prev;
            pre_last->_next = nullptr;
            delete last;
            _size--;
        }
    }

    void swap_front_and_back() {
        Node<T> *first = _head;
        Node<T> *second = first->_next;
        Node<T> *last = _head;
        while (last->_next != nullptr) {
            last = last->_next;
        }
        Node<T> *pre_last = last->_prev;

        second->_prev = last;
        last->_next = second;
        last->_prev = nullptr;

        pre_last->_next = first;
        first->_prev = pre_last;
        first->_next = nullptr;

        _head = last;

    }

    void pop_front() {
        if (_size == 0) {
            throw ("Nothing to pop");
        } else {
            if (_size == 1) {
                delete _head;
                _head = nullptr;
            } else {
                Node<T> *first = _head;
                Node<T> *second = first->_next;
                second->_prev = nullptr;
                delete first;
                _head = second;
            }
            _size--;

        }

    }

    void push_front(T data) {
        Node<T> *newNode = new Node<T>;
        newNode->_data = data;
        if (_size == 0) {
            _head = newNode;
        } else {
            Node<T> *current = _head;
            newNode->_next = current;
            current->_prev = newNode;
            _head = newNode;
        }
        _size++;
    }

    void insert(int index, T data) {
        if (index == 0) {
            push_front(data);
        } else if (_size == index) {
            push_back(data);
        } else if (index > _size) {
            throw ("Index out of range");
        } else {
            int cnt = 0;
            Node<T> *current = _head;
            while (cnt != index) {
                current = current->_next;
                cnt++;
            }
            Node<T> *pre = current->_prev;
            Node<T> *newNode = new Node<T>;

            newNode->_data = data;
            newNode->_next = current;
            newNode->_prev = pre;
            current->_prev = newNode;
            pre->_next = newNode;
            _size++;

        }
    }

    void print() {

        Node<T> *current = _head;
        while (current) {
            std::cout << current->_data << " ";
            current = current->_next;
        }
        std::cout << std::endl;
    }

};


int main() {

    List<int> myList;
//    List<char> myList2;

    myList.push_back(1);
    myList.push_back(1);

    myList.print();

    myList.push_back(3);
    myList.push_back(111);
    myList.push_front(11);
    myList.push_front(12);

    myList.print();

    myList.pop_front();


    myList.print();
    myList.pop_back();
    myList.print();

    myList.swap_front_and_back();
    myList.print();
    myList.insert(0, 99);
    myList.print();
    myList.insert(1, 100);
    myList.print();
    myList.insert(6, 101);
    myList.print();

    myList.insert(6, 102);
    myList.print();

}