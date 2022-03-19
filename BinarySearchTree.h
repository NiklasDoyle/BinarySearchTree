//This defines a Binary Search Tree with several functions that can store clubs at different universities

#include <iostream> //to use cout
#include <string> //to use strings
#include <cstdlib> //to use atoi

using namespace std;

//Club represents some club information
class Club
 {
  private:
    string clubName;
    string universityName;
    Club * left, * right, * parent;


  public:
    //The following two functions are constructors
    Club()
     {
      clubName = "?";
      universityName = "?";
      parent = NULL;
      left = NULL;
      right = NULL;
     }


    Club(string clubName1, string universityName1)
     {
      clubName = clubName1;
      universityName = universityName1;

      parent = NULL;
      left = NULL;
      right = NULL;
     }

    //The following functions are accessor functions
    Club * getLeft()
     {
      return left;
     }

    Club * getRight()
     {
      return right;
     }

    Club * getParent()
     {
      return parent;
     }

    string getClubName()
     {
         return clubName;
     }
     string getUniversityName()
     {
         return universityName;
     }


    //The following functions are mutator functions
    void setLeft(Club * other)
     {
       left = other;
     }

    void setRight(Club * other)
     {
       right = other;
     }

    void setParent(Club * other)
     {
       parent = other;
     }

    //The print method prints the clubName and universityName
    void print()
     {
         cout << "Club Name: " << clubName << endl;
         cout << "University Name: " << universityName << endl << endl;
     }

   //you can add more functions

 };

//class BinarySearchTree will contains clubs
class BinarySearchTree
 {
  private:
     Club * root;
     int size;

  public:
     BinarySearchTree();
     ~BinarySearchTree();
     int postOrderTreeDelete(Club *);
     bool isEmpty();
     void inOrderTreePrint();
     void preOrderTreePrint();
     void postOrderTreePrint();
     void inOrderTreeWalk(Club *);
     void preOrderTreeWalk(Club *);
     void postOrderTreeWalk(Club *);
     Club * treeSearchNode(Club *, string, string);
     Club * treeSearch(string, string);
     Club * treeMinimum();
     Club * treeMaximum();
     Club * treeMinimumNode(Club *);
     Club * treeMaximumNode(Club *);
     Club * treeSuccessor(string,string);
     Club * treePredecessor(string,string);
     bool treeInsert(string,string);
     bool rightRotate(string, string);
     bool leftRotate(string, string);
     int deleteNode(Club *);
 };

//The constructor initialize the root to be NULL
BinarySearchTree::BinarySearchTree()
 {
  root = NULL;
 }

//The descurtor should delete all nodes in the tree
//and perform garbage collections starting from leaves (bottom-up order).
//The destructor should also print “The number of nodes deleted: X”
//where X is the number of nodes deleted
BinarySearchTree::~BinarySearchTree()
 {
	int numDeleted = deleteNode(root);
	cout << "The number of nodes deleted: " << numDeleted << endl;
 }

//Supplement to deconstructor
int BinarySearchTree::deleteNode(Club* node)
{

	//Walks through tree in postOrder and deletes each node after its children have been deleted and increments a counter
	if(node != NULL){
		int counter = deleteNode(node->getLeft()) + deleteNode(node->getRight());
		delete(node);
		counter++;
		return counter;
	}
	return 0;
}
//Checks if the tree is empty
bool BinarySearchTree::isEmpty()
 {
   if (root == NULL)
    return true;
   else
    return false;
 }

//prints all nodes using in-order
void BinarySearchTree::inOrderTreePrint()
 {
  if (isEmpty())
    cout << "tree is empty" << endl;
  else
   {
    cout << "\n";
    inOrderTreeWalk(root);
    cout << "\n";
   }
 }

//prints all nodes using pre-order
void BinarySearchTree::preOrderTreePrint()
 {
  if (isEmpty())
    cout << "tree is empty" << endl;
  else
   {
    cout << "\n";
    preOrderTreeWalk(root);
    cout << "\n";
   }
 }

//prints all nodes using post-order
void BinarySearchTree::postOrderTreePrint()
 {
  if (isEmpty())
    cout << "tree is empty" << endl;
  else
   {
    cout << "\n";
    postOrderTreeWalk(root);
    cout << "\n";
   }
 }

void BinarySearchTree::inOrderTreeWalk(Club * node)
{
	//If there is a node,  it will first recursivley check its left, then print, then check its right
	if(node != NULL){
		inOrderTreeWalk(node->getLeft());
		node->print();
		inOrderTreeWalk(node->getRight());
	}

}

//If there is a node,  it will first print, then recursivley check its left, then check its right
void BinarySearchTree::preOrderTreeWalk(Club * node)
 {
	if(node != NULL){
		node->print();
		preOrderTreeWalk(node->getLeft());
		preOrderTreeWalk(node->getRight());
	}
 }

//If there is a node,  it will first recursivley check its left, then check its right, then print
void BinarySearchTree::postOrderTreeWalk(Club * node)
 {
	if(node != NULL){
		postOrderTreeWalk(node->getLeft());
		postOrderTreeWalk(node->getRight());
		node->print();
	}
 }

//This will search through the tree starting at a node to find a Club with a matching name and university
Club * BinarySearchTree::treeSearchNode(Club * node, string clubName, string universityName)
 {
	//If the node doesn't exist or is equal to the name return it
	if(node == NULL || (universityName + clubName).compare(node->getUniversityName() + node->getClubName()) == 0)
	{
		return node;
	}
	else
		//if the name of the university andd club put together is alphabetically before the current node, go left
		if((universityName + clubName).compare(node->getUniversityName() + node->getClubName()) < 0)
			return treeSearchNode(node->getLeft(), clubName, universityName);

		//if alphabetically after go right
		else
			return treeSearchNode(node->getRight(), clubName, universityName);

 }

//Searches the entire tree by starting at the root
Club * BinarySearchTree::treeSearch(string clubName, string universityName)
{
	return treeSearchNode(root, clubName, universityName);
}

//Searches for minimum starting at root
Club * BinarySearchTree::treeMinimum()
{
	return treeMinimumNode(root);

}

//Searches for Maximum starting at root
Club * BinarySearchTree::treeMaximum()
{
	return treeMaximumNode(root);

}

//Searcges for minimum starting at node
Club * BinarySearchTree::treeMinimumNode(Club * x)
{
	if(x == NULL)
		return NULL;

	//Keeps going left until it cant
	while(x->getLeft() != NULL)
	{
		x = x->getLeft();
	}

	return x;
}

//Searching for maximum starting at node
Club * BinarySearchTree::treeMaximumNode(Club * x)
{
	if(x == NULL)
			return NULL;

	//Keeping goiing right until it cant
	while(x->getRight()!= NULL)
	{
		x = x->getRight();
	}

	return x;

}

//Finds the next club in alphabetical order
Club * BinarySearchTree::treeSuccessor(string clubName, string universityName)
{
	//If the list is empty or the club doesnt exist return null
	if(isEmpty() || treeSearch(clubName, universityName) == NULL)
		return NULL;

	Club * x = treeSearch(clubName, universityName);
	Club * y;

	//If x has a right, find the minimum of x and return it
	if(x->getRight() != NULL)
	{
		return treeMinimumNode(x);
	}

	//if not go to the top of the chain and return that
	else
	{
		y = x->getParent();
		while(y != NULL && x == y->getRight())
		{
			x = y;
			y = y->getParent();
		}
		return y;
	}

}

//Finds the previous club in alphabetical order
Club * BinarySearchTree::treePredecessor(string clubName, string universityName)
{
	//If the list is empty or the club doesnt exist return null
	if(isEmpty() || treeSearch(clubName, universityName) == NULL)
		return NULL;

	Club * x = treeSearch(clubName, universityName);
	Club * y;

	//If x has a left, find the minimum of x and return it
	if(x->getLeft() != NULL)
	{
		return treeMaximumNode(x);
	}
	//if not go to the top of the chain and return that
	else
	{
		y = x->getParent();
		while(y != NULL && x == y->getLeft())
		{
			x = y;
			y = y->getParent();
		}
		return y;
	}
}

//Insert a new club into the tree
bool BinarySearchTree::treeInsert(string clubName, string universityName)
{
	Club * y = NULL;
	Club * x = root;

	//If club already exists don't insert it
	if(treeSearch(clubName, universityName) != NULL)
		return false;

	//Create new club
	Club * newClub = new Club(clubName, universityName);

	//Follow the chain to alphabetically find the correct place in the tree and set the parent
	while(x != NULL)
	{
		y = x;
		if ((universityName + clubName).compare(y->getUniversityName() + y->getClubName()) < 0)
			x = x->getLeft();
		else
			x = x->getRight();
	}
	newClub->setParent(y);

	//If list is empty make new club the root
	if(y == NULL)
		root = newClub;

	//else set it as the left/right of the parent node
	else
		if((universityName + clubName).compare(y->getUniversityName() + y->getClubName()) < 0)
			y->setLeft(newClub);
		else
			y->setRight(newClub);


	return true;

}

//Rotate a segment of the tree to the right
bool BinarySearchTree::rightRotate(string clubName, string universityName)
{
	//If tree is empty or Club does not exist return false
	if(isEmpty() || treeSearch(clubName, universityName) == NULL)
		return false;

	Club * x = treeSearch(clubName, universityName);
	Club * y = x->getLeft();

	//If this is the most left node then it can note be rotated
	if(x->getLeft() == NULL)
		return false;

	//y's right subtree becomes x's left subtree
	x->setLeft(y->getRight());

	if(y->getRight() != NULL)
		y->getRight()->setParent(x);

	y->setParent(x->getParent());

	//deals with if x was root
	if(x->getParent() == NULL)
		root = y;
	else
		if(x == x->getParent()->getRight())
			x->getParent()->setRight(y);
		else
			x->getParent()->setLeft(y);

	y->setRight(x);
	x->setParent(y);

	return true;
}

//Rotate a segment of the tree to the left
bool BinarySearchTree::leftRotate(string clubName, string universityName)
{
	//If tree is empty or Club does not exist return false
	if(isEmpty() || treeSearch(clubName, universityName) == NULL)
		return false;

	Club * x = treeSearch(clubName, universityName);
	Club * y = x->getRight();

	//If this is the most right node then it can note be rotated
	if(x->getRight() == NULL)
		return false;

	//y's left subtree becomes x's right subtree
	x->setRight(y->getLeft());

	if(y->getLeft() != NULL)
		y->getLeft()->setParent(x);

	y->setParent(x->getParent());

	//deals with if x was root
	if(x->getParent() == NULL)
		root = y;
	else
		if(x == x->getParent()->getLeft())
			x->getParent()->setLeft(y);
		else
			x->getParent()->setRight(y);

	y->setLeft(x);
	x->setParent(y);

	return true;
}

