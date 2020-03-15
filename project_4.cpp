#include <iostream>
//#include <conio.h>
#include "FHsearch_tree.h"

using namespace std;
//------------PrinteObject class----------------------------------------
template <typename Object>
class PrintObject
{
public:
   void operator()(Object obj)
   {
      cout << obj << " ";
   }
};
//---------------------------------------------FHsplayTree Prototype-----------------------------------------------------
template <class Comparable>
class FHsplayTree : public FHsearch_tree<Comparable> {
protected:
   void splay(FHs_treeNode<Comparable> * & root, const Comparable & x);
   void SingleLeftRotation(FHs_treeNode<Comparable> * & k2);
   void SingleRightRotation(FHs_treeNode<Comparable> * & k2);
   int max(int x, int y) { return ((x > y) ? (x) : (y)); }

public:
   bool insert(const Comparable &x);
   bool remove(const Comparable &x);
   bool find(const Comparable &x);
   bool contains(const Comparable &x) { find(x); return true; }
   const Comparable &showRoot() { return this->mRoot->data; }
   ~FHsplayTree() { this->clear(); }
};
//---------------------------------FHsplayTree Public Methods-----------------------------------------------------
template <class Comparable>
bool FHsplayTree<Comparable>::insert(const Comparable&x) {
   //PrintObject<int> print_me;
   if (this->mRoot == NULL) {
      this->mRoot = new FHs_treeNode<Comparable>(x, NULL, NULL);
      return true;
   }
   splay(this->mRoot, x);
   if (x < this->mRoot->data) {
      this->mRoot->lftChild = new FHs_treeNode<Comparable>(x, this->mRoot->lftChild, NULL);
      SingleRightRotation(this->mRoot);
      return true;
   }
   else if (this->mRoot->data < x) {
      this->mRoot->rtChild = new FHs_treeNode<Comparable>(x, NULL, this->mRoot->rtChild);
      SingleLeftRotation(this->mRoot);
      return true;
   }
   return false;

}
template <class Comparable>
bool FHsplayTree<Comparable>::remove(const Comparable&x) {
   if (this->mRoot == NULL) {
      return false;
   }
   splay(this->mRoot, x);
   FHs_treeNode<Comparable>* master_root = this->mRoot;
   if (x != master_root->data) {
      return false;
   }
   if (this->mRoot->lftChild == NULL) {
      this->mRoot->lftChild = master_root->rtChild;
   }
   else {
      this->mRoot = master_root->lftChild;
      splay(this->mRoot, x);
      this->mRoot->rtChild = master_root->rtChild;
   }
   delete master_root;
   master_root = this->mRoot;
   return true;
}
template <class Comparable>
bool FHsplayTree<Comparable>::find(const Comparable&x) {
   if (this->mRoot == NULL) {
      return false;
   }
   splay(this->mRoot, x);
   if (this->mRoot->data == x) {
      return true;
   }
   throw typename FHsearch_tree<Comparable>::NotFoundException();
}
//----------------------------------FHsplayTree Protected methods------------------------------------------------
template <class Comparable>
void FHsplayTree<Comparable>::splay(FHs_treeNode<Comparable> * & root, const Comparable & x) {
   FHs_treeNode<Comparable> *leftTree = NULL, *rightTree = NULL, *leftTreeMax = NULL, *rightTreeMin = NULL;
   while (root != NULL) {
      if (x < root->data) {
         if (root->lftChild == NULL) {
            break;
         }
         if (x < root->lftChild->data) {
            SingleRightRotation(root);
            if (root->lftChild == NULL) {
               break;
            }
         }
         if (rightTree == NULL) {
            rightTree = root;
            rightTreeMin = root;
            root = root->lftChild;
         }
         else {
            rightTreeMin->lftChild = root;
            rightTreeMin = root;
            root = root->lftChild;
         }
      }
      if (root->data < x) {
         if (root->rtChild == NULL) {
            break;
         }
         if (root->rtChild->data < x) {
            SingleLeftRotation(root);
            if (root->rtChild == NULL) {
               break;
            }
         }
         if (leftTree == NULL) {
            leftTree = root;
            leftTreeMax = root;
            root = root->rtChild;
         }
         else {
            leftTreeMax->rtChild = root;
            leftTreeMax = root;
            root = root->rtChild;
         }
      }
      if (root->data == x) {
         break;
      }
   }
   //assemble here
   if (leftTree != NULL) {
      leftTreeMax->rtChild = root->lftChild;
      root->lftChild = leftTree;
   }
   if (rightTree != NULL) {
      rightTreeMin->lftChild = root->rtChild;
      root->rtChild = rightTree;
   }
}
template <class Comparable>
void FHsplayTree<Comparable>::SingleLeftRotation(FHs_treeNode<Comparable> * & k2)
{
   FHs_treeNode<Comparable> *k1 = k2->rtChild;
   k2->rtChild = k1->lftChild;
   k1->lftChild = k2;
   k2->setHeight(max(this->findHeight(k2->lftChild), this->findHeight(k2->rtChild)) + 1);
   k1->setHeight(max(this->findHeight(k1->rtChild), k2->getHeight()) + 1);
   k2 = k1;
}
template <class Comparable>
void FHsplayTree<Comparable>::SingleRightRotation(FHs_treeNode<Comparable> * & k2)
{
   FHs_treeNode<Comparable> *k1 = k2->lftChild;
   k2->lftChild = k1->rtChild;
   k1->rtChild = k2;
   k2->setHeight(max(this->findHeight(k2->lftChild), this->findHeight(k2->rtChild)) + 1);
   k1->setHeight(max(this->findHeight(k1->lftChild), k2->getHeight()) + 1);
   k2 = k1;
}

int main() {
   FHsplayTree <int> testing_tree;
   PrintObject<int> print_me;
   const int size_of_tree = 32;

   //test for insertion
   for (int i = 0; i < size_of_tree; i += 2) { //these nodes even
      testing_tree.insert(i);
   }
   cout << "TREE after inserting even numbers: " << endl;
   testing_tree.traverse(print_me); //if in order then tree assembled right
   cout << endl << "-------------------------------------------------" << endl;
   for (int j = 1; j < size_of_tree; j += 2) {
      testing_tree.insert(j); //these nodes odd
   }
   cout << "TREE after inserting odd numbers: " << endl;
   testing_tree.traverse(print_me);
   cout << endl << "-------------------------------------------------" << endl;
   //test for contain and find
   testing_tree.contains(12); //calls find so this tests both contains() and find() method
   cout << "TREE after searching for 12 " << endl;
   testing_tree.traverse(print_me);
   cout << endl << "-------------------------------------------------" << endl;
   cout << "NEW SPLAYED ROOT SHOULD BE 12: " << testing_tree.showRoot() << endl;
   testing_tree.contains(25); //calls find so this tests both contains() and find() method
   cout << "TREE after searching for 25 " << endl;
   testing_tree.traverse(print_me);
   cout << endl << "-------------------------------------------------" << endl;
   cout << "NEW SPLAYED ROOT SHOULD BE 25: " << testing_tree.showRoot() << endl;
   //test for removal
   testing_tree.remove(11);
   cout << "TREE after removal of 11 " << endl;
   testing_tree.traverse(print_me);
   cout << endl << "-------------------------------------------------" << endl;
   testing_tree.remove(22);
   cout << "TREE after removal of 22 " << endl;
   testing_tree.traverse(print_me);
   cout << endl << "-------------------------------------------------" << endl;

   //_getch();
   return 0;
}
//------------------------------------------------------RUN--------------------------------------------------------------
//TREE after inserting even numbers :
//0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30
//------------------------------------------------ -
//TREE after inserting odd numbers :
//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
//------------------------------------------------ -
//TREE after searching for 12
//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
//------------------------------------------------ -
//NEW SPLAYED ROOT SHOULD BE 12: 12
//TREE after searching for 25
//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
//------------------------------------------------ -
//NEW SPLAYED ROOT SHOULD BE 25 : 25
//TREE after removal of 11
//0 1 2 3 4 5 6 7 8 9 10 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
//------------------------------------------------ -
//TREE after removal of 22
//0 1 2 3 4 5 6 7 8 9 10 12 13 14 15 16 17 18 19 20 21 23 24 25 26 27 28 29 30 31
//------------------------------------------------ -
//-----------------------------------------------------END OF SUBMISSION-----------------------------------------------------------