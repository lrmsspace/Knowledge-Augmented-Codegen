// Source: https://leetcode.com/problems/reach-end-of-array-with-max-score/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums of length n.
//
// Your goal is to start at index 0 and reach index n - 1. You can only jump to indices greater than your current index.
//
// The score for a jump from index i to index j is calculated as (j - i) * nums[i].
//
// Return the maximum possible total score by the time you reach the last index.
//
// Example:
// Input: nums = [1,3,1,5]
//
// Output: 7
//
// Explanation:
//
// First, jump to index 1 and then jump to the last index. The final score is 1 * 1 + 2 * 3 = 7.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//
// Helpful references (internal KB):
// - Convex hull trick and Li Chao tree (array, number, dp-1d)
//   • When to use: Use when the optimal solution for a subproblem depends only on solutions to smaller, contiguous subproblems. It's effective for optimizing sequential decision-making or finding optimal values in arrays.
//   • Idea: Dynamic Programming 1D solves problems by breaking them into overlapping subproblems and storing results to avoid recomputation. It typically achieves O(N) or O(N log N) time and O(N) or O(1) space complexity.
//   • Invariants: dp[i] correctly stores the optimal solution for the subproblem ending at index i.; All dp[j] for j < i have been computed and are correct.
//   • Tips: Clearly define the state: what does dp[i] represent for the subproblem?; Establish correct base cases for the smallest subproblems.
//   • Pitfalls: Incorrectly defining the state or recurrence relation.; Missing or incorrect base cases, leading to incorrect results.
// - Convex hull trick and Li Chao tree (geometry, array, sweep-line, binary-search)
//   • When to use: When optimizing dynamic programming states that involve minimizing or maximizing linear functions, especially when slopes are monotonic or queries can be processed offline.
//   • Idea: Convex Hull Trick optimizes dynamic programming problems by maintaining a lower (or upper) convex hull of linear functions. It allows efficient querying of the minimum (or maximum) value of these functions at a given point, typically achieving O(N log N) or O(N) complexity.
//   • Invariants: The set of active lines always forms a lower (or upper) convex hull.; Lines within the hull are ordered by their slopes.
//   • Tips: Sort lines by slope for O(N) or O(N log N) insertion.; Use a deque for O(N) CHT when both slopes and query points are monotonic.
//   • Pitfalls: Incorrectly assuming monotonicity of slopes or query points.; Floating point precision issues when dealing with intersections.
// - Convex hull trick and Li Chao tree (number, segment-tree, recursion)
//   • When to use: Used to find the minimum (or maximum) value among a set of linear functions at a given point. It is particularly efficient for dynamic sets of lines or when slopes are monotonic.
//   • Idea: The Convex Hull Trick (CHT) and Li Chao Tree efficiently find the minimum (or maximum) value of a set of linear functions at a query point. CHT typically achieves O(log N) or O(1) amortized time, while Li Chao Tree offers O(log C) for updates and queries.
//   • Invariants: In CHT, the lower envelope of lines forms a convex shape, with slopes monotonically ordered.; In Li Chao Tree, each node stores a line that is optimal at the segment's midpoint for lines added to that node.
//   • Tips: Ensure slopes are monotonic for efficient CHT implementations.; Li Chao Tree handles non-monotonic slopes but requires a coordinate range.
//   • Pitfalls: Floating point precision issues can lead to incorrect intersection calculations.; Incorrectly managing the convex hull structure (e.g., deque) in CHT.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long findMaximumScore(vector<int>& nums) {
        int n = nums.size();
        vector<long long> dp(n);
        dp[0] = 0;

        deque<int> dq;
        dq.push_back(0);

        for (int i = 1; i < n; ++i) {
            while (!dq.empty() && dp[dq.back()] + (long long)(i - dq.back()) * nums[dq.back()] <= dp[i]) {
                dq.pop_back();
            }
            if (!dq.empty()) {
                dp[i] = dp[dq.back()] + (long long)(i - dq.back()) * nums[dq.back()];
            }
            while (!dq.empty() && dp[dq.front()] <= dp[i]) {
                dq.pop_front();
            }
            dq.push_back(i);
        }

        return dp[n - 1];           
    }
};
