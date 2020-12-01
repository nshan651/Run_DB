/* [Merge Sort Algorithm]
*--algorithm to sort an array--
* --by Nick Shannon--
* --11/23/2020--
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rundb.d"

/*func prototype*/
static int mode_type(char *mode, int i, int j, struct DataRec *L, struct DataRec *R);

/*function to perform merge sort on an array*/
void mergeSort(int left, int right, char *mode) {	//(*myData)[] is a pointer

	if (left < right) {												//to global struct array
		//equivalent to (left+right)/2 but avoids overflow
		int middle = left + (right - left) / 2; 
		
		//sort first and second halves
		mergeSort(left, middle, mode);
		mergeSort(middle + 1, right, mode);
		//merge the two halves
		//merge(arry, left, middle, right);
		int i,j,k;	//indexes for right, left, and middle
		int size_left = middle - left + 1; //left partition size
		int size_right = right - middle;	//right partition size
		//temp arrays
		struct DataRec L[size_left];
		struct DataRec R[size_right];
		//copy new data into left and right arrays (L[] and R[])
		for (i =0; i < size_left; i++) {
			L[i] = myData[left + i]; 
		}
		for (j =0; j < size_right; j++) {
			R[j] = myData[middle + 1 + j];
		}
		//merge right and left arrays back into arry[]
		i =0;
		j =0;
		k =left;
		
		//merge the left and right struct arrays
		while (i < size_left && j < size_right) {

			//begin the merge
			if (mode_type(mode, i, j, L, R)) {
				myData[k] = L[i];
				i++;
			}
			else {
				myData[k] = R[j];
				j++;
			}
			k++;			
		}

		//copy any remaining elements of either the right or left arrays
		while (i < size_left) {
			myData[k] = L[i];
			i++;
			k++;
		}
		while (j < size_right) {
			myData[k] = R[j];
			j++;
			k++;
		}
	}
}

/*static function that determines how to sort struct array*/
static int mode_type(char *mode, int i, int j, struct DataRec *L, struct DataRec *R) {
	int condition;
	/*conditonal comparisons*/
			if (strcmp(mode, "distance/d") == 0) {
				condition = L[i].distance >= R[j].distance;

			}
			else if (strcmp(mode, "distance/a") == 0) {
				condition = L[i].distance <= R[j].distance;

			}
			else if (strcmp(mode, "time/d") == 0) {
				condition = L[i].timeInMinutes >= R[j].timeInMinutes;

			}
			else if (strcmp(mode, "time/a") == 0) {
				condition = L[i].timeInMinutes <= R[j].timeInMinutes;

			}
			else if (strcmp(mode, "date/d") == 0) {
				condition = L[i].edate >= R[j].edate;

			}
			else if (strcmp(mode, "date/a") == 0) {
				condition = L[i].edate <= R[j].edate; 
			}
			else {
				printf("FATAL ERROR");
				exit(0);
			}
		return condition;
}



/*
//test driver
int main(int argc, char **argv) {
	int test_array[] = {12, 11, 13, 5, 7, 9, 20};
	int size = sizeof(test_array) / sizeof(test_array[0]); // divide by one element to normalize bytes

	printf("intial array is\n");
	//printArray(test_array, size);

	//parameters: {array to sort}, {start}, {end}
	//mergeSort(0, size-1);

	printf("sorted array is\n");
	//printArray(test_array, size);

	return 0;
}
*/




