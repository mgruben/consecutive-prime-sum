#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

// https://en.wikipedia.org/wiki/Primality_test#Pseudocode
bool isPrime(int n) { 
    if (n <= 1) return false;
    if (n <= 3) return true;
    if ((n % 2 == 0) || (n % 3 == 0)) return false;
    int i = 5;
    while (i * i <= n) {
        if ((n % i == 0) || (n % (i + 2) == 0)) return false;
        i += 6;
    }
    return true;
}

/**
 * Return all prime numbers not greater than some integer n.
 * 
 * https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes#Pseudocode
 */
vector<int> sieve(int n) {
    vector<int> v;
    if (n < 2) return v;
    
    bool p[n];
    p[0] = p[1] = false;
    for (int i = 2; i < n; i++) p[i] = true;
    
    for (int i = 2; i * i < n; i++) {
        if (p[i]) {
            v.push_back(i);
            for (int j = i * i; j < n; j += i) {
                p[j] = false;
            }
        }
    }
    
    for (int i = (int) sqrt(n) + 1; i < n; i++) if (p[i]) v.push_back(i);
    return v;
}

/**
 * Returns the longest sum of consecutive primes below n
 */
int solve(int n) {
    vector<int> v = sieve(n);
    
    cout << "Primes: ";
    for (int i: v) cout << i << " ";
    cout << endl;
    cout << "There are " << v.size() << " primes" << endl;
    int sum = 0;
    int diff = 0;
    while (sum < n) sum += v[diff++];
    diff--; 
    int last = sum;
    cout << "Starting sum is " << sum << endl << endl;
    
    while ((sum > n || !isPrime(sum)) && diff > 0) {
        cout << endl << "Diff is now " << diff << endl;
        sum = last;
        cout << "Back to last sum: " << sum << endl;
        sum -= v[diff];
        cout << "Removing " << v[diff] << " from sum" << endl;
        cout << "sum is " << sum << endl;
        last = sum;
        if (isPrime(sum) && sum < n) return sum;
        for (int i = 0; sum < n; i++) {
            sum += v[i + diff];
            cout << "Adding " << v[diff] << " to sum" << endl;
            cout << "sum is " << sum << endl;
            if (isPrime(sum) && sum < n) return sum;
            sum -= v[i];
            cout << "Removing " << v[i] << " from sum" << endl;
            cout << "sum is " << sum << endl;
            if (isPrime(sum) && sum < n) return sum;
        }
        diff--;
    }
    if (isPrime(sum) && sum < n) return sum;
    return -1;
}

int main() {
    cout << solve(1000000) << endl;
    return 0;
}
