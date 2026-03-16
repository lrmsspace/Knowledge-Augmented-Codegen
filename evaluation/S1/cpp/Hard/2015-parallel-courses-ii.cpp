// Source: https://leetcode.com/problems/parallel-courses-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n, which indicates that there are n courses labeled from 1 to n. You are also given an array relations where relations[i] = [prevCoursei, nextCoursei], representing a prerequisite relationship between course prevCoursei and course nextCoursei: course prevCoursei has to be taken before course nextCoursei. Also, you are given the integer k.
//
// In one semester, you can take at most k courses as long as you have taken all the prerequisites in the previous semesters for the courses you are taking.
//
// Return the minimum number of semesters needed to take all courses. The testcases will be generated such that it is possible to take every course.
//
// Example:
// Input: n = 4, relations = [[2,1],[3,1],[1,4]], k = 2
// Output: 3
// Explanation: The figure above represents the given graph.
// In the first semester, you can take courses 2 and 3.
// In the second semester, you can take course 1.
// In the third semester, you can take course 4.
//
// Constraints:
// 1 <= n <= 15
// 	1 <= k <= n
// 	0 <= relations.length <= n * (n-1) / 2
// 	relations[i].length == 2
// 	1 <= prevCoursei, nextCoursei <= n
// 	prevCoursei != nextCoursei
// 	All the pairs [prevCoursei, nextCoursei] are unique.
// 	The given graph is a directed acyclic graph.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, array, bfs, counting)
//   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level to explore all reachable nodes. It is also suitable for finding connected components or checking reachability.
//   • Idea: Breadth-first search explores a graph layer by layer, finding the shortest path in terms of edges from a source node to all other reachable nodes. It typically runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently in the queue are at the same or next level of traversal from the source.; All nodes already dequeued have been fully processed, and their unvisited neighbors have been enqueued.
//   • Tips: Use a queue to manage nodes to visit in a FIFO manner.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing and cycles.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs or incorrect path lengths.; Not handling disconnected components if the goal is to traverse the entire graph.
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
        vector<int> preReq(n, 0);
        for (const auto& rel : relations) {
            preReq[rel[1] - 1] |= (1 << (rel[0] - 1));
        }

        const int FULL_MASK = (1 << n) - 1;
        vector<int> dp(1 << n, n + 1);
        dp[0] = 0;

        for (int mask = 0; mask <= FULL_MASK; ++mask) {
            int canTake = 0;
            for (int course = 0; course < n; ++course) {
                if ((mask & (1 << course)) == 0 && (preReq[course] & mask) == preReq[course]) {
                    canTake |= (1 << course);
                }
            }

            for (int submask = canTake; submask > 0; submask = (submask - 1) & canTake) {
                if (__builtin_popcount(submask) <= k) {
                    int nextMask = mask | submask;
                    dp[nextMask] = min(dp[nextMask], dp[mask] + 1);
                }
            }
        }

        return dp[FULL_MASK];           
    }
};
