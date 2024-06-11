#include <iostream>
#define PrintKey
#define DEBUG
#include "AVL.h"

int main()
{
    AVL<int,int> avl;
    for (int i = 0; i < 20; i++) {
        avl.Push(0 + rand() % 24, rand() % 10);
        //std::cout << avl << '\n';
    }
    //std::cout << avl << '\n';
    std::cout  << avl;
    //std::cout << "press key to delete: ";
    //int key;
    //std::cin >> key;
    //avl.Pop(key);

    //std::cout << avl << '\n';
}
