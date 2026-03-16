// Source: https://leetcode.com/problems/tuple-with-same-product/   |   Difficulty: Medium
//
// Problem Description:
// Given an array nums of distinct positive integers, return the number of tuples (a, b, c, d) such that a * b = c * d where a, b, c, and d are elements of nums, and a != b != c != d.
//
// Example:
// Input: nums = [2,3,4,6]
// Output: 8
// Explanation: There are 8 valid tuples:
// (2,6,3,4) , (2,6,4,3) , (6,2,3,4) , (6,2,4,3)
// (3,4,2,6) , (4,3,2,6) , (3,4,6,2) , (4,3,6,2)
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 104
// 	All elements in nums are distinct.
//
// Helpful references (internal KB):
// - Catalan Numbers (number, counting)
//   • When to use: Use when counting arrangements of objects that follow a specific non-crossing or balancing rule, often involving recursive decomposition or paths constrained by a diagonal.
//   • Idea: Catalan numbers count the number of ways to arrange certain combinatorial objects, such as balanced parentheses sequences or monotonic paths that do not cross a diagonal. They can be computed using a recurrence relation (O(N^2) with DP) or a direct binomial coefficient formula (O(N) or O(N log N)).
//   • Invariants: dp[i] stores the i-th Catalan number, correctly computed from dp[0] through dp[i-1].; For each n, the sum sum(dp[k] * dp[n-1-k]) iterates through all valid partitions of the problem.
//   • Tips: Memoize the recursive solution to avoid redundant computations, transforming it into dynamic programming.; For large N, use modular arithmetic if results are required modulo a prime to prevent integer overflow.
//   • Pitfalls: Forgetting to correctly handle the base cases, typically C0 = 1 and C1 = 1.; Encountering integer overflow when calculating large binomial coefficients without appropriate modular arithmetic.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int tupleSameProduct(vector<int>& nums) {
        int n = nums.size();
        int count = 0;
        unordered_map<int, int> productCount;

        // Count the occurrences of each product of pairs
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int product = nums[i] * nums[j];
                productCount[product]++;
            }
        }

        // Calculate the number of tuples for each product
        for (const auto& entry : productCount) {
            int k = entry.second;
            if (k > 1) {
                // For k pairs with the same product, we can form k * (k - 1) tuples
                count += k * (k - 1);
            }
        }

        return count;           
    }
};
