#ifndef NODE_H
#define NODE_H
template<typename T>
struct Node
{
    T key;
    Node* p;    
    Node* child[2];
    int bf; //balance factor   
    Node();   
    Node(T keyValue);  
};
template<typename T>
Node<T>::Node(T keyValue)
{
    key = keyValue;
    p = NULL;
    child[0] = NULL;
    child[1] = NULL;
    bf = 0;    //red, or balanced
}
template<typename T>
Node<T>::Node()
{
    p = NULL;
    child[0] = NULL;
    child[1] = NULL;
    bf = 0;    //black leaf
}
#endif