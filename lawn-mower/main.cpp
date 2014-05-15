#include <algorithm>
#include <iostream>

using namespace std;

bool check_pass(int n, double w, int max) {
    double z[1000];
    for (int i = 0; i < n; i++){
        cin >> z[i];
    }
    sort(z, z+n);
    if (w/2 < z[0] || (w/2 + z[n-1]) < max)
        return false;
    for (int i = 1; i < n; i++)
        if (z[i-1] + w < z[i])
            return false;
    return true;
}

int main() {
    int nx, ny;
    double w;
    cin >> nx >> ny >> w;
    bool x_pass, y_pass;
    while (nx != 0 || ny != 0 || w != 0.0) {
        x_pass = check_pass(nx, w, 75);
        y_pass = check_pass(ny, w, 100);
        if (x_pass && y_pass)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
        cin >> nx >> ny >> w;
    }
    return 0;
}
