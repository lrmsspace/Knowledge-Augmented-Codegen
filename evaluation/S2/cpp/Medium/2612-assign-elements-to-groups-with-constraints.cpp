// Source: https://leetcode.com/problems/assign-elements-to-groups-with-constraints/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array groups, where groups[i] represents the size of the ith group. You are also given an integer array elements.
//
// Your task is to assign one element to each group based on the following rules:
//
//
// 	An element at index j can be assigned to a group i if groups[i] is divisible by elements[j].
// 	If there are multiple elements that can be assigned, assign the element with the smallest index j.
// 	If no element satisfies the condition for a group, assign -1 to that group.
//
//
// Return an integer array assigned, where assigned[i] is the index of the element chosen for group i, or -1 if no suitable element exists.
//
// Note: An element may be assigned to more than one group.
//
// Example:
// Input: groups = [8,4,3,2,4], elements = [4,2]
//
// Output: [0,0,-1,1,0]
//
// Explanation:
//
//
// 	elements[0] = 4 is assigned to groups 0, 1, and 4.
// 	elements[1] = 2 is assigned to group 3.
// 	Group 2 cannot be assigned any element.
//
// Constraints:
// 1 <= groups.length <= 105
// 	1 <= elements.length <= 105
// 	1 <= groups[i] <= 105
// 	1 <= elements[i] <= 105
//
// Helpful references (internal KB):
// - Euler's totient function
//  (array, number, enumeration)
//   • When to use: Use when needing to count positive integers up to n that are relatively prime to n. It is also efficient for computing totient values for all numbers in a given range.
//   • Idea: Euler's totient function, φ(n), counts positive integers less than or equal to n that are relatively prime to n. It can be computed for a single n in O(sqrt(n)) using prime factorization, or for all numbers up to N in O(N log log N) using a sieve-like algorithm.
//   • Invariants: phi[i] stores the current totient value for i, which is i initially, then updated by (1 - 1/p) for each prime p dividing i.; After iterating through all primes p up to sqrt(N), phi[i] holds the correct totient value for all i <= N.
//   • Tips: For a single n, compute φ(n) using its prime factorization.; For all φ(i) up to N, use a sieve approach similar to Sieve of Eratosthenes.
//   • Pitfalls: Confusing 'relatively prime' with 'prime number'.; Applying the multiplicative property incorrectly when numbers share common factors.
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this when you need to find the longest possible subsequence of a given sequence where elements are in strictly increasing order. It is applicable for optimizing problems involving ordered selections from a sequence.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements are sorted in increasing order. It can be solved using dynamic programming in O(N^2) time or with a greedy approach using binary search in O(N log N) time.
//   • Invariants: The 'tails' array (or equivalent) is always sorted in increasing order.; For any index `i`, `tails[i]` stores the smallest ending element of an increasing subsequence of length `i+1` found so far.
//   • Tips: The O(N log N) approach maintains a 'tails' array where tails[i] stores the smallest ending element of an increasing subsequence of length i+1.; Use binary search (specifically `lower_bound` for strictly increasing) to find the correct position to update the 'tails' array.
//   • Pitfalls: Confusing subsequence with subarray; elements do not need to be contiguous.; Incorrectly applying binary search (e.g., using `upper_bound` instead of `lower_bound` for strict increase).
// - Kuhn's Algorithm for Maximum Bipartite Matching (graph, array, dfs)
//   • When to use: Use DFS to traverse or search a tree or graph, exploring each branch as far as possible before backtracking. It's ideal for connectivity, pathfinding, topological sorting, and cycle detection.
//   • Idea: DFS explores as far as possible along each branch before backtracking. It's a graph traversal algorithm with O(V+E) time complexity for adjacency list representation.
//   • Invariants: All nodes reachable from the starting node within the current path have been visited.; The current path from the start node to the current node is maintained.
//   • Tips: Use a visited set/array to prevent cycles and redundant work.; Recursion stack can lead to stack overflow for deep graphs.
//   • Pitfalls: Stack overflow with deep recursion on large graphs.; Incorrectly handling visited states can lead to infinite loops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> assignElements(vector<int>& groups, vector<int>& elements) {
        int n = groups.size();
        vector<int> assigned(n, -1);
        for (int j = 0; j < elements.size(); ++j) {
            for (int i = 0; i < n; ++i) {
                if (assigned[i] == -1 && groups[i] % elements[j] == 0) {
                    assigned[i] = j;
                }
            }
        }
        return assigned;            
    }
};
