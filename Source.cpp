/*
	Source.cpp
	Jake Wagner
	- This program tests the time complexity of 4 different methods for returning the Kth smallest
	  element from a list of intgers. The methods include: Mergesort, iterative Partition Sort,
	  recursive Partition Sort, and Median of the Medians Partition Sort.
*/
#include <time.h>
#include <math.h>
#include <iostream>
using namespace std;


//CONTROL VARIABLES
const int N = 10; //size of list to be sorted.
const float K = N/4; //kth smallest element to be returned(0, N/4, N/2, 3N/4, and N-1)
const int T = 25; //number of trials perarray size N and element K
const bool D = true; //optional displays for checking correctness of algorithms


//FUNCTION PROTOYPES
int mergeSort(int list[]);
void mergeSortRec(int list[], int first, int last);
void merge(int list[], int first, int mid, int last);
int ittPartition(int list[]);
int recPartition(int list[]);
//int medPartition(int list[]);
void partition(int list[], int low, int high, int &pivotposition);
int recPartitionRec(int list[], int low, int high, int &pivotposition, int k);
void dispArray(int list[]);
void copyList(int list1[], int list2[]);

//MAIN ============================================================================================
int main() {	
	//locale variables
	int list_unsorted[N];
	int list_copy[N];
	clock_t temp;
	clock_t timeResult = 0;
	int check;
	
	//First, initilize the list
	srand(time(0));
	for (int i = 0; i < N; ++i) {
		list_unsorted[i] = rand() % N*10; //range of 0-N*10, should yield similar number of duplicates per list[N]
	}
	

	//Display Run Info
	cout << "For list size N = " << N << ", returning the " << K/N << " smallest element.\n";
	cout << "Number of trials ran: " << T << endl;
	if (D) {
		dispArray(list_unsorted);
	}


	//call and time Algorithm1 - MergeSort (select-kth 1) theor: O(n log n)
	for (int i = 0; i < T; ++i) {
		//reset the list
		copyList(list_copy, list_unsorted);
		//time it
		temp = clock();
		check = mergeSort(list_copy);
		temp = clock() - temp;
		//aggregate time
		timeResult += temp;
	}
	cout << "Mergesort: average of                     " << ((float)timeResult) / CLOCKS_PER_SEC / T << " seconds.\n";
	if (D) {
		dispArray(list_copy);
		cout << "check = " << check << endl;
	}


	if (D) {
		dispArray(list_unsorted);
	}
	//call and time Algorithm2 - Iterative Partition Sort (select-kth 2) theor: Best O(n) Worst O(n^2)
	timeResult = 0;
	for (int i = 0; i < T; ++i) {
		//reset the list
		copyList(list_copy, list_unsorted); 
		//time it
		temp = clock();
		check = ittPartition(list_copy);
		temp = clock() - temp;
		//aggregate time
		timeResult += temp;
	}
	cout << "Iterative Partition Sort: average of      " << ((float)timeResult) / CLOCKS_PER_SEC / T << " seconds.\n";
	if (D) {
		dispArray(list_copy);
		cout << "check = " << check << endl;
	}


	if (D) {
		dispArray(list_unsorted);
	}
	//call and time Algorithm3 - Recursive Partition Sort (select-kth 3) theor: Best O(n) Worst O(n^2)
	timeResult = 0;
	for (int i = 0; i < T; ++i) {
		//reset the list
		copyList(list_copy, list_unsorted); 
		//time it
		temp = clock();
		check = recPartition(list_copy);
		temp = clock() - temp;
		//aggregate time
		timeResult += temp;
	}
	cout << "Recursive Partition Sort: average of      " << ((float)timeResult) / CLOCKS_PER_SEC / T << " seconds.\n";
	if (D) {
		dispArray(list_copy);
		cout << "check = " << check << endl;
	}


/*
	if (D) {
		dispArray(list_unsorted);
	}
	//call and time Algorithm4 - Median of Median Partition Sort (select-kth 4) theor: O(n)
	timeResult = 0;
	for (int i = 0; i < T; ++i) {
		//reset the list
		copyList(list_copy, list_unsorted); 
		//time it
		temp = clock();
//		check = medPartition(list_copy);
		temp = clock() - temp;
		//aggregate time
		timeResult += temp;
	}
	cout << "Median of Median Partion Sort: average of " << ((float)timeResult) / CLOCKS_PER_SEC / T << " seconds.\n";
	if (D) {
		dispArray(list_copy);
		cout << "check = " << check << endl;
	}
*/
	system("pause");
	return 0;
}//end main



//FUNCTION DECLARATIONS ===========================================================================
/*
dispArray
- Displays the list
@param list[] the array to be displayed
*/
void dispArray(int list[]) {
	for (int i = 0; i < N; ++i) {
		cout << list[i] << " ";
	}
	cout << endl;
}//end dispArray


 /*
 copyList
 - copies list2 into list1
 @param list1[] destination to be copied to
 @param list2[] source to be copied from
 */
void copyList(int list1[], int list2[]) {
	for (int i = 0; i < N; ++i) {
		list1[i] = list2[i];
	}
}//end copyList


/*
	mergeSort - Algorithm 1 - slect-kth 1
	 - Sorts an array based  list using MergeSort
	@param list[] the unsorted list of integers to be sorted
	@return the value of the Kth smallest element int the list,
		the sorted list by reference.
*/
int mergeSort(int list[]) {
	mergeSortRec(list, 0, N - 1);
	return list[((int)floor(K))];
}//end Mergesort


/*
	mergeSortRec
	- the recursive engine for mergeSort
	@param list[] the list to be sorted
	@param first index of first element to consider in list
	@param last index of last element to consider in list
*/
void mergeSortRec(int list[], int first, int last) {
	if (first < last) {
		//get midpoint
		int mid = first + (last - first) / 2;
		//sort left half of array
		mergeSortRec(list, first, mid);
		//sort right half of array
		mergeSortRec(list, mid+1, last);
		//merge halves
		merge(list, first, mid, last);
	}
	else
		return;
}//end mergeSortRec


void merge(int list[], int first, int mid, int last) {
	//locale varaibles
	int tempList[N];
	int first1 = first;	//begining of first subarray
	int last1 = mid;	//end of first subarray
	int first2 = mid + 1;//begining of second subarray
	int last2 = last;	//end of second subarray

	//while both subarrays are not empty, copy smaller item
	//	into the temporary array
	int i = first1;
	while((first1 <= last1) && (first2 <= last2)) {
		//here, tempList[first to index-1] in order
		if (list[first1] <= list[first2])
		{
			tempList[i] = list[first1];
			++first1;
		}
		else {
			tempList[i] = list[first2];
			++first2;
		}//end if/else
		++i;
	}//end forloop

	//finish remainder of subarrays if neccessary
	while (first1 <= last1) {
		tempList[i] = list[first1];
		++first1;
		++i;
	}
	while (first2 <= last2) {
		tempList[i] = list[first2];
		++first2;
		++i;
	}

	//finally, copy result back to original array
	for (int i = first; i <= last; ++i) {
		list[i] = tempList[i];
	}
}//end merge


/*
	partition
	- classic partition method taken from quicksort
	@param list[] reference to the list
	@param low bottom array index
	@param high top array index
	@param pivotposition reference to the pivotposition being searched
	@return adjusted pivotposition through reference 
*/
void partition(int list[], int low, int high, int &pivotposition) {
	int v = list[low];
	int j = low;
	for (int i = low + 1; i <= high; ++i) {
		if (list[i] < v) {
			++j;
			int temp = list[i];
			list[i] = list[j];
			list[j] = temp;
		}
	}
	pivotposition = j;
	int temp = list[low];
	list[low] = list[pivotposition];
	list[pivotposition] = temp;
}//end partition


/*
	ittPartition
	- itterative partition sort method for returning the Kth smallest element
	@param list[] the unsorted list
	@return the value of the Kth smallest element in the list
*/
int ittPartition(int list[]) {
	int m = 0;
	int j = N -1;
	int k = ((int)floor(K));
	int pivotposition = 0;
	for (; ;) {
		partition(list, m, j, pivotposition);
		if (k == pivotposition) {
			return list[k];
		}
		else if (k < pivotposition) {
			j = pivotposition - 1;
		}
		else {
			m = pivotposition + 1;
		}
	}
}//end ittPartition


/*
	recPartitionRec
	- the recursive engine for the recPartition method.
	@param list[] reference to the list
	@param low bottom array index
	@param high top array index
	@param pivotposition reference to the pivotposition being searched
	@param k the index key to look for
	@return the value of the kth smallest element in the list,
		adjusted pivotposition by reference
*/
int recPartitionRec(int list[], int low, int high, int &pivotposition, int k) {
	partition(list, low, high, pivotposition);
	if (k == pivotposition) {
		return list[k];
	}
	else if(K < pivotposition) {
		high = pivotposition - 1;
		return recPartitionRec(list, low, high, pivotposition, k);
	}
	else {
		low = pivotposition + 1;
		return recPartitionRec(list, low, high, pivotposition, k);
	}
}


int recPartition(int list[]) {
	int m = 0;
	int j = N - 1;
	int k = ((int)floor(K));
	int pivotposition = m + (j - m) / 2;

	return recPartitionRec(list, m, j, pivotposition, k);
}//end recPartition

