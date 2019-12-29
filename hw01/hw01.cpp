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
};
struct flow
{
    int id;
    int first;
    int second;
    int size;
};

struct graph **array;
int thoughnum, acceptflow;

void find_thout(int thoutnum, int acceptflow);
void creat_array(int i);
void take_or_throw(int requestflow);
void out_array(int num);
void dijkstra(int graph[][thoughnum], int src);
int minDistance(int dist[], bool sptset[]);

int main()
{
    //insert every data to 2 dem array
    cin >> thoughnum;
    cin >> acceptflow;
    find_thout(thoughnum, acceptflow);
    out_array(thoughnum);

    int requestflow;
    cin >> requestflow;
}
int minDistance(int dist[], bool sptset[])
{
    int min = __INT_MAX__, min_index;
    for (int i = 0; i < thoughnum; i++)
    {
        if (sptset[i] == false && dist[i] <= min)
            min = dist[i], min_index = i;
    }
    return min_index;
}
void dijkstra(int Graph[][thoughnum], int src)
{
    int dist[thoughnum]; //out array
    bool sptset[thoughnum];
    for (int i = 0; i < thoughnum; i++)
        dist[i] = __INT_MAX__, sptset[i] = false; //return all to false
    dist[src] = 0;
    for (int count = 0; count < thoughnum - 1; count++)
    {                                      //find shortest path from point src
        int u = minDistance(dist, sptset); //pick up the min vertex form src
        sptset[u] = true;                  //mark the vertex as process
        for (int v = 0; v < thoughnum; v++)
        {
            if (!sptset[v] && Graph[u][v] && dist[u] != __INT_MAX__ && dist[u] + Graph[u][v] < dist[v])
                dist[v] = dist[u] + Graph[u][v];
        }
    }
}
void creat_array(int i)
{
    array = (struct graph **)malloc(sizeof(struct graph *) * i); //malloc a 2 dem array
    for (int k = 0; k < i; k++)
        array[k] = (struct graph *)malloc(i * sizeof(struct graph));
    for (int k = 0; k < i; k++) //reset array
        for (int j = 0; j < i; j++)
            array[k][j].capacity = 0;
}
void find_thout(int thoutnum, int acceptflow)
{ //creat a array to store every line and point
    creat_array(thoutnum);
    int i, first_node, second_node, input_capacity, input_id;
    for (i = 0; i < acceptflow; i++)
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
}