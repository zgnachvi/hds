#include<iostream>
#include<cstdlib>
#include "Node.h"
#include "RB.h"
#include "drawTree.h"
#include "RBT.cpp"

using namespace std;

static int MAX_KEY_VALUE = 1000 * 1000 * 1000;
static int MAX_TREE_SIZE = 100 * 1000 * 1000;

void balancingExample();
int calculateHeight(Node<int>*);
inline int Max(int, int);

double balancing_rbt_via_balanceDSW(int, bool, bool);
double balancing_rbt_via_balanceR(int, bool, bool);
double balancing_rbt_via_balanceMod(int, bool, bool);

double getAverage(double *arr, int len);
double building_rbt_random(int, bool);
double building_rbt2_random(int, bool);
double building_rbt_inorder(int, bool);
double building_rbt2_inorder(int, bool);

void runBuildRBTRandom(int, int, bool);
void runBuildRBT2Random(int, int, bool);

void runBuildRBTInorder(int, int, bool);
void runBuildRBT2Inorder(int, int, bool);

void runBalanceDSWInorder(int, int, bool);
void runBalanceRInorder(int, int, bool);
void runBalanceModInorder(int, int, bool);

void runBalanceDSWRandom(int, int, bool);
void runBalanceRRandom(int, int, bool);
void runBalanceModRandom(int, int, bool);

double balancing_rbt_via_balanceDSW(int tree_size, bool print, bool inorder) {
	if (!tree_size || tree_size > MAX_TREE_SIZE) {
		cout << "Invalid tree size" << endl;
		return 0;
	}
	if (print) cout << "Balancing Red-black tree with " << tree_size << " nodes via \"DSW\" method" << endl;

	Tree<int> tree;
	clock_t start, finish;

	if (print) cout << "Test started..." << endl << endl;

	for (int i = 0; i < tree_size; i++) {
		Node<int>* node = new Node<int>(inorder ? i : rand() % MAX_KEY_VALUE);
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

double balancing_rbt_via_balanceR(int tree_size, bool print, bool inorder) {
	if (!tree_size || tree_size > MAX_TREE_SIZE) {
		cout << "Invalid tree size" << endl;
		return 0;
	}
	if (print) cout << "Balancing Red-black tree with " << tree_size << " nodes via \"balanceR\" method" << endl;

	Tree<int> tree;
	clock_t start, finish;

	if (print) cout << "Test started..." << endl << endl;

	for (int i = 0; i < tree_size; i++) {
		Node<int>* node = new Node<int>(inorder ? i : rand() % MAX_KEY_VALUE);
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

double balancing_rbt_via_balanceMod(int tree_size, bool print, bool inorder) {
	if (!tree_size || tree_size > MAX_TREE_SIZE) {
		cout << "Invalid tree size" << endl;
		return 0;
	}

	if (print) cout << "Balancing Red-black tree with " << tree_size << " nodes via \"balanceMod\" method" << endl;

	Tree<int> tree;
	clock_t start, finish;

	if (print) cout << "Test started..." << endl << endl;

	for (int i = 0; i < tree_size; i++) {
		Node<int>* node = new Node<int>(inorder ? i : rand() % MAX_KEY_VALUE);
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

double building_rbt2_random(int tree_size, bool print) {
	if (!tree_size || tree_size > MAX_TREE_SIZE) {
		cout << "Invalid tree size" << endl;
		return 0;
	}
	if (print) cout << "Building Red-black tree with " << tree_size << " nodes. Randomly" << endl;

	RBT* tree = new RBT();
	clock_t start, finish;

	if (print) cout << "started..." << endl;
	start = clock();
	for (int i = 0; i < tree_size; i++) {
		tree->insert(rand() % MAX_KEY_VALUE);
	}
	finish = clock();
	double time = ((double) (finish - start)) / 1000;

	if (print) {
		cout << "finished in: " << time << " ms" << endl;
		cout << "tree size: " << tree->getSize();
		cout << "; tree height: " << tree->getHeight() << endl << endl;
		cout << "Test completed successfully!" << endl << endl;
	}

	tree->destroy();

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

double building_rbt2_inorder(int tree_size, bool print) {
	if (!tree_size || tree_size > MAX_TREE_SIZE) {
		cout << "Invalid tree size" << endl;
		return 0;
	}
	if (print) cout << "Building Red-black tree with " << tree_size << " nodes. Inorder" << endl;

	RBT* tree = new RBT();
	clock_t start, finish;

	if (print) cout << "started..." << endl;

	start = clock();
	for (int i = 0; i < tree_size; i++) {
		tree->insert(i);
	}
	finish = clock();
	double time = ((double) (finish - start)) / 1000;

	if (print) {
		cout << "finished in: " << time << " ms" << endl;
		cout << "tree size: " << tree->getSize();
		cout << "; tree height: " << tree->getHeight() << endl << endl;
		cout << "Test completed successfully!" << endl << endl;
	}

	tree->destroy();

	return time;
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

int main() {
	srand(time(NULL));
	int start = MAX_TREE_SIZE;
	int n = 20;
	bool print = true;

	runBalanceDSWInorder(start, n, print);
	runBalanceRInorder(start, n, print);
	runBalanceModInorder(start, n, print);

	runBalanceDSWRandom(start, n, print);
	runBalanceRRandom(start, n, print);
	runBalanceModRandom(start, n, print);
}

// in-order
void runBalanceDSWInorder (int start, int n, bool print) {
	double times[n];
	for (int i = start; i <= MAX_TREE_SIZE; i *= 10) {
		for (int j = 0; j < n; j++) {
			times[j] = balancing_rbt_via_balanceDSW(i, print, true);
		}
		cout << "Balancing in-order built RBT (";
		cout << i << " nodes) ";
		cout << "via balanceDSW method... Tests run "<< n;
		cout <<" times. Average time: " << getAverage(times, n) << " milliseconds." << endl << endl;
	}
}

void runBalanceRInorder (int start, int n, bool print) {
	double times[n];
	for (int i = start; i <= MAX_TREE_SIZE; i *= 10) {
		for (int j = 0; j < n; j++) {
			times[j] = balancing_rbt_via_balanceR(i, print, true);
		}
		cout << "Balancing in-order built RBT (";
		cout << i << " nodes) ";
		cout << "via balanceR method... Tests run "<< n;
		cout <<" times. Average time: " << getAverage(times, n) << " milliseconds." << endl << endl;
	}
}

void runBalanceModInorder (int start, int n, bool print) {
	double times[n];
	for (int i = start; i <= MAX_TREE_SIZE; i *= 10) {
		for (int j = 0; j < n; j++) {
			times[j] = balancing_rbt_via_balanceMod(i, print, true);
		}
		cout << "Balancing in-order built RBT (";
		cout << i << " nodes) ";
		cout << "via balanceMod method... Tests run "<< n;
		cout <<" times. Average time: " << getAverage(times, n) << " milliseconds." << endl << endl;
	}
}


// random
void runBalanceDSWRandom (int start, int n, bool print) {
	double times[n];
	for (int i = start; i <= MAX_TREE_SIZE; i *= 10) {
		for (int j = 0; j < n; j++) {
			times[j] = balancing_rbt_via_balanceDSW(i, print, false);
		}
		cout << "Balancing randomly built RBT (";
		cout << i << " nodes) ";
		cout << "via balanceDSW method... Tests run "<< n;
		cout <<" times. Average time: " << getAverage(times, n) << " milliseconds." << endl << endl;
	}
}

void runBalanceRRandom (int start, int n, bool print) {
	double times[n];
	for (int i = start; i <= MAX_TREE_SIZE; i *= 10) {
		for (int j = 0; j < n; j++) {
			times[j] = balancing_rbt_via_balanceR(i, print, false);
		}
		cout << "Balancing randomly built RBT (";
		cout << i << " nodes) ";
		cout << "via balanceR method... Tests run "<< n;
		cout <<" times. Average time: " << getAverage(times, n) << " milliseconds." << endl << endl;
	}
}

void runBalanceModRandom (int start, int n, bool print) {
	double times[n];
	for (int i = start; i <= MAX_TREE_SIZE; i *= 10) {
		for (int j = 0; j < n; j++) {
			times[j] = balancing_rbt_via_balanceMod(i, print, false);
		}
		cout << "Balancing randomly built RBT (";
		cout << i << " nodes) ";
		cout << "via balanceMod method... Tests run "<< n;
		cout <<" times. Average time: " << getAverage(times, n) << " milliseconds." << endl << endl;
	}
}


// build
void runBuildRBTRandom (int start, int n, bool print) {
	double times[n];
	for (int i = start; i <= MAX_TREE_SIZE; i *= 10) {
		for (int j = 0; j < n; j++) {
			times[j] = building_rbt_random(i, print);
		}
		cout << "Building RBT(children array) randomly (" << i << " nodes)... ";
		cout << "Tests run "<< n << " times. ";
		cout << "Average time: " << getAverage(times, n) << " milliseconds." << endl << endl;
	}
}

void runBuildRBT2Random (int start, int n, bool print) {
	double times[n];
	for (int i = start; i <= MAX_TREE_SIZE; i *= 10) {
		for (int j = 0; j < n; j++) {
			times[j] = building_rbt2_random(i, print);
		}
		cout << "Building RBT(left/right) randomly (" << i << " nodes)... ";
		cout << "Tests run "<< n << " times. ";
		cout << "Average time: " << getAverage(times, n) << " milliseconds." << endl << endl;
	}
}

void runBuildRBTInorder (int start, int n, bool print) {
	double times[n];
	for (int i = start; i <= MAX_TREE_SIZE; i *= 10) {
		for (int j = 0; j < n; j++) {
			times[j] = building_rbt_inorder(i, print);
		}
		cout << "Building RBT(children array) in-order (" << i << " nodes)... ";
		cout << "Tests run "<< n << " times. ";
		cout << "Average time: " << getAverage(times, n) << " milliseconds." << endl << endl;
	}
}

void runBuildRBT2Inorder (int start, int n, bool print) {
	double times[n];
	for (int i = start; i <= MAX_TREE_SIZE; i *= 10) {
		for (int j = 0; j < n; j++) {
			times[j] = building_rbt2_inorder(i, print);
		}
		cout << "Building RBT(left/right) in-order (" << i << " nodes)... ";
		cout << "Tests run "<< n << " times. ";
		cout << "Average time: " << getAverage(times, n) << " milliseconds." << endl << endl;
	}
}
