#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MAX_VALUE   100000

int network(int c1, int c2, vector<int> * camarades) {
  queue<pair<int, int>> bfs;
  pair<int, int> examine;
  int x_distance;
  int depth;
  bfs.push(make_pair(c1, 0));
  while (!bfs.empty()) {
    examine = bfs.front();
    bfs.pop();
    depth = examine.second + 1;
    for (int camarade: camarades[examine.first]) {
      if(camarade != c2)
        bfs.push(make_pair(camarade , depth));
      else {
        x_distance = examine.second;
        return x_distance;
      }
    }
  }
  return -1;
}

int main() {
  int cases_nb, N, c, nc, c0, c1, c2;
  vector<int> camarades[MAX_VALUE];
  cin >> cases_nb;

  while (cases_nb--) {
    cin >> N;
    while (N--) {
      cin >> c >> nc;
      camarades[c].clear();
      while (nc--) {
        cin >> c0;
        camarades[c].push_back(c0);
      }
    }
    cin >> c1 >> c2;
    cout << c1 << " " << c2 << " " << network(c1, c2, camarades) << endl;
    if (cases_nb != 0)
      cout << endl;
  }
  return 0;
}
