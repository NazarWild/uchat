#include "../inc/libmx.h"
static int mini_quicksort(char **arr, int left, int right) {
	int small = left - 1;
	int pivot = right;
	char *swap;
	for(int i = left; i <= right - 1;i++) {
		if(mx_strlen(arr[i]) <= mx_strlen(arr[pivot])) {
		//if(mx_strcmp(arr[i],arr[pivot]) < 0) {
			small++;
			swap = arr[small];
			arr[small] = arr[i];
			arr[i] = swap;
		}
	}
			swap = NULL;
			swap = arr[small + 1];
			arr[small + 1] = arr[pivot];
			arr[pivot] = swap;
	return (small + 1);
}

 int mx_quicksort(char **arr, int left, int right) {
 	int counter = 0;
 	if(left < right) {
 		int pi = mini_quicksort(arr,left,right);
 		mx_quicksort(arr, left, pi - 1);
 		mx_quicksort(arr, pi + 1, right);
 		//counter = counter + (pi) + mx_quicksort(arr, left, pi - 1);
 		//counter = counter + mx_quicksort(arr, pi + 1, right);
  	}
 	return counter;
 }

