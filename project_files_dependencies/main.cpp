#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <iterator>
#include <algorithm>
#include <utility>
#include <stdio.h>
#include <cstring>

using namespace std;

static bool to_delete(pair<int, set<int> > x) {
  return x.second.empty();
}

static void compute(vector<pair<int, set<int> > > &edges) {
  priority_queue<int, vector<int>, greater<int> > output;
  set<int>::iterator it;
  int t;

  while (edges.size() != 0) {
    for (pair<int, set<int>> item: edges)
      if ((item.second).empty())
        output.push(item.first);
    edges.erase(remove_if(edges.begin(), edges.end(), to_delete), edges.end());
    t = output.top();
    output.pop();
    cout << t+1;
    for (pair<int, set<int>> item: edges)
      if ((it = (item.second).find(t)) != (item.second).end())
        (item.second).erase(it);
    if (edges.size() != 0 || output.size() != 0)
      cout << " ";
  }

  while (output.size() != 0) {
    cout << output.top()+1;
    output.pop();
    if (output.size() != 0)
      cout << " ";
  }
  cout << endl;
}

int main() {
  int cases_nb, N, M, k, Ti, tmp_int, i;
  cin >> cases_nb;

  while (cases_nb--) {
    cin >> N >> M;
    vector<pair<int, set<int>>> edges;
    bool ok[N];
    memset(ok, false, N);

    for (i = 0 ; i < M ; i++) {
      set<int> tmp_set;
      cin >> Ti;
      ok[Ti-1] = true;
      cin >> k;
      for (int j = 0 ; j < k ; j++) {
        cin >> tmp_int;
        tmp_set.insert(tmp_int-1);
      }
      edges.push_back(make_pair(Ti-1, tmp_set));
    }
    set<int> empty_set;
    for (i = 0 ; i < N ; i++)
      if (!ok[i])
        edges.push_back(make_pair(i, empty_set));
    compute(edges);
    if (cases_nb)
      cout << endl;
  }
  return 0;
}
