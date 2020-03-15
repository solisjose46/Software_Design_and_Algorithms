#include <iostream>
//#include <conio.h>
#include <time.h>
#include "FHsort.h"
#include "FHvector.h"

using namespace std;

//define array size and recursive limit
#define ARRAY_SIZE 40000
//#define ARRAY_SIZE 110000
//#define ARRAY_SIZE 180000
//#define ARRAY_SIZE 250000
#define RECURSIVE_LIMIT 2
//-------------------------------quickSortX---------------------
template <typename Comparable>
void quickSortX(FHvector<Comparable> & a, int left, int right, int & recLimit) {
   Comparable pivot;
   int i, j;

   if (left + recLimit <= right)
   {
      pivot = median3(a, left, right);
      for (i = left, j = right - 1; ; )
      {
         while (a[++i] < pivot)
            ;
         while (pivot < a[--j])
            ;
         if (i < j)
            mySwapFH(a[i], a[j]);
         else
            break;
      }

      mySwapFH(a[i], a[right - 1]);

      quickSortX(a, left, i - 1, recLimit);
      quickSortX(a, i + 1, right, recLimit);
   }
   else {
      insertionSort(a, left, right);
   }
}
// quickSortX public driver
template <typename Comparable>
void quickSortX(FHvector<Comparable> & a, int & recLimit)
{
   quickSortX(a, 0, a.size() - 1, recLimit);
}
//----------------------------------main-----------------------
int main() {
   FHvector <int> myvector;
   clock_t startTime, stopTime;
   double time1;
   int recLimit;

   //quickSortX recLimit 2 - 300
   srand(time(NULL));
   for (int k = RECURSIVE_LIMIT; k <= 300; k += 2) {
      myvector.clear();
      for (int i = 0; i < ARRAY_SIZE; ++i) {
         int random = rand() % ARRAY_SIZE + 1;
         myvector.push_back(random);
      }
      recLimit = k;
      startTime = clock();
      quickSortX(myvector, recLimit);
      stopTime = clock();
      time1 = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;
      cout << "LIMIT: " << recLimit << " this time: " << time1 << endl;
   }
   //_getch();
   return 0;
}
//----------------------TABLE---------------------------
//-----Array Size 40000-----
/* LIMIT: 2 this time : 0.054
   LIMIT : 20 this time : 0.072
   LIMIT : 38 this time : 0.078
   LIMIT : 56 this time : 0.047
   LIMIT : 74 this time : 0.068
   LIMIT : 92 this time : 0.062
   LIMIT : 94 this time : 0.058
   LIMIT : 96 this time : 0.057
   LIMIT : 98 this time : 0.079
   LIMIT : 100 this time : 0.102
   LIMIT : 102 this time : 0.06
   LIMIT : 104 this time : 0.087
   LIMIT : 106 this time : 0.068
   LIMIT : 108 this time : 0.064
   LIMIT : 110 this time : 0.102
   LIMIT : 130 this time : 0.073
   LIMIT : 132 this time : 0.073
   LIMIT : 134 this time : 0.104
   LIMIT : 136 this time : 0.114
   LIMIT : 138 this time : 0.072
   LIMIT : 140 this time : 0.079
   LIMIT : 142 this time : 0.075
   LIMIT : 144 this time : 0.08
   LIMIT : 146 this time : 0.079
   LIMIT : 148 this time : 0.101
   LIMIT : 150 this time : 0.081
   LIMIT : 152 this time : 0.088
   LIMIT : 154 this time : 0.082
   LIMIT : 156 this time : 0.118
   LIMIT : 158 this time : 0.086
   LIMIT : 160 this time : 0.082
   LIMIT : 162 this time : 0.114
   LIMIT : 164 this time : 0.088
   LIMIT : 166 this time : 0.088
   LIMIT : 168 this time : 0.084
   LIMIT : 170 this time : 0.094
   LIMIT : 172 this time : 0.121
   LIMIT : 174 this time : 0.091
   LIMIT : 176 this time : 0.106
   LIMIT : 178 this time : 0.109
   LIMIT : 180 this time : 0.113
   LIMIT : 182 this time : 0.098
   LIMIT : 184 this time : 0.092
   LIMIT : 186 this time : 0.146
   LIMIT : 188 this time : 0.096
   LIMIT : 190 this time : 0.098
   LIMIT : 192 this time : 0.105
   LIMIT : 210 this time : 0.178
   LIMIT : 228 this time : 0.12
   LIMIT : 246 this time : 0.118
   LIMIT : 264 this time : 0.142
   LIMIT : 282 this time : 0.139
   LIMIT : 300 this time : 0.144
   //-----Array Size 110000-----
   LIMIT : 2 this time : 0.104
   LIMIT : 4 this time : 0.125
   LIMIT : 6 this time : 0.1
   LIMIT : 8 this time : 0.083
   LIMIT : 10 this time : 0.084
   LIMIT : 12 this time : 0.087
   LIMIT : 14 this time : 0.132
   LIMIT : 16 this time : 0.092
   LIMIT : 18 this time : 0.088
   LIMIT : 20 this time : 0.097
   LIMIT : 22 this time : 0.101
   LIMIT : 24 this time : 0.093
   LIMIT : 26 this time : 0.101
   LIMIT : 28 this time : 0.098
   LIMIT : 30 this time : 0.098
   LIMIT : 32 this time : 0.11
   LIMIT : 50 this time : 0.127
   LIMIT : 68 this time : 0.134
   LIMIT : 86 this time : 0.163
   LIMIT : 104 this time : 0.179
   LIMIT : 124 this time : 0.208
   LIMIT : 140 this time : 0.219
   LIMIT : 142 this time : 0.244
   LIMIT : 160 this time : 0.239
   LIMIT : 178 this time : 0.262
   LIMIT : 180 this time : 0.268
   LIMIT : 182 this time : 0.271
   LIMIT : 184 this time : 0.287
   LIMIT : 186 this time : 0.279
   LIMIT : 188 this time : 0.302
   LIMIT : 190 this time : 0.281
   LIMIT : 192 this time : 0.302
   LIMIT : 194 this time : 0.293
   LIMIT : 196 this time : 0.279
   LIMIT : 198 this time : 0.303
   LIMIT : 200 this time : 0.31
   LIMIT : 202 this time : 0.292
   LIMIT : 204 this time : 0.301
   LIMIT : 206 this time : 0.285
   LIMIT : 208 this time : 0.306
   LIMIT : 226 this time : 0.323
   LIMIT : 244 this time : 0.351
   LIMIT : 262 this time : 0.381
   LIMIT : 264 this time : 0.392
   LIMIT : 266 this time : 0.359
   LIMIT : 268 this time : 0.38
   LIMIT : 270 this time : 0.405
   LIMIT : 272 this time : 0.382
   LIMIT : 274 this time : 0.384
   LIMIT : 276 this time : 0.394
   LIMIT : 278 this time : 0.383
   LIMIT : 280 this time : 0.392
   LIMIT : 282 this time : 0.39
   LIMIT : 284 this time : 0.367
   LIMIT : 286 this time : 0.4
   LIMIT : 288 this time : 0.412
   LIMIT : 290 this time : 0.414
   LIMIT : 292 this time : 0.405
   LIMIT : 294 this time : 0.439
   LIMIT : 296 this time : 0.416
   LIMIT : 298 this time : 0.44
   LIMIT : 300 this time : 0.415
   //-----Array Size 180000-----
   LIMIT : 2 this time : 0.177
   LIMIT : 38 this time : 0.178
   LIMIT : 54 this time : 0.209
   LIMIT : 72 this time : 0.23
   LIMIT : 74 this time : 0.257
   LIMIT : 76 this time : 0.423
   LIMIT : 78 this time : 0.412
   LIMIT : 80 this time : 0.417
   LIMIT : 82 this time : 0.373
   LIMIT : 84 this time : 0.4
   LIMIT : 86 this time : 0.475
   LIMIT : 88 this time : 0.431
   LIMIT : 90 this time : 0.292
   LIMIT : 92 this time : 0.268
   LIMIT : 94 this time : 0.272
   LIMIT : 96 this time : 0.28
   LIMIT : 98 this time : 0.28
   LIMIT : 100 this time : 0.389
   LIMIT : 102 this time : 0.279
   LIMIT : 104 this time : 0.287
   LIMIT : 106 this time : 0.345
   LIMIT : 108 this time : 0.293
   LIMIT : 110 this time : 0.294
   LIMIT : 112 this time : 0.3
   LIMIT : 114 this time : 0.301
   LIMIT : 116 this time : 0.425
   LIMIT : 118 this time : 0.318
   LIMIT : 120 this time : 0.313
   LIMIT : 122 this time : 0.554
   LIMIT : 124 this time : 0.371
   LIMIT : 126 this time : 0.362
   LIMIT : 128 this time : 0.344
   LIMIT : 130 this time : 0.332
   LIMIT : 132 this time : 0.528
   LIMIT : 134 this time : 0.352
   LIMIT : 136 this time : 0.353
   LIMIT : 138 this time : 0.392
   LIMIT : 140 this time : 0.366
   LIMIT : 142 this time : 0.362
   LIMIT : 144 this time : 0.515
   LIMIT : 146 this time : 0.637
   LIMIT : 148 this time : 0.644
   LIMIT : 150 this time : 0.658
   LIMIT : 152 this time : 0.665
   LIMIT : 154 this time : 0.656
   LIMIT : 156 this time : 0.651
   LIMIT : 158 this time : 0.669
   LIMIT : 160 this time : 0.683
   LIMIT : 162 this time : 0.681
   LIMIT : 164 this time : 0.683
   LIMIT : 166 this time : 0.704
   LIMIT : 184 this time : 0.772
   LIMIT : 186 this time : 0.76
   LIMIT : 188 this time : 0.78
   LIMIT : 190 this time : 0.78
   LIMIT : 192 this time : 0.795
   LIMIT : 194 this time : 0.782
   LIMIT : 196 this time : 0.794
   LIMIT : 198 this time : 0.873
   LIMIT : 200 this time : 0.899
   LIMIT : 202 this time : 0.851
   LIMIT : 204 this time : 0.905
   LIMIT : 206 this time : 0.843
   LIMIT : 208 this time : 0.906
   LIMIT : 210 this time : 0.837
   LIMIT : 212 this time : 0.877
   LIMIT : 214 this time : 0.989
   LIMIT : 216 this time : 0.919
   LIMIT : 218 this time : 0.938
   LIMIT : 220 this time : 0.918
   LIMIT : 222 this time : 0.851
   LIMIT : 224 this time : 0.888
   LIMIT : 226 this time : 0.975
   LIMIT : 228 this time : 0.959
   LIMIT : 230 this time : 0.923
   LIMIT : 232 this time : 0.855
   LIMIT : 234 this time : 0.903
   LIMIT : 252 this time : 0.981
   LIMIT : 254 this time : 0.99
   LIMIT : 256 this time : 1.012
   LIMIT : 258 this time : 1.013
   LIMIT : 260 this time : 0.999
   LIMIT : 262 this time : 1.014
   LIMIT : 280 this time : 1.082
   LIMIT : 282 this time : 1.101
   LIMIT : 284 this time : 1.098
   LIMIT : 286 this time : 1.118
   LIMIT : 288 this time : 1.083
   LIMIT : 290 this time : 1.135
   LIMIT : 292 this time : 1.108
   LIMIT : 294 this time : 1.147
   LIMIT : 296 this time : 1.143
   LIMIT : 298 this time : 1.133
   LIMIT : 300 this time : 1.162
   //-----Array Size 250000-----
   LIMIT : 2 this time : 0.242
   LIMIT : 20 this time : 0.222
   LIMIT : 22 this time : 0.212
   LIMIT : 24 this time : 0.216
   LIMIT : 26 this time : 0.313
   LIMIT : 28 this time : 0.242
   LIMIT : 46 this time : 0.273
   LIMIT : 48 this time : 0.269
   LIMIT : 50 this time : 0.269
   LIMIT : 52 this time : 0.314
   LIMIT : 54 this time : 0.288
   LIMIT : 56 this time : 0.285
   LIMIT : 58 this time : 0.289
   LIMIT : 60 this time : 0.477
   LIMIT : 62 this time : 0.503
   LIMIT : 64 this time : 0.466
   LIMIT : 66 this time : 0.474
   LIMIT : 68 this time : 0.49
   LIMIT : 70 this time : 0.484
   LIMIT : 72 this time : 0.498
   LIMIT : 74 this time : 0.505
   LIMIT : 76 this time : 0.516
   LIMIT : 78 this time : 0.531
   LIMIT : 80 this time : 0.534
   LIMIT : 82 this time : 0.543
   LIMIT : 84 this time : 0.554
   LIMIT : 86 this time : 0.617
   LIMIT : 88 this time : 0.626
   LIMIT : 90 this time : 0.579
   LIMIT : 92 this time : 0.611
   LIMIT : 94 this time : 0.666
   LIMIT : 96 this time : 0.679
   LIMIT : 98 this time : 0.667
   LIMIT : 100 this time : 0.693
   LIMIT : 102 this time : 0.713
   LIMIT : 104 this time : 0.694
   LIMIT : 106 this time : 0.706
   LIMIT : 108 this time : 0.71
   LIMIT : 126 this time : 0.787
   LIMIT : 128 this time : 0.788
   LIMIT : 130 this time : 0.827
   LIMIT : 148 this time : 0.88
   LIMIT : 150 this time : 0.883
   LIMIT : 152 this time : 0.915
   LIMIT : 170 this time : 0.973
   LIMIT : 172 this time : 0.978
   LIMIT : 174 this time : 1.01
   LIMIT : 192 this time : 1.079
   LIMIT : 194 this time : 1.134
   LIMIT : 196 this time : 1.124
   LIMIT : 198 this time : 1.082
   LIMIT : 200 this time : 1.096
   LIMIT : 202 this time : 1.095
   LIMIT : 204 this time : 1.125
   LIMIT : 222 this time : 1.202
   LIMIT : 240 this time : 1.276
   LIMIT : 242 this time : 1.302
   LIMIT : 244 this time : 1.285
   LIMIT : 246 this time : 1.301
   LIMIT : 262 this time : 1.384
   LIMIT : 264 this time : 1.412
   LIMIT : 266 this time : 1.416
   LIMIT : 268 this time : 1.371
   LIMIT : 270 this time : 1.437
   LIMIT : 272 this time : 1.44
   LIMIT : 274 this time : 1.433
   LIMIT : 276 this time : 1.45
   LIMIT : 278 this time : 1.452
   LIMIT : 280 this time : 1.497
   LIMIT : 282 this time : 1.538
   LIMIT : 300 this time : 1.533 */
   //-----comments on data-----
   //It appears the most linear and fastest times occur when recursion
   //limit is set bewtween 8 - 20. Also, times before 8 tend to be slightly
   //slower. Most likely due to recursion limit set low and insertion
   //sort isn't called when its most optimal to do so. (Array size < 15)