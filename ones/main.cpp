#include <iostream>

using namespace std;

#define MAX_VALUE 400

static bool table[MAX_VALUE][MAX_VALUE];
static int indices[MAX_VALUE];
static int n, m;

static bool recursive(int current_col) {
  if (current_col == m)
    return true;

  for (int col = current_col; col < m; col++) {
    for (int line = 0; line < n; line++) {
      if (!table[line][col] && table[line][current_col-1])
        for (int c = current_col; c < m; c++) {
          if (table[line][c])
            goto bad;
        }
    }
    for (int l = 0; l < n; l++)
      swap(table[l][col], table[l][current_col]);
    swap(indices[col], indices[current_col]);
    if(recursive(current_col+1))
      return true;

    for (int l = 0; l < n; l++)
      swap(table[l][col], table[l][current_col]);
    swap(indices[col], indices[current_col]);
bad: {}
  }
  return false;
}

static void ones() {
  cin >> n >> m;
  for (int j = 0; j < m; j++)
    indices[j] = j;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < m; j++) {
      table[i][j] = s[j] == '1';
    }
  }
  recursive(1);
  for (int j = 0; j < m; j++)
    cout << indices[j] << endl;
}

int main() {
  int cases_nb;
  cin >> cases_nb;
  while (cases_nb--){
    ones();
    if (cases_nb)
      cout << endl;
  }
  return 0;
}
