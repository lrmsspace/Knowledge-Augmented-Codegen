// Source: https://leetcode.com/problems/count-ways-to-group-overlapping-ranges/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array ranges where ranges[i] = [starti, endi] denotes that all integers between starti and endi (both inclusive) are contained in the ith range.
//
// You are to split ranges into two (possibly empty) groups such that:
//
//
// 	Each range belongs to exactly one group.
// 	Any two overlapping ranges must belong to the same group.
//
//
// Two ranges are said to be overlapping if there exists at least one integer that is present in both ranges.
//
//
// 	For example, [1, 3] and [2, 5] are overlapping because 2 and 3 occur in both ranges.
//
//
// Return the total number of ways to split ranges into two groups. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: ranges = [[6,10],[5,15]]
// Output: 2
// Explanation: 
// The two ranges are overlapping, so they must be in the same group.
// Thus, there are two possible ways:
// - Put both the ranges together in group 1.
// - Put both the ranges together in group 2.
//
// Constraints:
// 1 <= ranges.length <= 105
// 	ranges[i].length == 2
// 	0 <= starti <= endi <= 109
//
// Helpful references (internal KB):
// - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
//   • When to use: Use when you need to perform O(1) range queries on a static array for an associative operation, after an O(N log N) preprocessing step.
//   • Idea: A data structure that precomputes answers for all possible range queries using an associative operation on a static array. It achieves O(1) query time and O(N log N) build time by storing prefix-like sums within logarithmically sized blocks.
//   • Invariants: For each level k, the array is partitioned into 2^k segments.; Within each segment, table[k][j] stores the result of the associative operation from j to the segment's midpoint (or midpoint to j).
//   • Tips: Ensure the operation is associative (e.g., min, max, sum, gcd, bitwise operations).; Preprocessing takes O(N log N) time and space.
//   • Pitfalls: Not suitable for mutable arrays; updates require rebuilding the table.; Requires O(N log N) memory, which can be substantial for very large N.
// - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
//   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
//   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
//   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
//   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
//   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
// - Finding intersection of two segments (geometry, array, enumeration, two-pointers)
//   • When to use: Use this to determine if two line segments intersect and, if so, find the intersection point or the overlapping segment. It is useful for collision detection and computational geometry problems.
//   • Idea: This algorithm determines the intersection of two line segments by first handling parallel or collinear cases, then calculating the intersection point if lines are not parallel. It typically involves O(1) time complexity for a fixed number of segments.
//   • Invariants: Before checking for intersection, both segments are valid (non-degenerate or single points).; For non-parallel lines, the intersection point of their infinite extensions is uniquely determined.
//   • Tips: Handle general line intersection using parametric equations or cross products.; Project segments onto X and Y axes to check for overlap in collinear cases.
//   • Pitfalls: Incorrectly handling edge cases like segments sharing an endpoint or being single points.; Failing to distinguish between parallel and collinear segments.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countWays(int** ranges, int rangesSize, int* rangesColSize) {
    // Step 1: Sort the ranges by their start time
    qsort(ranges, rangesSize, sizeof(int*), compareRanges);

    // Step 2: Merge overlapping ranges and count the number of merged groups
    int mergedCount = 0;
    int currentEnd = -1;

    for (int i = 0; i < rangesSize; i++) {
        int start = ranges[i][0];
        int end = ranges[i][1];

        if (start > currentEnd) {
            // This range does not overlap with the previous one, so we start a new group
            mergedCount++;
            currentEnd = end;
        } else {
            // This range overlaps with the previous one, so we merge it by updating the end time
            if (end > currentEnd) {
                currentEnd = end;
            }
        }
    }

    // Step 3: The number of ways to split into two groups is 2^mergedCount (each group can be in either of the two groups)
    long long mod = 1000000007;
    long long result = 1;

    for (int i = 0; i < mergedCount; i++) {
        result = (result * 2) % mod;
    }

    return (int)result;     
}
