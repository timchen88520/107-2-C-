#include <bits/stdc++.h>
#include <stdio.h>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

class Request {
  int id;
  bool matched;
  int resourceID;
  double weight;
  static int total_linked;

 public:
  friend class Resource;

  Resource() {
    matched = false;
    resourceID = -1;
  }  // format to origin
  Set_ID_weight(int current_id, double current_weight) {
    id = current_id;
    weight = current_weight;
  }
  insert_resourceID(int i) { resourceID = i; }
  friend double check_weight(Request &);
  friend int return_id(Request &);
  friend double return_weight(Request &);
  friend bool check_linked(Request &);
  friend void connect(Request &, int);
  friend void print_save(Request &);
  friend void print_matched(Request &);
  friend void linker(Request &);
  friend void totallink(Request &);
};
double check_weight(Request &tmp) { return tmp.weight; }
int return_id(Request &tmp) { return tmp.id; }
double return_weight(Request &tmp) { return tmp.weight; }
void connect(Request &tmp, int tmp_id) { tmp.resourceID = tmp_id; }
void print_save(Request &tmp) { cout << tmp.total_linked << endl; }
void print_matched(Request &tmp) {
  cout << tmp.id << "\t" << tmp.resourceID << endl;
}
bool check_linked(Request &tmp) { return tmp.matched; }
void linker(Request &tmp){
  tmp.matched=1;
  return;
}
void totallink(Request &tmp){
  tmp.total_linked++;
}

int Request::total_linked = 0;

class Resource {
  int id;
  bool matched;
  int requesID;

 public:
  Resource() {
    matched = 0;
    requesID = -1;
  }
  bool operator->*(Request &);
  Set_id(int currentid) { id = currentid; }
  Get_id(int i) { requesID = i; }
  friend int output_id(Resource &);
};
int output_id(Resource &tmp) { return tmp.id; }
bool comp(double Max, double i) {
  if (Max < i)
    return true;
  else
    return false;
}
int main() {
  int tot_timeslot, tot_request = 0, tot_resource = 0, tot_input_point = 0,
                    tot_outout_point = 0;
  vector<Request> input;
  vector<Resource> output;
  int array[3][10000] = {0};
  Request *tmp_request;
  Resource *tmp_resource;

  std::random_device rd;  // creat random number
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dis(0.0, 1.0);
  auto randomx = std::bind(dis, gen);

  freopen("input.txt", "r", stdin);
  cin >> tot_timeslot;
  while (tot_timeslot > 0) {
    int point_id, input_num, output_num, tmp_i;
    cin >> point_id >> input_num >> output_num;
    for (tmp_i = tot_input_point; tmp_i < tot_input_point + input_num;
         tmp_i++) {  // insert every data to vector
      int tmp;
      cin >> tmp;
      tmp_request = new Request;
      tmp_request->Set_ID_weight(tmp, randomx());
      input.push_back(*tmp_request);
    }
    tot_input_point = tmp_i;
    for (tmp_i = tot_outout_point; tmp_i < tot_outout_point + output_num;
         tmp_i++) {  // insert out point to vector
      int tmp;
      cin >> tmp;
      tmp_resource = new Resource;
      tmp_resource->Set_id(tmp);
      output.push_back(*tmp_resource);
    }
    tot_outout_point = tmp_i;

    int link_num, last_link;
    cin >> link_num;
    while (link_num > 0) {  // insert link to a array 0=id 1=request 2=resource
      int link_id, link_request, link_resource;
      cin >> link_id >> link_request >> link_resource;
      array[0][link_id] = link_id;
      array[1][link_id] = link_request;
      array[2][link_id] = link_resource;
      last_link = link_id;

      link_num--;
    }
    // end of one time insert

    vector<Request>::iterator check_in;
    vector<Resource>::iterator check_out;

    for (check_out = output.begin(); check_out != output.end(); ++check_out) {
      int i, k, n = 0, maxin;
      int save[10000] = {0};
      double Max = 0.0;
      for (i = 0; i <= last_link; i++) {
        if (array[2][i] == output_id(*check_out)) {
          check_in = input.begin();
          while (array[1][i] != return_id(*check_in)){
             ++check_in;
          }
          //cout<<check_linked(*check_in)<<endl;
          if (check_linked(*check_in) != 1) {
            save[n] = array[1][i];
            n++;
          }
        }
      }
      check_in = input.begin();
      if (n > 0) {
        for (i = 0; i < n; i++) {
          while (save[i] > return_id(*check_in)) ++check_in;
          double tmp_weight = return_weight(*check_in);
          if (comp(Max, check_weight(*check_in))) {  // find out largest weight
            Max = check_weight(*check_in);
            maxin = return_id(*check_in);
          }
          check_in = input.begin();
        }
        while (maxin > return_id(*check_in)) ++check_in;
        if ((*check_out)->*(*check_in)) {
          connect(*check_in, output_id(*check_out));
        }
      }
    }
    tot_timeslot--;
  }
  // all input done
  freopen("output.txt", "w", stdout);
  vector<Request>::iterator answer;
  print_save(*answer);
  for (answer = input.begin(); answer != input.end(); answer++) {
    //cout<<"check  "<<check_linked(*answer)<<endl;
    int tmp=check_linked(*answer);
    ///cout<<"check2 "<<tmp<<endl;
    if (tmp == 1 ) print_matched(*answer);
  }
}

bool Resource::operator->*(Request &tmp) {
  if (matched == 0 && tmp.matched == 0) {
    linker(tmp);
    matched = 1;
    //tmp.total_linked++;
    totallink(tmp);
    return true;
  } else
    return false;
}
