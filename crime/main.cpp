#include <iostream>
#include <set>
#include <queue>

using namespace std;

#define N_MAX   1000

void PPPS(int n, int m) {
  int parent[N_MAX] = {0};
  int neighbour[N_MAX] = {0};
  int count[N_MAX] = {0};
  int a, b;
  while(m--) {
    scanf("%d %d", &a, &b);
    // If a is unmarked
    if (parent[a] == 0 && parent[b] == 0) {
      // Fill tables for a
      parent[a] = a;
      neighbour[a] = b;
      count[a] = 1;
      // Fill tables for b
      parent[b] = b;
      neighbour[b] = a;
      count[b] = 1;
    }
    else if (parent[a] != 0 && parent[b] == 0) {
      // Fill tables for b
      parent[b] = neighbour[a];
      neighbour[b] = parent[a];
      count[parent[b]] += 1;
    }
    else if (parent[b] != 0 && parent[a] == 0) {
      // Fill tables for a
      parent[a] = neighbour[b];
      neighbour[a] = parent[b];
      count[parent[a]] += 1;
    }
    // Tables are already filled for a and b.
    // If neighbour a == b, nothing to do.
    // Else, check if there is a conflict or if it is an "union" of two graphs.
    else if (neighbour[a] != parent[b]) {
      if (parent[a] == parent[b]) {
        cout << "Impossible" << endl;
        return;
      }
      else {
        // If it is an union, we have to scan the tables to search
        // for one of the graph (containing b) to rewrite its fields
        // with a's graph fields (parent, neighbour, count).
        for (int i = 1; i <= n; i++) {
          if (parent[i] == parent[b]) {
            parent[i] = neighbour[a];
            neighbour[i] = parent[a];
          }
          else if (parent[i] == neighbour[b]) {
            parent[i] = parent[a];
            neighbour[i] = neighbour[a];
          }
        }
      }
    }
  }
  // If we arrive here, there is a partition.
  // We only have to find which one include less edges.
  int cmin = 0;
  int c0, c1;
  queue<int> to_examine;
  set<int> examine;
  to_examine.push(parent[1]);
  examine.insert(parent[1]);
  examine.insert(neighbour[1]);
  while (!to_examine.empty()) {
    c0 = 0;
    c1 = 0;
    a = to_examine.front();
    to_examine.pop();
    for (int i = 1; i <= n; i++) {
      if (a == parent[i])
        c0 += count[i];
      else if (a == neighbour[i])
        c1 += count[i];
      else if (examine.find(parent[i]) == examine.end()) {
        examine.insert(parent[i]);
        examine.insert(neighbour[i]);
        to_examine.push(parent[i]);
      }
    }
    if (c0 < c1)
      cmin += c0;
    else
      cmin += c1;
  }
  cout << cmin << endl;
  return;
}

int main() {
  int n, m;
  while (scanf("%d %d", &n, &m) != EOF) {
    PPPS(n, m);
  }
  return 0;
}
