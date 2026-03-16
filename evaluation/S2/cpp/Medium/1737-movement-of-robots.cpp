// Source: https://leetcode.com/problems/movement-of-robots/   |   Difficulty: Medium
//
// Problem Description:
// Some robots are standing on an infinite number line with their initial coordinates given by a 0-indexed integer array nums and will start moving once given the command to move. The robots will move a unit distance each second.
//
// You are given a string s denoting the direction in which robots will move on command. 'L' means the robot will move towards the left side or negative side of the number line, whereas 'R' means the robot will move towards the right side or positive side of the number line.
//
// If two robots collide, they will start moving in opposite directions.
//
// Return the sum of distances between all the pairs of robots d seconds after the command. Since the sum can be very large, return it modulo 109 + 7.
//
// Note: 
//
//
// 	For two robots at the index i and j, pair (i,j) and pair (j,i) are considered the same pair.
// 	When robots collide, they instantly change their directions without wasting any time.
// 	Collision happens when two robots share the same place in a moment.
// 	
// 		For example, if a robot is positioned in 0 going to the right and another is positioned in 2 going to the left, the next second they'll be both in 1 and they will change direction and the next second the first one will be in 0, heading left, and another will be in 2, heading right.
// 		For example, if a robot is positioned in 0 going to the right and another is positioned in 1 going to the left, the next second the first one will be in 0, heading left, and another will be in 1, heading right.
//
// Example:
// Input: nums = [-2,0,2], s = "RLL", d = 3
// Output: 8
// Explanation: 
// After 1 second, the positions are [-1,-1,1]. Now, the robot at index 0 will move left, and the robot at index 1 will move right.
// After 2 seconds, the positions are [-2,0,0]. Now, the robot at index 1 will move left, and the robot at index 2 will move right.
// After 3 seconds, the positions are [-3,-1,1].
// The distance between the robot at index 0 and 1 is abs(-3 - (-1)) = 2.
// The distance between the robot at index 0 and 2 is abs(-3 - 1) = 4.
// The distance between the robot at index 1 and 2 is abs(-1 - 1) = 2.
// The sum of the pairs of all distances = 2 + 4 + 2 = 8.
//
// Constraints:
// 2 <= nums.length <= 105
// 	-2 * 109 <= nums[i] <= 2 * 109
// 	0 <= d <= 109
// 	nums.length == s.length 
// 	s consists of 'L' and 'R' only
// 	nums[i] will be unique.
//
// Helpful references (internal KB):
// - String Hashing (string, number, hashing, prefix-sum)
//   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
//   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
//   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
//   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
//   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
// - Placing Bishops on a Chessboard (array, counting, dp-2d)
//   • When to use: Use when counting non-attacking piece placements on a grid, especially when the problem can be decomposed into independent subproblems based on board properties like diagonals.
//   • Idea: This algorithm employs 2D dynamic programming to count the total number of ways to place non-attacking bishops on a chessboard. It leverages the independence of placements on black and white squares/diagonals, achieving a polynomial time complexity.
//   • Invariants: For any diagonal `i`, `D[i][j]` represents the number of ways to place `j` bishops on diagonal `i`.; Bishops placed on black diagonals do not attack bishops placed on white diagonals.
//   • Tips: Decompose the problem into independent subproblems for black and white squares/diagonals.; Identify the state for DP, typically `dp[diagonal_index][bishops_placed]`.
//   • Pitfalls: Incorrectly calculating the number of squares on each diagonal.; Overlapping bishops if diagonal definitions are not precise.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int sumDistance(vector<int>& nums, string s, int d) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        vector<long long> final_positions(n);
        
        for (int i = 0; i < n; ++i) {
            if (s[i] == 'R') {
                final_positions[i] = nums[i] + d;
            } else {
                final_positions[i] = nums[i] - d;
            }
        }
        
        sort(final_positions.begin(), final_positions.end());
        
        long long total_distance = 0;
        long long prefix_sum = 0;
        
        for (int i = 0; i < n; ++i) {
            total_distance = (total_distance + i * final_positions[i] - prefix_sum) % MOD;
            prefix_sum = (prefix_sum + final_positions[i]) % MOD;
        }
        
        return total_distance;          
    }
};
