/* [Binary Search Algorithm]
*--algorithm to search a sorted array--
* --by Nick Shannon--
* --11/23/2020--
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> //for floor() function
#include "rundb.d"

/*search function using binary search*/
int searchDB(char *date, int n) {
	char target_date[10];
	int left = 0;
	int right = n-1;
	int middle;
	int target;
	//int middle;
	if (check_date(date)) {
		//set struct values if date is valid
		strcpy(target_date, date);
		target = stringToEpochTime(target_date);
		//binary search
		while (left <= right) {
			middle = floor((left + right) /2);
			if (myData[middle].edate > target) {
				left = middle + 1;
			}
			else if (myData[middle].edate < target) {
				right = middle - 1;
			}
			else {
				printf("Entry found!\n");
				printf("\n Distance(mi)  Time(min)      Date\n");
				printf("+------------+----------+---------------+\n");
				printf("    %.2f        %.2f        %s\n\n",myData[middle].distance,myData[middle].timeInMinutes,
	                  myData[middle].date);
	            return middle; //return the target index
			}
		}
		if (myData[middle].edate != target) {
			printf("ERROR: target not found!\n");

		}
	} else {
		printf("not a valid date!\n");
		printf("enter a date in the form 'mm/dd/yyyy'\n");
	}
	return -1;
}

/* Test Driver
int main(int argc, char **argv) {
	int test[] = {1,4,16,22,23,27,29,55};
	printf("target value is: 16\n");
	//binarySearch(test, 8, 16);
	binarySearch(test, 8, 29);
	

}
*/

