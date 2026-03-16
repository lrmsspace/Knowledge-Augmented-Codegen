// Source: https://leetcode.com/problems/describe-the-painting/   |   Difficulty: Medium
//
// Problem Description:
// There is a long and thin painting that can be represented by a number line. The painting was painted with multiple overlapping segments where each segment was painted with a unique color. You are given a 2D integer array segments, where segments[i] = [starti, endi, colori] represents the half-closed segment [starti, endi) with colori as the color.
//
// The colors in the overlapping segments of the painting were mixed when it was painted. When two or more colors mix, they form a new color that can be represented as a set of mixed colors.
//
//
// 	For example, if colors 2, 4, and 6 are mixed, then the resulting mixed color is {2,4,6}.
//
//
// For the sake of simplicity, you should only output the sum of the elements in the set rather than the full set.
//
// You want to describe the painting with the minimum number of non-overlapping half-closed segments of these mixed colors. These segments can be represented by the 2D array painting where painting[j] = [leftj, rightj, mixj] describes a half-closed segment [leftj, rightj) with the mixed color sum of mixj.
//
//
// 	For example, the painting created with segments = [[1,4,5],[1,7,7]] can be described by painting = [[1,4,12],[4,7,7]] because:
//
// 	
// 		[1,4) is colored {5,7} (with a sum of 12) from both the first and second segments.
// 		[4,7) is colored {7} from only the second segment.
// 	
// 	
//
//
// Return the 2D array painting describing the finished painting (excluding any parts that are not painted). You may return the segments in any order.
//
// A half-closed segment [a, b) is the section of the number line between points a and b including point a and not including point b.
//
// Example:
// Input: segments = [[1,4,5],[4,7,7],[1,7,9]]
// Output: [[1,4,14],[4,7,16]]
// Explanation: The painting can be described as follows:
// - [1,4) is colored {5,9} (with a sum of 14) from the first and third segments.
// - [4,7) is colored {7,9} (with a sum of 16) from the second and third segments.
//
// Constraints:
// 1 <= segments.length <= 2 * 104
// 	segments[i].length == 3
// 	1 <= starti < endi <= 105
// 	1 <= colori <= 109
// 	Each colori is distinct.
//
// Helpful references (internal KB):
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
// - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
//   • When to use: When you need O(1) query time for any associative operation (like sum, min, max, GCD) on a static array, after an O(N log N) preprocessing step.
//   • Idea: A Disjoint Sparse Table is a data structure that supports O(1) range queries for any associative operation on a static array. It achieves this by precomputing results for specific disjoint and overlapping ranges, with an O(N log N) construction time and space complexity.
//   • Invariants: table[k][i] stores the result of the operation for a range of length 2^k starting at index i.; For any query [L, R], the result is obtained by combining two precomputed values from blocks that cover [L, mid] and [mid+1, R].
//   • Tips: Understand the block decomposition based on powers of two for construction.; Queries combine results from two precomputed blocks that cover the query range.
//   • Pitfalls: Does not support point updates efficiently; any modification requires a full rebuild.; Higher space complexity of O(N log N) compared to some other range query structures.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
long long** splitPainting(int** segments, int segmentsSize, int* segmentsColSize, int* returnSize, int** returnColumnSizes) {
    // Step 1: Create an array to store the changes in color sums at each coordinate
    int maxCoordinate = 0;
    for (int i = 0; i < segmentsSize; i++) {
        if (segments[i][1] > maxCoordinate) {
            maxCoordinate = segments[i][1];
        }
    }
    
    long long* colorChanges = (long long*)calloc(maxCoordinate + 1, sizeof(long long));
    
    // Step 2: Populate the color changes array using a sweep line approach
    for (int i = 0; i < segmentsSize; i++) {
        int start = segments[i][0];
        int end = segments[i][1];
        int color = segments[i][2];
        
        colorChanges[start] += color; // Start of a segment adds its color
        if (end <= maxCoordinate) {
            colorChanges[end] -= color; // End of a segment subtracts its color
        }
    }
    
    // Step 3: Create the result array to store the non-overlapping segments with their mixed colors
    long long** painting = (long long**)malloc(sizeof(long long*) * maxCoordinate); // Maximum possible segments is maxCoordinate
    *returnColumnSizes = (int*)malloc(sizeof(int) * maxCoordinate);
    
    int count = 0;
    long long currentColorSum = 0;
    
    for (int i = 0; i <= maxCoordinate; i++) {
        currentColorSum += colorChanges[i]; // Update the current color sum
        
        if (currentColorSum > 0) { // Only consider painted segments
            if (count > 0 && painting[count - 1][1] == i) {
                // Extend the previous segment if it ends at the current coordinate
                painting[count - 1][2] += currentColorSum; // Update the mixed color sum
            } else {
                // Start a new segment
                painting[count] = (long long*)malloc(sizeof(long long) * 3);
                painting[count][0] = i; // left coordinate
                painting[count][1] = i + 1; // right coordinate (half-open)
                painting[count][2] = currentColorSum; // mixed color sum
                (*returnColumnSizes)[count] = 3;
                count++;
            }
        }
    }
    
    free(colorChanges);
    *returnSize = count;
    return painting;                
}
