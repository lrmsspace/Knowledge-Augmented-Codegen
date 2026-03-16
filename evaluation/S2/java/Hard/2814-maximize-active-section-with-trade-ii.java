// Source: https://leetcode.com/problems/maximize-active-section-with-trade-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a binary string s of length n, where:
//
//
//  '1' represents an active section.
//  '0' represents an inactive section.
//
//
// You can perform at most one trade to maximize the number of active sections in s. In a trade, you:
//
//
//  Convert a contiguous block of '1's that is surrounded by '0's to all '0's.
//  Afterward, convert a contiguous block of '0's that is surrounded by '1's to all '1's.
//
//
// Additionally, you are given a 2D array queries, where queries[i] = [li, ri] represents a substring s[li...ri].
//
// For each query, determine the maximum possible number of active sections in s after making the optimal trade on the substring s[li...ri].
//
// Return an array answer, where answer[i] is the result for queries[i].
//
// Note
//
//
//  For each query, treat s[li...ri] as if it is augmented with a '1' at both ends, forming t = '1' + s[li...ri] + '1'. The augmented '1's do not contribute to the final count.
//  The queries are independent of each other.
//
// Example:
// Input: s = "01", queries = [[0,1]]
//
// Output: [1]
//
// Explanation:
//
// Because there is no block of '1's surrounded by '0's, no valid trade is possible. The maximum number of active sections is 1.
//
// Constraints:
// 1 <= n == s.length <= 105
//  1 <= queries.length <= 105
//  s[i] is either '0' or '1'.
//  queries[i] = [li, ri]
//  0 <= li <= ri < n
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Range Minimum Query (array, tree, lca)
//   • When to use: Use when needing to find the minimum element within various specified ranges of a static array efficiently, especially when many queries are expected after initial preprocessing.
//   • Idea: Range Minimum Query (RMQ) finds the minimum value in a given contiguous subsegment of an array. It typically involves preprocessing the array to achieve O(1) or O(log N) query time, with preprocessing in O(N log N) or O(N).
//   • Invariants: For a Sparse Table `st[i][j]`, `st[i][j]` stores the minimum in the range `[i, i + 2^j - 1]`.; During a query `[L, R]`, the chosen blocks `[L, L + 2^k - 1]` and `[R - 2^k + 1, R]` completely cover the target range.
//   • Tips: For static arrays, Sparse Table offers O(1) query time after O(N log N) preprocessing.; Segment Trees provide O(log N) query and update times, suitable for dynamic arrays.
//   • Pitfalls: Sparse Tables do not support updates efficiently; they are primarily for static data.; Off-by-one errors are common when calculating range indices or log values for segment lengths.
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public List<Integer> maxActiveSectionsAfterTrade(String s, int[][] queries) {
        int n = s.length();
        int[] prefixOnes = new int[n + 1];
        for (int i = 0; i < n; i++) {
            prefixOnes[i + 1] = prefixOnes[i] + (s.charAt(i) == '1' ? 1 : 0);
        }

        List<Integer> result = new ArrayList<>();
        for (int[] query : queries) {
            int l = query[0], r = query[1];
            int totalOnes = prefixOnes[r + 1] - prefixOnes[l];
            int totalZeros = (r - l + 1) - totalOnes;

            // The maximum active sections after trade is the maximum of:
            // 1. Keeping all '1's and converting one block of '0's to '1's.
            // 2. Keeping all '0's and converting one block of '1's to '0's.
            int maxActiveSections = Math.max(totalOnes + Math.min(1, totalZeros), totalZeros + Math.min(1, totalOnes));
            result.add(maxActiveSections);
        }

        return result;          
    }
}
