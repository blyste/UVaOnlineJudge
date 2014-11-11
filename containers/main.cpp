#include <iostream>
#include <string>

using namespace std;

int solution(string containers) {
  int i, j;
  char stack[26];
  int stack_nb = 1;
  stack[0] = containers[0];
  for (i = 1; i < containers.length(); i++) {
    for (j = 0; j < stack_nb && containers[i] > stack[j]; j++);
    if (j == stack_nb) {
      stack[stack_nb] = containers[i];
      stack_nb++;
    }
    else {
      stack[j] = containers[i];
    }
  }
  return stack_nb;
}

int main() {
  string containers;
  int i = 1;
  cin >> containers;
  while (containers != "end") {
    cout << "Case " << i++ << ": " << solution(containers) << endl;
    cin >> containers;
  }
  return 0;
}
