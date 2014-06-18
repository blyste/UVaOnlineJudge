#include <iostream>
#include <math.h>

#define MAX_BALLOONS 6

struct point {
  int x, y, z;
  double radius;
} point0, point1, points[MAX_BALLOONS];
bool visited[MAX_BALLOONS];
int count;
double max_volume, volume, box_volume;

double min(double a, double b) {
  if (a < b)
    return a;
  else
    return b;
}

void compare(int i, int j) {
  int k;
  if (j < i) {
    k = i;
    i = j;
    j = k;
  }
}

double distance(point i, point j) {
  return sqrt((double)(i.x - j.x)*(i.x - j.x) + (i.y - j.y)*(i.y - j.y) + (i.z - j.z)*(i.z - j.z));
}

void recursive(int m, double volume) {
  if (m == count) {
    if (volume > max_volume)
      max_volume = volume;
  }
  else {
    for (int i = 0; i < count; i++) {
      if (!visited[i]) {
        visited[i] = true;

        // Compare with all limits (box and balloons already in the box)
        // Therefore, find the maximum radius possible.
        double radius = point1.x - points[i].x;
        radius = min(radius, points[i].x - point0.x);
        radius = min(radius, points[i].y - point0.y);
        radius = min(radius, point1.y - points[i].y);
        radius = min(radius, points[i].z - point0.z);
        radius = min(radius, point1.z - points[i].z);
        for (int j = 0; j < count; j++)
          if (visited[j] && i !=j)
            radius = min(radius, distance(points[i], points[j]) - points[j].radius );

        points[i].radius = radius;
        // if point[i] is in another balloon
        if (radius < 0) {
          recursive(m + 1, volume);
        }
        // else the volume increase
        else {
          recursive(m + 1, volume + (4.0/3.0)*M_PI*radius*radius*radius);
        }

        // When we continue, we want to reinitialize the table visited
        visited[i] = false;
      }
    }
  }
}

int main() {
  int cases_nb = 0;
  int x, y, z, n;
  while (true) {
    scanf("%d", &n);
    // End of input
    if (!n)
      return 0;

    cases_nb += 1;
    // Box corners
    scanf("%d %d %d", &point0.x, &point0.y, &point0.z);
    scanf("%d %d %d", &point1.x, &point1.y, &point1.z);
    compare(point0.x, point1.x);
    compare(point0.y, point1.y);
    compare(point0.z, point1.z);
    box_volume = (point1.x - point0.x)*(point1.y - point0.y)*(point1.z - point0.z);

    // Balloons points
    count = 0;
    max_volume = 0;
    for (int i = 0; i < n; i++) {
      scanf("%d %d %d", &x, &y, &z);
      if (x > point0.x && x < point1.x && y > point0.y && y < point1.y && z > point0.z && z < point1.z) {
        points[count].x = x;
        points[count].y = y;
        points[count].z = z;
        points[count].radius = 0;
        visited[count] = false;
        count += 1;
      }
    }

    // Maximize the space occupied by balloons
    recursive(0, 0.0);
    printf("Box %d: %d\n\n", cases_nb, (int)round(box_volume - max_volume));
  }
  return 0;
}
