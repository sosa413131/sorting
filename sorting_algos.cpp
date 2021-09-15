#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int sequentialSearch(vector<int> v, int toFind) { //or linearSearch //Theta(N)
	for (int i = 0; i < v.size(); i++)
		if (v[i] == toFind) //this would run N/2 times
			return i;
	return -1;
}

int binarySearch(vector<int> v, int toFind) { //Theta(log N)
	int start = 0;
	int end = v.size() - 1;
	while (start <= end) {
		int mid = (start + end) / 2; //this would run log(n) times
		if (v[mid] == toFind)
			return mid;
		else if (v[mid] > toFind)
			end = mid - 1;
		else
			start = mid + 1;
	}
	return -1;
}

void selectionSort(vector<int>& v) { //Theta (N(N-1)/2).... Theta(N^2)
	for (int i = 0; i < v.size(); i++) { // This runs Theta(N)
		int min = i;
		for (int j = i + 1; j < v.size(); j++)
			if (v[j] < v[min]) //This runs Theta((N-1)/2) times
				min = j;
		int temp = v[min];
		v[min] = v[i];
		v[i] = temp;
	}
}
void insertionSort(vector<int>& v) { // Theta(N^2) (average) (Best case: Theta(N))
	for (int i = 1; i < v.size(); i++) { //this runs Theta(N)
		int temp = v[i];
		int j;
		for (j = i; j > 0 && v[j - 1] > temp; j--)
			v[j] = v[j - 1];
		v[j] = temp;
	}
}
void merge(vector<int>& v, int leftPos, int leftEnd, int rightEnd, vector<int>& temp) { //Theta(N)
	int rightPos = leftEnd + 1;
	int originalStart = leftPos;
	int tempPos = leftPos;
	while (leftPos <= leftEnd && rightPos <= rightEnd) {
		if (v[leftPos] < v[rightPos])
			temp[tempPos++] = v[leftPos++];
		else
			temp[tempPos++] = v[rightPos++];
	}
	while(leftPos <= leftEnd)
		temp[tempPos++] = v[leftPos++];
	while (rightPos <= rightEnd)
		temp[tempPos++] = v[rightPos++];
	for (int i = originalStart; i <= rightEnd; i++)
		v[i] = temp[i];
}
void mergeSort(vector<int>& v, int start, int end, vector<int>& temp) { //Theta(N log N)
	if (start < end) {
		int mid = (start + end) / 2;
		mergeSort(v, start, mid, temp);
		mergeSort(v, mid + 1, end, temp);
		merge(v, start, mid, end, temp);
	}
}
void mergeSort(vector<int>& v) { //driver for the real call
	vector<int> temp;
	temp.resize(v.size());
	mergeSort(v, 0, v.size() - 1, temp);
}
void insertionSort(vector<int>& v, int start, int end) { // Theta(N^2) (average) (Best case: Theta(N))
	for (int i = start+1; i <=end; i++) { //this runs Theta(N)
		int temp = v[i];
		int j;
		for (j = i; j > start && v[j - 1] > temp; j--)
			v[j] = v[j - 1];
		v[j] = temp;
	}
}
template <class T>
void quickSort(vector<T>& v, int start, int end) { //Theta (N^2) (worst case!) (average case; Theta(N log N)
	if ((end - start) <= 10)
		insertionSort(v, start, end);
	int center = (start + end) / 2;

	//median-of-three partitioning
	if (v[center] < v[start])
		swap(v[center], v[start]);
	if (v[end] < v[start])
		swap(v[end], v[start]);
	if (v[end] < v[center])
		swap(v[end], v[center]);
	T pivot = v[center];
	swap(v[center], v[end - 1]); //move pivot out of the way to make sorting easier
	int i = start;
	int j = end - 1;
	while (true) { //Theta(N)
		while (v[++i] < pivot) {} //find a value on the left that belongs on the right
		while (pivot < v[--j]) {} //find a value on the right that belongs on the left
		if (i < j)
			swap(v[i], v[j]);
		else
			break; //when i crosses j, we're finished
	}
	swap(v[i], v[end - 1]); //restore pivot to final place
	quickSort(v, start, i - 1);
	quickSort(v, i + 1, end);
}
template <class T>
void quickSort(vector<T>& v) {
	quickSort(v, 0, v.size() - 1);
}

void openInputFile(ifstream& inFile) {
	string filename;
	cout << "What filename? ";
	cin >> filename;
	inFile.open(filename);
	while (!inFile) { //uses operator bool to "test" the file object
		cout << "Bad filename" << endl;
		cout << "What filename? ";
		cin >> filename;
		inFile.clear(); // reset the failure flags in the object
		inFile.open(filename);
	}
}
void sayHello(ostream& outs) {
	outs << "Hello world!" << endl;
}

int main() {
	ofstream outFile("output.txt");
	sayHello(outFile);
	sayHello(cout);
}

template <class T>
class LList; //class pre-definition

template <class T>
class LListNode {
	T data;
	LListNode<T>* next;
public:
	LListNode(const T& newData = T(), LListNode<T>* newNext=nullptr) :data(newData), next(newNext) {}
	friend class LList<T>; //ok becuase the class was pre-defined
};

template <class T>
class LList {
	LListNode<T>* head;
};