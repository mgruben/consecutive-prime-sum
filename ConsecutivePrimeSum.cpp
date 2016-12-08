#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

// https://en.wikipedia.org/wiki/Primality_test#Pseudocode
bool isPrime(long long n) { 
    if (n <= 1) return false;
    if (n <= 3) return true;
    if ((n % 2 == 0) || (n % 3 == 0)) return false;
    long long i = 5;
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
vector<long long> sieve(long long n) {
    vector<long long> v;
    if (n < 2) return v;
    n = (long long) sqrt(n) * 10; // empirical upper bound
    bool p[n];
    p[0] = p[1] = false;
    for (long long i = 2; i < n; i++) p[i] = true;
    
    for (long long i = 2; i * i < n; i++) {
        if (p[i]) {
            v.push_back(i);
            for (long long j = i * i; j < n; j += i) {
                p[j] = false;
            }
        }
    }
    
    for (long long i = (long long) sqrt(n) + 1; i < n; i++) if (p[i]) v.push_back(i);
    return v;
}

/**
 * Returns the longest sum of consecutive primes below n
 */
long long solve(long long n) {
    // Get all primes under n
    vector<long long> v = sieve(n);
    
    /**
     * Sum the first primes until our sum exceeds n-1, and keep
     * track of the number of primes summed in `diff`.
     * 
     * Then backtrack one step because sum > n can't be a solution
     */
    long long sum = 0;
    long long diff = -1;
    while (sum < n) sum += v[++diff];
    sum -= v[diff--];
    
    cout << "Sieve returned " << v.size() << " primes" << endl;
    cout << "Diff is " << diff << endl;
    
    // Initialize a state variable so we can more easily start the
    // next iteration after decreasing sequence length
    long long last = sum;
    
    while ((sum > n || !isPrime(sum)) && diff > 0) {
        
        // Revert to previous starting position, and subtract last prime
        sum = last;
        sum -= v[diff];
        
        // Store this starting position for
        // the next-lower sequence length
        last = sum;
        
        // Check for primality
        if (isPrime(sum) && sum < n) return sum;
        
        /**
         * "Slide" our sequence of primes over our array of primes,
         * adding those that our slider catches up to and
         * subtracting those that our slider passes over
         */
        for (long long i = 0; sum < n; i++) {
            sum += v[i + diff];
            sum -= v[i];
            if (isPrime(sum) && sum < n) return sum;
        }
        diff--;
    }
    if (isPrime(sum) && sum < n) return sum;
    return -1;
}

int main() {
    cout << solve(100000000000) << endl;
    return 0;
}
