#include <iostream>
#include <vector>

using namespace std;

int main() {
    int max_value = 1000001;
    // List of primes number under max_value
    vector<int> primes;
    // Table to know whether a number (under max_value) is prime or not
    bool is_prime[max_value];
    // Fill list and table
    is_prime[0] = is_prime[1] = false;
    primes.push_back(2);
    for (int i = 2; i < max_value; i++)
        is_prime[i] = (i%2 == 1);
    for (int i = 3; i < max_value; i+=2) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = 2*i; j < max_value; j += i)
                is_prime[j] = false;
        }
    }

    int n;
    cin >> n;

    int a, b;
    while (n) {
        for (unsigned int i = 0; i < primes.size(); i++) {
            a = primes[i];
            b = n - a;
            if (is_prime[b])
                break;
        }
        cout << n << " = " << a << " + " << b << endl;
        cin >> n;
    }
    return 0;
}
