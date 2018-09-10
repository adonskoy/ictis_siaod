//
// Created by Антон Донской on 06/09/2018.
//

#include <iostream>


class BinTree {
public:
    int *_nodes;
    int _size;

    int get_left(int i) {
        int result = 2 * i + 1;
        if (result >= _size) {
            return NULL;
        } else {
            return result;
        }
    }

    int get_right(int i) {
        int result = 2 * i + 2;
        if (result >= _size) {
            return NULL;
        } else {
            return result;
        }
    }
    

    explicit BinTree(int size) {
        _size = size;
        _nodes = new int[_size];
    }

    void input() {
        for (int i(0); i < _size; ++i) {
            std::cin >> _nodes[i];
        }
    }

    void print() {
        for (int i(0); i < _size; ++i) {
            std::cout << _nodes[i] << " ";
        }
        std::cout << std::endl;
    }

    void process(int i) {
        if (get_left(i) && get_right(i)) {
            process(get_right(i));
            process(get_left(i));
            _nodes[i] = _nodes[get_left(i)] + _nodes[get_right(i)];
        }

    }

};


int main() {
    BinTree a(5);
    a.input();
    a.process(0);
    a.print();

}