#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

#define N 1021
#define P 257
#define st2 65535


struct Pair {
    bool flag = false;
    std::string key = "";
};

class MyHashTable {
private:
    std::vector<Pair> arr;
    int lucky, unlucky, count;
    int size_s = 0;
    int size_us = 0;
    float s_size = 0;
    float us_size = 0;
public:
    MyHashTable() {
        this->arr.resize(N);
        this->lucky = 0;
        this->unlucky = 0;
        this->count = 0;
    }

    unsigned short int str_to_int(std::string key) { //
        unsigned short int value = 0;
        unsigned short int temp;
        int n = key.length();
        if (n % 2) {
            key += " ";
            n++;
        }
        for (int i = 0; i < n / 2; i += 2) {
            temp = (unsigned short int) (key[i]);
            temp = temp << 8;
            temp = temp ^ (unsigned short int) (key[i + 1]);
            value += temp;
            value = value << 1;
        }
        return value;
    }

    int hashIt(const std::string &key) {
        unsigned short int value = this->str_to_int(key);
        int X;
        X = ((value * P) % st2) % N;
        return X;
    }

    int add(const std::string &key) {

        int num = this->hashIt(key);

        if (!this->arr[num].flag) {

            this->arr[num].flag = true;
            this->arr[num].key = key;

            this->lucky++;
            this->count++;

            this->size_s++;
            this->s_size++;

            return 1;
        } else {
            if (key != this->arr[num].key) {
                this->unlucky++;
                int c = this->hashIt(key);
                int tries = 1;
                for (int t = 1; t < N && c + t * t < N; t++) {
                    int i = c + t * t;
                    if (!this->arr[i].flag) {
                        this->arr[i].flag = true;
                        this->arr[i].key = key;
                        this->count++;
                        this->size_s++;
                        this->s_size += tries;
                        this->lucky++;
                        return 1;
                    } else if (this->arr[i].key == key) {
                        return -1;
                    }
                    this->unlucky++;
                    tries++;
                }
                this->us_size += tries;
                size_us++;
                return 0;
            } else {
//                this->lucky++;
                return -1;
            }
        }
    }


    bool isExsist(const std::string &key) {
        int num = hashIt(key);
        if (this->arr[num].flag && this->arr[num].key == key) {
            return true;
        } else {
            int c = this->hashIt(key);
            for (int t = 1; t < N && c + t * t < N; t++) {
                int i = c + t * t;
                if (this->arr[i].flag && this->arr[i].key == key) {
                    return true;
                }
            }
            return false;
        }
    }

    void prRes() {
        std::cout << this->lucky << "\t" << this->unlucky <<
                  "\t" << s_size / size_s << "\t" << us_size / size_us << "\n";
//        std::cout << this->lucky << "\t" << this->unlucky << "\t" << this->lucky + this->unlucky <<
//                  "\t" << this->count << "\t" << s_size / size_s << "\t" << us_size / size_us << "\n";
    }

    void prStat() {

    }
};


int main() {
    int zapp[11] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 95, 99};
    for (int j(0); j < 11; ++j) {
        std::fstream inp("input.txt", std::fstream::in);
        int st = zapp[j];
        int size = 1110;
        int zap = (int) (1110 * (st / 100.));
        MyHashTable a;
        for (int i(0); i < zap; ++i) {
            std::string tmp;
            inp >> tmp;
            a.add(tmp);
        }
        std::cout << st << ": ";
        a.prRes();
        inp.close();
    }
//    std::fstream out("output.txt", std::fstream::out);
}