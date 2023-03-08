#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <algorithm>
#include <iostream>
#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int calculateHeightIfBalanced(Node* root);


bool equalPaths(Node * root)
{
    // Add your code below
<<<<<<< HEAD
  int l, r = 0;
	if (root == nullptr)
	{
		return true;
	}

	l = calculateHeightIfBalanced(root->left);
	r = calculateHeightIfBalanced(root->right);

	if ((l == r) || ((l == 1  && r == 0) || (l == 0 && r == 1))) return true;


	return false;

}

int calculateHeightIfBalanced(Node* root)
{
  if (root == nullptr)
	{
		return 0;
	}

  return 1 + std::max(calculateHeightIfBalanced(root->left), calculateHeightIfBalanced(root->right));
=======
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
>>>>>>> d6904dcf54fbc6bdfdbef4711fb1f708e0224429
    
}

