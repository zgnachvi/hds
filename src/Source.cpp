#include<iostream>
#include<cstdlib>
#include "Node.h"
#include "RB.h"
#include "drawTree.h"
#include <stdio.h>
using namespace std;

int main()
{
	Tree<int> t;
	for (int i = 0; i <27; ++i)
	{
		Node<int>* n = new Node<int>(rand() % 555);
		t.insert(n);
	}
	freopen("data.out", "w", stdout);

	t.setModeOST();
	pretty_print_tree(t.root);

	t.balance();

	pretty_print_tree(t.root);
}