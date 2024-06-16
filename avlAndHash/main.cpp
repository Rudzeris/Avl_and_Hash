#include <iostream>
#define PrintKey
#define DEBUG
#include "component/AVL.h"

int main()
{
    AVL<int,int> avl;
    for (int i = 0; i < 6; i++) {
        avl.Push(0 + rand() % 24, rand() % 10);
    }
    std::cout  << avl << '\n';
    int key{0};
    
    while (key != -1) {
        std::cout << "Delete key: ";
        std::cin >> key;
        avl.Pop(key);
        std::cout << avl << '\n';
    }
}
