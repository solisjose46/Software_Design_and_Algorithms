#include <iostream>
//#include <conio.h>

using namespace std;

// ---------------------- FHlazySearchTreeNode Prototype --------------------------
template <class Comparable>
class FHlazySearchTreeNode
{
public:
   FHlazySearchTreeNode(const Comparable & d = Comparable(), FHlazySearchTreeNode *lt = NULL, FHlazySearchTreeNode *rt = NULL, bool is_deleted = false)
      : lftChild(lt), rtChild(rt), data(d), deleted_(is_deleted)
   { }

   FHlazySearchTreeNode *lftChild, *rtChild;
   Comparable data;
   bool deleted_;

   // for use only with AVL Trees
   virtual int getHeight() const { return 0; }
   virtual bool setHeight(int height) { return true; }
};
// ---------------------- FHlazySearchTree Prototype --------------------------
template <class Comparable>
class FHlazySearchTree
{
protected:
   int mSize; //tracks undeleted nodes
   int mSizeHard; //tracks both hard nodes and soft deleted nodes
   FHlazySearchTreeNode<Comparable> *mRoot;

public:
   FHlazySearchTree() { mSize = 0; mRoot = NULL; mSizeHard = 0; }
   FHlazySearchTree(const FHlazySearchTree &rhs)
   {
      mRoot = NULL; mSize = 0; mSizeHard = 0; *this = rhs;
   }
   ~FHlazySearchTree() { clear(); }

   const Comparable &findMin() const;
   const Comparable &findMax() const;
   const Comparable &find(const Comparable &x) const;

   bool empty() const { return (mSize == 0); }
   int size() const { return mSize; }
   void clear() { makeEmpty(mRoot); }
   const FHlazySearchTree & operator=(const FHlazySearchTree &rhs);

   bool insert(const Comparable &x);
   bool remove(const Comparable &x);
   bool contains(const Comparable &x) const { return find(mRoot, x) != NULL; }

   template <class Processor>
   void traverse(Processor func) const { traverse(mRoot, func); }
   int showHeight() const { return findHeight(mRoot); }
   bool CollectGarbage() { return GarbageRemoved(mRoot); }
   int getHardSize()const { return mSizeHard; }
protected:
   FHlazySearchTreeNode<Comparable> *clone(FHlazySearchTreeNode<Comparable> *root) const;
   FHlazySearchTreeNode<Comparable> *findMin(FHlazySearchTreeNode<Comparable> *root) const;
   FHlazySearchTreeNode<Comparable> *findMax(FHlazySearchTreeNode<Comparable> *root) const;
   FHlazySearchTreeNode<Comparable> *find(FHlazySearchTreeNode<Comparable> *root, const Comparable &x) const;
   bool insert(FHlazySearchTreeNode<Comparable> * &root, const Comparable &x);
   bool remove(FHlazySearchTreeNode<Comparable> * &root, const Comparable &x);
   void makeEmpty(FHlazySearchTreeNode<Comparable> * &subtreeToDelete);
   template <class Processor>
   void traverse(FHlazySearchTreeNode<Comparable> *treeNode, Processor func, int level = -1) const;
   int findHeight(FHlazySearchTreeNode<Comparable> *treeNode, int height = -1) const;
   bool GarbageRemoved(FHlazySearchTreeNode<Comparable> * start_node);
   FHlazySearchTreeNode<Comparable> * findHardMax(FHlazySearchTreeNode<Comparable> *root)const;
   bool HardRemove(FHlazySearchTreeNode<Comparable> * &root);
public:
   // for exception throwing
   class EmptyTreeException {};
   class NotFoundException {};
};

// FHlazySearchTree public method definitions -----------------------------
template <class Comparable>
const Comparable & FHlazySearchTree<Comparable>::findMin() const
{
   if (mRoot == NULL)
      throw EmptyTreeException();
   return findMin(mRoot)->data;
}
template <class Comparable>
const Comparable & FHlazySearchTree<Comparable>::findMax() const
{
   if (mRoot == NULL)
      throw EmptyTreeException();
   return findMax(mRoot)->data;
}

template <class Comparable>
const Comparable &FHlazySearchTree<Comparable>::find(const Comparable &x) const
{
   FHlazySearchTreeNode<Comparable> *resultNode;

   resultNode = find(mRoot, x);
   if (resultNode == NULL) {
      throw NotFoundException();
   }

   return resultNode->data;
}

template <class Comparable>
const FHlazySearchTree<Comparable> &FHlazySearchTree<Comparable>::operator= (const FHlazySearchTree &rhs)
{
   if (&rhs != this)
   {
      clear();
      mRoot = clone(rhs.mRoot);
      mSize = rhs.mSize;
      mSizeHard = rhs.mSizeHard; //not setting this->mSizeHard
   }
   return *this;
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::insert(const Comparable &x)
{
   if (insert(mRoot, x))
   {
      ++mSize;
      ++mSizeHard;
      return true;
   }
   return false;
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::remove(const Comparable &x)
{
   if (remove(mRoot, x))
   {
      --mSize;
      return true;
   }
   return false;
}

template <class Comparable>
template <class Processor>
void FHlazySearchTree<Comparable>::traverse(FHlazySearchTreeNode<Comparable> *treeNode, Processor func, int level) const
{
   if (treeNode == NULL)
      return;
   // we're not doing anything with level but its there in case we want it
   traverse(treeNode->lftChild, func, level + 1);
   if (treeNode->deleted_ == false)
      func(treeNode->data);
   traverse(treeNode->rtChild, func, level + 1);
}

//--------------------------------------FHlazySearchTree private method definitions -----------------------------
template <class Comparable>
FHlazySearchTreeNode<Comparable> *FHlazySearchTree<Comparable>::clone(FHlazySearchTreeNode<Comparable> *root) const
{
   FHlazySearchTreeNode<Comparable> *newNode;
   if (root == NULL)
      return NULL;

   newNode = new FHlazySearchTreeNode<Comparable>(root->data, clone(root->lftChild), clone(root->rtChild), root->deleted_);
   return newNode;
}
template <class Comparable>
FHlazySearchTreeNode<Comparable> *FHlazySearchTree<Comparable>::findHardMax(FHlazySearchTreeNode<Comparable> *root) const {
   if (root == NULL)
      return NULL;
   if (root->rtChild == NULL)
      return root;
   return findHardMax(root->rtChild);
}
template <class Comparable>
bool FHlazySearchTree<Comparable>::HardRemove(FHlazySearchTreeNode<Comparable> * &root)
{
   if (root == NULL)
      return false;

   if (root->lftChild != NULL && root->rtChild != NULL)
   {
      FHlazySearchTreeNode<Comparable> *minNode = findHardMax(root->rtChild);
      root->data = minNode->data;
      HardRemove(root->rtChild);
   }
   else
   {
      FHlazySearchTreeNode<Comparable> *nodeToRemove = root;
      root = (root->lftChild != NULL) ? root->lftChild : root->rtChild;
      delete nodeToRemove;
      --mSizeHard;
   }
   return true;
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::GarbageRemoved(FHlazySearchTreeNode<Comparable> * start_node)
{
   if (start_node == NULL)
      return false;

   GarbageRemoved(start_node->rtChild);
   GarbageRemoved(start_node->lftChild);

   if (start_node->deleted_ == true) {
      start_node->data = start_node->rtChild->data;
      HardRemove(start_node->rtChild);
      start_node->deleted_ = false;
   }
   return true;
}
template <class Comparable>
FHlazySearchTreeNode<Comparable> *FHlazySearchTree<Comparable>::findMin(FHlazySearchTreeNode<Comparable> *root) const
{
   if (root == NULL)
      return NULL;

   FHlazySearchTreeNode<Comparable> * p_left_child = findMin(root->lftChild);
   if (p_left_child != NULL) {
      if (p_left_child->deleted_ == false)
         return p_left_child;
   }
   if (root->deleted_ != true)
      return root;
   if (root->rtChild != NULL)
      return findMin(root->rtChild);
}

template <class Comparable>
FHlazySearchTreeNode<Comparable> *FHlazySearchTree<Comparable>::findMax(FHlazySearchTreeNode<Comparable> *root) const
{
   if (root == NULL)
      return NULL;

   FHlazySearchTreeNode<Comparable> * p_right_child = findMax(root->rtChild);
   if (p_right_child != NULL) {
      if (p_right_child->deleted_ == false)
         return p_right_child;
   }
   if (root->deleted_ != true)
      return root;
   if (root->lftChild != NULL)
      return findMax(root->lftChild);
}

template <class Comparable>
FHlazySearchTreeNode<Comparable>* FHlazySearchTree<Comparable>::find(FHlazySearchTreeNode<Comparable> *root, const Comparable &x) const
{
   if (root == NULL)
      return NULL;

   if (x < root->data)
      return find(root->lftChild, x);
   if (root->data < x)
      return find(root->rtChild, x);

   return root;
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::insert(FHlazySearchTreeNode<Comparable> * &root, const Comparable &x)
{
   if (root == NULL)
   {
      root = new FHlazySearchTreeNode<Comparable>(x, NULL, NULL, false);
      return true;
   }
   else if (x < root->data)
      return insert(root->lftChild, x);
   else if (root->data < x)
      return insert(root->rtChild, x);

   if (root->deleted_ == true) {
      root->deleted_ = false;
      ++mSize;
   }
   return false; //duplicate
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::remove(FHlazySearchTreeNode<Comparable> * &root, const Comparable &x)
{
   if (root == NULL)
      return false;

   if (x < root->data)
      return remove(root->lftChild, x);
   if (root->data < x)
      return remove(root->rtChild, x);

   // found the node
   if (root->deleted_ == true)
      return false;
   root->deleted_ = true;
   return true;
}

template <class Comparable>
void FHlazySearchTree<Comparable>::makeEmpty(FHlazySearchTreeNode<Comparable> * &subtreeToDelete)
{
   if (subtreeToDelete == NULL)
      return;

   // remove children
   makeEmpty(subtreeToDelete->lftChild);
   makeEmpty(subtreeToDelete->rtChild);

   // clear client's pointer
   if (subtreeToDelete->deleted_ == false)
      --mSize;
   delete subtreeToDelete;
   subtreeToDelete = NULL;
   --mSizeHard;

}

template <class Comparable>
int FHlazySearchTree<Comparable>::findHeight(FHlazySearchTreeNode<Comparable> *treeNode, int height) const
{
   int leftHeight, rightHeight;

   if (treeNode == NULL)
      return height;
   height++;
   leftHeight = findHeight(treeNode->lftChild, height);
   rightHeight = findHeight(treeNode->rtChild, height);
   return (leftHeight > rightHeight) ? leftHeight : rightHeight;
}
//---------------------------------------------------Print me--------------------------
template<class Object>
class Printme {
public:
   void operator()(Object obj) {
      cout << obj << endl;
   }
};

int main() {

   FHlazySearchTree<int> searchTree;
   Printme<int> intPrinter;

   searchTree.traverse(intPrinter);

   cout << "\ninitial size: " << searchTree.size() << endl;
   searchTree.insert(50);
   searchTree.insert(20);
   searchTree.insert(30);
   searchTree.insert(70);
   searchTree.insert(10);
   searchTree.insert(60);

   cout << "After populating -- traversal and sizes: \n";
   searchTree.traverse(intPrinter);
   cout << "\ntree 1 size: " << searchTree.size()
      << "  Hard size: " << searchTree.getHardSize() << endl;

   cout << "Collecting garbage on new tree - should be no garbage." << endl;
   searchTree.CollectGarbage();
   cout << "tree 1 size: " << searchTree.size()
      << "  Hard size: " << searchTree.getHardSize() << endl;

   // test assignment operator
   FHlazySearchTree<int> searchTree2 = searchTree;

   cout << "\n\nAttempting 1 removal: \n";
   if (searchTree.remove(20))
      cout << "removed " << 20 << endl;
   cout << "tree 1 size: " << searchTree.size()
      << "  Hard size: " << searchTree.getHardSize() << endl;

   cout << "Collecting Garbage - should clean 1 item. " << endl;
   searchTree.CollectGarbage();
   cout << "tree 1 size: " << searchTree.size()
      << "  Hard size: " << searchTree.getHardSize() << endl;

   cout << "Collecting Garbage again - no change expected. " << endl;
   searchTree.CollectGarbage();
   cout << "tree 1 size: " << searchTree.size()
      << "  Hard size: " << searchTree.getHardSize() << endl;

   // test soft insertion and deletion:

   cout << "Adding 'hard' 22 - should see new sizes. " << endl;
   searchTree.insert(22);
   searchTree.traverse(intPrinter);
   cout << "\ntree 1 size: " << searchTree.size()
      << "  Hard size: " << searchTree.getHardSize() << endl;

   cout << "\nAfter soft removal. " << endl;
   searchTree.remove(22);
   searchTree.traverse(intPrinter);
   cout << "\ntree 1 size: " << searchTree.size()
      << "  Hard size: " << searchTree.getHardSize() << endl;

   cout << "Repeating soft removal. Should see no change. " << endl;
   searchTree.remove(22);
   searchTree.traverse(intPrinter);
   cout << "\ntree 1 size: " << searchTree.size()
      << "  Hard size: " << searchTree.getHardSize() << endl;

   cout << "Soft insertion. Hard size should not change. " << endl;
   searchTree.insert(22);
   searchTree.traverse(intPrinter);
   cout << "\ntree 1 size: " << searchTree.size()
      << "  Hard size: " << searchTree.getHardSize() << endl;

   searchTree.CollectGarbage();

   cout << "\nsearchTree now:\n";
   searchTree.traverse(intPrinter);
   cout << "\ntree 1 size: " << searchTree.size()
      << "  Hard size: " << searchTree.getHardSize() << endl;

   searchTree2.insert(500);
   searchTree2.insert(200);
   searchTree2.insert(300);
   searchTree2.insert(700);
   searchTree2.insert(100);
   searchTree2.insert(600);
   cout << "\nsearchTree2:\n";
   searchTree2.traverse(intPrinter);
   cout << "\ntree 2 size: " << searchTree2.size()
      << "  Hard size: " << searchTree2.getHardSize() << endl;

   cout << "MAX: " << searchTree2.findMax() << endl;
   cout << "MAX Should be: " << searchTree2.find(700) << endl;

   cout << "MIN: " << searchTree2.findMin() << endl;
   cout << "Min should be: " << searchTree2.find(10);

   //soft delete then find new max
   cout << "Removed: " << searchTree2.find(700) << endl;
   searchTree2.remove(700);
   cout << "Removed: " << searchTree2.find(600) << endl;
   searchTree2.remove(600);
   cout << "MAX: " << searchTree2.findMax() << endl;
   cout << "MAX Should be: " << searchTree2.find(500) << endl;

   //_getch();
   return 0;
}
//-------------------------------------------------------------RUN----------------------------------------------------------------------
//initial size : 0
//After populating -- traversal and sizes :
//   10
//   20
//   30
//   50
//   60
//   70
//
//   tree 1 size: 6  Hard size : 6
//   Collecting garbage on new tree - should be no garbage.
//   tree 1 size : 6  Hard size : 6
//
//
//   Attempting 1 removal :
//   removed 20
//   tree 1 size : 5  Hard size : 6
//   Collecting Garbage - should clean 1 item.
//   tree 1 size : 5  Hard size : 5
//   Collecting Garbage again - no change expected.
//   tree 1 size : 5  Hard size : 5
//   Adding 'hard' 22 - should see new sizes.
//   10
//   22
//   30
//   50
//   60
//   70
//
//   tree 1 size: 6  Hard size : 6
//
//   After soft removal.
//   10
//   30
//   50
//   60
//   70
//
//   tree 1 size: 5  Hard size : 6
//   Repeating soft removal.Should see no change.
//   10
//   30
//   50
//   60
//   70
//
//   tree 1 size: 5  Hard size : 6
//   Soft insertion.Hard size should not change.
//   10
//   22
//   30
//   50
//   60
//   70
//
//   tree 1 size: 6  Hard size : 6
//
//   searchTree now :
//10
//22
//30
//50
//60
//70
//
//tree 1 size: 6  Hard size : 6
//
//searchTree2 :
//   10
//   20
//   30
//   50
//   60
//   70
//   100
//   200
//   300
//   500
//   600
//   700
//
//   tree 2 size: 12  Hard size : 12
//   MAX : 700
//   MAX Should be : 700
//   MIN : 10
//   Min should be : 10Removed : 700
//   Removed : 600
//   MAX : 500
//   MAX Should be : 500
//---------------------------------------------------------------END OF SUBMISSION----------------------------------------------------------