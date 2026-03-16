// Source: https://leetcode.com/problems/minimum-moves-to-pick-k-ones/   |   Difficulty: Hard
//
// Problem Description:
// You are given a binary array nums of length n, a positive integer k and a non-negative integer maxChanges.
//
// Alice plays a game, where the goal is for Alice to pick up k ones from nums using the minimum number of moves. When the game starts, Alice picks up any index aliceIndex in the range [0, n - 1] and stands there. If nums[aliceIndex] == 1 , Alice picks up the one and nums[aliceIndex] becomes 0(this does not count as a move). After this, Alice can make any number of moves (including zero) where in each move Alice must perform exactly one of the following actions:
//
//
//  Select any index j != aliceIndex such that nums[j] == 0 and set nums[j] = 1. This action can be performed at most maxChanges times.
//  Select any two adjacent indices x and y (|x - y| == 1) such that nums[x] == 1, nums[y] == 0, then swap their values (set nums[y] = 1 and nums[x] = 0). If y == aliceIndex, Alice picks up the one after this move and nums[y] becomes 0.
//
//
// Return the minimum number of moves required by Alice to pick exactly k ones.
//
// Example:
// Input: nums = [1,1,0,0,0,1,1,0,0,1], k = 3, maxChanges = 1
//
// Output: 3
//
// Explanation: Alice can pick up 3 ones in 3 moves, if Alice performs the following actions in each move when standing at aliceIndex == 1:
//
//
//  At the start of the game Alice picks up the one and nums[1] becomes 0. nums becomes [1,0,0,0,0,1,1,0,0,1].
//  Select j == 2 and perform an action of the first type. nums becomes [1,0,1,0,0,1,1,0,0,1]
//  Select x == 2 and y == 1, and perform an action of the second type. nums becomes [1,1,0,0,0,1,1,0,0,1]. As y == aliceIndex, Alice picks up the one and nums becomes [1,0,0,0,0,1,1,0,0,1].
//  Select x == 0 and y == 1, and perform an action of the second type. nums becomes [0,1,0,0,0,1,1,0,0,1]. As y == aliceIndex, Alice picks up the one and nums becomes [0,0,0,0,0,1,1,0,0,1].
//
//
// Note that it may be possible for Alice to pick up 3 ones using some other sequence of 3 moves.
//
// Constraints:
// 2 <= n <= 105
//  0 <= nums[i] <= 1
//  1 <= k <= 105
//  0 <= maxChanges <= 105
//  maxChanges + sum(nums) >= k
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - 0-1 BFS (graph, array, dijkstra, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
//   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
//   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
//   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
//   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long minimumMoves(vector<int>& nums, int k, int maxChanges) {
        int n = nums.size();
        vector<int> ones;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 1) {
                ones.push_back(i);
            }
        }

        int totalOnes = ones.size();
        if (k > totalOnes) return -1;

        vector<long long> prefixSum(totalOnes + 1, 0);
        for (int i = 0; i < totalOnes; ++i) {
            prefixSum[i + 1] = prefixSum[i] + ones[i];
        }

        long long minMoves = LLONG_MAX;
        for (int start = 0; start <= totalOnes - k; ++start) {
            int end = start + k - 1;
            long long medianPos = ones[start + k / 2];
            long long leftCount = k / 2;
            long long rightCount = k - leftCount - 1;

            long long leftSum = prefixSum[start + leftCount] - prefixSum[start];
            long long rightSum = prefixSum[end + 1] - prefixSum[start + leftCount + 1];

            long long moves = (medianPos * leftCount - leftSum) + (rightSum - medianPos * rightCount);
            if (moves < minMoves) {
                minMoves = moves;
            }
        }

        return minMoves;            
    }
};
