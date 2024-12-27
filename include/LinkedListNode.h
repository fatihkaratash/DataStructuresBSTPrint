/**

*/

#ifndef LINKEDLISTNODE_H
#define LINKEDLISTNODE_H

#include "BST.h"

class LinkedListNode {
public:
    BST* bst;
    LinkedListNode* sonraki;

    LinkedListNode() {
        bst = new BST();
        sonraki = nullptr;
    }
    
    ~LinkedListNode() {
        if (bst) {  
            delete bst;
            bst = nullptr;
        }
    }
};

#endif
