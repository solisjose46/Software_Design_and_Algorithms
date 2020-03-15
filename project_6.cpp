#include <iostream>
//#include <conio.h>
#include <time.h>
#include <math.h>
#include "FHvector.h"

using namespace std;
//----------------ArraySize----------------------------------
#define ARRAY_SIZE 10000
//#define ARRAY_SIZE 41000
//#define ARRAY_SIZE 72000
//#define ARRAY_SIZE 103000
//#define ARRAY_SIZE 134000
//#define ARRAY_SIZE 200000
//----------------gap sequeces------ 
//implied sequence shellSort1()
int gapArray[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288 };
int sedgewickArray[14]; //very large numbers, overflows at 15
int MarcinArray[] = { 1,4,10,23,57,132,301,701,
1750,3937,8858,19930,44842 };
//----------------shellSortX---------------------------------
template <typename Comparable>
void shellSortX(FHvector<Comparable> & a, int gaps[], int gapArraySize)
{
   int k, pos, arraySize, GAP, MAX_GAP_SIZE;
   Comparable tmp;
   //get largest appropriate gap size
   for (int j = 0; j < gapArraySize; ++j) {
      if (gaps[j] > floor(ARRAY_SIZE / 3)) {
         MAX_GAP_SIZE = j;
         break;
      }
      else if (j == gapArraySize - 1) {
         MAX_GAP_SIZE = j;
      }
   }
   arraySize = a.size();
   for (int i = 0; i <= MAX_GAP_SIZE; ++i) {
      GAP = gaps[MAX_GAP_SIZE - i];
      for (pos = GAP; pos < arraySize; pos++)
      {
         tmp = a[pos];
         for (k = pos; k >= GAP && tmp < a[k - GAP]; k -= GAP)
            a[k] = a[k - GAP];
         a[k] = tmp;
      }
   }

}
//-----------------shellSort #1-------------------------------
template <typename Comparable>
void shellSort1(FHvector<Comparable> & a)
{
   int k, pos, arraySize, ONE;
   Comparable tmp;

   arraySize = a.size();
   for (ONE = arraySize / 2; ONE > 0; ONE /= 2)
      for (pos = ONE; pos < arraySize; pos++)
      {
         tmp = a[pos];
         for (k = pos; k >= ONE && tmp < a[k - ONE]; k -= ONE)
            a[k] = a[k - ONE];
         a[k] = tmp;
      }
}
//------------------------main-----------------------------
int main() {
   clock_t startTime, stopTime;
   double time1, time2, time3, time4;

   //initialize sedgewickArray 
   cout << "initialize and display sedgewick" << endl;
   for (int j = 0; j < sizeof(sedgewickArray) / sizeof(sedgewickArray[0]); ++j) {
      sedgewickArray[j] = 9 * pow(4, j) - 9 * pow(2, j) + 1;
      cout << j << ": " << sedgewickArray[j] << endl;
   }
   //initialize vecotors w/ randoms
   FHvector<int> fhVectorOfInts1; //shellSort1
   FHvector<int> fhVectorOfInts2; //spec
   FHvector<int> fhVectorOfInts3; //sedgewick
   FHvector<int> fhVectorOfInts4; //Marcin
   srand(time(NULL));
   for (int i = 0; i < ARRAY_SIZE; ++i) {
      int random = rand() % ARRAY_SIZE;
      fhVectorOfInts1.push_back(random);
      fhVectorOfInts2.push_back(random);
      fhVectorOfInts3.push_back(random);
      fhVectorOfInts4.push_back(random);
   }
   cout << "------------------------------------------------" << endl;
   //array sizes
   int MarcinArraySize = sizeof(MarcinArray) / sizeof(MarcinArray[0]);
   int SedgewickArraySize = sizeof(sedgewickArray) / sizeof(sedgewickArray[0]);;
   int gapArraysize = sizeof(gapArray) / sizeof(gapArray[0]);
   //shellSort1
   startTime = clock();
   shellSort1(fhVectorOfInts1);
   stopTime = clock();
   time1 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;
   //gapArray
   startTime = clock();
   shellSortX(fhVectorOfInts2, gapArray, gapArraysize);
   stopTime = clock();
   time2 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;
   //sedgewick
   startTime = clock();
   shellSortX(fhVectorOfInts3, sedgewickArray, SedgewickArraySize);
   stopTime = clock();
   time3 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;
   //Marcin
   startTime = clock();
   shellSortX(fhVectorOfInts4, MarcinArray, MarcinArraySize);
   stopTime = clock();
   time4 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;
   //display times
   cout << "shellSort1 time: " << time1 << " seconds" << endl;
   cout << "gapArray time: " << time2 << " seconds" << endl;
   cout << "Sedgewick time: " << time3 << " seconds" << endl;
   cout << "Marcin time: " << time4 << " seconds" << endl;

   //_getch();
   return 0;
}
//-----------------------RUN ArraySize 10,000------------------------
//initialize and display sedgewick
//0: 1
//1 : 19
//2 : 109
//3 : 505
//4 : 2161
//5 : 8929
//6 : 36289
//7 : 146305
//8 : 587521
//9 : 2354689
//10 : 9427969
//11 : 37730305
//12 : 150958081
//13 : 603906049
//------------------------------------------------
//shellSort1 time : 0.028 seconds
//gapArray time : 0.052 seconds
//Sedgewick time : 0.024 seconds
//Marcin time : 0.014 seconds
//-----------------------RUN ArraySize 41,000------------------------
//shellSort1 time : 0.154 seconds
//gapArray time : 0.348 seconds
//Sedgewick time : 0.128 seconds
//Marcin time : 0.067 seconds
//-----------------------RUN ArraySize 72,000------------------------
//shellSort1 time : 0.248 seconds
//gapArray time : 0.702 seconds
//Sedgewick time : 0.215 seconds
//Marcin time : 0.137 seconds
//-----------------------RUN ArraySize 103,000------------------------
//shellSort1 time : 0.354 seconds
//gapArray time : 1.268 seconds
//Sedgewick time : 0.316 seconds
//Marcin time : 0.244 seconds
//-----------------------RUN ArraySize 134,000------------------------
//shellSort1 time : 0.467 seconds
//gapArray time : 2.167 seconds
//Sedgewick time : 0.464 seconds
//Marcin time : 0.269 seconds
//-----------------------RUN ArraySize 200,000------------------------
//shellSort1 time : 0.828 seconds
//gapArray time : 2.833 seconds
//Sedgewick time : 0.609 seconds
//Marcin time : 0.405 seconds
//------------------------Citation--------------------------
//credit for MarcinArray(how do you cite a paper in a cpp?),
//Best Increments for the Average Case of Shellsort by Marin Ciura
//Department of Computer Science, Silesian Institute of Technology
//-----------------------HW Question---------------------------
//As explained in the module, gapArray's gaps are calculated by
//the formula 2k. This will result in only even gaps computed
//(powers of 2) which will result in even postions not mixing
//w/ odd until the final pass when N = 1 which is just
//insertion sort. = slow
//For shellsort1, the default gap sequence, gap = N/2,
//computes gaps that are not only powers of 2. This variety is why
//shellsort1 is faster.
//Overall, Marcin > Sedgewick > shellSort1 > gapArray
//-------------------------------END of SUBMISSION----------------