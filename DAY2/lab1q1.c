#include <stdio.h>
#include <limits.h>
int main()
 {
int n, i;
FILE *fp;
fp = fopen("input.txt", "r");
if (fp == NULL) {
printf("File not found!\n");
return 1;
}
fscanf(fp, "%d", &n);
int arr[n];
for(i = 0; i < n; i++)
fscanf(fp, "%d", &arr[i]);
fclose(fp);
int smallest = INT_MAX, secondSmallest = INT_MAX;
int largest = INT_MIN, secondLargest = INT_MIN;
for(i = 0; i < n; i++) {
if(arr[i] < smallest) {
secondSmallest = smallest;
smallest = arr[i];
}
else if(arr[i] < secondSmallest && arr[i] != smallest) {
secondSmallest = arr[i];
}
if(arr[i] > largest) {
secondLargest = largest;
largest = arr[i];
}
else if(arr[i] > secondLargest && arr[i] != largest) {
secondLargest = arr[i];
}
}
printf("Second Smallest = %d\n", secondSmallest);
printf("Second Largest = %d\n", secondLargest);
return 0;
}