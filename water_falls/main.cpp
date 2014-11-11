#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  int testcases, test;
  int NP, NS, i;
  int x, y, y0, w, h;
  float m;
  // pair<pair<x1, y1>, pair<x2, y2>>
  vector<pair<pair<int, int>, pair<int, int>>> roofs;
  vector<pair<int, int>> sources;
  int x1, x2, y1, y2;
  int c;

  cin >> testcases;
  for (test = 0; test < testcases; test++) {
    roofs.clear();
    sources.clear();

    // Get entries with x1 < x2;
    cin >> NP;
    for (i = 0; i < NP; i++) {
      cin >> x1 >> y1 >> x2 >> y2;
      if (x1 > x2) {
        x = x1;
        y = y1;
        x1 = x2;
        y1 = y2;
        x2 = x;
        y2 = y;
      }
      roofs.push_back(make_pair(make_pair(x1, y1), make_pair(x2, y2)));
    }
    cin >> NS;
    for (i = 0; i < NS; i++) {
      cin >> x1 >> y1;
      sources.push_back(make_pair(x1, y1));
    }

    c = 0;
    // Get solution for each drop.
    for (pair<int, int> s: sources) {
      // (x, y) coordinates of the drop
      // m <-> y of the drop on the given roof.
      x = s.first;
      y = s.second;
      while (y != 0) {
        y0 = 0;
        w = 0;
        h = 0;
        // Find closest roof by finding all roofs under the drop, and find the biggest y
        for (pair<pair<int, int>, pair<int, int>> r: roofs) {
          x1 = r.first.first;
          x2 = r.second.first;
          y1 = r.first.second;
          y2 = r.second.second;
          if (x1 < x && x2 > x) {
            // m = a * x + b
            m = (y2 - y1) / ((float)(x2 - x1)) * x + ((y1 * x2) - (y2 * x1)) / ((float)(x2 - x1));
            if (m > y0 && m < y) {
              // Find a roof that is under the drop (and above another roof)
              y0 = m;
              if (y1 > y2) {
                h = y2;
                w = x2;
              }
              else {
                h = y1;
                w = x1;
              }
            }
          }
        }
        if (y0 == 0) {
          // No roof found => exit !
          y = 0;
        }
        else {
          // Root found, calculate new position of drop
          x = w;
          y = h;
        }
      }
      cout << x <<endl;
      if (c++ != NS - 1 || test != testcases - 1)
        cout << endl;
    }

  }
  return 0;
}
