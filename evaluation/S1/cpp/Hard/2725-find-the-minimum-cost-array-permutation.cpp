// Source: https://leetcode.com/problems/find-the-minimum-cost-array-permutation/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums which is a permutation of [0, 1, 2, ..., n - 1]. The score of any permutation of [0, 1, 2, ..., n - 1] named perm is defined as:
//
// score(perm) = |perm[0] - nums[perm[1]]| + |perm[1] - nums[perm[2]]| + ... + |perm[n - 1] - nums[perm[0]]|
//
// Return the permutation perm which has the minimum possible score. If multiple permutations exist with this score, return the one that is lexicographically smallest among them.
//
// Example:
// Input: nums = [1,0,2]
//
// Output: [0,1,2]
//
// Explanation:
//
//
//
// The lexicographically smallest permutation with minimum cost is [0,1,2]. The cost of this permutation is |0 - 0| + |1 - 2| + |2 - 1| = 2.
//
// Constraints:
// 2 <= n == nums.length <= 14
// 	nums is a permutation of [0, 1, 2, ..., n - 1].
//
// Helpful references (internal KB):
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Depth-first search (graph, array, stack, dfs)
//   • When to use: Use DFS when you need to explore all reachable nodes from a starting point, find paths, detect cycles, or perform topological sorting in a graph. It is suitable for problems requiring deep exploration before backtracking.
//   • Idea: Depth-first search is an algorithm for traversing or searching tree or graph data structures. It explores as far as possible along each branch before backtracking, typically running in O(V + E) time for graphs.
//   • Invariants: All nodes currently on the recursion stack (or explicit stack) are part of the current path from the source.; Once a node `v` is marked `visited`, it will not be processed again by the main traversal logic.
//   • Tips: Use a `visited` array or set to track explored nodes.; Pass the parent node in recursive calls to correctly detect cycles.
//   • Pitfalls: Risk of stack overflow for very deep graphs with recursive implementations.; Failure to use a `visited` array leads to infinite loops in cyclic graphs.
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
    vector<int> findPermutation(vector<int>& nums) {
        int n = nums.size();
        vector<bool> used(n, false);
        vector<int> perm(n, -1);

        function<long long(int)> compute_score = [&](int start) {
            long long score = 0;
            for (int i = 0; i < n; ++i) {
                int curr = perm[(start + i) % n];
                int next = perm[(start + i + 1) % n];
                score += abs(curr - nums[next]);
            }
            return score;
        };

        long long min_score = LLONG_MAX;
        vector<int> best_perm;

        function<void(int)> backtrack = [&](int pos) {
            if (pos == n) {
                long long score = compute_score(0);
                if (score < min_score || (score == min_score && perm < best_perm)) {
                    min_score = score;
                    best_perm = perm;
                }
                return;
            }

            for (int i = 0; i < n; ++i) {
                if (!used[i]) {
                    used[i] = true;
                    perm[pos] = i;
                    backtrack(pos + 1);
                    used[i] = false;
                }
            }
        };

        backtrack(0);
        return best_perm;           
    }
};
