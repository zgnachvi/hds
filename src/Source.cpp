#include<iostream>
#include<cstdlib>
#include "Node.h"
#include "RB.h"
#include "drawTree.h"

using namespace std;

static int MAX_KEY_VALUE = 1000 * 1000 * 1000;
static int MAX_TREE_SIZE = 100 * 1000 * 1000;

void balancingExample();
int calculateHeight(Node<int>*);
inline int Max(int, int);

double balancing_rbt_via_balanceDSW(int, bool);
double balancing_rbt_via_balanceR(int, bool);
double balancing_rbt_via_balanceMod(int, bool);

double getAverage(double *arr, int len);
double building_rbt_random(int, bool);
double building_rbt_inorder(int, bool);

double balancing_rbt_via_balanceDSW(int tree_size, bool print) {
	if (!tree_size || tree_size > MAX_TREE_SIZE) {
		cout << "Invalid tree size" << endl;
		return 0;
	}
	if (print) cout << "Balancing Red-black tree with " << tree_size << " nodes via \"DSW\" method" << endl;

	Tree<int> tree;
	clock_t start, finish;

	if (print) cout << "Test started..." << endl << endl;

	for (int i = 0; i < tree_size; i++) {
		Node<int>* node = new Node<int>(rand() % MAX_KEY_VALUE);
		tree.insert(node);
	}

	if (print) {
		cout << "tree size: " << tree.getSize();
		cout << "; tree height: " << calculateHeight(tree.root) << endl;

		cout << "balancing..." << endl;
	}
	start = clock();
	tree.balanceDSW();
	finish = clock();

	double time = ((double) (finish - start)) / 1000;

	if (print) {
		cout << "balanced in: " << time << " ms" << endl;

		cout << "tree size: " << tree.getSize();
		cout << "; tree height: " << calculateHeight(tree.root) << endl << endl;

		cout << "Test completed successfully!" << endl << endl;
	}

	return time;
}

double balancing_rbt_via_balanceR(int tree_size, bool print) {
	if (!tree_size || tree_size > MAX_TREE_SIZE) {
		cout << "Invalid tree size" << endl;
		return 0;
	}
	if (print) cout << "Balancing Red-black tree with " << tree_size << " nodes via \"balanceR\" method" << endl;

	Tree<int> tree;
	clock_t start, finish;

	if (print) cout << "Test started..." << endl << endl;

	for (int i = 0; i < tree_size; i++) {
		Node<int>* node = new Node<int>(rand() % MAX_KEY_VALUE);
		tree.insert(node);
	}

	if (print) {
		cout << "tree size: " << tree.getSize();
		cout << "; tree height: " << calculateHeight(tree.root) << endl;

		cout << "balancing..." << endl;
	}

	start = clock();
	tree.setModeOST();
	tree.balance();
	tree.setModeRBT();
	finish = clock();

	double time = ((double) (finish - start)) / 1000;

	if (print) {
		cout << "balanced in: " << time << " ms" << endl;

		cout << "tree size: " << tree.getSize();
		cout << "; tree height: " << calculateHeight(tree.root) << endl << endl;

		cout << "Test completed successfully!" << endl << endl;
	}

	return time;
}

double balancing_rbt_via_balanceMod(int tree_size, bool print) {
	if (!tree_size || tree_size > MAX_TREE_SIZE) {
		cout << "Invalid tree size" << endl;
		return 0;
	}

	if (print) cout << "Balancing Red-black tree with " << tree_size << " nodes via \"balanceMod\" method" << endl;

	Tree<int> tree;
	clock_t start, finish;

	if (print) cout << "Test started..." << endl << endl;

	for (int i = 0; i < tree_size; i++) {
		Node<int>* node = new Node<int>(rand() % MAX_KEY_VALUE);
		tree.insert(node);
	}


	if (print) {
		cout << "tree size: " << tree.getSize();
		cout << "; tree height: " << calculateHeight(tree.root) << endl;

		cout << "balancing..." << endl;
	}

	start = clock();
	tree.setModeOST();
	tree.balanceMod();
	tree.setModeRBT();
	finish = clock();

	double time = ((double) (finish - start)) / 1000;

	if (print) {
		cout << "balanced in: " << time << " ms" << endl;

		cout << "tree size: " << tree.getSize();
		cout << "; tree height: " << calculateHeight(tree.root) << endl << endl;

		cout << "Test completed successfully!" << endl << endl;
	}

	return time;
}

double building_rbt_random(int tree_size, bool print) {
	if (!tree_size || tree_size > MAX_TREE_SIZE) {
		cout << "Invalid tree size" << endl;
		return 0;
	}
	if (print) cout << "Building Red-black tree with " << tree_size << " nodes. Randomly" << endl;

	Tree<int> tree;
	clock_t start, finish;

	if (print) cout << "started..." << endl;
	start = clock();
	for (int i = 0; i < tree_size; i++) {
		Node<int>* node = new Node<int>(rand() % MAX_KEY_VALUE);
		tree.insert(node);
	}
	finish = clock();
	double time = ((double) (finish - start)) / 1000;

	if (print) {
		cout << "finished in: " << time << " ms" << endl;
		cout << "tree size: " << tree.getSize();
		cout << "; tree height: " << calculateHeight(tree.root) << endl << endl;
		cout << "Test completed successfully!" << endl << endl;
	}

	return time;
}

double building_rbt_inorder(int tree_size, bool print) {
	if (!tree_size || tree_size > MAX_TREE_SIZE) {
		cout << "Invalid tree size" << endl;
		return 0;
	}
	if (print) cout << "Building Red-black tree with " << tree_size << " nodes. Inorder" << endl;

	Tree<int> tree;
	clock_t start, finish;

	if (print) cout << "started..." << endl;

	start = clock();
	for (int i = 0; i < tree_size; i++) {
		Node<int>* node = new Node<int>(i);
		tree.insert(node);
	}
	finish = clock();
	double time = ((double) (finish - start)) / 1000;

	if (print) {
		cout << "finished in: " << time << " ms" << endl;

		cout << "tree size: " << tree.getSize();
		cout << "; tree height: " << calculateHeight(tree.root) << endl << endl;

		cout << "Test completed successfully!" << endl << endl;
	}

	return time;
}

int main() {
	srand(time(NULL));

	for (int i = 1000; i <= 100000; i *= 10) {
		int n = 10;
		double times[n];
		for (int j = 0; j < n; j++) {
			times[j] = building_rbt_random(i, false);
		}
		cout << "Average time: " << getAverage(times, n) << endl << endl;

		building_rbt_inorder(i, false);
		balancing_rbt_via_balanceR(i, false);
		balancing_rbt_via_balanceMod(i, false);
		balancing_rbt_via_balanceDSW(i, false);
	}

}

double getAverage (double *arr, int len) {
	double sum = 0;
	for (int i=0; i<len; i++) {
		sum += arr[i];
	}
	return sum / len;
}

void balancingExample() {
	Tree<int> t;
	for (int i = 0; i < 27; ++i) {
		Node<int>* n = new Node<int>(rand() % 555);
		t.insert(n);
	}
	freopen("data.out", "w", stdout);

	t.setModeOST();
	pretty_print_tree(t.root);

	t.balance();
	pretty_print_tree(t.root);
}

int calculateHeight(Node<int>* node) {
	if (node != NULL) {
		return 1
				+ Max(calculateHeight(node->child[0]),
						calculateHeight(node->child[1]));
	}
	return 0;
}

int calculateSize(Node<int>* node) {
	if (node != NULL) {
		return 1 + calculateSize(node->child[0]) + calculateSize(node->child[1]);
	}
	return 0;
}

inline int Max(int l, int r) {
	return l > r ? l : r;
}
