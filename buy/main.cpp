#include <iostream>
#include <set>
#include <climits>

using namespace std;

#define MAX_VALUE 1001

static int parents[MAX_VALUE];

// Search for minimal cost for a given subnetwork, knowing the initial
// cost of this subnetwork, and sorted edges between all nodes.
int kruskal(set<pair<int, pair<int, int>>> edges, int cost, int n) {
  int n1, n2, big_parent, small_parent;
  for (pair<int, pair<int, int>> item: edges) {
    n1 = item.second.first;
    n2 = item.second.second;
    if (parents[n1] != parents[n2]) {
      if (parents[n1] > parents[n2]) {
        small_parent = parents[n2];
        big_parent = parents[n1];
      }
      else {
        small_parent = parents[n1];
        big_parent = parents[n2];
      }
      for (int i = 1; i <= n; i++)
        if (parents[i] == big_parent)
          parents[i] = small_parent;
      cost += item.first;
    }
  }
  return cost;
}

void buy_build() {
  int n, q, cities_nb, cost, city;
  cin >> n >> q;
  set<int> subnetworks[8];
  int subnetworks_cost[8];
  // Get subnetworks
  for (int i = 0; i < q; i++) {
    cin >> cities_nb >> cost;
    subnetworks_cost[i] = cost;
    for (int j = 0; j < cities_nb; j++) {
      cin >> city;
      subnetworks[i].insert(city);
    }
  }
  int distance;
  int x[MAX_VALUE];
  int y[MAX_VALUE];
  set<pair<int, pair<int, int>>> edges;
  // Fill coordinates and dist in sorted set edges
  for (int i = 1; i <= n; i++) {
    cin >> x[i] >> y[i];
    for (int j = 1; j < i; j++) {
      distance = x[i]*x[i] + x[j]*x[j] - 2*x[i]*x[j] + y[i]*y[i] +y[j]*y[j] - 2*y[i]*y[j];
      edges.insert(make_pair(distance, make_pair(i, j)));
    }
  }

  // launch Kruskal with no subnetwork to initialize minimum_cost.
  for (int i = 1; i <= n; i++)
    parents[i] = i;
  int minimum_cost = kruskal(edges, 0, n);
  int initial_cost;
  int parent;
  // Launch Kruskal for each case and compute the minimum_cost.
  for (int i = 1; i < (1 << q); i++) {
    initial_cost = 0;
    for (int i = 1; i <= n; i++)
      parents[i] = i;
    for (int j = 0; j < q; j++) {
      if ((1 << j) & i) {
        initial_cost += subnetworks_cost[j];
        parent = parents[*subnetworks[j].begin()];
        for (int node: subnetworks[j]) {
          // Add parent for subnetwork and if there is an intersection,
          // fill parents correctly.
          if (parents[node] == node && node > parent)
            parents[node] = parent;
          else if (parents[node] < parent) {
            for (int i = 1; i <= n; i++)
              if (parents[i] == parent)
                parents[i] = parents[node];
          }
          else if (parents[node] > parent) {
            for (int i = 1; i <= n; i++)
              if (parents[i] == parents[node])
                parents[i] = parent;
          }
        }
      }
    }
    cost = kruskal(edges, initial_cost, n);
    if (minimum_cost > cost) {
      minimum_cost = cost;
    }
  }
  cout << minimum_cost << endl;
}

int main() {
  int cases_nb;
  cin >> cases_nb;
  while (cases_nb--) {
    buy_build();
    if (cases_nb)
      cout << endl;
  }
  return 0;
}
