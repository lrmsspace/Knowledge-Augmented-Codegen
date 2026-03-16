// Source: https://leetcode.com/problems/largest-component-size-by-common-factor/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array of unique positive integers nums. Consider the following graph:
//
//
// 	There are nums.length nodes, labeled nums[0] to nums[nums.length - 1],
// 	There is an undirected edge between nums[i] and nums[j] if nums[i] and nums[j] share a common factor greater than 1.
//
//
// Return the size of the largest connected component in the graph.
//
// Example:
// Input: nums = [4,6,15,35]
// Output: 4
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	1 <= nums[i] <= 105
// 	All the values of nums are unique.
//
// Helpful references (internal KB):
// - Sieve of Eratosthenes (array, sieve, enumeration)
//   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
//   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
//   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
//   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
// - Finding Bridges Online (graph, tree, union-find, counting)
//   • When to use: Use when you need to dynamically track bridges and 2-edge-connected components in a graph as edges are added. It efficiently updates the graph structure and bridge count in an online fashion.
//   • Idea: This algorithm maintains 2-edge-connected components and bridges in a graph as edges are added, using a Union-Find structure to manage components and a forest to represent the relationships between them. It typically achieves near-amortized constant time per edge addition.
//   • Invariants: Each 2-edge-connected component is represented by a single root in the Union-Find structure.; The set of bridges forms a forest where each node is a 2-edge-connected component.
//   • Tips: Represent 2-edge-connected components using Union-Find for efficient merging.; Maintain a forest where nodes are 2-edge-connected components and edges are bridges.
//   • Pitfalls: Incorrectly identifying when an edge forms a cycle with existing bridges.; Failing to update the bridge count accurately when bridges are removed.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int largestComponentSize(vector<int>& nums) {
        const int maxNum = 100000;
        vector<int> spf(maxNum + 1, 0); // smallest prime factor
        for (int i = 2; i * i <= maxNum; ++i) {
            if (spf[i] == 0) {
                for (int j = i * i; j <= maxNum; j += i) {
                    if (spf[j] == 0) {
                        spf[j] = i;
                    }
                }
            }
        }
        for (int i = 2; i <= maxNum; ++i) {
            if (spf[i] == 0) {
                spf[i] = i;
            }
        }

        unordered_map<int, int> parent;
        function<int(int)> find = [&](int x) {
            if (parent.find(x) == parent.end()) {
                parent[x] = x;
            }
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        };
        auto unite = [&](int x, int y) {
            int px = find(x);
            int py = find(y);
            if (px != py) {
                parent[py] = px;
            }
        };

        for (int num : nums) {
            int original = num;
            unordered_set<int> factors;
            while (num > 1) {
                factors.insert(spf[num]);
                num /= spf[num];
            }
            for (int factor : factors) {
                unite(original, factor);
            }
        }

        unordered_map<int, int> componentSize;
        int largestSize = 0;
        for (int num : nums) {
            int root = find(num);
            componentSize[root]++;
            largestSize = max(largestSize, componentSize[root]);
        }

        return largestSize;         
    }
};
