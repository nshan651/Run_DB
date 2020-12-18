/*Program to calculate derivations of 
*data entries*/
#include <stdio.h>
#include <stdlib.h>

/*mph*/
float miles_per_hour(float distanceInMiles, float timeInMinutes) {
	return (distanceInMiles/(timeInMinutes/60));
}

/*kph*/
float kilometers_per_hour(float distanceInMiles, float timeInMinutes) {
	return ((1.609*distanceInMiles)/(timeInMinutes/60));
}

/*calculate minutes per mile*/
float min_per_mile(float distanceInMiles, float timeInMinutes) {
	return (timeInMinutes/distanceInMiles);
}

/*calculate kilometers per mile*/
float min_per_kilometer(float distanceInMiles, float timeInMinutes) {
	return (timeInMinutes/(1.609*distanceInMiles));
}
