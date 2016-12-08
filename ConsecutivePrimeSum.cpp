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
 * Returns the first N prime numbers in a vector.
 * 
 * For use in easily adding primes to and subtracting primes from
 * the current sum.
 */
vector<int> firstNPrimes(int N) {
    vector<int> v;
    return v;
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

void test() {
    for (int i: sieve(1000)) cout << i << " ";
    cout << endl;
}

int main() {
    test();
    return 0;
}
