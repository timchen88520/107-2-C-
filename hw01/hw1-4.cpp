#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;
struct graph
{
    int capacity;
    int load;
};
struct path
{
    int id;
    int from;
    float cost;
};
struct output
{
    int id;
    int nums[100];
};
struct graph **array;
struct output out[10000];
int vertex_num, acceptflow_num, totle_output = 0, totle_throughput = 0;

void creat_2dem_array();
void out_array();
void out_table(struct path *now);
void find_flow(int acceptflow_num);
void take_or_throw();
void shortestpath();
float count_weight(int size, int already_capacity, int already_load);
void printout();

int main()
{
    freopen("input.txt", "r", stdin);
    cin >> vertex_num >> acceptflow_num;
    find_flow(acceptflow_num);
    take_or_throw();
    printout();
    return 0;
}
void take_or_throw()
{
    int requestflow;
    cin >> requestflow;
    for (int i = 0; i < 10000; i++)
        for (int k = 0; k < 100; k++)
            out[i].nums[k] = -1;
    while (requestflow > 0)
    {
        shortestpath();
        requestflow--;
    }
}
void shortestpath()
{
    struct path table[vertex_num];
    int first, second, flow_id, flow_size;
    queue<int> save;
    for (int i = 0; i < vertex_num; i++)
    { //creat table
        table[i].id = i;
        table[i].cost = 10000;
        table[i].from = -1;
    }
    cin >> flow_id >> first >> second >> flow_size;
    table[first].from = -2; //mark the first one
    table[first].cost = 0;
    save.push(table[first].id);
    while (!save.empty())
    {
        int now = save.front(); //pop out a element every time
        for (int i = 0; i < vertex_num; i++)
        { //find oput every point can go from pop item(also haven't went already)
            if (array[now][i].capacity > 0 && i != now)
            { //now = next point
                float count;
                // mark where it from point now
                count = count_weight(flow_size, array[i][now].capacity, array[i][now].load); //count point to next lengh
                if ((table[now].cost + count < table[i].cost) && (flow_size + array[i][now].load <= array[i][now].capacity))
                { //if current + lengh <next.cost , replace next.cost
                    table[i].cost = table[now].cost + count;
                    table[i].from = now;
                    save.push(i);
                }
            }
        }
        int check = table[second].from;
        save.pop();
    }

    if (table[second].from != -1) //max == no road to final point
    {
        totle_throughput += flow_size;
        int check = second, last = 0, tot = 0;
        out[totle_output].id = flow_id;

        while (1)
        { //out all path OBO
            out[totle_output].nums[tot] = check;
            tot++;

            last = check;
            check = table[last].from;
            if (check == -2)
                break;
            array[last][check].load += flow_size;
            array[check][last].load += flow_size;
        }
        totle_output++;
    }
}
float count_weight(int size, int already_capacity, int already_load)
{
    float last;
    last = (float)already_load / (((float)already_capacity) - ((float)already_load));
    if (already_load == already_capacity)
        last = 10001;

    return last;
}
void printout()
{
    cout << totle_output << "\t" << totle_throughput << endl;
    for (int i = 0; i < totle_output; i++)
    {
        int count_num = 0;
        cout << out[i].id;
        for (int k = 0; out[i].nums[k] != -1; k++)
            count_num++;
        for (int k = count_num - 1; k > -1; k--)
            cout << "\t" << out[i].nums[k];
        cout << endl;
    }
}
void find_flow(int acceptflow_num)
{
    creat_2dem_array();
    int first_node, second_node, input_capacity, input_id;
    for (int i = 0; i < acceptflow_num; i++)
    {
        cin >> input_id >> first_node >> second_node >> input_capacity;
        array[first_node][second_node].capacity = input_capacity;
        array[second_node][first_node].capacity = input_capacity;
    }
}
void out_array()
{
    for (int i = 0; i < vertex_num; i++)
    {
        for (int k = 0; k < vertex_num; k++)
        {
            cout << array[i][k].load << "\t";
        }
        cout << endl;
    }
}
void out_table(struct path *now)
{
    for (int i = 0; i < vertex_num; i++)
        cout << i << "\t" << now[i].from << "\t" << now[i].cost << endl;
}
void creat_2dem_array()
{
    array = new struct graph *[vertex_num];
    for (int i = 0; i < vertex_num; i++)
        array[i] = new struct graph[vertex_num];

    for (int i = 0; i < vertex_num; i++)
        for (int j = 0; j < vertex_num; j++)
        {
            array[i][j].capacity = 2;
            array[i][j].load = 0;
        }
}