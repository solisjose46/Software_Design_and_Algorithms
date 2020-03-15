#include <iostream>
//#include <conio.h>
#include <stdlib.h>
#include <time.h> 

using namespace std;
#define MAT_SIZE 200 //set size here
//---------------------------------------------------------------Global------------------------------------------------
typedef float * DynMat[MAT_SIZE];
const float default_val = 0.0; //set default value here
const int max_random_value = 10;
const int max_random_percent = 100;
int startTime, stopTime;
//--------------------------------------------------------------DynMat functions-------------------------------------------
void matMultDyn(const DynMat & matA, const DynMat & matB, DynMat & matC) {
   for (int i = 0; i < MAT_SIZE; ++i) {
      for (int j = 0; j < MAT_SIZE; ++j) {
         matC[i][j] = 0;
         for (int k = 0; k < MAT_SIZE; ++k) {
            matC[i][j] += matA[i][k] * matB[k][j];
         }
      }
   }
}
void matShowDyn(const DynMat & matA, int start, int size) {
   for (int i = start; i < size; ++i) {
      for (int j = start; j < size; ++j) {
         cout << matA[i][j] << "\t";
      }
      cout << endl;
   }
}
//-----------------------------------------------------------------main-------------------------------------------------------
int main() {
   //seed for random number generator
   srand(time(NULL));
   //Random value, percent and sparse matriz size
   const float random_percent = (rand() % max_random_percent) * 0.001; //multiply by 0.001 to get range 0.1% - 10%
   const int sparse_matrix_size = random_percent * MAT_SIZE;
   int random_row, random_column;
   float random_value;
   //non sparse dynamic matrix
   DynMat mDyn, ansDyn;

   //allocate rows and set default
   for (int i = 0; i < MAT_SIZE; ++i) {
      mDyn[i] = new float[MAT_SIZE];
      ansDyn[i] = new float[MAT_SIZE];
      for (int j = 0; j < MAT_SIZE; ++j) {
         (mDyn[i])[j] = default_val;
         (ansDyn[i])[j] = default_val;
      }
   }

   //random number generator
   for (int k = 0; k < sparse_matrix_size; ++k) {
      random_value = (rand() % max_random_value) * 0.1; //multiply by 0.1 to ensure range 0 - 1
      random_row = rand() % max_random_value;
      random_column = rand() % max_random_value;
      (mDyn[random_row])[random_column] = random_value;
   }

   startTime = clock();  // ------------------ start
   matMultDyn(mDyn, mDyn, ansDyn);
   stopTime = clock();  // ---------------------- stop

   //print time and size
   matShowDyn(ansDyn, 0, sparse_matrix_size);
   cout << "\nSize = " << MAT_SIZE << " Dyn Array Mult Elapsed Time: " << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC << " seconds." << endl << endl;

   //_getch();
   return 0;
}
//------------------------------------------------Run--------------------------------------------------------
//0.14    0       0       0.08    0       0.36    0       0.36    0       0       0       0
//0       0       0       0.12    0.27    0.12    0       0       0.04    0       0       0
//0       0       0       0       0       0       0       0       0       0       0       0
//0       0       0       0       0.54    0       0       0       0       0       0       0
//0       0       0       0       0       0       0       0       0       0       0       0
//0       0       0       0       0       0.36    0       0       0       0       0       0
//0       0       0       0       0       0       0       0       0       0       0       0
//0       0       0       0       0       0       0       0       0       0       0       0
//0       0       0       0.42    0       0.42    0       0.24    0.14    0       0       0
//0       0       0       0       0       0       0       0       0       0       0       0
//0       0       0       0       0       0       0       0       0       0       0       0
//0       0       0       0       0       0       0       0       0       0       0       0
//
//Size = 200 Dyn Array Mult Elapsed Time : 0.056 seconds.
//---------------------------------------------Assignment Questions--------------------------------------------------
//1. Smallest value M with non zero time was 45
//2. M |45      90      135     180    225
//Time |0.001   0.008   0.031   0.04   0.115 (seconds)
//3. The program would not respond (or I didnt wait long enough) when I set M to 1500, at 1200 time was 15.998
//4. I expected to see O(N^3) since I used three for loops in my multiplication matrix algorithm. The times seem to display that and is even more 
//noticible when M gets larger. Big Theta would also be N^3 because the (Omega) lower limit is also be N^3.
//---------------------------------------------End of Submission-------------------------------------------------------