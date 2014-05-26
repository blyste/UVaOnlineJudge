#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static void water_level(void) {
  vector<pair<float, float>> citerns;
  float min_level, height, width, depth;
  float volume_left, level, surface, sub_level;
  int citerns_nb;
  cin >> citerns_nb;
  while (citerns_nb--) {
    cin >> min_level >> height >> width >> depth;
    citerns.push_back(make_pair(min_level, width*depth));
    citerns.push_back(make_pair(min_level+height, -width*depth));
  }
  cin >> volume_left;
  sort(citerns.begin(), citerns.end());
  level = 0;
  surface = 0;
  for (pair<float, float> item: citerns) {
    if (surface == 0) {
      level = item.first;
      surface += item.second;
      continue;
    }
    sub_level = volume_left / surface;
    if (sub_level <= (item.first - level)) {
      printf("%.2f\n", level + sub_level);
      return;
    }
    else {
      volume_left -= surface * (item.first - level);
      level = item.first;
      surface += item.second;
    }
  }
  cout << "OVERFLOW" << endl;
  return;
}

int main() {
  int cases_nb;
  cin >> cases_nb;
  while (cases_nb--) {
    water_level();
    if (cases_nb)
      cout << endl;
  }
  return 0;
}
