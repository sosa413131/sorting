#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <list>

using namespace std;

void openInputFile(ifstream& inFile) {
	string filename;
	cout << "What file? ";
	cin >> filename;
	inFile.open(filename);
	while (!inFile) {
		cout << "BAD FILENAME!" << endl;
		cout << "What file? ";
		cin >> filename;
		inFile.clear(); //recommended, but not required anymore (c++14)
		inFile.open(filename);
	}
}

template<class T>
int sequentialSearch(vector<T> v, const T& toFind) { //Theta(N)
	for (int i = 0; i < v.size(); i++)
		if (v[i] == toFind)
			return i;
	return -1;
}

template<class T>
int binarySearch(vector<T> v, const T& toFind) { //Theta(log N)
	int start = 0;
	int end = v.size() - 1;
	while (start <= end) {
		int mid = (start + end) / 2;
		if (v[mid] == toFind)
			return mid;
		else if (v[mid] > toFind)
			end = mid - 1;
		else
			start = mid + 1;
	}
	return -1;
}

template <class T>
void selectionSort(vector<T>& v) { //Theta(N^2)
	for (int i = 0; i < v.size(); i++) { //choose a location 0-v.size()
		int indexOfMin = i;
		for (int j = i + 1; j < v.size(); j++) { //find the minimum element from i to v.size()
			if (v[j] < v[indexOfMin])
				indexOfMin = j;
		}
		//swap the values
		T temp = v[i];
		v[i] = v[indexOfMin];
		v[indexOfMin] = temp;
	}
}

template <class T>
void insertionSort(vector<T>& v) {  // Between Theta(N) and Theta(N^2)
	for (int i = 1; i < v.size(); i++) { //Theta(N)
		int j = i;
		T temp = v[j];
		while (j > 0 && v[j - 1] > temp) //Worst Case: Theta(N), Best case: Theta(1)
			v[j] = v[j - 1];
		v[j] = temp;
	}
}

template <class T>
void insertionSort(vector<T>& v, int start, int end) {  // Between Theta(N) and Theta(N^2)
	for (int i = start+1; i < end; i++) { //Theta(N)
		int j = i;
		T temp = v[j];
		while (j > start && v[j - 1] > temp) //Worst Case: Theta(N), Best case: Theta(1)
			v[j] = v[j - 1];
		v[j] = temp;
	}
}

template<class T>
void merge(vector<T>& v, int leftPos, int leftEnd, int rightEnd, vector<T>& temp) { //theta(N)
	int rightPos = leftEnd + 1;
	int originalStart = leftStart;
	int tempPos = leftPos;
	while (leftPos <= leftEnd && rightPos <= rightEnd) {
		if (v[leftPos] < v[rightPos])
			temp[tempPos++] = v[leftPos++];
		else
			temp[tempPos++] = v[rightPos++];
	}
	while (leftPos <= leftEnd)
		temp[tempPos++] = v[leftPos++];
	while (rightPos <= rightEnd)
		temp[tempPos++] = v[rightPos++];
	for (int i = originalStart; i <= rightend; i++)
		v[i] = temp[i];
}

template<class T>
void mergeSort(vector<T>& v, int start, int end, vector<T>& temp) {
	if (start < end) {
		int mid = (start + end) / 2;
		mergesort(v, start, mid, temp);
		mergesort(v, mid + 1, end, temp);
		merge(v, start, mid, end, temp);
	}
}
template<class T>
void mergeSort(vector<T>& v) { //driver
	vector<T> temp;
	temp.resize(v.size());
	mergesort(v, 0, v.size() - 1, temp); //call the "real" function to do the work
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


template <class T> //class predefinition
class LList;
template <class T>
class LListItr;

template <class T>
class LListNode {
	T data;
	LListNode<T>* next;
	LListNode<T>* prev;
public:
	LListNode(const T& newdata = T(), LListNode<T>* newnext = nullptr, LListNode<T>* newprev = nullptr) :data(newdata), next(newnext), prev(newprev) {}
	friend class LList<T>;
	friend class LListItr<T>;
};
class EmptyListError {};

template <class S>
class LListItr {
	LListNode<S>* ptr;
public:
	LListItr(LListNode<S>* newptr = nullptr) :ptr(newptr) {}
	S& operator*() { return ptr->data; }
	S operator*() const { return ptr->data; }
	LListItr operator++(int);
	LListItr& operator++();
	LListItr operator--(int);
	LListItr& operator--();
	bool operator==(const LListItr<S>& rhs) const { return ptr == rhs.ptr; }
	bool operator!=(const LListItr<S>& rhs) const { return ptr != rhs.ptr; }
	friend class LList<S>;
};

template <class T>
class LList {
	LListNode<T>* head;
	LListNode<T>* tail;
	int numElements;
public:

	LListItr<T> begin() { return head->next; }
	LListItr<T> end() { return tail; }
	bool isEmpty() const { return numElements == 0; }
	LList();
	virtual ~LList();
	void push_front(const T& newdata);
	void push_back(const T& newdata) { insertAfter(newdata, tail->prev); }
	int size() const { return numElements; }
	void clear();
	LList(const LList<T>& rhs);
	LList& operator=(const LList& rhs);
	T pop_front() { if (!isEmpty()) return removeNode(head->next); else throw EmptyListError(); }
	T pop_back() { if (!isEmpty()) return removeNode(tail->prev); else throw EmptyListError(); }

	void insertAfter(const T& newdata, LListItr<T> itr);
	T removeNode(LListItr<T> itr);
};
template <class T>
LListItr<T> LListItr<T>::operator--(int) {
	LListItr<T> temp = *this;
	if (ptr->prev != nullptr)
		ptr = ptr->prev;
	return temp;
}
template <class T>
LListItr<T>& LListItr<T>::operator--() {
	if (ptr->prev != nullptr)
		ptr = ptr->prev;
	return *this;
}

template <class T>
LListItr<T> LListItr<T>::operator++(int) {
	LListItr<T> temp = *this;
	if (ptr->next != nullptr)
		ptr = ptr->next;
	return temp;
}
template <class T>
LListItr<T>& LListItr<T>::operator++() {
	if (ptr->next != nullptr)
		ptr = ptr->next;
	return *this;
}
template <class T>
T LList<T>::removeNode(LListItr<T> itr) {
	LListNode<T>* toDelete = itr.ptr;
	T retval = toDelete->data;
	toDelete->prev->next = toDelete->next;
	toDelete->next->prev = toDelete->prev;

	delete toDelete;
	numElements--;
	return retval;
}

template <class T>
void LList<T>::insertAfter(const T& newdata, LListItr<T> itr) {
	LListNode<T>* temp = itr.ptr;
	numElements++;
	temp->next = new LListNode<T>(newdata, temp->next, temp);
	temp->next->next->prev = temp->next;


	/*LListNode<T>* newnode = new LListNode<T>;
	newnode->prev = temp;
	newnode->next = temp->next;
	temp->next = newnode;
	newnode->next->prev = newnode;
	*/

}
template <class T>
LList<T>& LList<T>::operator=(const LList<T>& rhs) {
	if (this == &rhs)
		return *this;
	clear();

	for (LListNode<T>* temp = rhs.head->next; temp != rhs.tail; temp = temp->next)
		push_back(temp->data);
	return *this;
}
template <class T>
LList<T>::LList(const LList<T>& rhs) {
	numElements = 0;
	head = new LListNode<T>(T(), new LListNode<T>); //create two dummy nodes.
	tail = head->next;
	tail->prev = head;
	*this = rhs;
}
template <class T>
void LList<T>::clear() {
	while (!isEmpty())
		removeNode(head->next);
}
template <class T>
void LList<T>::push_front(const T& newdata) {
	insertAfter(newdata, head);
}
template <class T>
LList<T>::~LList() {
	clear();
	delete head;
	delete tail;
}
template <class T>
LList<T>::LList() {
	numElements = 0;
	head = new LListNode<T>(T(), new LListNode<T>); //create two dummy nodes.
	tail = head->next;
	tail->prev = head;
}



int main() {
	list<int> l1;
	l1.push_back(10);
	l1.push_back(20);

	list<int>::iterator i = l1.begin();
	cout << *i << endl; //print the first element of the list
	i++;
	cout << *i << endl; //print the second element of the list

	list<int>::iterator endDemo = l1.end();
	//cout << *endDemo << endl; // NOT VALID!!!!!!
	endDemo--;
	cout << *endDemo << endl; // OK, this is the last element!
}