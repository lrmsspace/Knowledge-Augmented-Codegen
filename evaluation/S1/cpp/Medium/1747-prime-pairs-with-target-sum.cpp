// Source: https://leetcode.com/problems/prime-pairs-with-target-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n. We say that two integers x and y form a prime number pair if:
//
//
// 	1 <= x <= y <= n
// 	x + y == n
// 	x and y are prime numbers
//
//
// Return the 2D sorted list of prime number pairs [xi, yi]. The list should be sorted in increasing order of xi. If there are no prime number pairs at all, return an empty array.
//
// Note: A prime number is a natural number greater than 1 with only two factors, itself and 1.
//
// Example:
// Input: n = 10
// Output: [[3,7],[5,5]]
// Explanation: In this example, there are two prime pairs that satisfy the criteria. 
// These pairs are [3,7] and [5,5], and we return them in the sorted order as described in the problem statement.
//
// Constraints:
// 1 <= n <= 106
//
// Helpful references (internal KB):
// - Sieve of Eratosthenes (array, bitset, sieve)
//   • When to use: When you need to find all prime numbers up to a certain limit N, or efficiently check primality for many numbers within that range. It is ideal for precomputing primes.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer N by iteratively marking multiples of each prime. It achieves O(N log log N) time complexity and O(N) space.
//   • Invariants: For any number i less than the current prime p, is_prime[i] correctly reflects its primality.; All multiples of primes smaller than the current prime p have already been marked as composite.
//   • Tips: Optimize by starting marking multiples from p*p for each prime p.; Use a bitset for memory efficiency when N is large.
//   • Pitfalls: Forgetting to explicitly handle 0 and 1 as non-prime.; Incorrectly marking multiples, e.g., starting from 2*p instead of p*p.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Linear Sieve (array, sieve)
//   • When to use: Use when you need to find the smallest prime factor or full prime factorization for all numbers up to a given limit N in linear time. It's particularly useful for tasks requiring precomputed factorizations.
//   • Idea: The Linear Sieve computes the smallest prime factor for every number up to N, ensuring each composite number is marked exactly once by its smallest prime factor. It achieves this in O(N) time complexity.
//   • Invariants: Every number `i` from 2 to N has its `lp[i]` correctly set to its smallest prime factor.; The `primes` array contains all prime numbers less than or equal to the current iteration `i`.
//   • Tips: Stores the smallest prime factor (lp) for each number.; Efficiently generates all prime numbers up to N.
//   • Pitfalls: Higher memory usage compared to the classic Sieve of Eratosthenes due to storing lp array.; Can be slower in practice than optimized Sieve of Eratosthenes for merely generating primes.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<vector<int>> findPrimePairs(int n) {
        // Linear Sieve to find all primes up to n
        vector<int> lp(n + 1, 0); // lp[i] = least prime factor of i
        vector<int> primes;
        for (int i = 2; i <= n; ++i) {
            if (lp[i] == 0) {
                lp[i] = i;
                primes.push_back(i);
            }
            for (int p : primes) {
                if (p > lp[i] || i * p > n) break;
                lp[i * p] = p;
            }
        }

        vector<vector<int>> result;
        // Find prime pairs (x, y) such that x + y = n and x <= y
        for (int x : primes) {
            if (x > n / 2) break; // Ensure x <= y
            int y = n - x;
            if (lp[y] == y) { // Check if y is prime
                result.push_back({x, y});
            }
        }

        return result;          
    }
};
