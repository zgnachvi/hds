#include <iostream>
#include <cstdlib>
#include <fstream>
#include "RBTNode.cpp"

using namespace std;

class RBT {
public:
    RBTNode* root;

    RBT () {
		root = NULL;
	}

	int insertNode(RBTNode* z) {
		RBTNode* y = NULL;
		RBTNode* x = root;

		while (x != NULL) {
			y = x;
			if (z->key < x->key) {
				x = x->left;
			} else {
				x = x->right;
			}
		}
		z->parent = y;
		if (y == NULL) {
			root = z;
		} else if (z->key < y->key) {
			y->left = z;
		} else if (z->key > y->key) {
			y->right = z;
		} else {
			return 0;
		}
		z->color = 1;

		insertFixup(z);

		return 1;
	}

	int insert (int key) {
		return insertNode(new RBTNode(key));
	}

	void insertFixup(RBTNode* z) {
		while (z->parent != NULL && z->parent->color == 1) {
			if (z->parent == z->parent->parent->left) {
				RBTNode* y = z->parent->parent->right;
				if (y != NULL && y->color == 1) {
					z->parent->color = 0;
					y->color = 0;
					z->parent->parent->color = 1;
					z = z->parent->parent;
				} else {
					if (z == z->parent->right) {
						z = z->parent;
						rotateLeft(z);
					}

					if (z->parent != NULL) {
						z->parent->color = 0;
						if (z->parent->parent != NULL) {
							z->parent->parent->color = 1;
							rotateRight(z->parent->parent);
						}
					}
				}
			} else {
				RBTNode* y = z->parent->parent->left;
				if (y != NULL && y->color == 1) {
					z->parent->color = 0;
					y->color = 0;
					z->parent->parent->color = 1;
					z = z->parent->parent;
				} else {
					if (z == z->parent->left) {
						z = z->parent;
						rotateRight(z);
					}
					if (z->parent != NULL) {
						z->parent->color = 0;
						if (z->parent->parent != NULL) {
							z->parent->parent->color = 1;
							rotateLeft(z->parent->parent);
						}
					}
				}
			}
		}
		root->color = 0;
	}

	void rotateLeft(RBTNode* x) {
		RBTNode* y = x->right;
		x->right = y->left;
		if (y->left != NULL) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == NULL) {
			root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->left = (x);
		x->parent = y;
	}

	void rotateRight(RBTNode* x) {
		RBTNode* y = x->left;
		x->left = (y->right);
		if (y->right != NULL) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == NULL) {
			root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->right = x;
		x->parent = y;
	}

	virtual ~RBT() {};

	inline int Max( int l, int r) {
		return l > r ? l : r;
	}

	int count (RBTNode* node) {
		if (node == NULL) {
			return 0;
		} else {
			return 1 + count(node->left) + count(node->right);
		}
	}

	int getSize () {
		return count(root);
	}

	int calculateHeight (RBTNode* node) {
		if (node == NULL) {
			return 0;
		} else {
			return 1 + Max (calculateHeight(node->left), calculateHeight(node->right));
		}
	}

	int getHeight () {
		return calculateHeight(root);
	}

	void destroy () {
		destroyTree(root);
	}

	void destroyTree(RBTNode* node) {
		if (node != NULL) {
			destroyTree(node->left);
			destroyTree(node->right);
			delete node;
		}
	}
};
