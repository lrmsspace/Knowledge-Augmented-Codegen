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
// - Finding intersection of two segments (geometry, array, enumeration, two-pointers)
//   • When to use: Use this to determine if two line segments intersect and, if so, find the intersection point or the overlapping segment. It is useful for collision detection and computational geometry problems.
//   • Idea: This algorithm determines the intersection of two line segments by first handling parallel or collinear cases, then calculating the intersection point if lines are not parallel. It typically involves O(1) time complexity for a fixed number of segments.
//   • Invariants: Before checking for intersection, both segments are valid (non-degenerate or single points).; For non-parallel lines, the intersection point of their infinite extensions is uniquely determined.
//   • Tips: Handle general line intersection using parametric equations or cross products.; Project segments onto X and Y axes to check for overlap in collinear cases.
//   • Pitfalls: Incorrectly handling edge cases like segments sharing an endpoint or being single points.; Failing to distinguish between parallel and collinear segments.
// - Search for a pair of intersecting segments (geometry, enumeration, sweep-line)
//   • When to use: When needing to efficiently detect if any two line segments among a given set intersect, or to find one such intersecting pair.
//   • Idea: This algorithm efficiently determines if any two line segments in a given set intersect by processing events along a sweep line, typically achieving O(N log N) time complexity.
//   • Invariants: All segments fully to the left of the sweep line have been processed and do not intersect each other.; The active set contains all segments currently intersecting the sweep line, ordered by their y-coordinate.
//   • Tips: Represent segments by their endpoints as event points, sorted by x-coordinate.; Use a balanced binary search tree (or similar structure) to maintain active segments ordered by their y-coordinate at the sweep line.
//   • Pitfalls: Floating point precision issues can lead to incorrect intersection detection or ordering.; Degenerate cases like collinear segments or multiple segments intersecting at a single point.
// - Finding intersection of two segments (geometry, interval, simulation, interval-scheduling)
//   • When to use: When determining if two line segments in 2D space cross, touch, or overlap, and to find the nature of their intersection (point, segment, or empty).
//   • Idea: This algorithm determines if two line segments intersect and calculates their intersection point or segment. It typically involves checking for orientation changes and handling special cases like collinearity, with an O(1) time complexity.
//   • Invariants: The bounding boxes of the two segments must overlap for an intersection to be possible.; If segments are collinear, their intersection is either empty, a point, or a sub-segment.
//   • Tips: Use a bounding box check first for early exit optimization.; Handle collinear segments as a distinct special case.
//   • Pitfalls: Incorrectly handling parallel or perfectly collinear segments.; Floating point inaccuracies leading to false positives or negatives.
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
    // Step 1: Create an array to store the changes in color at each point
    int maxPoint = 0;
    for (int i = 0; i < segmentsSize; i++) {
        if (segments[i][1] > maxPoint) {
            maxPoint = segments[i][1];
        }
    }
    
    long long* colorChanges = (long long*)calloc(maxPoint + 1, sizeof(long long));
    
    // Step 2: Mark the changes in color for each segment
    for (int i = 0; i < segmentsSize; i++) {
        int start = segments[i][0];
        int end = segments[i][1];
        int color = segments[i][2];
        
        colorChanges[start] += color; // Add color at the start
        if (end <= maxPoint) {
            colorChanges[end] -= color; // Subtract color at the end
        }
    }
    
    // Step 3: Calculate the prefix sum to get the current color at each point
    long long currentColor = 0;
    int lastPoint = 0;
    int resultSize = 0;
    
    // We will store the results in a dynamic array
    long long** result = (long long**)malloc(sizeof(long long*) * (maxPoint + 1));
    *returnColumnSizes = (int*)malloc(sizeof(int) * (maxPoint + 1));
    
    for (int i = 0; i <= maxPoint; i++) {
        currentColor += colorChanges[i];
        
        if (currentColor > 0) { // If there is a color at this point
            if (resultSize == 0 || result[resultSize - 1][2] != currentColor) {
                // If it's a new segment or the color has changed, we need to start a new segment
                if (resultSize > 0) {
                    result[resultSize - 1][1] = i; // Close the previous segment
                }
                result[resultSize] = (long long*)malloc(sizeof(long long) * 3);
                result[resultSize][0] = lastPoint; // Start of the new segment
                result[resultSize][2] = currentColor; // Color of the new segment
                (*returnColumnSizes)[resultSize] = 3;
                resultSize++;
            }
        } else if (resultSize > 0 && result[resultSize - 1][1] == 0) {
            // If there is no color and the last segment is not closed, close it
            result[resultSize - 1][1] = i;
        }
        lastPoint = i;
    }
    *returnSize = resultSize;
    return result;
}
