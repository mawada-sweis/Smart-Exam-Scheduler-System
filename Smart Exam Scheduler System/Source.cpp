#include <iostream>
#include <queue>
#include <vector>
#include <random>

using namespace std;
#define length 10

struct exam
{
	int domain_value,
		exam_order,
		time;
	char hole;
	queue<int> time_domain;
	queue<char> hole_domain;
	
	exam() {
		this->time = 0;
		this->hole = ' ';
		this->exam_order = 0;

		time_domain.push(1);
		time_domain.push(2);
		time_domain.push(3);
		time_domain.push(4);

		hole_domain.push('A');
		hole_domain.push('B');
		hole_domain.push('C');

		this->domain_value = time_domain.size()*hole_domain.size();
	}
	
	template<typename T>
	T random(vector<exam> const &v)
	{
		//auto it = v.cbegin();
		//exam random = v.cbegin() + (rand() % (v.end() - v.cbegin() + 1));
		//int random = rand() % v.size();

		//return *(it + random);
	}
	
	//template <typename v>
	//v backtracking_1(vector<exam> graph_1) {
	//	//G1: 1 3     G2: 4 9 10      G3: 2 5 6 7 8

	//	return random(graph_1);
	//}

};

struct graph {
	vector<exam> graph_1,
		graph_2,
		graph_3;
	
	void update_queue(exam* E) {
		for (int j = 0; j < length; j++)
		{
			switch (j) {
			case 0:
			case 2:
				insert(graph_1, E[j]);
				break;
			case 3:
			case 8:
			case 9:
				insert(graph_2, E[j]);
				break;
			case 1:
			case 4:
			case 5:
			case 6:
			case 7:
				insert(graph_3, E[j]);
				break;
			}
		}
	}
	
	// Function to swap position of two exam elements
	void swap(exam *a, exam *b) {
		exam temp = *b;
		*b = *a;
		*a = temp;
	}

	// Function to heapify the tree
	void heapify(vector<exam> &graph, int i) {

		// Find the largest among root, left child and right child
		int largest = i,
			left = i + 1,
			right = i + 2;

		if (left < graph.size() &&
			graph[left].domain_value > graph[largest].domain_value)
			largest = left;
		if (right < graph.size() &&
			graph[right].domain_value > graph[largest].domain_value)
			largest = right;

		// Swap and continue heapifying if root is not largest
		if (largest != i) {
			swap(&graph[i], &graph[largest]);
			heapify(graph, largest);
		}
	}

	// Function to insert an element into the tree
	void insert(vector<exam> &graph, exam new_Exam) {
		if (graph.size() == 0)
			graph.push_back(new_Exam);
		else {
			graph.push_back(new_Exam);
			for (size_t i = 0; i < graph.size(); i++) {
				heapify(graph, i);
			}
		}
	}

	// Function to delete an element from the tree
	void deleteNode(vector<exam> &graph, exam ex) {
		int i;
		for (i = 0; i < graph.size(); i++) {
			if (ex.domain_value == graph[i].domain_value)
				break;
		}
		swap(&graph[i], &graph[graph.size() - 1]);

		graph.pop_back();
		for (size_t i = graph.size(); i >= 0; i--) {
			heapify(graph, i);
		}
	}

	// Print the tree
	void print_graph() {
			for (size_t j = 0; j < graph_1.size(); j++) {
				cout << graph_1[j].exam_order << "\t";
			}
			cout << "\n";
			for (size_t j = 0; j < graph_2.size(); j++) {
				cout << graph_2[j].exam_order << "\t";
			}
			cout << "\n";
			for (size_t j = 0; j < graph_3.size(); j++) {
				cout << graph_3[j].exam_order << "\t";
			}
	}
};

int main() {

	exam E[length];
	
	for (size_t i = 0; i < length; i++)
	{
		E[i].exam_order = i + 1;
	}

	graph graph_structure;

	graph_structure.update_queue(E);
	
	int e = rand() % graph_structure.graph_2.size();
	cout << graph_structure.graph_2[e].exam_order;
	system("pause");
	return 0;
}