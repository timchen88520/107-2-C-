#include <bits/stdc++.h>
#include <random>
#include <vector>
#define MAX 10000;
using namespace std;

class Request {
 private:
  static int total_linked;
  int id;
  bool linked;
  int output;
  double accept;

 public:
  Request() {
    linked = 0;
    output = -1;
  }
  Setid(int node, double x) {
    id = node;
    accept = x;
  }
  Getid(int i) { output = i; }
  friend void linker(Request &);
  friend void match(Request &, int);
  friend int islink(Request &);
  friend int return_id(Request &);
  friend double check_weight(Request &);
  friend void totallink(Request &);
  friend void printlist(Request &);
  friend void printmatch(Request &);
};

int Request::total_linked = 0;

void linker(Request &b) {
  b.linked = 1;
  return;
}

int islink(Request &b) { return b.linked; }

int return_id(Request &b) { return b.id; }

double check_weight(Request &b) { return b.accept; }

void totallink(Request &b) { b.total_linked++;}

void printlist(Request &b) { cout << b.total_linked << endl; }

void printmatch(Request &b) { cout << b.id << "       " << b.output << endl; }

class Resource {
 private:
  int id;
  bool linked;
  int input;

 public:
  Resource() {
    linked = 0;
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
  int arr[3][10000] = {0};
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
      arr[0][lineid] = lineid;
      arr[1][lineid] = linein;
      arr[2][lineid] = lineout;
    }
    // input finished

    vector<Resource>::iterator check_out;
    vector<Request>::iterator check_in;
    for (check_out = output.begin(); check_out != output.end(); ++check_out) {
      int ii, kk, n = 0, maxin;
      int save[10000] = {0};
      double Max = 0.0;
      check_in = input.begin();

      for (kk = 0; kk <= lineid; kk++) {
        if (arr[2][kk] == output_id(*check_out)) {
          save[n] = arr[1][kk];
          n++;
        }
      }
      if (n > 0) {
        for (ii = 0; ii < n; ii++) {
          while (save[ii] > return_id(*check_in)) ++check_in;

          if (cmp(Max, check_weight(*check_in))) {
            Max = check_weight(*check_in);
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
      cout<<"id"<<return_id(*view)<<" = "<<check_weight(*view)<<endl;*/

  //   freopen("hw2_ans.txt","w",stdout);
  //   freopen("1ans.txt","w",stdout);
  //   freopen("2ans.txt","w",stdout);
  freopen("output.txt", "w", stdout);
  vector<Request>::iterator ans;
  printlist(*ans);
  for (ans = input.begin(); ans != input.end(); ++ans)
    if (islink(*ans)) printmatch(*ans);

  return 0;
}

bool Resource::operator->*(Request &b) {
  if (linked == 0 && islink(b) == 0) {
    linker(b);
    linked = 1;
    totallink(b);
    return true;
  } else
    return false;
}
