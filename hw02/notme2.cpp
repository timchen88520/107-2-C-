#include <bits/stdc++.h>
#include <random>
#include <vector>
#define MAX 10000;
using namespace std;

class Request {
 private:
  static int total;
  int id;
  bool matched;
  int output;
  double weight;

 public:
  Request() {
    matched = 0;
    output = -1;
  }
  Setid(int node, double x) {
    id = node;
    weight = x;
  }
  Getid(int i) { output = i; }
  friend void linker(Request &);
  friend void match(Request &, int);
  friend int check_linked(Request &);
  friend int return_id(Request &);
  friend double isaccept(Request &);
  friend void totallink(Request &);
  friend void printlist(Request &);
  friend void printmatch(Request &);
};

int Request::total = 0;

void linker(Request &b) {
  b.matched = 1;
  return;
}

int check_linked(Request &b) { return b.matched; }

int return_id(Request &b) { return b.id; }

double isaccept(Request &b) { return b.weight; }

void totallink(Request &b) { b.total++; }

void printlist(Request &b) { cout << b.total << endl; }

void printmatch(Request &b) { cout << b.id << "       " << b.output << endl; }

class Resource {
 private:
  int id;
  bool matched;
  int input;

 public:
  Resource() {
    matched = 0;
    input = -1;
  }
  Setid(int node) { id = node; }
  Getid(int i) { input = i; }
  bool operator->*(Request &);
  friend int output_id(Resource &);
};

int output_id(Resource &a) { return a.id; }

void match(Request &b, int _id) { b.output = _id; }

bool cmp(double Max, double i) {
  if (Max < i)
    return true;
  else
    return false;
}

int main() {
  vector<Request> input;
  vector<Resource> output;
  int i, j, k, tmp;
  int incounter = 0;
  int outcounter = 0;
  int times;
  int nodein, nodeout, timeid, line, lineid, linein, lineout;
  int array[3][10000] = {0};
  Request *node1;
  Resource *node2;
  // random seed
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dis(0.0, 1.0);
  auto randx = std::bind(dis, gen);
  //   freopen("hw2_que.txt","r",stdin);
  //   freopen("request1.txt","r",stdin);
  //   freopen("request2.txt","r",stdin);
  freopen("input.txt", "r", stdin);
  cin >> times;
  while (times--) {
    cin >> timeid >> nodein >> nodeout;
    for (i = incounter; i < nodein + incounter; i++) {
      cin >> tmp;
      node1 = new Request;
      node1->Setid(tmp, randx());
      input.push_back(*node1);
    }
    incounter = i;

    for (j = outcounter; j < nodeout + outcounter; j++) {
      cin >> tmp;
      node2 = new Resource;
      node2->Setid(tmp);
      output.push_back(*node2);
    }
    outcounter = j;

    cin >> line;
    for (k = 0; k < line; k++) {
      cin >> lineid >> linein >> lineout;
      array[0][lineid] = lineid;
      array[1][lineid] = linein;
      array[2][lineid] = lineout;
    }
    // input finished

    vector<Resource>::iterator check_out;
    vector<Request>::iterator check_in;
    for (check_out = output.begin(); check_out != output.end(); ++check_out) {
      int ii, kk, n = 0, maxin;
      int save[10000] = {0};
      double Max = 0.0;
      check_in = input.begin();
      // cout<<return_id(*check_in)<<endl;
      // cout<<lineid<<endl;
      for (kk = 0; kk <= lineid; kk++) {
        if (array[2][kk] == output_id(*check_out)) {
          check_in = input.begin();
          // cout<<return_id(*check_in)<<endl;
          while (array[1][kk] != return_id(*check_in)) {
            // cout<<array[1][kk]<<"  "<<return_id(*check_in)<<endl;
            ++check_in;
          }
          cout << check_linked(*check_in) << endl;

          if (check_linked(*check_in) == 0) {
            // cout<<array[1][kk]<<endl;
            save[n] = array[1][kk];
            n++;
          }
        }
      }
      check_in = input.begin();
      if (n > 0) {
        for (ii = 0; ii < n; ii++) {
          while (save[ii] > return_id(*check_in)) ++check_in;

          if (cmp(Max, isaccept(*check_in))) {
            Max = isaccept(*check_in);
            maxin = return_id(*check_in);
          }

          check_in = input.begin();
        }

        while (maxin > return_id(*check_in)) ++check_in;

        if ((*check_out)->*(*check_in)) match(*check_in, output_id(*check_out));
      }
    }
  }
  /*        vector<Request>::iterator view;
      for(view = input.begin(); view != input.end(); ++view)
      cout<<"id"<<return_id(*view)<<" = "<<isaccept(*view)<<endl;*/

  //   freopen("hw2_ans.txt","w",stdout);
  //   freopen("1ans.txt","w",stdout);
  //   freopen("2ans.txt","w",stdout);
  freopen("output1.txt", "w", stdout);
  vector<Request>::iterator ans;
  printlist(*ans);
  for (ans = input.begin(); ans != input.end(); ++ans)
    if (check_linked(*ans)) printmatch(*ans);

  return 0;
}

bool Resource::operator->*(Request &b) {
  if (matched == 0 && check_linked(b) == 0) {
    linker(b);
    matched = 1;
    totallink(b);
    return true;
  } else
    return false;
}
