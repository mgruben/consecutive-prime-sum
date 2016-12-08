#include <iostream>
#include <vector>

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
    
}
