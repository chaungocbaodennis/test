#include<stdio.h>
#include<string.h>
#include<time.h>
#include"linkedList.h"
#include"Dictionary.h"

int const buffer_size = 256;
	//char buffer[buffer_size];
enum BOOLEAN
{
	TRUE = 1,
	FALSE = 0,
};

enum state
{
	STATE1,
	STATE2,
	STATE3,
	STATE4,
	STATE5,
};

enum state state_var;

// A utility function of print an array of size n
void printArray(int arr[], int first,int end)
{
   int i;
   for (i=first; i <= end; i++)
       printf("%d ", arr[i]);
   printf("\n");
}

int fib_recursive(int n)
{
   if (n <= 1)
	   return n;
   else
	   return fib_recursive(n-1) + fib_recursive(n-2); //Time Complexity: T(n) = T(n-1) + T(n-2) which is exponential.
}


int fib_iterative(int n)
{
  int a = 0, b = 1, c, i;

  if( n == 0)
  {
    return a;
  }
  else if (n == 1)
  {
	  return b;
  }

  for (i = 2; i <= n; i++)
  {
     c = a + b;
     a = b;
     b = c;
  }
  return b;
}

/**********************************************************************
Determine whether an integer is a palindrome. Do this without extra space.
***********************************************************************/
char isPalindrome(int input_int) {
    if (input_int < 0)
    return 0;
    int div = 1;

    while (input_int / div >= 10)
    {
        div *= 10; //eventually, div == (#digit - 1)
    }

    while (input_int != 0)
    {
        int l = input_int / div; //left digit
        int r = input_int % 10; //right digit
        if (l != r)
        {
        	return 0;
        }
        input_int = (input_int % div) / 10; //chop left digit and then right digit
        div /= 100; //step down 2 digits
    }
    return 1;
}


/**********************************************************************
Given an integer, write a function to determine if it is a power of two.
***********************************************************************/
unsigned char isPowerOfTwo_divMethod(int n)
{
	if (n < 1 )
	{
		return 0;
	}
	else if ( n == 1)
	{
		return 1;
	}
	else
	{
		/*
		 * keep divide by 2
		 * once remainder non-zero: jump out the loop and return FALS
		 * however, corner case is when n reach 2:
		 * if reach 2 means definitely this is a power of 2
		 */
		while (n%2 == 0)
		{
			//printf("n is: %d \n", n);
			if ((n%2 == 0) && (n/2 == 1)) // This is when n == 2
			{
				return 1;
			}
			n /= 2;
		}
		return 0; // if exit to here, means not Power of 2
	}
}

unsigned char isPowerOfTwo_bitCheckMethod(int n)
{
	unsigned char idx,numOfBitOne = 0;
	unsigned char numOfBitToCheck = sizeof(n)*8 ;

	if (n < 1) return 0;

	/*
	 * if power of 2, should be only 1 digit "1"
	 */
	for (idx = 0; idx < numOfBitToCheck; idx ++)
	{
		if ((n & 0x00000001) == 1)
		{
			numOfBitOne++;
		}
		n = n >> 1;
	}

	if (numOfBitOne == 1) return 1;
	else return 0;
}


/***********************************************************************************************
Given an array and a value, remove all instances of that value in place and return the new length.
The order of elements can be changed. It doesn't matter what you leave beyond the new length.
************************************************************************************************/
int removeElement(int A[], int len, int elem)
{
/*
 * iterate from 0 to "the end"
 * if found element: set value of that position to value of "last item"
 * then "shrink" the array: len--
 * because at current position is the value of "last item"; so we don't need that "last item" in new array anymore
 */
	int i = 0;
    while(i < len)
    {
        if(A[i] == elem)
        {
        	len --; //new length shrink down 1
            A[i] = A[len]; //replace with "last value"
        }
        else //not equal, just continue to advance
        {
        	i++;
        }
    }
    return len;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////        BIT MANIPULATOR    ////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

/***********************************************************************************************
Reverse bits of a given 32 bits unsigned integer.
For example, given input 43261596 (represented in binary as 00000010100101000001111010011100), return 964176192 (represented in binary as 00111001011110000010100101000000).
************************************************************************************************/
unsigned int reverseBits(unsigned int n) {
	unsigned char cnt = 0;
	unsigned int getBitmasked = 1;
	unsigned int setBitMasked = 0x80000000;
	unsigned int reversed = 0;

//	for (cnt = 0; cnt < 32; cnt++)
//	{
//		printf ("shifted number %x \n",(n >> cnt));
//		if (((n >> cnt) & 0x00000001) == 1)
//		{
//			reversed |=	(1 << (31 -cnt));
//		}
//	}

	for (cnt = 0; cnt < 32; cnt++)
	{
		//printf ("shifted number %x \n",(n >> cnt));

		if ((n & getBitmasked) == getBitmasked)
		{
			reversed |=	setBitMasked;
		}
		getBitmasked = getBitmasked << 1;
		setBitMasked = setBitMasked >> 1;
	}

	return reversed;
}

/***********************************************************
 * Write a function that takes an unsigned integer and returns the number of ’1' bits it has (also known as the Hamming weight).
For example, the 32-bit integer ’11' has binary representation 00000000000000000000000000001011, so the function should return 3.
***********************************************************/
int hammingWeight(unsigned int n) {
	unsigned char cnt = 0;
	unsigned char buff = 0;
	//int tmp = 0;
	for (cnt = 0; cnt < 32; cnt++)
	{
		//printf ("%d ",(n >> cnt));

		if ((n & 0x00000001) == 1)
			buff++;
		n = n >> 1;
	}
	//printf("\n");
	return buff;
}


/*
 	 You are given two 32-bit numbers, N and M, and two bit positions, i and j Write a
	method to set all bits between i and j in N equal to M (e g , M becomes a substring of
	N located at i and starting at j)
	EXAMPLE:
	Input: N = 10000000000, M = 10101, i = 2, j = 6
	Output: N = 10001010100
 */
static int updateBits(int n, int m, int i, int j)
{
	int max = ~0; /* All 1’s */
	/*
	  in binary representation, i and j are counted from right to left, starting from 0
	 */
	printf("n        : 0x%08x \n",n);
	printf("m        : 0x%08x \n",m);

	/*
	 * (1 << (j+1)) : '1' at (j+1)
	 * (1 << (j+1)) - 1 : '1' from j to right
	 * max - ((1 << (j+1)) - 1) : '0' from j to right, the rest is '1'
	 */
	int left = max - ((1 << (j+1)) - 1);
	printf("left     : 0x%08x \n",left);

	/*
	 * (1 << i) : '1' at i
	 * ((1 << i) - 1) :  '1' from i to right, the rest is '0'
	 */
	int right = ((1 << i) - 1);
	printf("right    : 0x%08x \n",right);

	// 1’s, with 0s between i and j (including i and j)
	int mask = left | right;

	printf("mask     : 0x%08x \n",mask);
	printf("n & mask : 0x%08x \n",(n & mask));
	printf("m << i   : 0x%08x \n",m << i);

	// Clear i through j, then put m in there
	return (n & mask) | (m << i);
}

/*
 Given an integer, print the next smallest and next largest number that have the same
number of 1 bits in their binary representation
 */
static unsigned char GetBit(int n, int index)
{
   return ((n & (1 << index)) > 0);
}

static int SetBit(int n, int index, unsigned char b)
{
    if (b) //set bit
    {
    	return n | (1 << index);
    }
    else //clear bit
    {
    	int mask = ~(1 << index);
    	return n & mask;
   }
}

static int GetNext_NP(int n)
{
   if (n <= 0) return -1;

   printf("original number       : 0x%08x \n",n);
   int index = 0;
   int countOnes = 0;

   // Find first one.
   while (!GetBit(n, index)) index++; // if '0' continue until '1'

   // Turn on next zero.
   while (GetBit(n, index))
   {
	   index++;
	   countOnes++;
   }
   n = SetBit(n, index, 1);
   printf("Turn on next zero     : 0x%08x \n",n);

   // Turn off previous one
   index--;
   n = SetBit(n, index, 0);
   countOnes--;
   printf("Turn off previous one : 0x%08x \n",n);
   /*
    push all the '1' on the right of that position just turn off, to the right
    */

   // Set zeros
   for (int i = index - 1; i >= countOnes; i--)
   {
	   n = SetBit(n, i, 0);
   }
   printf("Set zeros             : 0x%08x \n",n);

   // Set ones
   for (int i = countOnes - 1; i >= 0; i--)
   {
	   n = SetBit(n, i, 1);
   }
   printf("Set ones              : 0x%08x \n",n);
   return n;
}

static int GetPrevious_NP(int n)
{
	if (n <= 0) return -1; // Error

	int index = 0;
	int countZeros = 0;

	// Find first zero.
	while (GetBit(n, index)) index++;

	// Turn off next 1.
	while (!GetBit(n, index))
	{
		index++;
		countZeros++;
	}
	n = SetBit(n, index, 0);

	// Turn on previous zero
	index--;
	n = SetBit(n, index, 1);
	countZeros--;

	// Set ones
	for (int i = index - 1; i >= countZeros; i--)
	{
		n = SetBit(n, i, 0);
	}

	// Set zeros
	for (int i = countZeros - 1; i >= 0; i--)
	{
		n = SetBit(n, i, 1);
	}

	return n;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

char isLittleEndian (void)
{
	short x = 0x0001;
	char* y = (char*)&x;
	if (*y == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
 * Given an array of integers and an integer k,
 * find out whether there are two distinct indices i and j in the array
 * such that nums[i] = nums[j] and the difference between i and j
 * is at most k.
 */
unsigned char containsNearbyDuplicate(int* nums, int numsSize, int k)
{
	int  start_idx,stop_idx,i,y = 0;
	if ((numsSize <= 1)
		//|| (numsSize < k)
		|| (k < 1)
		)
	{
		return 0;
	}
	else
	{
		for (i = 0;i < numsSize;i++)
		{
			start_idx = i;

			//determine stop_idx: set it size of (k+1) or "clamp at arr len, whichever come first
			if (start_idx + k > numsSize) stop_idx = numsSize;
			else stop_idx = start_idx + k + 1;

			//printf ("Start and stop idx: %d %d \n",start_idx,stop_idx);

			//check in that sub-array, if found duplicate, return immediately
			for (y = start_idx + 1;y < stop_idx;y++)
			{
				//printf ("Numbers are: %d %d \n",nums[start_idx],nums[y]);
				if (nums[start_idx] == nums[y])
					return 1;
			}
			//printf ("===== \n");
		}
		return 0;
	}
}

/*
 * Given a string s consists of upper/lower-case alphabets and empty space characters ' ',
 * return the length of last word in the string.
* If the last word does not exist, return 0.
* Note: A word is defined as a character sequence consists of non-space characters only.
* For example,
* Given s = "Hello World",
* return 5.
 */
int lengthOfLastWord(char* s)
{
	unsigned int strlen = 0;
	unsigned int start_idx = 0;
	unsigned int stop_idx = 0;

	//get string length
	for (strlen  = 0; s[strlen] != '\0'; strlen++) {}

	printf ("length of string is: %d \n",strlen);

	if (strlen == 0) return 0;

	//get start_idx of the last word
	//by advance backward from the back, stop when hit NON-space
	for (start_idx = strlen-1; s[start_idx] == ' '; start_idx--)
	{
		if (start_idx == 0) return 0;
	}
	printf ("start_idx: %d \n",start_idx);

	//get stop_idx of the last word
	//by advance backward from the start_idx, stop when hit space
	for (stop_idx = start_idx; s[stop_idx] != ' '; stop_idx--)
	{
		if (stop_idx == 0) break;
	}
	printf ("stop_idx: %d \n",stop_idx);

	if (s[stop_idx] != ' ')
	{
		return start_idx - stop_idx + 1;
	}
	else
	{
		return start_idx - stop_idx;
	}
}

/*
 * Compare two version numbers version1 and version2.
 * If version1 > version2 return 1,
 * 		if version1 < version2 return -1,
 * 		otherwise return 0.
 * You may assume that the version strings are non-empty and contain only digits and the . character.
 * The . character does not represent a decimal point and is used to separate number sequences.
 * For instance, 2.5 is not "two and a half" or "half way to version three",
 * it is the fifth second-level revision of the second first-level revision.
 * Here is an example of version numbers ordering:
 * 0.1 < 1.1 < 1.2 < 13.37
 */

int compareVersion(char* version1, char* version2)
{
	unsigned int strlen1 = 0;
	unsigned int strlen2 = 0;
	unsigned int idx = 0;
	unsigned char truncated = 0;

	printf ("string len is: %d \n", strlen(version1));

	for (idx = 0; version1[idx] != '\0'; idx++)
	{
		if (truncated == 1)
		{
			strlen1++;
		}
		else if (version1[idx] != '0' && truncated == 0)
		{
			truncated = 1;
			strlen1++;
		}

	}
	printf ("length of string 1 is: %d \n",strlen1);

	truncated  = 0;
	for (idx = 0; version2[idx] != '\0'; idx++)
	{
		if (truncated == 1)
		{
			strlen2++;
		}
		else if (version2[idx] != '0' && truncated == 0)
		{
			truncated = 1;
			strlen2++;
		}

	}
	printf ("length of string 2 is: %d \n",strlen2);

	if (strlen1 >= strlen2)
	{
		for (idx = 0; idx < strlen1; idx++ )
		{
			if (version2[idx] == '\0')
				return 1;
			else if (version1[idx] > version2[idx])
				return 1;
			else if (version2[idx] > version1[idx])
				return -1;
		}
		return 0;
	}
	else
	{
		for (idx = 0; idx < strlen2; idx++ )
		{
			if (version1[idx] == '\0')
				return 1;
			else if (version1[idx] > version2[idx])
				return 1;
			else if (version2[idx] > version1[idx])
				return -1;
		}
		return 0;
	}
}

char* addBinary(char* a, char* b)
{
	char* addBinary(char* a, char* b);
	int la = strlen(a);
	int lb = strlen(b);
	int lr = la > lb ? la : lb;
	int carry = 0;
	char *res = (char*)calloc(lr + 2, sizeof(char));
	res[lr + 1] = '\0';
	la--; lb--;
	while (la >= 0 || lb >= 0) {
	    int ba = la >= 0 ? a[la--] - '0' : 0;
	    int bb = lb >= 0 ? b[lb--] - '0' : 0;
	    int br = ba ^ bb ^ carry;
	    carry = (ba & bb) | (carry & (ba ^ bb));
	    res[lr--] = br + '0';
	}
	if (!carry) return res + 1;
	res[0] = '1';
	return res;
}

void reverse_array(int *nums , int begin , int end)
{
    int tmp;
    unsigned int idx;

    while(begin < end)
    {
        tmp = nums[begin];
        nums[begin] = nums[end];
        nums[end] = tmp;
        begin++;
        end--;
    }
//	for (idx = 0; idx < 7; idx++)
//	{
//		printf ("array element is: [%d] --> %d \n", idx, nums[idx]);
//	}
//	printf ("================ \n");
}


/* ROTATE ARRAY
 * Input:  arr[] = [1, 2, 3, 4, 5, 6, 7]
 *          k = 2
 *	Output: arr[] = [3, 4, 5, 6, 7, 1, 2]
 */
void rotate_array(int* nums, int numsSize, int k)
{
    if((k == 0) || (k == numsSize))
    	return;
    if(numsSize == 0 )
    	return;
/* array rotation is achieve by 2 steps:
 * 1: reverse entire array
 * 2: reverse 2 sub-array to re-construct original order
 */

    reverse_array(nums,0,numsSize-1);

    if( k > numsSize)
    	k = k % numsSize;

    if( (numsSize - k) != 0)
    {
    	reverse_array(nums,0,k-1);
    	reverse_array(nums,k,numsSize-1);
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////           SORTING     ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void quicksort_arr(int arr[],int first,int last)
{
	int pivot,j,temp,i;
	/*
	 * The basic concept is to pick one of the elements in the array as a pivot value
	 * around which the other elements will be rearranged.
	 * Everything less than the pivot is moved left of the pivot (into the left partition).
	 * Similarly, everything greater than the pivot goes into the right partition.
	 * At this point each partition is recursively quicksorted.
	 */
	printf("Initial array[%d->%d]: ",first,last);
	printArray(arr,first,last);
	if(first < last)
	{
	 pivot = first; //take the pivot as the left most item
	 i = first;
	 j = last;

	 while(i<j)
	 {
		 while(arr[i] <= arr[pivot] && i < last) //smaller or equal than the pivot, move from left
		 {
			 i++; //advance to right until hit either last item or hit an item > pivot
		 }

		 while(arr[j] > arr[pivot]) //larger than pivot, move from right
		 {
			 j--; //move back from right most until hit an item <= pivot
		 }

		 if(i < j)
		 {
			//swap
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			printArray(arr,first,last);
		 }
	 }
	 // once step out of this while() loop, i == j
	 printf("pivot new idx: %d\n",j);
	 //swap the pivot item with the middle item after partition
	 temp = arr[pivot];
	 arr[pivot] = arr[j];
	 arr[j]= temp;

	 printArray(arr,first,last);

	 //recursively do for two halves
	 quicksort_arr(arr,first,j-1);
	 quicksort_arr(arr,j+1,last);
	}
}

void merge_arr(int arr[], int first, int mid, int last)
{
	int* temp_arr = (int*)malloc((last+1) * sizeof (int));
    int i = first, j = mid + 1, k = 0;
/*
 *  merge 2 sorted sub-array: [first..mid] and [mid+1..last]
 */
    //check one by one in both sub array and copy in increasing order
    while (i <= mid && j <= last) //once this loop done, one of the 2 sub-array are exhausted
    {
        if (arr[i] <= arr[j])
        	{temp_arr[k++] = arr[i++];}
        else
        	{temp_arr[k++] = arr[j++];}
    }

    //copy the rest into temp array
    while (i <= mid)
    	{temp_arr[k++] = arr[i++];}

    while (j <= last)
    	{temp_arr[k++] = arr[j++];}

    k--; //important because now k is 1 step above last index, need to minus 1
    while (k >= 0)
    {
    	arr[first + k] = temp_arr[k]; //copy data from temp array back to original array
        k--;
    }
    free(temp_arr);
    printf ("merge_arr[%d..%d..%d] : ",first,mid,last);
    printArray(arr,first,last);
}

void mergeSort_arr(int arr[], int first, int last)
{
    printf ("mergeSort_arr[%d..%d]: ",first,last);
    printArray(arr,first,last);
	if (first < last)
    {
        int m = (last + first)/2;
        mergeSort_arr(arr, first, m);
        mergeSort_arr(arr, m + 1, last);
        merge_arr(arr, first, m, last);
    }
}

void bubbleSort_arr(int arr[],int len)
{
	int i,x,k,temp,any_swap_done = 1;

	printf("Initial array: ");
	printArray(arr,0,len-1);

	/*
	 * repeatedly move the largest element to the highest index position of the array
	 */
	for(i = 0;any_swap_done && (i < len - 1); i++) //if previous run, no swap done, means already sorted
	{
		any_swap_done = 0;
		for (k = 0; k < len - i - 1;k++) //after each iteration, the largest items already at last indexes;
		{
			if (arr[k] > arr[k+1])
			{
				temp = arr[k];
				arr[k] = arr[k+1];
				arr[k+1] = temp;
				any_swap_done = 1;
			}
		}

		printf("Sorting %d:     ",i);
		printArray(arr,0,len-1);
	}

	printf("Sorted array:  ");
	printArray(arr,0,len-1);
}

void selectionSort_arr(int arr[], int len)
{
	int i,x, eff_size, maxpos, tmp;
	printf("Initial array: ");
	printArray(arr,0,len-1);
	/*
	 * repeatedly find the next largest element in the array and move it to its highest position in the sorted array
	 */
	for (eff_size = len; eff_size > 1; eff_size--) //after each iteration, largest item will be move to the end; hence, shrink "effective" array by one
	{
		for (i = 0; i < eff_size; i++)
		{
			maxpos = (arr[i] > arr[maxpos] ? i : maxpos); //update index of largest item
		}
		//swap largest item to last index in the "effective" array
		tmp = arr[maxpos];
		arr[maxpos] = arr[eff_size - 1];
		arr[eff_size - 1] = tmp;

		printf("Sorting %d:     ",i);
		printArray(arr,0,len-1);
	}
	printf("Sorted array:  ");
	printArray(arr,0,len-1);
}

/* Function to sort an array using insertion sort*/
void insertionSort_arr(int arr[], int len)
{
	int i, key, j;

	printf("Initial array: ");
	printArray(arr,0,len-1);

	for (i = 1; i < len; i++)
	{
		/*
		 *every iteration looks at sub array [0..i]
		 *after each iteration, sub array [0..i] is sorted
		 */

		key = arr[i]; //set the key to be last element of sub array
		j = i-1; //check all the other element , from right -> left

		/*
		 * note that j is initialize to (i-1)
		 * only need to advance j (right->left) if  arr[j] > key
		 */
		while (j >= 0 && arr[j] > key)
		{
			/*
			 * Move elements of arr[0..i-1], that are greater than key, to one position ahead
			 * of their current position (i.e copy to the right).
			 * This will result in duplicate
			 * Eventually, the last duplicate will be replace by key
			*/
			arr[j+1] = arr[j];
			j--;
			printf("Sorting %d:     ",i);
			printArray(arr,0,len-1);
		}
		arr[j+1] = key;

		//after every iteration, sub array [0..i] is sorted
		printf("Sorting %d:     ",i);
		printArray(arr,0,len-1);
	}

	printf("Sorted array:  ");
	printArray(arr,0,len-1);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////

int binary(int a[],int element_to_be_search,int start_idx,int end_idx)
{
     int mid = 0;
     int c = 0;

     if(start_idx <= end_idx)
     {
          mid = (end_idx + end_idx)/2;
          if(element_to_be_search == a[mid])
          {
              c = 1;
              return c;
          }
          else if(element_to_be_search < a[mid])
          {
              return binary(a,element_to_be_search,start_idx,mid-1);
          }
          else
              return binary(a,element_to_be_search,mid+1,end_idx);
     }
     else
     {
    	 return c;
     }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////           STRING     ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Swaps strings by swapping pointers */
/* have to use double pointer */
void swap_string1(char **str1_ptr, char **str2_ptr)
{
  char *temp = *str1_ptr;
  *str1_ptr = *str2_ptr;
  *str2_ptr = temp;
}

/* Swaps strings by swapping data*/
void swap_string2(char *str1, char *str2)
{
  char *temp = (char *)malloc((strlen(str1) + 1) * sizeof(char));
  strcpy(temp, str1);
  strcpy(str1, str2);
  strcpy(str2, temp);
  free(temp);
}

/* return the string length except /0 */
unsigned int string_len(char* str)
{
	unsigned int string_length = 0;
	while (*str != 0)
	{
		str++;
		string_length++;
	}
	return string_length;
}

#define XOR_SWAP(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)


void reverse_string_inplace(char*str)
{
	char* end_idx = str + strlen(str) - 1;
    // swap the values in the two given variables
    // XXX: fails when a and b refer to same memory location

    // walk inwards from both ends of the string,
    // swapping until we get to the middle
	while (str < end_idx)
	{
		XOR_SWAP(*str, *end_idx);
		str++;
		end_idx--;
	}
}


char *string_reverse2(const char *string)
{
	char* new_string = (char*)malloc((strlen(string)+1)*sizeof(char));
	char idx = 0;
	for (idx = 0; idx < strlen(string); idx++)
	{
		new_string[idx] = string [strlen(string) - idx - 1];
	}
	new_string[strlen(string)] = '\0';
	return new_string;
}

void naive_Pattern_Search(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int i = 0;
    /* A loop to slide pat[] one by one */
    for (i = 0; i <= N - M; i++) // No need to loop the entire txt[]. If got match, worst case is the match at the end
    {
        int j;

        /* For current index i, check for pattern match */
        for (j = 0; j < M; j++)
        {
        	if (txt[i+j] != pat[j]) break;
        }

        if (j == M)  // if pat[0...M-1] = txt[i, i+1, ...i+M-1]
        {
        	printf("Pattern found at index %d \n", i);
        }
    }
}

void computeLPSArray(char *pat, int M, int *lps)
{
	//https://www.youtube.com/watch?v=KG44VoDtsAA

	int len = 0;  // length of the previous longest prefix suffix
    int i;

    lps[0] = 0; // lps[0] is always 0
    i = 1;

    // the loop calculates lps[i] for i = 1 to M-1
    while (i < M)
    {
       if (pat[i] == pat[len])
       {
         len++;
         lps[i] = len;
         i++;
       }
       else // (pat[i] != pat[len])
       {
         if (len != 0) //which means: the previous sub-pattern has a prefix same as a suffix =>
        	           // there is a same starting and ending sequence of length len
        	 	       // now since (pat[i] != pat[len]), which means our matching streak has stopped
        	 	 	   // we need to restart from the next longest matching prefix suffix
         {
           // This is tricky. Consider the example
           // AAACAAAA and i = 7.
           len = lps[len-1]; //lps[len-1] gives the longest prefix suffix from 0 -> (len-1)
           	   	   	   	   	 //That's the next longest matching prefix suffix

           // Also, note that we do not increment i here
         }
         else // if (len == 0)
         {
           lps[i] = 0;
           i++;
         }
       }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////        HASH TABLE     ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////


/* Given an array of integers, find if the array contains any duplicates.
 * Your function should return true if any value appears at least twice in the array,
 * and it should return false if every element is distinct. */
//enum BOOLEAN containsDuplicate(int* nums, int numsSize)

//Dennis: test with array of string instead, because Dict works with string type
enum BOOLEAN containsDuplicate(char** arr_string, int numsSize)
{
	/* algo: interate array, add each item into dict
	 * if no collision: no duplicate */
	unsigned int idx = 0;
	Dict d = DictCreate();
	for (idx = 0; idx < numsSize; idx++)
	{
		if (DictInsertToBackWithCheck(d,arr_string[idx],arr_string[idx]) == FALSE)
		{
			printf("Got duplicate: %s \n",arr_string[idx]);
			return FALSE;
		}
	}
	printf("No duplicate \n");
	DictDestroy(d);
	return TRUE;
}

/* Given two strings s and t, write a function to determine if t is an anagram of s.
 * An anagram is a type of word play, the result of rearranging the letters of a word or phrase
 * to produce a new word or phrase, using all the original letters exactly once */
enum BOOLEAN isAnagram(const char* s, const char* t)
{
	Dict d = DictCreate();
	unsigned int strlen = 0;
	char string_1char[2] = {' ','\0'};

	/* add each character of 1st string into Dict */
	for (strlen = 0; s[strlen] != '\0'; strlen++)
	{
		string_1char[0] = s[strlen];
		DictInsert(d,string_1char,string_1char);
	}
	DictPrint(d);

	/* remove each character of 2nd string from Dict */
	for (strlen = 0; t[strlen] != '\0'; strlen++)
	{
		string_1char[0] = t[strlen];
		DictDelete(d,string_1char);
		if (d->n == 0) //once Dict empty, jump out
		{
			break;
		}
	}
	DictPrint(d);

	/* if Dict empty and all character in 2nd string is consumed */
	if ((t[++strlen] == '\0') && (d->n == 0))
	{
		printf("Is Anagram \n");
		return TRUE;
	}
	else
	{
		printf("Is NOT Anagram \n");
		return FALSE;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

/********* Knuth-Morris-Pratt Algorithm **************/
/* The trick is: once there is a mismatch, shift right the pattern by how much ? */
/* Let's say you found a mismatch at index 5 (of pattern), which mean 0->4 are matched
   If shift by 1:
   	   in place of 1->4, now is  0->3, are tested against that same text portion (for eg "ABCD"
   	   1->4 were matched
   	   if we know that 0->3 and 1->4 are different, definitely 0->3 will not be matched
   	   hence shift by 1 is just a waste of time !
   So, we need to maximize our shift before test again. If just shift 1 by 1, that's Naive searching
   That's where the LPS array come into place

   https://www.youtube.com/watch?v=t4xUA-aHzy8

  http://jakeboxer.com/blog/2009/12/13/the-knuth-morris-pratt-algorithm-in-my-own-words/

  bacbababaabcbab
    |||||N
    abababca

	subpattern :ababc -> length of prefix is 3 -> can skip 5 - 3 = 2

  // x denotes a skip
  bacbababaabcbab
    xx|||
      abababca
*/

void KMPSearch(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int *lps = (int *)malloc(sizeof(int)*M);
    int j  = 0;  // index for pat[]

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int i = 0;  // index for txt[]
    while (i < N)
    {
      if (pat[j] == txt[i])
      {
        j++;
        i++;
      }

      if (j == M)
      {
        printf("Found pattern at index %d \n", i-j);
        j = lps[j-1];
      }

      // mismatch after j matches
      else if (i < N && pat[j] != txt[i])
      {
        // Do not match lps[0..lps[j-1]] characters,
        // they will match anyway
    	// increase i or decrease j mean the same thing: shift pattern to right
        if (j != 0)
         j = lps[j-1];
        else
         i = i+1;
      }
    }
    free(lps); // to avoid memory leak
}

/* Function to swap values at two pointers */
void swap(char *x, char *y)
{
	printf("swap %c to %c ",*x,*y);
	char temp;
	temp = *x;
	*x = *y;
	*y = temp;
}


/*
   http://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/
   Function to print permutations of string
   This function takes three parameters:
   1. String
   2. Starting index of the string
   3. Ending index of the string. */
void permute(char *a, int left, int right)
{
   int i;
   if (left == right) //if only 1 item left, this is one permutation
   {
	   printf("permutation: %s\n",a);
   }
   else
   {
       for (i = left; i <= right; i++)
       {
    	  /*
    	  swap the first item with the rest, including itself !
    	   */
    	  swap((a+left), (a+i));
    	  printf("new string %s\n",a);

    	  /*
    	  exclude 1st item, recursively do new string
    	   */
          permute(a, left+1, right);
          printf("backtrack ");

          /*why need this backtrack:
           we do swap in-place, meaning original string is changed -> have to swap back to restore
           */
          swap((a+left), (a+i)); //backtrack
          printf("new string %s\n",a);
       }
   }
}

void* aligned_malloc(size_t required_bytes, size_t alignment)
{
	/* The idea is that we have to malloc MORE than what required
	   because after allocation, we have freedom to select what memory location that aligned
	   for e.g: if alignment is 4, required byte is 2
	     0 1 2 3
	     4 5 6 7
	     we have to allocate such as the allocated memory region cover addr "4"; so we can "set back" to 4 as starting address
	     if let's say allocated memory 1->2, there is no way you can make it aligned, unless copy manually
	 */
	void* p1; // original block
	void** p2; // aligned block

	/*the offset comprise of 2 components:
	 (alignment - 1): to make sure allocated memory region cover "alignment addresses". For eg: if alignment is 4, those alignment addresses are 4 8 12..
	 sizeof(void*): size of p1
	 */
	int offset = alignment - 1 + sizeof(void*);

	if ((p1 = (void*)malloc(required_bytes + offset)) == NULL)
	{
		return NULL;
	}

	/*
	 & ~(alignment - 1) : this will "move back" addr to the nearest "alignment addresses"
	 eg: alignment 4 0x100, addr: 6 0x110
	  0x110 &~ (0x100 - 1) = 0x100 -> 4
	 */
	p2 = (void**)(((size_t)(p1) + offset) & ~(alignment - 1));
	p2[-1] = p1;
	return p2;
}

void aligned_free(void *p)
{
	free(((void**)p)[-1]);
}

int** My2DAlloc(int rows, int cols)
{
	int header = rows * sizeof(int*);
	int data = rows * cols * sizeof(int);
	int** rowptr = (int**)malloc(header + data);
	printf ("rowptr 0x%x \n",rowptr);
	int* buf = (int*)(rowptr + rows);
	printf ("buf 0x%x \n",buf);
	int k;
	for (k = 0; k < rows; ++k)
	{
		rowptr[k] = buf + k*cols;
		printf ("rowptr[%d] 0x%x \n",k,rowptr[k]);
	}
	return rowptr;
}

/*
 * The atoi() function takes a string (which represents an integer)
 * as an argument and returns its value.
 */
int atoi(char* str)
{
	int output_int = 0;
	unsigned int idx = 0;
	/* iterate from left
	 * each iteration, current value is shift left by multiply to 10
	 * first iteration, no shift because mutiply to 0 */
	for (idx = 0; *(str + idx) != '\0'; idx++)
	{
		output_int = output_int*10 + (*(str + idx) - '0'); //(*(str + idx) - '0') is the int value of that digit
	}
	return output_int;
}


/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
*/
char* itoa_c(int value, char* result, int base)
{
	// check that the base if valid
	if ( base < 2 || base > 36 )
	{
		*result = '\0';
		return result;
	}

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do
	{
		tmp_value = value;
		value /= base;
		/*  tmp_value - value * base : last digit (rightmost) with sign, i.e it can be negative or positive
		 * '0' start at 35 index */
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + (tmp_value - value * base)];

		printf("tmp:value:indx:value:character = %d:%d:%d:%d:%c \n",tmp_value,value,35 + (tmp_value - value * base),value,*(ptr-1));
	} while ( value );

	// Apply negative sign
	if ( tmp_value < 0 )	*ptr++ = '-';
	*ptr-- = '\0'; //add '\0' to the end, but ptr point to the one right before it

	/* reverse string
	 * ptr1 and result point to the same location
	 * note that the string being reversed exclude '\0'*/
	while ( ptr1 < ptr )
	{
		tmp_char = *ptr;
		*ptr-- = *ptr1;
		*ptr1++ = tmp_char;
	}

	return result;
}

char *itobase10(char *buf, int value)
{
    sprintf(buf, "%d", value);
    return buf;
}

/* Given an array of size n, find the majority element.
 * The majority element is the element that appears more than n/2 times.
 * You may assume that the array is non-empty
 * and the majority element always exist in the array.*/
int majorityElement(int* nums, int numsSize)
{
	/* observation:
	 * only 1 major element exist
	 * only need to check for half of an array, excluding itself */

/* Boyer–Moore majority vote algorithm
 * http://www.cs.utexas.edu/~moore/best-ideas/mjrty/example.html
 */
	unsigned int counter = 0;
	int candidate = 0;
	unsigned int idx = 0;

/* 1st run we will sweep down the sequence starting at the pointer position shown above.
 * As we sweep we maintain a pair consisting of a current candidate and a counter.
 * Initially, the current candidate is unknown and the counter is 0.
 * When we move the pointer forward over an element e:
 	 * If the counter is 0, we set the current candidate to e and we set the counter to 1.
 	 * If the counter is not 0, we increment or decrement the counter according to whether e is the current candidate.
 * When we are done, the current candidate is the majority element, if there is a majority.
 * */

/* the objective of 1st pass is NOT to identify the real majority
 * but to ELIMINATE all those that's IMPOSSIBLE to be majority
 * and leave out only 1 candidate */
	for (idx = 0; idx < numsSize; idx++)
	{
		if (counter == 0)
		{
			counter++;
			candidate = nums[idx];
		}
		else
		{
			(candidate == nums[idx]) ? counter++ : counter-- ;
		}
		printf ("counter : candidate %d : %d \n",counter, candidate);
	}

/* after 1st pass, we identify one candidate that is not canceled out
 * need to 2nd pass to confirm if it's really the majority element
 * for example {1,1,1,1,3,3,3,3,7,7,9};
 */

	counter = 0;
	for (idx = 0; idx < numsSize; idx ++)
	{
		if (candidate == nums[idx]) {counter++;}
	}

	if (counter > numsSize/2)
	{
		printf("majority element is: %d\n",candidate);
		return candidate;
	}
	else
	{
		printf("no majority element ! \n");
		return -1;
	}
}

/* Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
 * The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not. */
enum BOOLEAN isValid(char* s)
{
	struct ListNode* head = NULL;


	unsigned int idx = 0;
	for (idx = 0; s[idx] != '\0'; idx++)
	{
		int tmp = s[idx];
		if ((s[idx] == '{')
			 || (s[idx] == '(')
			 || (s[idx] == '[')
				)
		{
			push(&head,tmp,0);
		}
		else if  ((s[idx] == '}')
				 || (s[idx] == ')')
				 || (s[idx] == ']')
				   )
		{
			int open_paren = pop(&head);
			//printf ("open_paren: %d \n",open_paren);
			if (
					((s[idx] == '}') && (open_paren != 123))
				 ||	((s[idx] == ']') && (open_paren != 91))
				 || ((s[idx] == ')') && (open_paren != 40))
			   )
			{
				printf ("Is NOT valid Parentheses %c \n",s[idx]);
				return FALSE;
			}
		}
	}
	printf ("Is valid Parentheses \n");
	return TRUE;
}

int main ()
{
	// http://wiki.eclipse.org/CDT/User/FAQ#Eclipse_console_does_not_show_output_on_Windows
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	clock_t begin, end;
	float time_spent = 0;
	begin = clock();
	unsigned int idx = 0;
	int  arr[] = {1,2,3,4,5,6,7};
	int unsorted_arr[] = {1,5,4,0};

	unsigned int T = 0;
	unsigned int flipping_int = 1;
	int r_idx,c_idx;
	unsigned int N,K;


    float arr2[5] = {12.5, 10.0, 13.5, 90.5, 0.5};
    float *ptr1 = &arr2[0];
    float *ptr2 = ptr1 + 3;

    printf("%f ", *ptr2);
    printf (" %d %d %d \n",ptr2, ptr1, ptr2 - ptr1);

    /********************* Test array address *************************/
    char arri[] = {1,2,3,4,5,6,7,8};
	printf ("size of arri: %d \n", sizeof(arri));
	printf ("size of &arri: %d \n", sizeof(&arri));
	printf ("number of element: %d \n", sizeof(arri)/sizeof(arri[0]));
	printf ("arri : %d \n", arri);
	printf ("&arri: %d \n",&arri);
	printf ("arri  + 1: %d \n", arri + 1);
	printf ("&arri + 1: %d \n",&arri + 1);
	char char_var = 1;
	char* ptr;
	ptr = &char_var;
	printf ("ptr  + 0: %d \n", ptr + 0);
	printf ("ptr  + 1: %d \n", ptr + 1);
	printf ("&ptr + 0: %d \n",&ptr + 0);
	printf ("&ptr + 1: %d \n",&ptr + 1);
	printf ("====================================================== \n");
	/*****************************************************************/

	/***************************** test String ************************/
	char test_string[] = {'a','b','c','1','2','3','\0'};
	const char test_string1[] = {'A','B','C','1','2','3','\0'};
	char* reversed_string;
	char* str1 = "Geek";
	char* str2 = "For";
	printf ("Length of string is: %d \n", string_len(test_string));
	printf("Swap String Before: str1 is %s, str2 is %s \n", str1, str2);
	swap_string1(&str1, &str2);
	printf("Swap String After: str1 is %s, str2 is %s \n", str1, str2);

	char str3[10] = "ABC";
	char str4[10] = "DEF";
	printf("Swap String Before: str3 is %s, str4 is %s \n", str3, str4);
	swap_string2(&str3, &str4);
	printf("Swap String After: str3 is %s, str4 is %s \n", str3, str4);

	printf("Reverse String Before: %s \n", test_string);
	reverse_string_inplace(test_string);
	printf("Reverse String After: %s \n", test_string);

	printf("Reverse String Before: %s \n", test_string1);
	reversed_string = string_reverse2(test_string1);
	printf("Reverse String After (new string): %s \n", reversed_string);

	printf ("====================================================== \n");
	/*****************************************************************/

	/******************** test Hamming weight ************************/
	printf ("Number of digit 1 is: %d \n", hammingWeight(7));

	printf ("====================================================== \n");
	/*****************************************************************/
	unsigned int ui_x = -1;
	printf ("unsigned int assigned neg value: 0x%08X \n", ui_x);
	printf ("unsigned int assigned neg value: %d \n", ui_x);

	printf ("\n====================================================== \n");

	/***********************test quick sort *************************/
	printf("testing quick sort \n");
	int array_quicksort[10] = {5,7,4,9,5,4,2,6,9,3};
	quicksort_arr(array_quicksort,0,sizeof(array_quicksort)/sizeof(array_quicksort[0])-1);
	printf ("\n====================================================== \n");

	/***********************test merge sort *************************/
	printf("testing merge sort \n");
	int array_mergesort[10] = {5,7,4,9,5,4,2,6,9,3};
	mergeSort_arr(array_mergesort,0,sizeof(array_mergesort)/sizeof(array_mergesort[0])-1);
	printf ("\n====================================================== \n");

	/***********************test bubble sort *************************/
	printf("testing bubble sort \n");
	int array_bubblesort[] = {45,67,12,34,25,39};
	bubbleSort_arr(array_bubblesort,sizeof(array_bubblesort)/sizeof(array_bubblesort[0]));
	printf ("\n====================================================== \n");

	/***********************test selection sort *************************/
	printf("testing selection sort \n");
	int array_selectionsort[] = {1,2,3,4,6,0};
	selectionSort_arr(array_selectionsort,sizeof(array_selectionsort)/sizeof(array_selectionsort[0]));
	printf ("\n====================================================== \n");

	/***********************test insertion sort *************************/
	printf("testing insertion sort \n");
	int array_insertionsort[] = {1,2,3,4,6,0};
	insertionSort_arr(array_insertionsort,sizeof(array_insertionsort)/sizeof(array_insertionsort[0]));
	printf ("\n====================================================== \n");

	/***********************test string permutation *************************/
	printf("testing string permutation \n");
	char str[] = "ABC";
	int n = strlen(str);
	permute(str, 0, n-1);
	printf ("\n====================================================== \n");

	/***********************test system endian *************************/
	printf("Is this system little Endian: %d \n",isLittleEndian());
	printf ("size of enum: %d \n", sizeof(state_var));
	printf ("\n====================================================== \n");

	printf("test 2D array address \n");
	int arr2D[2][3] = {{1,2,3},{4,5,6}};
	for (r_idx = 0; r_idx<2; r_idx++)
	{
		for (c_idx = 0; c_idx<3; c_idx++)
		{
			printf("0x%x ",&arr2D[r_idx][c_idx]);
		}
		printf ("\n");
	}
	printf ("\n");
	printf("0x%x \n",arr2D);
	printf("0x%x \n",*(arr2D + 1));
	printf("%d \n",*(*(arr2D + 1)+1));
	printf("%d \n",*(((int *)arr2D)+1*3+1));
	printf("0x%x \n",**arr2D);
	printf ("\n====================================================== \n");

	/***********************test 2D array dynamic allocation *************************/
	printf("2D array allocation\n");
	My2DAlloc(2,3);
	printf ("\n====================================================== \n");

	/***********************test update bit *************************/
	printf("test update bit \n");
	printf("updated number is: 0x%08x \n",updateBits(0xffffffff,0x00,2,6));
	printf ("\n====================================================== \n");

	/***********************test next largest *************************/
	printf("testing next largest \n");
	GetNext_NP(0x0F00001C);
	printf ("\n====================================================== \n");

	/***********************test linked list *************************/

	printf("testing linked list \n");
	struct ListNode* head = NULL;
	push(&head,1,1);
	push(&head,6,1);
	push(&head,7,1);
	push(&head,2,1);
	push(&head,8,1);
	push(&head,4,0);
	push(&head,0,0);
	printf("print linked list: \n");
	printList(head);
	printf("testing linked list reverse: \n");
	printList_reverse(head);
	printf("\n");
	printf("remove 2 from the end: \n");
	removeNthFromEnd(head,2);
	printList(head);
	printf("Sort list: \n");
	printf("Original list: \n");
	printList(head);
	head = listsort(head,0,0);
	printf("Sorted list: \n");
	printList(head);
	printf ("\n====================================================== \n");

	/***********************test hash table (dictionary) *************************/
	printf("testing dictionary \n");
	Dict d;
    char buf[512];
    int i;

    d = DictCreate();

    DictInsert(d, "foo", "hello world");
    puts(DictSearch(d, "foo"));
    DictInsert(d, "foo", "hello world2");
    puts(DictSearch(d, "foo"));
    DictDelete(d, "foo");
    puts(DictSearch(d, "foo"));
    DictDelete(d, "foo");

    DictDelete(d, "foo");

    for(i = 0; i < 10000; i++) {
        sprintf(buf, "%d", i);
        DictInsert(d, buf, buf);
    }
    DictDestroy(d);

	Dict d2 = DictCreate();
	DictInsertToBackWithCheck(d2, "foo", "hello world");
	DictInsertToBackWithCheck(d2, "foo1", "hello world1");
	DictInsertToBackWithCheck(d2, "foo", "hello world");
	DictInsertToBackWithCheck(d2, "foo", "hello world");
	DictPrint(d2);
	DictDestroy(d2);

	printf ("\n====================================================== \n");

	/***********************test hash containsDuplicate (dictionary) *************************/
	printf("testing containsDuplicate \n");

	char* arryDuplicate[5] = {"abc","e","f","g","abd"};
	containsDuplicate(arryDuplicate, sizeof(arryDuplicate)/sizeof(arryDuplicate[0]));
	printf ("\n====================================================== \n");

	/***********************test hash Anagram (dictionary) *************************/
	printf("testing Anagram \n");
	char* s = "anagram";
	char* t = "nagaramx";

	isAnagram(s,t);
	printf ("\n====================================================== \n");
	/***********************test is Power of 2  *************************/
	printf("testing is Power of 2 (division method) \n");
	printf("Is power of 2: %d \n", isPowerOfTwo_divMethod(1));
	printf("Is power of 2: %d \n", isPowerOfTwo_divMethod(0));
	printf("Is power of 2: %d \n", isPowerOfTwo_divMethod(0x80));
	printf("Is power of 2: %d \n", isPowerOfTwo_divMethod(0x80000000));
	printf("testing is Power of 2 (bit check method) \n");
	printf("Is power of 2: %d \n", isPowerOfTwo_bitCheckMethod(1));
	printf("Is power of 2: %d \n", isPowerOfTwo_bitCheckMethod(0));
	printf("Is power of 2: %d \n", isPowerOfTwo_bitCheckMethod(0x80));
	printf("Is power of 2: %d \n", isPowerOfTwo_bitCheckMethod(0x80000000));
	printf ("\n====================================================== \n");

	/***********************test removeElement *************************/
	printf("testing removeElement \n");
	int arrToRemoveElement[8] = {1,2,3,4,5,6,7,8};
	int newLen = 0;
	printf("original array:      ");
	printArray(arrToRemoveElement,0,sizeof(arrToRemoveElement)/sizeof(arrToRemoveElement[0])-1);
	newLen = removeElement(arrToRemoveElement, sizeof(arrToRemoveElement)/sizeof(arrToRemoveElement[0]),4);
	printf("after removed array: ");
	printArray(arrToRemoveElement,0,newLen - 1);
	printf ("\n====================================================== \n");

	/***********************test reverseBits *************************/
	printf("testing reverseBits \n");
	unsigned int toBeReversed= 43261596;
	printf("reversed int: %d \n",reverseBits(toBeReversed));
	printf ("\n====================================================== \n");

	/***********************test rotate_array *************************/

	printf("testing rotate_array \n");
	int arrToRotate[7] = {1,2,3,4,5,6,7};
	printf("original array: ");
	printArray(arrToRotate,0,sizeof(arrToRotate)/sizeof(arrToRotate[0])-1);
	rotate_array(arrToRotate,sizeof(arrToRotate)/sizeof(arrToRotate[0]),3);
	printf("rotate array:   ");
	printArray(arrToRotate,0,sizeof(arrToRotate)/sizeof(arrToRotate[0])-1);
	printf ("\n====================================================== \n");

	/***********************test containsNearbyDuplicate *************************/

	printf("testing containsNearbyDuplicate \n");
	int arr_containsNearbyDuplicate[10] = {1,2,3,4,5,6,7,1,9,10};
	printf("original array: ");
	printArray(arr_containsNearbyDuplicate,0,sizeof(arr_containsNearbyDuplicate)/sizeof(arr_containsNearbyDuplicate[0])-1);
	printf("Is contain duplicate within %d: %d \n",2,
			containsNearbyDuplicate(arr_containsNearbyDuplicate,sizeof(arr_containsNearbyDuplicate)/sizeof(arr_containsNearbyDuplicate[0]),3));
	printf ("\n====================================================== \n");

	/***********************test lengthOfLastWord *************************/
	printf("testing lengthOfLastWord \n");
	char* str_lengthOfLastWord = "Hello World1";
	printf("Length of last word: %d \n", lengthOfLastWord(str_lengthOfLastWord));
	printf ("\n====================================================== \n");

	/***********************test compareVersion *************************/
	printf("testing compareVersion \n");
	char* ver1 = "1.1";
	char* ver2 = "01.1";
	printf("version: %d \n", compareVersion(ver1,ver2));
	printf ("\n====================================================== \n");

	/***********************test itoa_c *************************/
	printf("testing itoa_c \n");
	char intToStringResult[100];
	itoa_c(-1234,intToStringResult,10);
	printf ("intToStringResult: %s \n",intToStringResult);
	printf ("\n====================================================== \n");

	/***********************test majorityElement *************************/
	printf("testing majorityElement \n");
	int majorityElement_arr1[13] = {1,1,1,3,3,7,7,3,3,3,7,3,3};
	int majorityElement_arr2[11] = {1,1,1,1,3,3,3,3,7,7,9};
	majorityElement(majorityElement_arr1,sizeof(majorityElement_arr1)/sizeof(majorityElement_arr1[0]));
	majorityElement(majorityElement_arr2,sizeof(majorityElement_arr2)/sizeof(majorityElement_arr2[0]));
	printf ("\n====================================================== \n");

	/***********************test valid parenthese *************************/
	printf("testing valid parenthese \n");
	char* parenthese1 = "()[]{}";
	char* parenthese2 = "([)]";

	isValid(parenthese1);
	isValid(parenthese2);
	printf ("\n====================================================== \n");

	unsigned char u_char = -1;
	printf("%d \n",u_char);
	printf("%u \n",u_char);

	unsigned int u_int = -1;
	printf("%d \n",u_int);
	printf("%u \n",u_int);

	signed s_int = -1;
	printf("%d \n",s_int);
	printf("%u \n",s_int);


	end = clock();
	time_spent = (double)(end - begin);
	printf("Execution time: %f \n", time_spent);

	return 0;
}
