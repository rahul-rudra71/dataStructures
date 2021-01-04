#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctime>
using namespace std;

void insertionSort(int arr[], int n) {
	int j, key;
	for (int i = 1; i < n; i++) {
		//store the current value as the key
		key = arr[i];
		j = i - 1;
		//shift elements in array until key is in appropriate location
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
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
			insertionSort(arr, fileSize);

			//print out duration of sorting time. sorted array
			duration = (clock() - start) / (double)CLOCKS_PER_SEC;
			cout << "duration of "+ type[j] +": " << duration << '\n';
			//printArray(arr, fileSize);
		}
	}
	return 0;
}