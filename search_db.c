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

/*search function using binary search
* int *buf is a pointer to an array where possible matches 
* will be stored for later use*/
void searchDB(char *date, int n, int *buf) {
	char target_date[10]; // <--get rid of this later
	int left = 0;
	int right = n-1;
	int middle, target, i;
	int count = 0;
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
				buf[0] = middle; //first entry found!
				count++; 
				//begin middle-out apporach to find other entries on same date
				i =1;
				while ( (myData[middle-i].edate == target) || 
					(myData[middle+i].edate == target) ) {
					if (myData[middle-i].edate == target) {
						buf[i] = middle-i;
						count++;
						i++;
					}
					else if (myData[middle+i].edate == target) {
						buf[i] = middle+i;
						count++;
						i++;
					}
					else {
						break;
					}
				} 

				//set sentinal value to -1 so that we know length of buf[]
				buf[count] = -1;
				//print matches found to the terminal
				printf("Entries found: %d\n\n", count);
				for (i =0; i < count; i++) {			
					printf("[%d]\n      Distance(mi)  Time(min)      Date\n", i);
					printf("     +------------+----------+-------------+\n");
					printf("         %.2f       %.2f     %s\n\n",myData[buf[i]].distance,myData[buf[i]].timeInMinutes,
		                  myData[buf[i]].date);
				}
	            return; //void return
			}//end else
		}
		if (myData[middle].edate != target) {
			printf("ERROR: target not found!\n");
		}
	} else {
		printf("not a valid date!\n");
		printf("enter a date in the form 'mm/dd/yyyy'\n");
	}
	return;
}


