#include <cassert>
#include "Rope.h"
#include <algorithm>

// Should advance to the next Node using in-order traversal
// It can point at any Node, not just leaves
// Operator++ was implemented in the lecture
rope_iterator &rope_iterator::operator++()
{
	//  if i have right subtree, find left most element of those
	if (ptr_->right != NULL)
	{ 
		ptr_=ptr_->right; 
		while (ptr_->left != NULL) { ptr_ = ptr_->left; }
	}
	else
	{
		// Keep going up as long as I'm my parent's right child
		while (ptr_->parent && ptr_->parent->right == ptr_)
		{ ptr_ = ptr_->parent; }
		// Go up one more time
		ptr_ = ptr_->parent;
	}
	return *this;
}

// Point to the first Node for in-order traversal
rope_iterator Rope::begin() const
{
	// Keep going left until we reach the leaf node
	if(!root) {return rope_iterator(nullptr);}
	Node *tmp = root;
	while (tmp->left != nullptr) { tmp = tmp->left; }
	return rope_iterator(tmp);
}

Rope::Rope()
{
	//default constructor
	size_ = 0;
	root = nullptr;
}

// Should make the root = p and adjust any member variables
// This should not make a copy of the rope with root at p,
// it should just "steal" the Node*
Rope::Rope(Node *p)
{
	//copy root and size
	root = p;
	int newsize = 0;
	updatesize(p, newsize);
	size_ = newsize;
}

void Rope::destroy_tree(Node *ptr)
{
	if (ptr == nullptr) { return;}
	// Recursively deletes all the children nodes through a
	// post order traversal
	destroy_tree(ptr->left);
	destroy_tree(ptr->right);
	delete ptr;
	size_ = 0;
}

Rope::~Rope()
{
	//post order traversal destructor
	this->destroy_tree(root);
	root = nullptr;
}

//Constructor which copies the root of the tree as well as the size
Rope::Rope(const Rope &r)
{
	//copy tree and size
	root = copy_tree(r.expose_root(), nullptr);
	int newsize = 0;
	updatesize(r.expose_root(), newsize);
	size_ = newsize;
}

// Assignment operator
Rope &Rope::operator=(const Rope &r)
{
	if (this != &r)
	{
		//destroy tree
		this->destroy_tree(root);
		//copy tree
		root = copy_tree(r.expose_root(), nullptr);
		//update size
		int newsize = 0;
		updatesize(r.expose_root(), newsize);
		size_ = newsize;
	}
	return *this;
}

Node* Rope::copy_tree(Node *rootptr, Node *parentptr)
{
	// Checks if the current pointer of the tree is null
	if (!rootptr) { return nullptr;}
	// Creates a new node and copies the value and weight
	Node *tmp = new Node();
	tmp->value = rootptr->value;
	tmp->weight = rootptr->weight;
	// Recursively moves to the left and to the right, tmp will
	// essentially be the parentptr in the recursive call (Pre-Order)
	tmp->left = copy_tree(rootptr->left, tmp);
	tmp->right = copy_tree(rootptr->right, tmp);
	// Copies the parent pointer as well
	tmp->parent = parentptr;
	return tmp;
}

Node* Rope::findindex(int& index) const
{
	Node *tmp = root;
	// Loops through the tree until the leaf node is reached
	while (tmp->left != nullptr || tmp->right != nullptr)
	{
		// Index is larger than the weight of the current node
		if (index >= tmp->weight) { index -= tmp->weight; tmp = tmp->right; }
		// Index is smaller than the weight of the current node
		else { tmp = tmp->left; }
	}
	return tmp;
}

// Get a single character at index i
bool Rope::index(int i, char &c) const
{
	if (!root) { return false; }
	// Invalid index
	int thesize = 0;
	updatesize(root, thesize);
	if (i > thesize || i < 0) { return false; }
	// Loops through the tree until the leaf node is reached
	Node *tmp = findindex(i);
	// Returns the index of the string at the leaf node
	c = tmp->value[i];
	return true;
}

// Add the other rope (r)'s string to the end of my string
void Rope::concat(const Rope &r)
{
	if(size_ == 0) {*this = r; return;} 
	//Create a new root and connect it to the left and right roots.
	Node* tmp = new Node();
	tmp->left = root;
	//Creates a copy of the right tree to prevent memory from being free twice
	tmp->right = copy_tree(r.expose_root(), tmp);
	root->parent = tmp;
	tmp->right->parent = tmp;
	int newsize = 0;
	//Update size and update the root
	updatesize(r.expose_root(), newsize);
	size_ += newsize;
	int concatsize = 0;
	updatesize(root, concatsize);
	tmp->weight = concatsize;
	root = tmp;
}

void Rope::concat_no_copy(Rope& r1, Rope& r2)
{
	//Nothing to concat for root1, so essentially make rope 2 into rope 1
	if(r1.size_== 0) 
	{ 
		r1.root = r2.root; 
		r2.root = nullptr; 
		r1.size_ = r2.size_;
		r2.size_ = 0;
		return; 
	}
	//Nothing to concat
	if(r2.size_== 0) { return; }
	//Create a new root and connect it to the left and right roots.
	Node* tmp = new Node();
	tmp->left = r1.root;
	tmp->right = r2.root;
	r1.root->parent = tmp;
	r2.root->parent = tmp;	
	int concatsize = 0;
	//Update the size and pointers
	updatesize(r1.root, concatsize);
	tmp->weight = concatsize;
	r1.root = tmp;
	r2.root = nullptr;
	r1.size_ += r2.size_;
	r2.size_ = 0;
}

// Get a substring from index i to index j.
// Includes both the characters at index i and at index j.
// String can be one character if i and j match
// Returns true if a string was returned, and false otherwise
// Function should be written with efficient running time.
bool Rope::report(int i, int j, std::string &s) const
{
	//Resets the string
	s.clear();
	if(size_ == 0 && i == 0 && j<=1) { return true;}
	// Invalid index, giving segmentation fault
	if (i < 0 || i > int(s.size()) || i > j || i > root->weight) { return false;}
	int count = j - i + 1;
	if (i == j) { char single = index(j, single); s = single; return true; }
	// Loops through the tree until the leaf node is reached
	Node *tmp = findindex(i); Node *tmp2 = tmp;
	// Loops through the tree until the leaf node is reached
	while (count > 0)
	{
		s += tmp2->value.substr(i, std::min((int)tmp2->value.size() - i, count));
		i = 0; //Reset i which is the index since we will be going to the next leaf node
		count -= std::min((int)tmp2->value.size() - i, count);
		if (count <= 0) break;
		// Move to next node
		while (tmp2->parent->right == tmp2 || (tmp2->parent->left == tmp2 && tmp2->parent->right == nullptr))
		{ tmp2 = tmp2->parent; }
		tmp2 = tmp2->parent->right;
		while (tmp2->left != nullptr) { tmp2 = tmp2->left; }
	}
	return true;
}

//Traverse through the tree and adds up the weight of the leaf nodes
void Rope::updatesize(Node* ptr, int& newsize) const
{
	if (!ptr) {return;}
	//Means we have reached a leaf node
	if (!ptr->right && !ptr->left) { newsize+=ptr->weight; return; }
	if (ptr->left) {updatesize(ptr->left, newsize); }
	if (ptr->right) {updatesize(ptr->right, newsize);}
	return;
}

//Splits the node into two as well as the value that the node contains.
void Rope::splitnode(Node*& tmp, int i)
{
	//Splits up the value at the Node
	std::string left = tmp->value.substr(0, i);
	std::string right = tmp->value.substr(i, tmp->value.size()-i);
	//Clears the value because it will no longer be a leaf node
	tmp->value.clear();
	//Make two children node and initalize their data respectively
	Node* lefttmp = new Node();
	lefttmp->value = left;
	lefttmp->weight = left.size();
	lefttmp->parent = tmp;
	tmp->left = lefttmp;
	Node* righttmp = new Node();
	righttmp->value = right;
	righttmp->weight = right.size();
	righttmp->parent = tmp;
	tmp->right = righttmp;
	//Update the size for all the nodes involved.
	int newsize = 0;
	updatesize(tmp->left, newsize);
	tmp->weight = newsize;
	tmp = righttmp;
}
// The first i characters should stay in the current rope, while a new
// Rope (rhs) should contain the remaining size_-i characters.
// A valid split should always result in two ropes of non-zero length.
// If the split would not be valid, this rope should not be changed,
// and the rhs rope should be an empty rope.
// The return value should be this rope (the "left") part of the string
// This function should move the nodes to the rhs instead of making new copies.
Rope &Rope::split(int i, Rope &rhs)
{
	int realsize = 0;
	updatesize(root, realsize);
	//Invalid splitting, return an empty rope
	if (i < 0 || i >= realsize) { rhs = Rope(); return *this; }
	if(i == 0) 
	{ 
		//Move tree to the right rope
		rhs.root = this->root;
		int _size = 0;
		updatesize(root, _size);
		rhs.size_ = _size;
		//Make original rope as an empty rope
		this->root = nullptr;
		this->size_ = 0;
		return *this;
	}
	Node* tmp = findindex(i);
	//If the index at the leaf node is not 0, then we need to split up the node
	if(i != 0) { splitnode(tmp, i);}
	//Container to hold the root nodes each time a disconnect is made
	std::vector<Rope> roottracker;
	//While the current node has parents
	int currentsize = 0; 
	//While the current node is the left children of its parent
	while(tmp->parent != nullptr)
	{
		if (tmp->parent->left == tmp) { tmp = tmp->parent;} 
		else {break;}
	}
	if(tmp->parent != nullptr)
	{
		tmp = tmp->parent;
		//Before disconnect, store the node that is about to get delete for concat later
		Rope therope(tmp->right);
		roottracker.push_back(therope);
		currentsize += therope.size();
		//Disconnect
		tmp->right->parent = nullptr; tmp->right = nullptr;
	}
	///While the current node has parents
	while(tmp->parent != nullptr)
	{
		//Check if a left child for the parent exists
		//If the current node is its parents left
		if(tmp->parent->left == tmp)
		{
			tmp = tmp->parent;
			tmp->weight -= currentsize; 
			if(tmp->right != nullptr)
			{
				//Before disconnect, store the node that is about to get delete for concat later
				Rope therope(tmp->right);
				currentsize += therope.size();
				roottracker.push_back(therope);
				//Disconnect
				tmp->right->parent = nullptr; tmp->right = nullptr;
			}
		}
		//Else means the current node is its parents right
		else {tmp = tmp->parent; }
	}
	//Make a new rope
	Rope answer;
	//Concat everything into the rope
	for(int i = 0; i<int(roottracker.size()); i++) { concat_no_copy(answer, roottracker[i]); }
	rhs = answer;
	int thesize = 0;
	updatesize(rhs.root, thesize);
	rhs.size_ = thesize;
	this->size_ -= rhs.size_;
	rhs = answer;
	return *this;
}