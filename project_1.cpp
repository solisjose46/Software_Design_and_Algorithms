#include <iostream>
//#include <conio.h>
#include <string>
#include "FHlist.h"
#include "FHvector.h"

using namespace std;
//------------------------------------------MatNode-----------------------
template <class Object>
class MatNode
{
protected:
   int col;
public:
   Object data;
   MatNode(int cl = 0, Object dt = Object()) : col(cl), data(dt) {}
   int getCol() const { return col; }
   bool SetCol(int new_col) { col = new_col; return true; }
   const Object & operator=(const Object &x) { return (data = x); }
};
//-----------------------------------------SparseMat-------------------------------
template <class Object>
class SparseMat {
protected:
   typedef FHlist< MatNode<Object> > MatRow;
   typedef FHvector<MatRow> MasterCol;

   MasterCol rows;
   Object defaultVal;
   int rowSize, colSize;

   const static int min_row_size = 1;
   const static int min_col_size = 1;
public:
   SparseMat(int, int, const Object &);
   bool set(int, int, const Object &);
   const Object & get(int, int) const;
   void clear();
   void showSubSquare(int, int);
   ~SparseMat();
};
template <class Object>
SparseMat<Object>::SparseMat(int set_row_size, int set_col_size, const Object & set_default) {
   if (set_row_size >= min_row_size) {
      rowSize = set_row_size;
      rows.resize(rowSize);
   }
   else {
      rowSize = min_row_size;
      rows.resize(rowSize);
   }
   if (set_col_size >= min_col_size) {
      colSize = set_col_size;
   }
   else {
      colSize = min_col_size;
   }
   defaultVal = set_default;
}
template <class Object>
bool SparseMat<Object>::set(int row, int col, const Object & data_in) {
   if (!(row >= rowSize || row < 0 || col >= colSize || col < 0)) { //boundary violations
      typename MatRow::iterator list_iter = rows[row].begin();
      if (rows[row].empty()) {
         if (!(data_in == defaultVal)) {
            rows[row].insert(list_iter, MatNode<Object>(col, data_in));
            return true;
         }
         return true;
      }
      for (list_iter; list_iter != rows[row].end(); ++list_iter) {
         if ((*list_iter).getCol() == col) {
            if (data_in == defaultVal) {
               rows[row].erase(list_iter);
               return true;
            }
            else if (!(data_in == (*list_iter).data)) {
               (*list_iter).data = data_in;
               (*list_iter).SetCol(col);
               return true;
            }
            return true;
         }
      }
      if (data_in != defaultVal) {
         rows[row].insert(list_iter, MatNode<Object>(col, data_in));
      }
      return true;
   }
   return false;
}
template <class Object>
const Object & SparseMat<Object>::get(int row, int col)const {
   try {
      if (!(row >= rowSize || row < 0 || col >= colSize || col < 0)) {
         if (!(rows[row].empty())) {
            typename MatRow::const_iterator list_iter = rows[row].begin();
            for (list_iter; list_iter != rows[row].end(); ++list_iter) {
               if ((*list_iter).getCol() == col) {
                  return (*list_iter).data;
               }
            }
         }
         return defaultVal;
      }
      throw string("Out of bounds");
   }
   catch (string out_of_bounds) {
      cout << out_of_bounds << endl;
   }
}
template <class Object>
void SparseMat<Object>::clear() {
   for (int i = 0; i < rowSize; ++i) {
      if (!(rows[i]).empty()) {
         rows[i].clear();
      }
   }
}
template <class Object>
void SparseMat<Object>::showSubSquare(int start, int size) {
   if (!(start >= rowSize || start >= colSize || start < 0)) { //check boundaries
      for (int i = start; i < size; ++i) {
         if (!rows[i].empty()) {
            typename MatRow::iterator list_iter = rows[i].begin();
            for (int k = start; k < size; ++k) {
               if ((*list_iter).getCol() <= k) {
                  cout << (*list_iter).data << "\t";
                  ++list_iter;
               }
               else {
                  cout << defaultVal << "\t";
               }
            }
         }
         else {
            for (int j = start; j < size; ++j) {
               cout << defaultVal << "\t";
            }
         }
         cout << endl;
      }
   }
}
template <class Object>
SparseMat<Object>::~SparseMat() {}
//--------------------------------------------other--------------------------------------------------------
#define MAT_SIZE 100000
typedef SparseMat<float> SpMat;
//---------------------------------------------main--------------------------------------------------------
int main() {

   SpMat mat(MAT_SIZE, MAT_SIZE, 0); // 100000 x 100000 filled with 0

// test mutators
   mat.set(2, 5, 10);
   mat.set(2, 5, 35);   // should overwrite the 10
   mat.set(3, 9, 21);
   mat.set(MAT_SIZE, 1, 5);  // should fail silently
   mat.set(9, 9, mat.get(3, 9));  // should copy the 21 here
   mat.set(4, 4, -9);
   mat.set(4, 4, 0);   // should remove the -9 node entirely
   mat.set(MAT_SIZE - 1, MAT_SIZE - 1, 99);

   // show top left 15x15
   mat.showSubSquare(0, 15);

   // show bottom right 15x15
   mat.showSubSquare(MAT_SIZE - 15, 15);

   //_getch();
   return 0;
}
//-----------------------------------------------output from screen--------------------------------------------------
//0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
//
//0       0       0       0       0       35      0       0       0       0       0       0       0       0       0
//
//0       0       0       0       0       0       0       0       0       21      0       0       0       0       0
//
//0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
//
//0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
//
//0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
//
//0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
//
//0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
//
//0       0       0       0       0       0       0       0       0       21      0       0       0       0       0
//
//0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
//
//0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
//
//0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
//
//0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
//
//0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
//----------------------------------------End of Submission----------------------------------------------------------