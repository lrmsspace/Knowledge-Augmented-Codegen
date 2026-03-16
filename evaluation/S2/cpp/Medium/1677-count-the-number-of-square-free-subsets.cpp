// Source: https://leetcode.com/problems/count-the-number-of-square-free-subsets/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer 0-indexed array nums.
//
// A subset of the array nums is square-free if the product of its elements is a square-free integer.
//
// A square-free integer is an integer that is divisible by no square number other than 1.
//
// Return the number of square-free non-empty subsets of the array nums. Since the answer may be too large, return it modulo 109 + 7.
//
// A non-empty subset of nums is an array that can be obtained by deleting some (possibly none but not all) elements from nums. Two subsets are different if and only if the chosen indices to delete are different.
//
// Example:
// Input: nums = [3,4,4,5]
// Output: 3
// Explanation: There are 3 square-free subsets in this example:
// - The subset consisting of the 0th element [3]. The product of its elements is 3, which is a square-free integer.
// - The subset consisting of the 3rd element [5]. The product of its elements is 5, which is a square-free integer.
// - The subset consisting of 0th and 3rd elements [3,5]. The product of its elements is 15, which is a square-free integer.
// It can be proven that there are no more than 3 square-free subsets in the given array.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 30
//
// Helpful references (internal KB):
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
// - Euler's totient function
//  (array, number, enumeration)
//   • When to use: Use when needing to count positive integers up to n that are relatively prime to n. It is also efficient for computing totient values for all numbers in a given range.
//   • Idea: Euler's totient function, φ(n), counts positive integers less than or equal to n that are relatively prime to n. It can be computed for a single n in O(sqrt(n)) using prime factorization, or for all numbers up to N in O(N log log N) using a sieve-like algorithm.
//   • Invariants: phi[i] stores the current totient value for i, which is i initially, then updated by (1 - 1/p) for each prime p dividing i.; After iterating through all primes p up to sqrt(N), phi[i] holds the correct totient value for all i <= N.
//   • Tips: For a single n, compute φ(n) using its prime factorization.; For all φ(i) up to N, use a sieve approach similar to Sieve of Eratosthenes.
//   • Pitfalls: Confusing 'relatively prime' with 'prime number'.; Applying the multiplicative property incorrectly when numbers share common factors.
// - Factorial modulo 
// p (number, counting, recursion)
//   • When to use: Use when the problem asks for the total count of possibilities or arrangements that can be naturally broken down into smaller, self-similar subproblems. It's effective for exploring decision trees or state spaces.
//   • Idea: Counting determines the number of elements or event occurrences. It uses combinatorial or iterative/recursive methods, often with O(N) or O(log N) complexity.
//   • Invariants: Each recursive call processes a smaller, well-defined subproblem.; The base cases correctly return the count for the simplest scenarios.
//   • Tips: Identify the smallest subproblem and its base cases to stop recursion.; Define the recursive relation clearly, showing how larger problems depend on smaller ones.
//   • Pitfalls: Incorrectly defining base cases can lead to infinite recursion or incorrect results.; Overlapping subproblems without memoization can lead to exponential time complexity.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

#include <vector>
#include <array>
#include <cstdint>

using namespace std;

class Solution {
public:
    int squareFreeSubsets(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        // primes up to 30 that we care about
        const array<int,10> primes = {2,3,5,7,11,13,17,19,23,29};

        vector<int> cnt(31, 0);
        for (int v : nums) cnt[v]++;

        // dp over prime masks (10 primes)
        const int M = 1<<10;
        vector<int64_t> dp(M, 0);
        dp[0] = 1; // empty selection of non-1 numbers

        int ones = cnt[1];

        // process numbers 2..30
        for (int v = 2; v <= 30; ++v) {
            int c = cnt[v];
            if (c == 0) continue;

            // skip numbers divisible by a square (>1)
            bool bad = false;
            for (int p : primes) {
                if (v % (p*p) == 0) { bad = true; break; }
            }
            if (bad) continue;

            int mask = 0;
            for (int i = 0; i < (int)primes.size(); ++i) {
                if (v % primes[i] == 0) mask |= (1<<i);
            }

            // we can choose at most one element with this prime-mask in any subset
            // but there are `c` distinct indices that have value v, so there are `c` ways
            // to pick one when we choose to include this mask.
            for (int s = M-1; s >= 0; --s) {
                if ((s & mask) == 0) {
                    int ns = s | mask;
                    dp[ns] = (dp[ns] + dp[s] * c) % MOD;
                }
            }
        }

        // sum all dp entries (A), multiply by 2^ones to account for ones, subtract empty
        int64_t A = 0;
        for (int s = 0; s < M; ++s) A = (A + dp[s]) % MOD;

        auto modpow = [&](int64_t a, int64_t e){
            int64_t r = 1;
            while (e) {
                if (e & 1) r = (r * a) % MOD;
                a = (a * a) % MOD;
                e >>= 1;
            }
            return r;
        };

        int64_t pow1 = modpow(2, ones);
        int64_t ans = (A * pow1 - 1) % MOD;
        if (ans < 0) ans += MOD;
        return (int)ans;
    }
};