#include <iostream>
#include "btree/btree.h"

int main(int, char**){
    BTree<int> btree(3);
    btree.Insert(10);
    // btree.Insert(20);
    // btree.Insert(30);

    // btree.Print();

    std::cout << btree.Search(10) << std::endl;

    return 0;
}
