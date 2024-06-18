#include <iostream>
#define PrintKey
#define DEBUG
#include "component/AVL.h"
#include "component/Hash.h"

void DemoAVL() {
    AVL<int, int> avl;
    for (int i = 0; i < 6; i++) {
        avl.Push(0 + rand() % 24, rand() % 10);
    }
    std::cout << avl << '\n';
    int key{ 0 };

    while (key != -1) {
        std::cout << "Delete key: ";
        std::cin >> key;
        avl.Pop(key);
        std::cout << avl << '\n';
    }
}


class MyFunc : public UFuncForHash<char>{
    virtual int GetHash(const char& key) {
        return key-'a';
    }
};

int main()
{
    Hash<char, int> hash(10);
    int b = 1;
    char a = 'a';
    hash.SetHashFunction(new MyFunc());
    for(int i =0;i<50;i++)
        hash.Push(a++, b++);

    hash.Print();

    char key;
    std::cout << "Key: ";
    std::cin >> key;
    std::cout << hash.Search(key);
}
