#include <iostream>
#include <string>
#include <queue>
#include <vector>

using namespace std;
#define length 10

struct exam
{
	int value_ordering;
	string time,
		hole;
	exam* next;
	queue<string> domain;
	exam(string time = "un defined",
		string hole = "un defined") {
		this->time = time;
		this->hole = hole;
		this->next = nullptr;
		this->value_ordering = 12;
	}
};

void print_domain(exam e, int i) {
	cout << "Exam (" << i << ") ->\t";
	while (!e.domain.empty())
	{
		cout << e.domain.front()<< "\t";
		e.domain.pop();
	}
	cout << endl;
}

void print_value(exam e, int i) {
	cout << "Exam (" << i << ") -> " << e.value_ordering;
	cout << endl;
}

void update_domain(exam *E)
{
	for (size_t i = 0; i <length; i++)
	{
		switch (i + 1)
		{
			case 1:
			case 4:
				for (size_t j = 0; j <3; j++)
				{
					for (size_t c = 65; c <68; c += 2)
					{
						string s = "t" + to_string(j + 1) + "," + char(c);
						E[i].domain.push(s);
					}
				}
				break;
			case 2:
			case 5:
			case 6:
				for (size_t j = 0; j < 4; j++)
				{
					for (size_t c = 65; c < 68; c++)
					{
						string s = "t" + to_string(j + 1) + "," + char(c);
						E[i].domain.push(s);
					}
				}
				break;
			case 3:
				for (size_t j = 1; j <4; j++)
				{
					for (size_t c = 65; c <68; c += 2)
					{
						string s = "t" + to_string(j + 1) + "," + char(c);
						E[i].domain.push(s);
					}
				}
				break;
			case 7:
			case 8:
				for (size_t j = 0; j < 4; j++)
				{
					for (size_t c = 65; c < 67; c++)
					{
						string s = "t" + to_string(j + 1) + "," + char(c);
						E[i].domain.push(s);
					}
				}
				break;
			case 9:
				for (size_t j = 0; j < 3; j++)
				{
					for (size_t c = 65; c < 67; c++)
					{
						string s = "t" + to_string(j + 1) + "," + char(c);
						E[i].domain.push(s);
					}
				}
				break;
			case 10:
				for (size_t j = 2; j < 4; j++)
				{
					for (size_t c = 65; c < 67; c++)
					{
						string s = "t" + to_string(j + 1) + "," + char(c);
						E[i].domain.push(s);
					}
				}
				break;
		}
	}
	
	for (size_t i = 0; i < length; i++)
	{
		E[i].value_ordering = E[i].domain.size();
	}

}


// Function to swap position of two elements
void swap(exam *a, exam *b) {
	exam temp = *b;
	*b = *a;
	*a = temp;
}

// Function to heapify the tree
void heapify(vector<exam> &ue, int i) {

	// Find the largest among root, left child and right child
	int largest = i,
		left = i + 1,
		right = i + 2;

	if (left < ue.size() &&
		ue[left].value_ordering > ue[largest].value_ordering)
		largest = left;
	if (right < ue.size() &&
		ue[right].value_ordering > ue[largest].value_ordering)
		largest = right;

	// Swap and continue heapifying if root is not largest
	if (largest != i) {
		swap(&ue[i], &ue[largest]);
		heapify(ue, largest);
	}
}

// Function to insert an element into the tree
void insert(vector<exam> &ue, exam new_Exam) {
	if (ue.size() == 0)
		ue.push_back(new_Exam);
	else {
		ue.push_back(new_Exam);
		for (int i = ue.size(); i >= 0; i--) {
			heapify(ue, i);
		}
	}
}

// Function to delete an element from the tree
void deleteNode(vector<exam> &ue, exam ex) {
	int i;
	for (i = 0; i < ue.size(); i++) {
		if (ex.value_ordering == ue[i].value_ordering)
			break;
	}
	swap(&ue[i], &ue[ue.size() - 1]);

	ue.pop_back();
	for (int i = ue.size(); i >= 0; i--) {
		heapify(ue, i);
	}
}

// Print the tree
void printArray(vector<exam> &hT) {
	for (int i = 0; i < hT.size(); ++i)
		cout << i << " " << hT[i].value_ordering << "\n";
	cout << "\n";
}

int main() {

	exam E[length];
	update_domain(E);
	
	for (size_t i = 0; i < length; i++)
	{
		print_domain(E[i], i + 1);
		print_value(E[i], i + 1);
	}

	vector<exam> unassigned_exam,
		assigned_exam;
	for (size_t i = 0; i < length; i++)
	{
		insert(unassigned_exam, E[i]);
	}
	cout << "Max-Heap array: ";
	printArray(unassigned_exam);

	for (size_t i = 0; i < length; i++)
	{
		deleteNode(unassigned_exam, E[i]);
	}
	cout << "After deleting an element: ";

	printArray(unassigned_exam);

	system("pause");
	return 0;
}