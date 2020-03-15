#include <iostream>
//#include <conio.h>
#include <vector>
#include <exception>
#include <cmath>
#include <stdlib.h>
#include <time.h> 
#include "FHhashQP"
#include "FHsort.h"
#include "FHvector.h"
#include "EBookEntry.h"

using namespace std;
//--------------------------CLIENT/GLOBAL Prototypes--------------------------
int Hash(const EBookEntry & item);
int Hash(const string & key);
int Hash(int key);
//string getKey(const EBookEntry & item); //-----string equality
int getKey(const EBookEntry & item); //-----ID equality
//----------------FHhashQP-----------------------------------------
template <class Object>
class FHhashQP
{
protected:
   static const int INIT_TABLE_SIZE = 7;
   static const float INIT_MAX_LAMBDA;

   enum ElementState { ACTIVE, EMPTY, DELETED };
   class HashEntry;

   FHvector<HashEntry> mArray;
   int mSize;
   int mLoadSize;
   int mTableSize;
   float mMaxLambda;

public:
   FHhashQP(int tableSize = INIT_TABLE_SIZE);
   bool contains(const Object & x) const;
   void makeEmpty();
   bool insert(const Object & x);
   bool remove(const Object & x);
   static long nextPrime(long n);
   int size() const { return mSize; }
   bool setMaxLambda(float lm);

protected:
   void rehash();
   int myHash(const Object & x) const;
   int findPos(const Object & x) const;
};
template <class Object>
const float FHhashQP<Object>::INIT_MAX_LAMBDA = 0.49F;
// definition of nested FHhashQP<Object>::HashEntry class ----------------
template <class Object>
class FHhashQP<Object>::HashEntry
{
public:
   Object data;
   ElementState state;
   HashEntry(const Object & d = Object(), ElementState st = EMPTY)
      : data(d), state(st)
   { }
};
// FHhashQP method definitions -------------------
template <class Object>
FHhashQP<Object>::FHhashQP(int tableSize) : mSize(0), mLoadSize(0)
{
   if (tableSize < INIT_TABLE_SIZE)
      mTableSize = INIT_TABLE_SIZE;
   else
      mTableSize = nextPrime(tableSize);
   mArray.resize(mTableSize);
   makeEmpty();
   mMaxLambda = INIT_MAX_LAMBDA;
}
template <class Object>
int FHhashQP<Object>::myHash(const Object & x) const
{
   int hashVal;

   hashVal = Hash(x) % mTableSize;
   if (hashVal < 0)
      hashVal += mTableSize;

   return hashVal;
}
template <class Object>
void FHhashQP<Object>::makeEmpty()
{
   int k, size = mArray.size();

   for (k = 0; k < size; k++)
      mArray[k].state = EMPTY;
   mSize = mLoadSize = 0;
}
template <class Object>
bool FHhashQP<Object>::contains(const Object & x) const
{
   return mArray[findPos(x)].state == ACTIVE;
}
template <class Object>
bool FHhashQP<Object>::remove(const Object & x)
{
   int bucket = findPos(x);

   if (mArray[bucket].state != ACTIVE)
      return false;

   mArray[bucket].state = DELETED;
   mSize--;      // mLoadSize not dec'd because it counts any non-EMP location
   return true;
}
template <class Object>
bool FHhashQP<Object>::insert(const Object & x)
{
   int bucket = findPos(x);

   if (mArray[bucket].state == ACTIVE)
      return false;

   mArray[bucket].data = x;
   mArray[bucket].state = ACTIVE;
   mSize++;

   // check load factor 
   if (++mLoadSize > mMaxLambda * mTableSize)
      rehash();

   return true;
}
template <class Object>
int FHhashQP<Object>::findPos(const Object & x) const
{
   int kthOddNum = 1;
   int index = myHash(x);

   while (mArray[index].state != EMPTY
      && mArray[index].data != x)
   {
      index += kthOddNum;  // k squared = (k-1) squared + kth odd #
      kthOddNum += 2;   // compute next odd #
      if (index >= mTableSize)
         index -= mTableSize;
   }

   return index;
}
template <class Object>
void FHhashQP<Object>::rehash()
{
   FHvector<HashEntry> oldArray = mArray;
   int k, oldTableSize = mTableSize;

   mTableSize = nextPrime(2 * oldTableSize);
   mArray.resize(mTableSize);
   for (k = 0; k < mTableSize; k++)
      mArray[k].state = EMPTY;

   mSize = mLoadSize = 0;
   for (k = 0; k < oldTableSize; k++)
      if (oldArray[k].state == ACTIVE)
         insert(oldArray[k].data);
}
template <class Object>
bool FHhashQP<Object>::setMaxLambda(float lam)
{
   if (lam < .1 || lam > .49)
      return false;
   mMaxLambda = lam;
   return true;
}
template <class Object>
long FHhashQP<Object>::nextPrime(long n)
{
   long k, candidate, loopLim;

   // loop doesn't work for 2 or 3
   if (n <= 2)
      return 2;
   else if (n == 3)
      return 3;

   for (candidate = (n % 2 == 0) ? n + 1 : n; true; candidate += 2)
   {
      // all primes > 3 are of the form 6k +/- 1
      loopLim = (long)((sqrt((float)candidate) + 1) / 6);

      // we know it is odd.  check for divisibility by 3
      if (candidate % 3 == 0)
         continue;

      // now we can check for divisibility of 6k +/- 1 up to sqrt
      for (k = 1; k <= loopLim; k++)
      {
         if (candidate % (6 * k - 1) == 0)
            break;
         if (candidate % (6 * k + 1) == 0)
            break;
      }
      if (k > loopLim)
         return candidate;
   }
}//----------------------------FHhashQPwFind----------------------------
//-------------------FHhashQPwFind----------------------------------
template <class Object, typename KeyType>
class FHhashQPwFind : public FHhashQP<Object>
{
public:
   const Object find(const KeyType & key);
protected:
   int myHashKey(const KeyType & key) const;
   int findPosKey(const KeyType & key) const;

public:
   class NotFoundException {};
};
//----------------PUBLIC METHODS-------------------------------
template <class Object, typename KeyType>
const Object FHhashQPwFind<Object, KeyType>::find(const KeyType & key) {
   typename FHhashQP<Object>::HashEntry searchResult = this->mArray[findPosKey(key)];
   if (getKey(searchResult.data) == key) {
      return searchResult.data;
   }
   throw NotFoundException();
}
//----------------PROTECTED METHODS----------------------------
template <class Object, typename KeyType>
int FHhashQPwFind<Object, KeyType>::myHashKey(const KeyType & key) const
{
   int hashVal;

   hashVal = Hash(key) % this->mTableSize;
   if (hashVal < 0)
      hashVal += this->mTableSize;

   return hashVal;
}
template <class Object, typename KeyType>
int FHhashQPwFind<Object, KeyType>::findPosKey(const KeyType & key) const
{
   int kthOddNum = 1;
   int index = myHashKey(key);

   while (this->mArray[index].state != FHhashQP<Object>::EMPTY
      && getKey(this->mArray[index].data) != key)
   {
      index += kthOddNum;  // k squared = (k-1) squared + kth odd #
      kthOddNum += 2;   // compute next odd #
      if (index >= this->mTableSize)
         index -= this->mTableSize;
   }
   return index;
}
//---------------------------main------------------------------------------
int main() {
   EBookEntryReader mylibrary("catalog-short4.txt");
   FHhashQPwFind<EBookEntry, int> hashTable; //-----for ID equality
   //FHhashQPwFind<EBookEntry, string> hashTable; //-----for any string equality
   EBookEntry::setSortType(EBookEntry::SORT_BY_ID); //-----ID
   //EBookEntry::setSortType(EBookEntry::SORT_BY_CREATOR); //-----string
   const int library_size = mylibrary.getNumBooks(); //4863

   //generate random indices
   srand(time(NULL)); //initilize random seed
   int random_ints[25];
   const int size_of_random_ints = 25;
   for (int i = 0; i < size_of_random_ints; ++i) {
      int x = rand() % library_size + 1;
      random_ints[i] = x;
   }
   cout << "25 random ints generated" << endl;
   cout << "---------------------------" << endl;
   //load books into hashtable
   cout << "Load books with random idices into hashTable" << endl;
   for (int j = 0; j < size_of_random_ints; ++j) {
      hashTable.insert(mylibrary[random_ints[j]]);
   }
   //display the random indices w/ their entries
   cout << "Display random ints w/ book" << endl;
   for (int k = 0; k < size_of_random_ints; ++k) {
      cout << "RANDOM ints[" << k << "]: " << random_ints[k] << "\t";
      cout << "BOOK in hashtable: " << mylibrary[random_ints[k]].getTitle() << endl;
   }
   cout << "---------------------------" << endl;

   //---------------Test for int
   cout << "Testing find using id(int)" << endl;
   EBookEntry findbook;
   try {
      for (int i = 0; i < size_of_random_ints; ++i) {
         findbook = hashTable.find(mylibrary[random_ints[i]].getETextNum());
         cout << "Hashtable #" << i << ": " << findbook.getTitle() << endl;
      }
   }
   catch (FHhashQPwFind<EBookEntry, int>::NotFoundException & e) {
      cout << "NOT FOUND" << endl;
   }
   cout << "---------------------------" << endl;
   //fail x2
   cout << "FAIL TWICE" << endl;
   try {
      int x = rand() % library_size + 1; //low chance of generating a duplicate
      findbook = hashTable.find(x);
      cout << "FOUND: " << findbook.getTitle() << endl;
   }
   catch (FHhashQPwFind<EBookEntry, int>::NotFoundException & e) {
      cout << "NOT FOUND" << endl;
   }
   try {
      int x = rand() % library_size + 1;
      findbook = hashTable.find(x);
      cout << "FOUND: " << findbook.getTitle() << endl;
   }
   catch (FHhashQPwFind<EBookEntry, int>::NotFoundException & e) {
      cout << "NOT FOUND" << endl;
   }
   //----------------END of int test

  //---------------test for string
    // cout << "Testing find using creator(string)" << endl;
    // EBookEntry findbook;
    // try {
    //    for (int i = 0; i < size_of_random_ints; ++i) {
    //       findbook = hashTable.find(mylibrary[random_ints[i]].getCreator());
    //       cout << "Hashtable #" << i << ": " << findbook.getTitle() << endl;
    //    }
    //}
    // catch (FHhashQPwFind<EBookEntry, string>::NotFoundException & e) {
    //    cout << "NOT FOUND" << endl;
    // }
    // cout << "---------------------------" << endl;
    // //fail x2
    // cout << "FAIL TWICE" << endl;
    // try {
    //    findbook = hashTable.find("Bill Shakespeare");
    //    cout << "FOUND: " << findbook.getTitle() << endl;
    // }
    // catch (FHhashQPwFind<EBookEntry, string>::NotFoundException & e) {
    //    cout << "NOT FOUND" << endl;
    // }
    // try {
    //    findbook = hashTable.find("Steve King");
    //    cout << "FOUND: " << findbook.getTitle() << endl;
    // }
    // catch (FHhashQPwFind<EBookEntry, string>::NotFoundException & e) {
    //    cout << "NOT FOUND" << endl;
    // }
  //--------END OF string test

   //_getch();
   return 0;
}

//-----------Client/Global Function---------------------------------
int Hash(const EBookEntry & item)
{
   return Hash(item.getETextNum());  //-----ID equality
   //return Hash( item.getCreator() );  //-----string equality
}

// a hash routine for strings that admits negative returns
int Hash(const string & key)
{
   unsigned int k, retVal = 0;

   for (k = 0; k < key.length(); k++)
      retVal = 37 * retVal + key[k];

   return retVal;
}
int Hash(int key)
{
   return key;
}
//string getKey(const EBookEntry & item) //-----string
//{
//   return item.getCreator();
//}
int getKey(const EBookEntry & item) //-----ID
{
   return item.getETextNum();
}
//---------------------------RUN FOR FHhashQPwFind<EBookEntry, int> hashTable;
//25 random ints generated
//-------------------------- -
//Load books with random idices into hashTable
//Display random ints w / book
//RANDOM ints[0]: 3072    BOOK in hashtable : Notes and Queries, Number 227, March 4, 1854A Medium of Inter - communication for Literary Men, Artists, Antiquaries, Genealogists, etc.
//RANDOM ints[1] : 3854    BOOK in hashtable : Little Women
//RANDOM ints[2] : 3336    BOOK in hashtable : Adenoids: What They Are, How To Recognize Them, What To Do For Them
//RANDOM ints[3] : 4633    BOOK in hashtable : The Idler Magazine, Volume III, March 1893An Illustrated Monthly
//RANDOM ints[4] : 2451    BOOK in hashtable : Commercialism and Journalism
//RANDOM ints[5] : 3321    BOOK in hashtable : Suspended JudgmentsEssays on Books and Sensations
//RANDOM ints[6] : 3465    BOOK in hashtable : Crooked Trails and Straight
//RANDOM ints[7] : 2327    BOOK in hashtable : Seven O'Clock Stories
//RANDOM ints[8] : 1109    BOOK in hashtable : Three Young Knights
//RANDOM ints[9] : 187     BOOK in hashtable : Opening Ceremonies of the New York and Brooklyn Bridge, May 24, 1883
//RANDOM ints[10] : 3151   BOOK in hashtable : The Sign of the Spider
//RANDOM ints[11] : 1191   BOOK in hashtable : RussiaAs Seen and Described by Famous Writers
//RANDOM ints[12] : 799    BOOK in hashtable : The Bobbsey Twins in the Great West
//RANDOM ints[13] : 787    BOOK in hashtable : The Complete Poetical Works of Samuel Taylor ColeridgeVol I and II
//RANDOM ints[14] : 1115   BOOK in hashtable : The Palace of Pleasure, Volume 1
//RANDOM ints[15] : 1968   BOOK in hashtable : Two Dyaloges(c. 1549)
//RANDOM ints[16] : 4578   BOOK in hashtable : The Idler Magazine, Volume III, June 1893An Illustrated Monthly
//RANDOM ints[17] : 3207   BOOK in hashtable : A Little Maid of Massachusetts Colony
//RANDOM ints[18] : 1529   BOOK in hashtable : Ellen of Villenskovand Other Ballads
//RANDOM ints[19] : 248    BOOK in hashtable : The Book - CollectorA General Survey of the Pursuit and of those who haveengaged in it at Home and Abroad from the Earliest Periodto the Present Time
//RANDOM ints[20] : 1989   BOOK in hashtable : Kings in Exile
//RANDOM ints[21] : 4091   BOOK in hashtable : The Sailor's Word-BookAn Alphabetical Digest of Nautical Terms, including Some More Especially Military and Scientific, but Useful to Seamen; as well as Archaisms of Early Voyagers, etc.
//RANDOM ints[22] : 954    BOOK in hashtable : TheoA Sprightly Love Story
//RANDOM ints[23] : 4799   BOOK in hashtable : Tessa1901
//RANDOM ints[24] : 1436   BOOK in hashtable : Art in NeedleworkA Book about Embroidery
//-------------------------- -
//Testing find using id(int)
//Hashtable #0: Notes and Queries, Number 227, March 4, 1854A Medium of Inter - communication for Literary Men, Artists, Antiquaries, Genealogists, etc.
//Hashtable #1: Little Women
//Hashtable #2: Adenoids: What They Are, How To Recognize Them, What To Do For Them
//Hashtable #3: The Idler Magazine, Volume III, March 1893An Illustrated Monthly
//Hashtable #4: Commercialism and Journalism
//Hashtable #5: Suspended JudgmentsEssays on Books and Sensations
//Hashtable #6: Crooked Trails and Straight
//Hashtable #7: Seven O'Clock Stories
//Hashtable #8: Three Young Knights
//Hashtable #9: Opening Ceremonies of the New York and Brooklyn Bridge, May 24, 1883
//Hashtable #10: The Sign of the Spider
//Hashtable #11: RussiaAs Seen and Described by Famous Writers
//Hashtable #12: The Bobbsey Twins in the Great West
//Hashtable #13: The Complete Poetical Works of Samuel Taylor ColeridgeVol I and II
//Hashtable #14: The Palace of Pleasure, Volume 1
//Hashtable #15: Two Dyaloges(c. 1549)
//Hashtable #16: The Idler Magazine, Volume III, June 1893An Illustrated Monthly
//Hashtable #17: A Little Maid of Massachusetts Colony
//Hashtable #18: Ellen of Villenskovand Other Ballads
//Hashtable #19: The Book - CollectorA General Survey of the Pursuit and of those who haveengaged in it at Home and Abroad from the Earliest Periodto the Present Time
//Hashtable #20: Kings in Exile
//Hashtable #21: The Sailor's Word-BookAn Alphabetical Digest of Nautical Terms, including Some More Especially Military and Scientific, but Useful to Seamen; as well as Archaisms of Early Voyagers, etc.
//Hashtable #22: TheoA Sprightly Love Story
//Hashtable #23: Tessa1901
//Hashtable #24: Art in NeedleworkA Book about Embroidery
//-------------------------- -
//FAIL TWICE
//NOT FOUND
//NOT FOUND

//-----------------------------RUN for FHhashQPwFind<EBookEntry, string> hashTable;
//25 random ints generated
//-------------------------- -
//Load books with random idices into hashTable
//Display random ints w / book
//RANDOM ints[0]: 2409    BOOK in hashtable : Word Study and English GrammarA Primer of Information about Words, Their Relations and Their Uses
//RANDOM ints[1] : 4068    BOOK in hashtable : Religion and Theology : A Sermon for the TimesPreached in the Parish Church of Crathie, fifth September and in the College Church, St Andrews
//RANDOM ints[2] : 841     BOOK in hashtable : The Rival Campers AshoreThe Mystery of the Mill
//RANDOM ints[3] : 2212    BOOK in hashtable : The Plain Man and His Wife
//RANDOM ints[4] : 881     BOOK in hashtable : The Philadelphia Magazines and their Contributors 1741 - 1850
//RANDOM ints[5] : 2353    BOOK in hashtable : Elementary Theosophy
//RANDOM ints[6] : 3956    BOOK in hashtable : Laurence Sterne in GermanyA Contribution to the Study of the Literary Relations ofEngland and Germany in the Eighteenth Century
//RANDOM ints[7] : 1877    BOOK in hashtable : Punch or the London Charivari, Vol. 147, October 7, 1914
//RANDOM ints[8] : 1318    BOOK in hashtable : Poems
//RANDOM ints[9] : 3061    BOOK in hashtable : The story of my first novel; How a novel is written
//RANDOM ints[10]: 408    BOOK in hashtable : Records of a Family of Engineers
//RANDOM ints[11] : 1976   BOOK in hashtable : Little Brother
//RANDOM ints[12] : 4276   BOOK in hashtable : The Pretty Sister Of Jos├⌐1889
//RANDOM ints[13] : 2397   BOOK in hashtable : Comedies by Holberg : Jeppe of the Hill, The Political Tinker, Erasmus Montanus
//RANDOM ints[14] : 4774   BOOK in hashtable : Stray Leaves from an Arctic Journal; or , Eighteen Months in the Polar Regions, in Search of SirJohn Franklin's Expedition, in the Years 1850-51
//RANDOM ints[15]: 3100   BOOK in hashtable : The 2003 CIA World Factbook
//RANDOM ints[16] : 13     BOOK in hashtable : Astounding Stories, March, 1931
//RANDOM ints[17] : 2028   BOOK in hashtable : McTeague
//RANDOM ints[18] : 67     BOOK in hashtable : The Italian Twins
//RANDOM ints[19] : 4005   BOOK in hashtable : The Art of AnglingWherein are discovered many rare secrets, very necessaryto be knowne by all that delight in that recreation
//RANDOM ints[20] : 2717   BOOK in hashtable : Alice's Adventures in Wonderland
//RANDOM ints[21] : 2326   BOOK in hashtable : Chronicle of the Conquest of Granada
//RANDOM ints[22] : 368    BOOK in hashtable : Two New Pocket Gophers from Wyoming and Colorado
//RANDOM ints[23] : 3176   BOOK in hashtable : Sundry Accounts
//RANDOM ints[24] : 741    BOOK in hashtable : Strange Alliance
//-------------------------- -
//Testing find using creator(string)
//Hashtable #0: Word Study and English GrammarA Primer of Information about Words, Their Relations and Their Uses
//Hashtable #1: Religion and Theology : A Sermon for the TimesPreached in the Parish Church of Crathie, fifth September and in the College Church, St Andrews
//Hashtable #2: The Rival Campers AshoreThe Mystery of the Mill
//Hashtable #3: The Plain Man and His Wife
//Hashtable #4: The Philadelphia Magazines and their Contributors 1741 - 1850
//Hashtable #5: Elementary Theosophy
//Hashtable #6: Laurence Sterne in GermanyA Contribution to the Study of the Literary Relations ofEngland and Germany in the Eighteenth Century
//Hashtable #7: Punch or the London Charivari, Vol. 147, October 7, 1914
//Hashtable #8: Poems
//Hashtable #9: The story of my first novel; How a novel is written
//Hashtable #10: Records of a Family of Engineers
//Hashtable #11: Little Brother
//Hashtable #12: The Pretty Sister Of Jos├⌐1889
//Hashtable #13: Comedies by Holberg : Jeppe of the Hill, The Political Tinker, Erasmus Montanus
//Hashtable #14: Stray Leaves from an Arctic Journal; or , Eighteen Months in the Polar Regions, in Search of SirJohn Franklin's Expedition, in the Years 1850-51
//Hashtable #15: The 2003 CIA World Factbook
//Hashtable #16: Punch or the London Charivari, Vol. 147, October 7, 1914
//Hashtable #17: McTeague
//Hashtable #18: The Italian Twins
//Hashtable #19: The Art of AnglingWherein are discovered many rare secrets, very necessaryto be knowne by all that delight in that recreation
//Hashtable #20: Alice's Adventures in Wonderland
//Hashtable #21: Chronicle of the Conquest of Granada
//Hashtable #22: Two New Pocket Gophers from Wyoming and Colorado
//Hashtable #23: Sundry Accounts
//Hashtable #24: Strange Alliance
//-------------------------- -
//FAIL TWICE
//NOT FOUND
//NOT FOUND
//----------------------------END OF SUBMISSION--------------------------------------------------------