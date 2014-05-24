#include <iostream>
#include <cstring>
#include <climits>

using namespace std;

#define MAZE_WIDTH 100

// Method to count the number of mice that could escape.
// Use Dijkstra algorithm.
int escape(int graph[MAZE_WIDTH][MAZE_WIDTH], int n, int e, int t) {
  // Shortest distance from exit to i.
  int dist[n];
  int non_marked = n;
  bool marked[n];

  // Initialize all distances as infinite and marked[] as false.
  for (int i = 0; i < n; i++) {
    dist[i] = INT_MAX;
    marked[i] = false;
  }
  // Shortest distance from exit to itself = 0
  dist[e] = 0;

  while (non_marked--) {
    // Choose the smallest edge with marked == false
    int imin;
    for (int i = 0; i < n ; i++) {
      if (!marked[i]) {
        imin = i;
        break;
      }
    }
    for (int i = imin + 1; i < n ; i++) {
      if (!marked[i] && dist[i] < dist[imin])
        imin = i;
    }
    marked[imin] = true;
    // Update the value of its neightboors
    for (int i = 0 ; i < n ; i++) {
      if (!marked[i] && graph[imin][i] != -1 && dist[imin] + graph[imin][i] < dist[i])
        dist[i] = dist[imin] + graph[imin][i];
    }
  }

  // Count the number of mice at a distance < t
  int mice = 0;
  for (int i = 0 ; i < n ; i++) {
    if (dist[i] <= t)
      mice++;
  }
  return mice;
}

int main() {
  int nb;
  int n, e, t, connections;
  int a, b, time;

  // Adjacency matrix : graph.
  int graph[MAZE_WIDTH][MAZE_WIDTH];

  cin >> nb;
  // For each test case, find the result.
  for (int i = 0; i < nb; i++) {
    // Reset the adjacency matrix.
    memset(graph, -1, MAZE_WIDTH * MAZE_WIDTH * sizeof(int));
    cin >> n >> e >> t >> connections;
    // Fill the adjacency matrix.
    for (int j = 0; j < connections; j++) {
      cin >> a >> b >> time;
      graph[b-1][a-1] = time;
    }
    // Use dijkstra to find the minimum time for each cell.
    // Return the nomber of mice allowed to escape.
    cout << escape(graph, n, e - 1, t) << endl;
    if (i != nb-1)
      cout << endl;
  }

}
