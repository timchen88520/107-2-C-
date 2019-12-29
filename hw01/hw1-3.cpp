#include <iostream>
#include <stdio.h>
#include <list>
using namespace std;
struct graph
{
	int id;
	int first;
	int second;
	int capacity;
	int load;
};

struct graph **array;
int vertex_num, acceptflow_num;

void find_flow(int vertex_num, int acceptflow_num);
void creat_2dem_array(int i);
void creat_1dem_array(int num, int *arry);
void take_or_throw(int requestflow);
void out_array(int num);
void shortestpath(int current, int goal, int *distance, int *found);
int choose(int distance[], int vertex_num, int found[]);
float count_load(int u, int w);
void take_or_throw();

int main()
{
	//insert every data to 2 dem array
	cin >> vertex_num;
	cin >> acceptflow_num;
	find_flow(vertex_num, acceptflow_num);
	out_array(vertex_num);

	int requestflow;
	cin >> requestflow;
	while (requestflow > 0)
	{
		take_or_throw();
		requestflow--;
	}
}


void creat_2dem_array(int num)
{
	array = new struct graph *[num];
	for (int k = 0; k < num; k++)
		array[k] = new struct graph[num];

	for (int k = 0; k < num; k++) //return every to 0
		for (int j = 0; j < num; j++)
		{
			array[k][j].capacity = 0;
			array[k][j].load = 0;
		}
}
void find_flow(int thoutnum, int acceptflow_num)
{ //creat a array to store every line and point
	creat_2dem_array(thoutnum);
	int i, first_node, second_node, input_capacity, input_id;
	for (i = 0; i < acceptflow_num; i++)
	{ //start insert data to array
		cin >> input_id >> first_node >> second_node >> input_capacity;
		array[first_node][second_node].capacity = input_capacity; //insert data to first-second
		array[first_node][second_node].id = input_id;
		array[first_node][second_node].first = first_node;
		array[first_node][second_node].second = second_node;

		array[second_node][first_node].capacity = input_capacity; //insert data to second first
		array[second_node][first_node].id = input_id;
		array[second_node][first_node].first = first_node;
		array[second_node][first_node].second = second_node;
	}
}
void out_array(int num)
{ //output array to check
	for (int i = 0; i < num; i++)
	{
		for (int k = 0; k < num; k++)
		{
			cout << array[i][k].capacity << "\t";
		}
		cout << endl;
	}
	//cout << array[2][0].capacity << endl;
}
