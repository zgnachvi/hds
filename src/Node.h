#ifndef NODE_H
#define NODE_H
template<typename T>
struct Node {
    T key;  
    Node* child[2];
    int bf; //balance factor   
    Node();   
    Node(T keyValue);  
};

template<typename T>
Node<T>::Node(T keyValue) {
    key = keyValue;
    child[0] = NULL;
    child[1] = NULL;
    bf = 1;    //red, or balanced
}

template<typename T>
Node<T>::Node() {
    child[0] = NULL;
    child[1] = NULL;
    bf = 1; //black leaf
}
#endif