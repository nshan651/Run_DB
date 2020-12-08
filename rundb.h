/*RunDB Header File*/
#include <time.h> //for converting date to epoch time
#define DB "running_data.csv" //database name
/*exception handling using perror() library function*/
#define TRY(a)  if (!(a)) {perror(#a);exit(1);} 
#define TRY2(a) if((a)<0) {perror(#a);exit(1);}
/*max number of entries in the db and max line length to read*/
#define MAX_ELEMENTS 10000 
#define MAX_LINE_LEN 250   
/*define boolean values*/
#define TRUE 1
#define FALSE 0
/*DEFINE_DATA def referencing rundb.d to intialize global struct 
*with STORAGE_CLASS name
*/
#ifdef DEFINE_DATA
#define STORAGE_CLASS
#else
#define STORAGE_CLASS extern
#endif
/*typedefs*/
typedef unsigned char BOOL;

/*global function prototypes*/
void mergeSort(int left, int right, char *mode);
void structToEpochTime (int num);
int readDB(FILE *f); //func to read db
int writeDB(FILE *f); //func to write to db

void searchDB(char *date, int n, int *buf);
//void searchDB(char *date, int n, int *buf); //func to search db

int check_date(char *c); //func to validate date entered via terminal
int stringToEpochTime (char *my_date);

/*struct to contain each data record*/
struct DataRec {
	float distance;		
	float timeInMinutes;
	char date[25];
	time_t edate;
};