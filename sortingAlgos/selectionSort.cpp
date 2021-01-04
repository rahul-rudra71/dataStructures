#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctime>
using namespace std;

void swap(int *x, int *y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

void selectionSort(int arr[], int n) {
	int min_idx;

	// One by one move boundary of unsorted subarray
	for (int i = 0; i < n - 1; i++) {
		// Find the minimum element in unsorted array
		min_idx = i;
		for (int j = i + 1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;

		// Swap the found minimum element with the first element
		swap(&arr[min_idx], &arr[i]);
	}
}

void printArray(int arr[], int n) {
	for (int i = 0; i < n; i++)
		cout << arr[i] << ' ';
}

int main() {
	int sizes[] = {5000, 10000, 20000, 50000};
	string type[] = {"Asc", "Des", "Ran"};
	for(int i = 0; i < 4; i++) {
		cout << "**** File Size: " << sizes[i] << " ****\n";
		for(int j = 0; j < 3; j++) {
			//collect contents of file and store them into array
			int fileSize = sizes[i];
			int arr[fileSize];
			ifstream File;
			File.open("testFiles/"+ to_string(fileSize) + type[j] +".txt");
			int ind = 0;
			while (!File.eof()) {
				File >> arr[ind];
				ind++;
			}
			File.close();

			// start clock
			clock_t start;
			double duration;
			start = clock();

			//start sort
			selectionSort(arr, fileSize);

			//print out duration of sorting time. sorted array
			duration = (clock() - start) / (double)CLOCKS_PER_SEC;
			cout << "duration of "+ type[j] +": " << duration << '\n';
			//printArray(arr, fileSize);
		}
	}
	return 0;
}