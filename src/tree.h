#include <iostream>
#include <random>
#include "math.h"
#include "Node.h"
using namespace std;

template<typename T>
class Tree {
	int size;
	int sign(int n);
	int N(Node<T>* n);
	Node<T>* ostRotate(Node<T>* x, bool dir);
	void inorderWolk(Node<T>* x);
	Node<T>* insert_R(Node<T>* p, T k);
	Node<T>* insert_T(Node<T>* p, T k);
	Node<T>* balanceR(Node<T>* h);
	Node<T>* partR(Node<T>* h, int k);
	Node<T>* balanceMod(Node<T>* h);
public:
	Node<T>* root;
	Tree();
	~Tree();
	void insert(T k);
	Node<T>* search(T k);
	Node<T>* getRoot(){ return root; }
	int getSize() 	{ return size; }
	void destroyTree(Node<T>* node);
	Node<T>* select(Node<T>* node, int i);
	void checkNode(Node<T>* x);
	int height(Node<T>* x);
	void balance();
	void balanceMod();
};

 //aq n-ic gvinda, radgan ar vicit romel xeshi cavardeba
template<typename T>
Node<T>* Tree<T>::insert_T(Node<T>* p, T k) {
	if (p == NULL) return  new Node<T>(k);
	bool d = (k >= p->key);
	p->child[d] = insert_T(p->child[d], k);
	p = ostRotate(p, !d);
	return p;
}
template<typename T>
Node<T>* Tree<T>::insert_R(Node<T>* p, T k) {
	static default_random_engine dre;					
	static uniform_real_distribution<double> rdi;		
	if (p == NULL) return   new Node<T>(k);
	if (rdi(dre) < 1.0 / (N(p) + 1))
            return insert_T(p, k);
	bool d = (k >= p->key);
	p->child[d] = insert_R(p->child[d], k);
	(p->bf)++;
	return p; 
}
template<typename T>
void Tree<T>::insert(T k) {
	root = insert_R(root, k);
}
template<typename T>
Node<T>* Tree<T>::ostRotate(Node<T>* x, bool dir) {
	Node<T>* y = x->child[!dir];
	x->child[!dir] = y->child[dir];
	
	y->child[dir] = x;

	x->bf = N(x->child[0]) + N(x->child[1]) + 1;
	y->bf = N(y->child[0]) + N(y->child[1]) + 1;

	return y;
}

template<typename T>
Tree<T>::Tree() {
	root = NULL;
	size = 0;
}

template<typename T>
Tree<T>::~Tree() {
	destroyTree(root);
}

template<typename T>
int Tree<T>::sign(int n) {
	if (n > 0) {
            return 1;
        }
	return 0;
}

template<typename T>
int Tree<T>::N(Node<T>* n) {
	if (NULL == n) return 0;
	return n->bf;
}

template<typename T>
Node<T>* Tree<T>::search(T k) {
	Node<T>* x = root;
	while (NULL != x && k != x->key) {
		x = x->child[k >= x->key];
        }
	return x;
}
template<typename T>
void Tree<T>::inorderWolk(Node<T>* x) {
	if (NULL != x) {
		inorderWolk(x->child[0]);
		cout << x->key << "\t";
		inorderWolk(x->child[1]);
	}
}

template<typename T>
void Tree<T>::destroyTree(Node<T>* node) {
	if (node != NULL) {
		destroyTree(node->child[1]);
		destroyTree(node->child[0]);
		delete node;
	}
}

template<typename T>
Node<T>* Tree<T>::select(Node<T>* node, int i)
{
	if (i<0 || i > node->bf) {
		cout << "Correct order!" << endl;
		return NULL;
	}
	int r = 1 + N(node->child[0]);
	if (i == r) return node;
	if (i < r) return select(node->child[0], i);
	return select(node->child[1], i - r);
}

template<typename T>
int Tree<T>::height(Node<T>* x) {
	if (NULL == x) {
            return -1;
        }
	int u = height(x->child[0]);
	int v = height(x->child[1]);
	return (u < v) ? (v + 1) : (u + 1);
}

template<typename T>
void Tree<T>::checkNode(Node<T>* x) {
	if (NULL != x) cout << x->key << endl;
	if (NULL != x->child[0]) cout << x->child[0]->key << endl;
	if (NULL != x->child[1]) cout << x->child[1]->key << endl;
}

template<typename T>
void Tree<T>::balance() {
	root = balanceR(root);
}

template<typename T>
Node<T>* Tree<T>::balanceR(Node<T>* h)
{
	if (h == NULL || h->bf < 2) {
            return h;
        }
	h = partR(h, h->bf / 2);
	h->child[0] = balanceR(h->child[0]);
	h->child[1] = balanceR(h->child[1]);
        
	return h;
}
template<typename T>
Node<T>* Tree<T>::partR(Node<T>* h, int k) {
	int t = N(h->child[0]);
	if (t != k) {
		int dir = (t < k) ? 1 : 0;
		h->child[dir] = partR(h->child[dir], k - dir*(t + 1));
		h = ostRotate(h, !dir);
	}
	return h;
}
template<typename T>
void Tree<T>::balanceMod() {
	root = balanceMod(root);
}

template<typename T>
Node<T>* Tree<T>::balanceMod(Node<T>* h) {
	if (h == NULL || h->bf < 2) return h;

	int height = (int)log2(h->bf);
	if (h->bf <= 3 * (int)pow(2, height - 1) - 1) {
		h = partR(h, h->bf - (int)pow(2, height - 1));
		h->child[1] = balanceR(h->child[1]);
		h->child[0] = balanceMod(h->child[0]);
	} else {
		h = partR(h, (int)pow(2, height) - 1);
		h->child[1] = balanceMod(h->child[1]);
		h->child[0] = balanceR(h->child[0]);
	}
	return h;
}