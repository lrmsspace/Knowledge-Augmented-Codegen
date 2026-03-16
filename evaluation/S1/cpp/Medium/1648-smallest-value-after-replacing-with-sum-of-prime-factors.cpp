// Source: https://leetcode.com/problems/smallest-value-after-replacing-with-sum-of-prime-factors/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer n.
//
// Continuously replace n with the sum of its prime factors.
//
//
// 	Note that if a prime factor divides n multiple times, it should be included in the sum as many times as it divides n.
//
//
// Return the smallest value n will take on.
//
// Example:
// Input: n = 15
// Output: 5
// Explanation: Initially, n = 15.
// 15 = 3 * 5, so replace n with 3 + 5 = 8.
// 8 = 2 * 2 * 2, so replace n with 2 + 2 + 2 = 6.
// 6 = 2 * 3, so replace n with 2 + 3 = 5.
// 5 is the smallest value n will take on.
//
// Constraints:
// 2 <= n <= 105
//
// Helpful references (internal KB):
// - Linear Sieve (array, sieve)
//   • When to use: Use when you need to find the smallest prime factor or full prime factorization for all numbers up to a given limit N in linear time. It's particularly useful for tasks requiring precomputed factorizations.
//   • Idea: The Linear Sieve computes the smallest prime factor for every number up to N, ensuring each composite number is marked exactly once by its smallest prime factor. It achieves this in O(N) time complexity.
//   • Invariants: Every number `i` from 2 to N has its `lp[i]` correctly set to its smallest prime factor.; The `primes` array contains all prime numbers less than or equal to the current iteration `i`.
//   • Tips: Stores the smallest prime factor (lp) for each number.; Efficiently generates all prime numbers up to N.
//   • Pitfalls: Higher memory usage compared to the classic Sieve of Eratosthenes due to storing lp array.; Can be slower in practice than optimized Sieve of Eratosthenes for merely generating primes.
// - Minimum stack / Minimum queue (stack, simulation)
//   • When to use: When you need to perform standard stack operations (push, pop) and also query the minimum element currently in the stack, all in constant time.
//   • Idea: Augments a standard stack by storing each element along with the minimum value encountered up to that point in the stack. This allows O(1) retrieval of the current minimum, while push and pop operations also remain O(1).
//   • Invariants: The top element's second component (minimum_so_far) always represents the minimum value currently in the entire stack.; For any element (value, min_so_far) in the stack, min_so_far is the minimum of 'value' and all elements below it.
//   • Tips: Store elements as pairs: (actual_value, minimum_at_this_level).; When pushing, the new minimum_at_this_level is min(new_value, stack.top().second) if stack is not empty, else new_value.
//   • Pitfalls: Forgetting to handle the empty stack case when calculating the minimum for a new element.; Incorrectly assuming the minimum can be tracked with a single auxiliary variable without considering pops.
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this when you need to efficiently calculate the total count or sum of all positive divisors for a given integer. It is applicable in number theory problems or combinatorial tasks involving factors.
//   • Idea: This method computes the number of divisors and sum of divisors of an integer n by first finding its prime factorization. The core idea leverages properties of multiplicative functions, with a typical complexity of O(sqrt(n)) for factorization.
//   • Invariants: During prime factorization, temp_n always holds the remaining unfactored part of the original number.; The current_prime_factor iterates through potential prime divisors in increasing order.
//   • Tips: First find the prime factorization n = p1^a1 * p2^a2 * ... * pk^ak.; Number of divisors d(n) = (a1+1)(a2+1)...(ak+1).
//   • Pitfalls: Forgetting to handle the special case of n=1 (1 divisor, sum 1).; Incorrectly calculating powers or sums, especially for large exponents.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int smallestValue(int n) {
        // Linear Sieve to compute smallest prime factors up to n
        const int MAX_N = 100000;
        int lp[MAX_N + 1] = {0}; // lp[i] = least prime factor of i
        int primes[MAX_N / 10]; // enough space for primes
        int prime_count = 0;

        for (int i = 2; i <= MAX_N; ++i) {
            if (lp[i] == 0) {
                lp[i] = i;
                primes[prime_count++] = i;
            }
            for (int j = 0; j < prime_count && primes[j] <= lp[i] && i * primes[j] <= MAX_N; ++j) {
                lp[i * primes[j]] = primes[j];
            }
        }

        auto sum_of_prime_factors = [&](int x) -> int {
            int sum = 0;
            while (x > 1) {
                sum += lp[x];
                x /= lp[x];
            }
            return sum;
        };

        int current = n;
        while (true) {
            int next_value = sum_of_prime_factors(current);
            if (next_value == current) {
                break;
            }
            current = next_value;
        }

        return current;         
    }
};
