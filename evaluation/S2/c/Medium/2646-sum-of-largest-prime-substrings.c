// Source: https://leetcode.com/problems/sum-of-largest-prime-substrings/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, find the sum of the 3 largest unique prime numbers that can be formed using any of its substrings.
//
// Return the sum of the three largest unique prime numbers that can be formed. If fewer than three exist, return the sum of all available primes. If no prime numbers can be formed, return 0.
//
// Note: Each prime number should be counted only once, even if it appears in multiple substrings. Additionally, when converting a substring to an integer, any leading zeros are ignored.
//
// Example:
// Input: s = "12234"
//
// Output: 1469
//
// Explanation:
//
//
// 	The unique prime numbers formed from the substrings of "12234" are 2, 3, 23, 223, and 1223.
// 	The 3 largest primes are 1223, 223, and 23. Their sum is 1469.
//
// Constraints:
// 1 <= s.length <= 10
// 	s consists of only digits.
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - String Hashing (string, number, hashing, prefix-sum)
//   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
//   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
//   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
//   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
//   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this when you need to efficiently calculate the total count or sum of all positive divisors for a given integer. It is applicable in number theory problems or combinatorial tasks involving factors.
//   • Idea: This method computes the number of divisors and sum of divisors of an integer n by first finding its prime factorization. The core idea leverages properties of multiplicative functions, with a typical complexity of O(sqrt(n)) for factorization.
//   • Invariants: During prime factorization, temp_n always holds the remaining unfactored part of the original number.; The current_prime_factor iterates through potential prime divisors in increasing order.
//   • Tips: First find the prime factorization n = p1^a1 * p2^a2 * ... * pk^ak.; Number of divisors d(n) = (a1+1)(a2+1)...(ak+1).
//   • Pitfalls: Forgetting to handle the special case of n=1 (1 divisor, sum 1).; Incorrectly calculating powers or sums, especially for large exponents.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long sumOfLargestPrimes(char* s) {
    // Helper function to check if a number is prime
    int isPrime(int num) {
        if (num < 2) return 0;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) return 0;
        }
        return 1;
    }

    // Use a set to store unique primes
    int primes[100]; // To store unique primes, max possible is less than 100 for substrings of length <= 10
    int primeCount = 0;

    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        for (int j = i; j < len; j++) {
            // Extract substring and convert to integer
            char buffer[11]; // Max length of substring is 10 + null terminator
            strncpy(buffer, s + i, j - i + 1);
            buffer[j - i + 1] = '\0'; // Null-terminate the string

            // Convert to integer, ignoring leading zeros
            int num = atoi(buffer);

            // Check if it's prime and add to the set if it is
            if (isPrime(num)) {
                int exists = 0;
                for (int k = 0; k < primeCount; k++) {
                    if (primes[k] == num) {
                        exists = 1;
                        break;
                    }
                }
                if (!exists && primeCount < 100) {
                    primes[primeCount++] = num;
                }
            }
        }
    }

    // Sort the unique primes in descending order
    for (int i = 0; i < primeCount - 1; i++) {
        for (int j = i + 1; j < primeCount; j++) {
            if (primes[i] < primes[j]) {
                int temp = primes[i];
                primes[i] = primes[j];
                primes[j] = temp;
            }
        }
    }

    // Sum the three largest unique primes
    long long sum = 0;
    for (int i = 0; i < primeCount && i < 3; i++) {
        sum += primes[i];
    }

    return sum;     
}
