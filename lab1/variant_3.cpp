#include <iostream>
#include <map>

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
        auto *newNode = new Node<T>;
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
        auto *newNode = new Node<T>;
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
            auto *newNode = new Node<T>;

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


std::string help_message = "Structure of all command: command_name list_name [args]\n\n"
                           "Available commands:\n"
                           "\tinit list_name\n"
                           "\tdelete list_name\n"
                           "\tpush_back list_name value\n"
                           "\tpush_front list_name value\n"
                           "\tpop_back list_name\n"
                           "\tpop_front list_name\n"
                           "\tprint list_name\n"
                           "\tswap list_name\n"
                           "\tinsert list_name value position\n\n"
                           "If you want to exit, just type exit\n\n";
std::map<std::string, List<int> > lists;
std::map<std::string, void (*)(std::string)> menu;
std::map<std::string, bool> shouldExsist;


class Menu {

public:
    static void init_list(const std::string name) {
        lists[name] = List<int>();
        std::cout << "[INFO] List with name '" + name + "' created" << std::endl;
    }

    static void delete_list(std::string name) {
        lists.erase(name);
        std::cout << "[INFO] List with name '" + name + "' deleted" << std::endl;
    }

    static void push_back(std::string name) {
        int value;
        std::cin >> value;
        lists[name].push_back(value);
        std::cout << "[INFO] Pushed back element to list '" + name + "'" << std::endl;
    }

    static void push_front(std::string name) {
        int value;
        std::cin >> value;
        lists[name].push_front(value);
        std::cout << "[INFO] Pushed front element to list '" + name + "'" << std::endl;
    }

    static void pop_front(std::string name) {
        lists[name].pop_front();
        std::cout << "[INFO] Poped front element to list '" + name + "'" << std::endl;
    }

    static void pop_back(std::string name) {
        lists[name].pop_back();
        std::cout << "[INFO] Poped back element to list '" + name + "'" << std::endl;
    }

    static void print(std::string name) {
        lists[name].print();
    }

    static void push_pos(std::string name) {

        int value;
        std::cin >> value;
        int pos;
        std::cin >> pos;

        try {
            lists[name].insert(pos, value);
            std::cout << "[INFO] Inserted element to pos " + std::to_string(pos) + " in list '" + name + "'"
                      << std::endl;
        } catch (...) {
            std::cout << "[ERROR] Index out of range" << std::endl;
        }

    }

    static void swap_elems(std::string name) {
        lists[name].swap_front_and_back();
        std::cout << "[INFO] Swaped first and last elements from list '" + name + "'" << std::endl;
    }


    Menu() {
        menu["init"] = Menu::init_list;
        shouldExsist["init"] = false;

        menu["delete"] = Menu::delete_list;
        shouldExsist["delete"] = true;

        menu["push_back"] = Menu::push_back;
        shouldExsist["push_back"] = true;

        menu["push_front"] = Menu::push_front;
        shouldExsist["push_front"] = true;

        menu["pop_front"] = Menu::pop_front;
        shouldExsist["pop_front"] = true;

        menu["pop_back"] = Menu::pop_back;
        shouldExsist["pop_back"] = true;

        menu["print"] = Menu::print;
        shouldExsist["print"] = true;

        menu["insert"] = Menu::push_pos;
        shouldExsist["insert"] = true;

        menu["swap"] = Menu::swap_elems;
        shouldExsist["swap"] = true;
    }

    ~Menu() {
        menu.clear();
        lists.clear();
    }


    void handle() {
        std::cout << help_message << std::endl;
        while (true) {
            std::cout << ">";
            std::string command;
            std::cin >> command;
            if (command == "exit") {
                return;
            }
            if (menu.find(command) != menu.end()) {
                std::string name;
                std::cin >> name;

                if ((shouldExsist[command] && (lists.find(name) != lists.end())) ||
                    (!shouldExsist[command] && (lists.find(name) == lists.end()))) {
                    menu[command](name);
                } else {

                    if ((shouldExsist[command] && (lists.find(name) == lists.end()))) {
                        std::cout << "[ERROR] List with name '" + name + "' doesn't exsist" << std::endl;
                    } else if (!shouldExsist[command] && (lists.find(name) != lists.end())) {
                        std::cout << "[ERROR] List with name '" + name + "' already exsist" << std::endl;
                    }

                }

            } else {
                std::cout << "Uknown command\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
        }
    }
};

int main() {
    Menu menu;
    menu.handle();
}