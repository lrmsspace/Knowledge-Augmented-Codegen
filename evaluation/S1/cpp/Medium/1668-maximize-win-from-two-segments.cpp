// Source: https://leetcode.com/problems/maximize-win-from-two-segments/   |   Difficulty: Medium
//
// Problem Description:
// There are some prizes on the X-axis. You are given an integer array prizePositions that is sorted in non-decreasing order, where prizePositions[i] is the position of the ith prize. There could be different prizes at the same position on the line. You are also given an integer k.
//
// You are allowed to select two segments with integer endpoints. The length of each segment must be k. You will collect all prizes whose position falls within at least one of the two selected segments (including the endpoints of the segments). The two selected segments may intersect.
//
//
// 	For example if k = 2, you can choose segments [1, 3] and [2, 4], and you will win any prize i that satisfies 1 <= prizePositions[i] <= 3 or 2 <= prizePositions[i] <= 4.
//
//
// Return the maximum number of prizes you can win if you choose the two segments optimally.
//
// Example:
// Input: prizePositions = [1,1,2,2,3,3,5], k = 2
// Output: 7
// Explanation: In this example, you can win all 7 prizes by selecting two segments [1, 3] and [3, 5].
//
// Constraints:
// 1 <= prizePositions.length <= 105
// 	1 <= prizePositions[i] <= 109
// 	0 <= k <= 109 
// 	prizePositions is sorted in non-decreasing order.
//
//
//  
// .spoilerbutton {display:block; border:dashed; padding: 0px 0px; margin:10px 0px; font-size:150%; font-weight: bold; color:#000000; background-color:cyan; outline:0; 
// }
// .spoiler {overflow:hidden;}
// .spoiler > div {-webkit-transition: all 0s ease;-moz-transition: margin 0s ease;-o-transition: all 0s ease;transition: margin 0s ease;}
// .spoilerbutton[value="Show Message"] + .spoiler > div {margin-top:-500%;}
// .spoilerbutton[value="Hide Message"] + .spoiler {padding:5px;}
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
// - Suffix Array (string, array, counting-sort, radix-sort)
//   • When to use: Use when you need to efficiently query or analyze all suffixes of a string, often for pattern matching, string searching, or finding repeated substrings. It provides a sorted order of all suffixes.
//   • Idea: The Suffix Array algorithm constructs an array containing the starting indices of all suffixes of a string, sorted lexicographically. It typically uses a doubling strategy with counting sort or radix sort in each step, achieving an O(N log N) time complexity.
//   • Invariants: After iteration k, p contains the sorted indices of all cyclic substrings of length 2^k.; After iteration k, c[i] represents the equivalence class of the cyclic substring starting at i with length 2^k.
//   • Tips: Append a unique, smallest character (e.g., '$') to the string to handle suffixes as cyclic shifts.; Utilize counting sort for efficient sorting of characters and pairs of equivalence classes.
//   • Pitfalls: Incorrectly handling the sentinel character can lead to incorrect suffix order or out-of-bounds access.; Off-by-one errors when calculating indices for cyclic shifts or substring lengths.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maximizeWin(vector<int>& prizePositions, int k) {
        int n = prizePositions.size();
        vector<int> prefix(n, 0);
        prefix[0] = 1;
        for (int i = 1; i < n; ++i) {
            prefix[i] = prefix[i - 1] + (prizePositions[i] != prizePositions[i - 1] ? 1 : 0);
        }

        auto count_in_range = [&](int left, int right) -> int {
            // Count unique prizes in [left, right]
            int lidx = lower_bound(prizePositions.begin(), prizePositions.end(), left) - prizePositions.begin();
            int ridx = upper_bound(prizePositions.begin(), prizePositions.end(), right) - prizePositions.begin() - 1;
            if (lidx > ridx) return 0;
            return prefix[ridx] - (lidx > 0 ? prefix[lidx - 1] : 0);
        };

        vector<int> max_from_left(n, 0);
        int max_unique = 0;
        for (int i = 0; i < n; ++i) {
            int left = prizePositions[i] - k;
            int cnt = count_in_range(left, prizePositions[i]);
            max_unique = max(max_unique, cnt);
            max_from_left[i] = max_unique;
        }

        vector<int> max_from_right(n, 0);
        max_unique = 0;
        for (int i = n - 1; i >= 0; --i) {
            int right = prizePositions[i] + k;
            int cnt = count_in_range(prizePositions[i], right);
            max_unique = max(max_unique, cnt);
            max_from_right[i] = max_unique;
        }

        int result = 0;
        for (int i = 0; i < n - 1; ++i) {
            result = max(result, max_from_left[i] + max_from_right[i + 1]);
        }
        result = max(result, max_from_left[n - 1]); // single segment case

        return result;          
    }
};
