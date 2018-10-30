#include <iostream>
#include <queue>
#include <stack>
#include <map>

struct Edge {
    int value;
    Edge *leftChild = nullptr;
    Edge *rightChild = nullptr;

    bool hasChild() {
        return this->leftChild || this->rightChild;
    }
};


void dfs(Edge *edge) {
    if (edge) {
        if (edge->hasChild()) {
            edge->value = 0;

            if (edge->leftChild) {
                edge->value = edge->leftChild->value;
                if (edge->leftChild->hasChild()) {
                    dfs(edge->leftChild);
                    edge->value += edge->leftChild->value;
                }

            }

            if (edge->rightChild) {
                edge->value += edge->rightChild->value;
                if (edge->rightChild->hasChild()) {
                    dfs(edge->rightChild);
                    edge->value += edge->rightChild->value;
                }

            }
        }
    }
}

void bfs(Edge *edge) {
    std::queue<Edge *> q;
    std::stack<Edge *> s;

    q.push(edge);
    while (!q.empty()) {
        Edge *tmp = q.front();
        q.pop();

        if (tmp->hasChild()) {
            tmp->value = 0;
            bool lateUpdate = false;
            if (tmp->leftChild) {
                tmp->value += tmp->leftChild->value;
                q.push(tmp->leftChild);
                if (tmp->leftChild->hasChild()) {
                    lateUpdate = true;
                }
            }

            if (tmp->rightChild) {
                tmp->value += tmp->rightChild->value;
                q.push(tmp->rightChild);
                if (tmp->rightChild->hasChild()) {
                    lateUpdate = true;
                }
            }

            if (lateUpdate) {
                s.push(tmp);
            }
        }
    }
    while (!s.empty()) {
        Edge *tmp = s.top();
        s.pop();
        if (tmp->rightChild && tmp->rightChild->hasChild()) {
            tmp->value += tmp->rightChild->value;
        }
        if (tmp->leftChild && tmp->leftChild->hasChild()) {
            tmp->value += tmp->leftChild->value;
        }

    }
}


int main() {
    std::map<std::string, Edge *> edges;
    while (true) {
        std::cout << ">";
        std::string command;
        std::cin >> command;
        if (command == "exit") {
            break;
        } else if (command == "add") {
            std::string name;
            int value;
            std::cin >> name >> value;
            Edge *tmp = new Edge;
            tmp->value = value;
            edges[name] = tmp;
        } else if (command == "left") {
            std::string parrent;
            std::string child;
            std::cin >> parrent >> child;
            if (edges.find(parrent) == edges.end()) {
                std::cout << "[ERROR] Edge named " << parrent << " doesn't exist\n";
                continue;
            }
            if (edges.find(child) == edges.end()) {
                std::cout << "[ERROR] Edge named " << child << " doesn't exist\n";
                continue;
            }
            edges[parrent]->leftChild = edges[child];
        } else if (command == "right") {
            std::string parrent;
            std::string child;
            std::cin >> parrent >> child;
            if (edges.find(parrent) == edges.end()) {
                std::cout << "[ERROR] Edge named " << parrent << " doesn't exist\n";
                continue;
            }
            if (edges.find(child) == edges.end()) {
                std::cout << "[ERROR] Edge named " << child << " doesn't exist\n";
                continue;
            }
            edges[parrent]->rightChild = edges[child];
        } else if (command == "print") {
            std::string edge;
            std::cin >> edge;
            if (edges.find(edge) == edges.end()) {
                std::cout << "[ERROR] Edge named " << edge << " doesn't exist\n";
                continue;
            }
            std::queue<Edge *> q;
            q.push(edges[edge]);
            while (!q.empty()) {
                Edge *tmp = q.front();
                q.pop();
                std::cout << tmp->value << " ";
                if (tmp->leftChild) {
                    q.push(tmp->leftChild);
                }
                if (tmp->rightChild) {
                    q.push(tmp->rightChild);
                }

            }
            std::cout << std::endl;
        } else if (command == "bfs") {
            std::string edge;
            std::cin >> edge;
            if (edges.find(edge) == edges.end()) {
                std::cout << "[ERROR] Edge named " << edge << " doesn't exist\n";
                continue;
            }
            bfs(edges[edge]);
        } else if (command == "dfs") {
            std::string edge;
            std::cin >> edge;
            if (edges.find(edge) == edges.end()) {
                std::cout << "[ERROR] Edge named " << edge << " doesn't exist\n";
                continue;
            }
            dfs(edges[edge]);
        } else {
            std::cout << "Unknown command\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }
}