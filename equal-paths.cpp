#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int calculateHeightIfBalanced(Node* root);


bool equalPaths(Node * root)
{
    // Add your code below
    int l, r = 0;

	l = calculateHeightIfBalanced(root->left);
	r = calculateHeightIfBalanced(root->right);

	if (l == r)
	{
		return true;
	}


	return false;

}

int calculateHeightIfBalanced(Node* root)
{
    if (root == nullptr)
	{
		return 0;
	}
    return 1 + std::max(calculateHeightIfBalanced(root->left), calculateHeightIfBalanced(root->right));
    
}

