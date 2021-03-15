#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <tuple>

using namespace std;
#define length 10

struct exam
{
	int exam_order;
	tuple<int, char> suggest;
	vector< tuple<int, char> > domain_list;
	exam() 
	{
		this->exam_order = 0;
		suggest = make_tuple(0, ' ');
	}
};

struct graph {
	vector<exam> graph_1,
		graph_2;
	
	// Function to print the suggest for each exam in each graph
	void print_graph() {
		cout << "\n*************************************\n";
		cout << "Graph 1 : \n";
		for (size_t i = 0; i < graph_1.size(); i++)
		{
			cout << graph_1[i].exam_order << "\t";
		}
		cout << "\nGraph 2 : \n";
		for (size_t i = 0; i < graph_2.size(); i++)
		{
			cout << graph_2[i].exam_order << "\t";
		}
		cout << "\n*************************************\n";
	}

	// Function to assign exams to each graph according to time constraint
	void update_queue(exam* E)
	{
		for (int j = 0; j < length; j++)
		{
			switch (j) 
			{
			case 0:
			case 2:
			case 3:
			case 8:
			case 9:
				insert(graph_1, E[j]);
				break;
			case 1:
			case 4:
			case 5:
			case 6:
			case 7:
				insert(graph_2, E[j]);
				break;
			}
		}
		print_graph();
	}
	
	// Function to heapify the tree
	void heapify(vector<exam>& graph,
		int i)
	{
		// Find the largest among root, left child and right child
		int largest = i,
			left = i + 1,
			right = i + 2;

		if (left < graph.size() &&
			graph[left].domain_list.size() > graph[largest].domain_list.size())
			largest = left;

		if (right < graph.size() &&
			graph[right].domain_list.size() > graph[largest].domain_list.size())
			largest = right;

		// Swap and continue heapifying if root is not largest
		if (largest != i) 
		{
			swap(graph[i], graph[largest]);
			heapify(graph, largest);
		}
	}

	// Function to insert an element into the tree
	void insert(vector<exam> &graph,
		exam new_Exam) 
	{
		if (graph.size() == 0)
			graph.push_back(new_Exam);
		else 
		{
			graph.push_back(new_Exam);
			for (int i = 0; i < graph.size(); i++) 
			{
				heapify(graph, i);
			}
		}
	}

};

// Function to update the domain list for each exam in his constraint
void update_domain_list(exam exams[]) {
	for (size_t i = 0; i < length; i++)
	{
		switch (i + 1) {
		case 1: 
		case 4:
			for (int k = 1; k < 4; k++) {
				for (char c = 65; c < 68; c++) {
					if (c == 66)
						continue;
					exams[i].domain_list.push_back(make_tuple(k, c));
				}
			}
			break;
		
		case 2: 
		case 5: 
		case 6:
			for (int k = 1; k < 5; k++) {
				for (char c = 65; c < 68; c++) {
					exams[i].domain_list.push_back(make_tuple(k, c));
				}
			}
			break;
		
		case 3:
			for (int k = 2; k < 5; k++) {
				for (char c = 65; c < 68; c++) {
					if (c == 66)
						continue;
					exams[i].domain_list.push_back(make_tuple(k, c));
				}
			}
			break;
		
		case 7:
		case 8: 
			for (int k = 1; k < 5; k++) {
				for (char c = 65; c < 67; c++) {
					exams[i].domain_list.push_back(make_tuple(k, c));
				}
			}

			break;
		
		case 9:
			for (int k = 1; k < 4; k++) {
				for (char c = 65; c < 67; c++) {
					exams[i].domain_list.push_back(make_tuple(k, c));
				}
			}
			break;
		
		case 10:
			for (int k = 2; k < 5; k++) {
				for (char c = 65; c < 67; c++) {
					exams[i].domain_list.push_back(make_tuple(k, c));
				}
			}
			break;
		}
	}
}

// Function to delete the suggested value after assign it to the variable from each exam in each graph
void pop_domain(graph& all_graph,
	tuple<int,char> suggest_to_remove) {

	for (size_t i = 0; i < all_graph.graph_1.size(); i++)
	{
		for (size_t k = 0; k < all_graph.graph_1[i].domain_list.size(); k++)
		{
			if (all_graph.graph_1[i].domain_list[k] == suggest_to_remove) 
			{
				for (size_t j = k; j < all_graph.graph_1[i].domain_list.size() - 1; j++)
				{
					all_graph.graph_1[i].domain_list[j].swap(all_graph.graph_1[i].domain_list[j + 1]);
				}
				all_graph.graph_1[i].domain_list.pop_back();
			}
		}
		
	}

	for (size_t i = 0; i < all_graph.graph_2.size(); i++)
	{
		for (size_t k = 0; k < all_graph.graph_2[i].domain_list.size(); k++)
		{
			if (all_graph.graph_2[i].domain_list[k] == suggest_to_remove)
			{
				for (size_t j = k; j < all_graph.graph_2[i].domain_list.size()-1; j++)
				{
					all_graph.graph_2[i].domain_list[j].swap(all_graph.graph_2[i].domain_list[j + 1]);
				}
				all_graph.graph_2[i].domain_list.pop_back();
			}
		}

	}

}

// Function to test if each suggest in the graph is unique value
bool is_unique(vector<exam> this_graph) {
	
	for (size_t i = 0; i < this_graph.size() - 1; i++)
	{
		for (size_t j = i + 1; j < this_graph.size(); j++)
		{
			if (this_graph[i].suggest == this_graph[j].suggest)
			{
				return false;
			}
		}
	}
	return true;
}

// Function to delete the wrong random suggest from each exam in his graph 
void pop_unique_suggest(vector<exam> this_graph,
	exam* e) 
{
	for (size_t i = 0; i < this_graph.size(); i++)
	{
		for (size_t j = 1; j < this_graph[i].domain_list.size(); j++)
		{
			if (this_graph[i].suggest == this_graph[i].domain_list[j])
			{
				for (size_t k = j; k < this_graph[i].domain_list.size() - 1; k++)
				{
					this_graph[i].domain_list[k].swap(this_graph[i].domain_list[k + 1]);
				}
				this_graph[i].domain_list.pop_back();
			}
		}
	}
}

// Function to find index of spacific exam order
int index_of(vector<exam> g, int element) {
	for (int i = 0; i < g.size(); i++)
	{
		if (g[i].exam_order == element) {
			return i;
		}
	}
	return -1;
}

// Function to assign each variable to a specific value from its domain
void backtracking(graph &all_graph,
	exam* e) 
{
	bool to_break = false;
	int i = all_graph.graph_1.size() - 1;
	do 
	{
		srand(time(0));
		for (int j = i; j >= 0; j--)
		{
			all_graph.graph_1[j].suggest =
				all_graph.graph_1[j].domain_list[rand() % all_graph.graph_1[j].domain_list.size()];
		}
		if (get<0>(all_graph.graph_1.at(index_of(all_graph.graph_1, 3)).suggest) > get<0>(all_graph.graph_1.at(index_of(all_graph.graph_1, 1)).suggest) &&
			all_graph.graph_1.at(index_of(all_graph.graph_1, 9)).suggest < all_graph.graph_1.at(index_of(all_graph.graph_1, 10)).suggest &&
			all_graph.graph_1.at(index_of(all_graph.graph_1, 4)).suggest < all_graph.graph_1.at(index_of(all_graph.graph_1, 10)).suggest &&
			is_unique(all_graph.graph_1)) 
		{
			for (size_t l = 0; l < 4; l++)
			{
				if (l == 1)
					continue;
				e[l].suggest =
					all_graph.graph_1[index_of(all_graph.graph_1, l + 1)].suggest;
			}
			for (size_t l = 8; l < 10; l++)
			{
				e[l].suggest =
					all_graph.graph_1[index_of(all_graph.graph_1, l + 1)].suggest;
			}
			to_break = true;
		}
		else
		{
			pop_unique_suggest(all_graph.graph_1,e);
		}
	} while (!to_break);	
	for (; i >= 0; i--)
	{
		pop_domain(all_graph, all_graph.graph_1[i].suggest);
	}

	to_break = false;
	i = all_graph.graph_2.size() - 1;
	do
	{
		srand(time(0));
		for (int j = i; j >= 0; j--) 
		{
			all_graph.graph_2[j].suggest =
				all_graph.graph_2[j].domain_list[rand() % all_graph.graph_2[j].domain_list.size()];
		}
		if (is_unique(all_graph.graph_2)) 
		{
			for (int l = 1; l < 8; l++) {
				if (l == 2 || l == 3)
					continue;
				e[l].suggest =
					all_graph.graph_2[index_of(all_graph.graph_2, l+ 1)].suggest;
			}
			to_break = true;
		}
		else
		{
			pop_unique_suggest(all_graph.graph_2, e);

		}
	} while (!to_break);
	for (; i >= 0; i--)
	{
		pop_domain(all_graph, all_graph.graph_2[i].suggest);

	}
}

void print_exam(exam* e) {
	for (size_t i = 0; i < length; i++)
	{
		cout << "E" << e[i].exam_order << " -> (t";
		cout << get<0>(e[i].suggest) << "," << get<1>(e[i].suggest) << ")\n";
	}
}

int main() 
{

	exam E[length];
	
	for (int i = 0; i < length; i++)
		E[i].exam_order = i + 1;

	update_domain_list(E);
	
	graph graph_structure;

	graph_structure.update_queue(E);
	
	backtracking(graph_structure, E);
		
	print_exam(E);
	
	return 0;
}