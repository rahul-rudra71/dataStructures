#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctime>
using namespace std;

void merge(int arr[], int k, int m, int r) {
	int n1 = m - k + 1;
	int n2 = r - m;
	int L[n1], R[n2];

	//create left and right array
	for (int i = 0; i < n1; i++)
		L[i] = arr[k + i];

	for (int i = 0; i < n2; i++)
		R[i] = arr[m + 1 + i];

	int i = 0; 
	int j = 0;  

	//sort arrays based off lowest number betweeen left and right array
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	//which ever array has leftover elements copy to end of sorted portion
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(int arr[], int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;

		//seperate left and right side of the arrays
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		//merge left and right side of array
		merge(arr, l, m, r);
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
			mergeSort(arr, 0, fileSize - 1);

			//print out duration of sorting time. sorted array
			duration = (clock() - start) / (double)CLOCKS_PER_SEC;
			cout << "duration of "+ type[j] +": " << duration << '\n';
			//printArray(arr, fileSize);
		}
	}
	return 0;
}