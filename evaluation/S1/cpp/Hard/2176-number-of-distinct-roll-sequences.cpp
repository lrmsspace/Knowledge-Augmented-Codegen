// Source: https://leetcode.com/problems/number-of-distinct-roll-sequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n. You roll a fair 6-sided dice n times. Determine the total number of distinct sequences of rolls possible such that the following conditions are satisfied:
//
//
// 	The greatest common divisor of any adjacent values in the sequence is equal to 1.
// 	There is at least a gap of 2 rolls between equal valued rolls. More formally, if the value of the ith roll is equal to the value of the jth roll, then abs(i - j) > 2.
//
//
// Return the total number of distinct sequences possible. Since the answer may be very large, return it modulo 109 + 7.
//
// Two sequences are considered distinct if at least one element is different.
//
// Example:
// Input: n = 4
// Output: 184
// Explanation: Some of the possible sequences are (1, 2, 3, 4), (6, 1, 2, 3), (1, 2, 3, 1), etc.
// Some invalid sequences are (1, 2, 1, 3), (1, 2, 3, 6).
// (1, 2, 1, 3) is invalid since the first and third roll have an equal value and abs(1 - 3) = 2 (i and j are 1-indexed).
// (1, 2, 3, 6) is invalid since the greatest common divisor of 3 and 6 = 3.
// There are a total of 184 distinct sequences possible, so we return 184.
//
// Constraints:
// 1 <= n <= 104
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Lattice points inside non-lattice polygon (number, recursion, counting, gcd)
//   • When to use: Use when counting pairs or elements satisfying divisibility or GCD conditions. Also applicable for summing functions over pairs using number theory properties.
//   • Idea: This approach leverages number theoretic properties like GCD, LCM, and prime factorization to efficiently count elements or pairs satisfying specific criteria. It often involves iterating through divisors or multiples, achieving complexities like O(N log N) or O(sqrt N) per query.
//   • Invariants: All numbers processed so far have their relevant number-theoretic properties (e.g., prime factors, divisors) correctly determined.; The current count or sum accurately reflects all valid combinations found up to the current iteration.
//   • Tips: Precompute primes or divisors using a sieve for efficiency.; Utilize properties of GCD and LCM, such as gcd(a,b) * lcm(a,b) = a * b.
//   • Pitfalls: Overcounting or undercounting when using inclusion-exclusion.; Integer overflow with large products or sums.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int distinctSequences(int n) {
        const int MOD = 1e9 + 7;
        // Adjacency list based on GCD=1 condition for dice faces 1-6
        const int adj[6][4] = {
            {1, 2, 4, 5},    // From 1: can go to 2,3,5,6 (0-based: 1,2,4,5)
            {0, 2, 3, 5},    // From 2: can go to 1,3,4,6
            {0, 1, 3, 4},    // From 3: can go to 1,2,4,5
            {1, 2, 4},       // From 4: can go to 2,3,5
            {0, 2, 3, 5},    // From 5: can go to 1,3,4,6
            {0, 1, 3}        // From 6: can go to 1,2,4
        };

        // dp[i][j]: number of sequences of length i ending with face j+1
        long long dp[n + 1][6];
        for (int j = 0; j < 6; ++j) {
            dp[1][j] = 1; // Base case: length 1 sequences
        }

        for (int i = 2; i <= n; ++i) {
            for (int j = 0; j < 6; ++j) {
                dp[i][j] = 0;
                for (int k = 0; k < (j == 3 ? 3 : 4); ++k) { // Adjust size for face '4'
                    int nextFace = adj[j][k];
                    dp[i][j] = (dp[i][j] + dp[i - 1][nextFace]) % MOD;
                }
            }
        }

        long long result = 0;
        for (int j = 0; j < 6; ++j) {
            result = (result + dp[n][j]) % MOD;
        }

        return (int)result;         
    }
};
