#include<iostream>
#include"Node.h"
#include"math.h"
using namespace std;
typedef enum {
	RB, OST
} Mode;

template<typename T>
class Tree {
	int size;
	Mode mode;
	Node<T>* maximal;
	int sign(int n);
	int N(Node<T>* n);
	Node<T>* rotate(Node<T>* x, bool dir);
	void insertBST(Node<T>* z);
	void BSTinsertMax(Node<T>* z);
	// x->child[!dir] != NULL !!!
	void RBinsertFixup(Node<T>* z);
	void inorderWolk(Node<T>* x);
	int updateSizes(Node<T>* h);
	Node<T>* balanceR(Node<T>* h);
	Node<T>* longRotate(Node<T>* x, Node<T>* h);
	Node<T>* balanceIt(Node<T>* h);
	Node<T>* balanceMod(Node<T>* h);
	void colorTree(Node<T>* node, int maxHeight);
	int tree_to_vine(Node<T>* r);
	int fullSize(int size);
	void compression(Node<T>* root, int count);
	void vine_to_tree(Node<T>* root, int size);
	void updateParents (Node<T>* node, Node<T>* parent);
public:
	Node<T>* root;
	Tree();
	Tree(Mode m);
	~Tree();
	void insert(Node<T>* z);
	Node<T>* search(T k);
	int getSize() {
		return size;
	}
	Node<T>* getMaximal() {
		return maximal;
	}
	void insertMax(Node<T>* z);
	void destroyTree(Node<T>* node);
	Node<T>* select(Node<T>* node, int i);
	Node<T>* partR(Node<T>* h, int k);

	void setModeOST(void);
	void setModeRBT(void);
	void balance();
	void balanceMod();
	void balanceNew();
	void balanceDSW();
};

template<typename T>
Tree<T>::Tree() {
	root = NULL;
	maximal = NULL;
	mode = RB;
	size = 0;
}

template<typename T>
Tree<T>::Tree(Mode m) {
	root = NULL;
	maximal = NULL;
	mode = m;
	size = 0;
}

template<typename T>
Tree<T>::~Tree() {
	destroyTree(root);
}

template<typename T>
int Tree<T>::sign(int n) {
	if (n > 0)
		return 1;
	return 0;
}
template<typename T>
int Tree<T>::N(Node<T>* n) {
	if (mode == OST) {
		if (NULL == n)
			return 0;
		return n->bf;
	}
	cout << "You are in \"RB\" mode!" << endl;
	return 0;
}

template<typename T>
Node<T>* Tree<T>::rotate(Node<T>* x, bool dir) {
	Node<T>* y = x->child[!dir];
	x->child[!dir] = y->child[dir];
	if (NULL != y->child[dir])
		y->child[dir]->p = x;
	y->p = x->p;
	if (x->p == NULL)
		root = y;
	else
		x->p->child[x == x->p->child[1]] = y;
	y->child[dir] = x;
	x->p = y;
	if (mode == OST) {
		x->bf = N(x->child[0]) + N(x->child[1]) + 1;
		y->bf = N(y->child[0]) + N(y->child[1]) + 1;
	}
	return y;
}

template<typename T>
void Tree<T>::insertBST(Node<T>* z) {
	size++;
	Node<T>* x(root);
	Node<T>* y(NULL);
	while (NULL != x) {
		y = x;
		x = x->child[z->key >= x->key];
	}
	z->p = y;
	if (y == NULL)
		root = maximal = z;

	else {
		y->child[z->key >= y->key] = z;
		if (z->key > maximal->key)
			maximal = z;
	}
}
template<typename T>
void Tree<T>::BSTinsertMax(Node<T>* z) {
	size++;
	if (root == NULL)
		root = maximal = z;
	else {
		maximal->child[1] = z;
		z->p = maximal;
		maximal = z;
	}
}
template<typename T>
void Tree<T>::RBinsertFixup(Node<T>* z) {
	while (z != root && z->p->bf == 0) {
		bool side(z->p->key >= z->p->p->key);
		Node<T>* y = z->p->p->child[!side];
		if (NULL != y && y->bf == 0) {
			z->p->bf = 1;
			y->bf = 1;
			z->p->p->bf = 0;
			z = z->p->p;
			continue;
		}
		if (z == z->p->child[!side]) {
			z = z->p;
			rotate(z, side);
		}
		z->p->bf = 1;
		z->p->p->bf = 0;
		rotate(z->p->p, !side);
	}
	root->bf = 1;
}
template<typename T>
Node<T>* Tree<T>::search(T k) {
	Node<T>* x = root;
	while (NULL != x && k != x->key)
		x = x->child[k >= x->key];
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
void Tree<T>::insert(Node<T>* z) {
	if (mode == RB) {
		insertBST(z);
		RBinsertFixup(z);
	} else
		cout << "In OST mode insert is not allowed!" << endl;
}
template<typename T>
void Tree<T>::insertMax(Node<T>* z) {
	if (mode == RB) {
		BSTinsertMax(z);
		RBinsertFixup(z);
	} else
		cout << "In OST mode insert is not allowed!" << endl;
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
int Tree<T>::updateSizes(Node<T>* h) {
	if (h == NULL)
		return 0;

	int lN = updateSizes(h->child[0]);
	int rN = updateSizes(h->child[1]);
	h->bf = 1 + lN + rN;

	return h->bf;
}
template<typename T>
void Tree<T>::setModeOST(void) {
	mode = OST;
	updateSizes(root);
}

template<typename T>
void Tree<T>::setModeRBT(void) {
	mode = RB;
	int maxHeight = (int)log2(size);
	colorTree(root, maxHeight);
}

template<typename T>
void Tree<T>::colorTree(Node<T>* node, int maxHeight) {
	static int level = -1;
	if (node != NULL) {
		level++;
		node->bf = level < maxHeight ? 0 : 1;
		colorTree(node->child[0], maxHeight);
		colorTree(node->child[1], maxHeight);
		level--;
   }
}

template<typename T>
Node<T>* Tree<T>::select(Node<T>* node, int i) {
	if (mode == RB || i < 0 || i > node->bf) {
		cout << "Correct mode or order" << endl;
		return NULL;
	}
	int r = 1 + N(node->child[0]);
	if (i == r)
		return node;
	if (i < r)
		return select(node->child[0], i);
	return select(node->child[1], i - r);
}

template<typename T>
Node<T>* Tree<T>::partR(Node<T>* h, int k) {
	int t = N(h->child[0]);

	if (t != k) {
		int dir = (t < k) ? 1 : 0;
		h->child[dir] = partR(h->child[dir], k - dir * (t + 1));
		h = rotate(h, !dir);
	}
	return h;
}

template<typename T>
void Tree<T>::balance() {
	root = balanceR(root);
}

template<typename T>
Node<T>* Tree<T>::balanceR(Node<T>* h) {
	if (h == NULL || h->bf < 2)
		return h;

	h = partR(h, h->bf / 2);

	h->child[0] = balanceR(h->child[0]);
	if (NULL != h->child[0])
		h->child[0]->p = h;
	h->child[1] = balanceR(h->child[1]);
	if (NULL != h->child[1])
		h->child[1]->p = h;
	return h;
}

template<typename T>
Node<T>* Tree<T>::longRotate(Node<T>* x, Node<T>* h) {
	//Precondition: x != h, x is in sub-tree of h
	if (x == h)
		return h;

	Node<T>* tail[2] = { x->child[0], x->child[1] };
	T key = x->key;
	bool d = (x->key >= x->p->key);
	Node<T>* turn = x->p;

	while (1) {
		turn->child[d] = tail[!d];
		if (NULL != turn->child[d])
			turn->child[d]->p = turn;
		turn->bf = N(turn->child[0]) + N(turn->child[1]) + 1;

		while (turn != h && turn == turn->p->child[d]) {
			turn = turn->p;
			turn->bf = N(turn->child[0]) + N(turn->child[1]) + 1;
		}
		d = !d;
		tail[d] = turn;
		if (turn == h) {
			x->child[d] = tail[d];
			//if (NULL != x->child[d])		// ????
			x->child[d]->p = x;
			x->child[!d] = tail[!d];
			if (NULL != x->child[!d])
				x->child[!d]->p = x;
			x->bf = N(x->child[0]) + N(x->child[1]) + 1;
			x->p = h->p;			///////
			return x;
		}
		turn = turn->p;
		turn->bf = N(turn->child[0]) + N(turn->child[1]) + 1;
	}
}

template<typename T>
Node<T>* Tree<T>::balanceIt(Node<T>* h) {
	if (h == NULL || h->bf < 2)
		return h;
	Node<T>* x = select(h, h->bf / 2 + 1);
	h = longRotate(x, h);
	//  	cout << h->key << endl;             ////////////
	h->child[0] = balanceIt(h->child[0]);
//	h->child[0]->p = h->child[0];		//
	h->child[1] = balanceIt(h->child[1]);
//	h->child[1]->p = h->child[1];		///
	return h;
}
template<typename T>
void Tree<T>::balanceNew() {
	root = balanceIt(root);
}
template<typename T>
Node<T>* Tree<T>::balanceMod(Node<T>* h) {
	if (h == NULL || h->bf < 2)
		return h;

	int height = (int) log2(h->bf);

	if (h->bf <= 3 * (int) pow(2, height - 1) - 1) {

		h = partR(h, h->bf - (int) pow(2, height - 1) + 1 - 1);

		h->child[0] = balanceMod(h->child[0]);
		if (NULL != h->child[0])
			h->child[0]->p = h;
		h->child[1] = balanceR(h->child[1]);
		if (NULL != h->child[1])
			h->child[1]->p = h;
	} else {

		h = partR(h, (int) pow(2, height) - 1);

		h->child[0] = balanceR(h->child[0]);
		if (NULL != h->child[0])
			h->child[0]->p = h;
		h->child[1] = balanceMod(h->child[1]);
		if (NULL != h->child[1])
			h->child[1]->p = h;
	}

	return h;
}

template<typename T>
void Tree<T>::balanceMod() {
	root = balanceMod(root);
}

template<typename T>
int Tree<T>::tree_to_vine (Node<T>* r) {
   Node<T>* vineTail = r;
   Node<T>* remainder = vineTail->child[1];

   int size = 0;
   Node<T>* tempPtr;
   while (remainder != NULL) {
	  // თუ მარცხენა შვილი აღარ ჰყავს, იტერაცია გადადის მიმდინარე კვანძის მარჯვენა შვილზე
	  if (remainder->child[0] == NULL) {
		 vineTail = remainder;
		 remainder = remainder->child[1];
		 size++;
	  }
	  // შეამცირე მარცხენა ქვეხე მარჯვნივ მობრუნებით
	  else {
		  // მობრუნება მარჯვნივ
		 tempPtr = remainder->child[0];
		 remainder->child[0] = tempPtr->child[1];
		 tempPtr->child[1] = remainder;
		 remainder = tempPtr;
		 vineTail->child[1] = tempPtr;
	  }
   }

   return size;
}

template<typename T>
int Tree<T>::fullSize(int size) {
	int n = 1;
	while (n <= size) {
		n = n + n + 1;
	}
	return n / 2;
}

template<typename T>
void Tree<T>::compression(Node<T>* root, int count) {
	Node<T>* scanner = root;
	// მობრუნება მარცხნივ
	for (int i = 0; i < count; i++) {
		Node<T>* child = scanner->child[1];
		scanner->child[1] = child->child[1];
		scanner = scanner->child[1];
		child->child[1] = scanner->child[0];
		scanner->child[0] = child;
	}
}

template<typename T>
void Tree<T>::vine_to_tree(Node<T>* root, int size) {
	int fullCount = fullSize(size);
	compression(root, size - fullCount);
	for (size = fullCount; size > 1; size /= 2) {
		compression(root, size / 2);
	}
}

template<typename T>
void Tree<T>::updateParents(Node<T>* node, Node<T>* parent) {
	if (node != NULL) {
		updateParents(node->child[0], node);
		updateParents(node->child[1], node);
		node->p = parent;
	}
}

template<typename T>
void Tree<T>::balanceDSW () {
	Node<int>* pseudo_root = new Node<int>(-1);
	pseudo_root->child[1] = root;

	int size = tree_to_vine(pseudo_root);
	vine_to_tree(pseudo_root, size);

	root = pseudo_root->child[1];

	updateParents(root, NULL);
}
