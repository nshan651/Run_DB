/* [Merge Sort Algorithm]
*--algorithm to sort an array--
* --by Nick Shannon--
* --11/23/2020--
*/
#include <stdio.h>
#include <stdlib.h>

/*function to perform merge sort on an array*/
void mergeSort(int arry[], int left, int right) {
	if (left < right) {
		//equivalent to (left+right)/2 but avoids overflow
		int middle = left + (right - left) / 2; 
		
		//sort first and second halves
		mergeSort(arry, left, middle);
		mergeSort(arry, middle + 1, right);

		//merge the two halves
		//merge(arry, left, middle, right);
		int i,j,k;	//indexes for right, left, and middle
		int size_left = middle - left + 1; //left partition size
		int size_right = right - middle;	//right partition size
		//temp arrays
		int L[size_left], R[size_right];
		//copy new data into left and right arrays (L[] and R[])
		for (i =0; i < size_left; i++) {
			L[i] = arry[left + i]; 
		}
		for (j =0; j < size_right; j++) {
			R[j] = arry[middle + 1 + j];
		}
		//merge right and left arrays back into arry[]
		i =0;
		j =0;
		k =left;
		while (i < size_left && j < size_right) {
			if (L[i] <= R[j]) {
				arry[k] = L[i];
				i++;
			}
			else {
				arry[k] = R[j];
				j++;
			}
			k++;
		}
		//copy any remaining elements of either the right or left arrays
		while (i < size_left) {
			arry[k] = L[i];
			i++;
			k++;
		}
		while (j < size_right) {
			arry[k] = R[j];
			j++;
			k++;
		}
	}
}

/*test driver
int main(int argc, char **argv) {
	int test_array[] = {12, 11, 13, 5, 7, 9, 20};
	int size = sizeof(test_array) / sizeof(test_array[0]); // divide by one element to normalize bytes

	printf("intial array is\n");
	//printArray(test_array, size);

	//parameters: {array to sort}, {start}, {end}
	mergeSort(test_array, 0, size-1);

	printf("sorted array is\n");
	//printArray(test_array, size);

	return 0;
}
*/


