//
// Created by Антон Донской on 2018-12-09.
//


#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

#define N 1024
#define P 257
#define st2 65535


struct Pair {
    bool flag = false;
    std::string key = "";
};

class MyHashTable {
private:
    std::vector<Pair> arr;
public:
    MyHashTable() {
        arr.resize(N);
    }

    unsigned short int str_to_int(std::string key) {
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
        unsigned short int value = str_to_int(key);
        int X;
        X = ((value * P) % st2) % N;
        return X;
    }

};


//int main2() {
//    Pair htable[N];
//
//    ifstream fin;
//    fin.open("Lab4.txt", ios::in);
//
//    ofstream fout;
//    fout.open("results_Lab4.txt", ios::out);
//
//    string key;
//    double count = 0;
//    int n = N / 10;
//    int lucky = 0, unlucky = 0, num;
//
//    for (int j = 1; j <= 10; j++) {
//        for (int i = 0; i < n; i++) {
//            fin >> key;
//            num = hashIt(key);
//            if (0 <= num && num < N)
//                /*cout << "num = ok! "*/;
//            else {
//                cout << "\nnum = DANGER! ";
//                system("pause");
//            }
//            if (!htable[num].flag) {
//                htable[num].flag = true;
//                htable[num].key = key;
//                lucky++;
//                count++;
//            } else {
//                if (key != htable[num].key) {
//                    unlucky++;
//                    int c = hh(key);
//                    if (0 < c && c < N)
//                        /*cout << "c = ok! "*/;
//                    else {
//                        cout << "\n c = DANGER! ";
//                        system("pause");
//                    }
//                    for (int t = 1; t < N; t++) {
//                        int ind = (num + t * c) % N;
//                        if (!htable[ind].flag) {
//                            htable[ind].flag = true;
//                            htable[ind].key = key;
//                            count++;
//                            t = N;
//                        } else if (htable[ind].key == key) t = N;
//                    }
//                } else lucky++;
//            }
//        }
//        fout << count / N << ' ' << lucky << ' ' << unlucky << endl;
//        lucky = 0;
//        unlucky = 0;
//    }
//
//    for (int i = 0; i < 1024; i++)
//        cout << i << ' ' << htable[i].key << endl;
//    cin >> key;
//    num = hashIt(key);
//    cout << num << endl;
//    if (key == htable[num].key)
//        cout << num << ' ' << key << endl;
//    else {
//        int c = hh(key);
//        if (0 < c && c < N)
//            /*cout << "c = ok! "*/;
//        else {
//            cout << "\n c = DANGER! ";
//            system("pause");
//        }
//        for (int t = 1; t < N; t++) {
//            int ind = (num + t * c) % N;
//            cout << ind << endl;
//            if (htable[ind].key == key) {
//                cout << ind << ' ' << key << endl;
//                t = N;
//            }
//        }
//    }
//}

int main() {
//    main2();
}