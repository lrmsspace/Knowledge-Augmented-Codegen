// Source: https://leetcode.com/problems/maximum-points-inside-the-square/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D array points and a string s where, points[i] represents the coordinates of point i, and s[i] represents the tag of point i.
//
// A valid square is a square centered at the origin (0, 0), has edges parallel to the axes, and does not contain two points with the same tag.
//
// Return the maximum number of points contained in a valid square.
//
// Note:
//
//
// 	A point is considered to be inside the square if it lies on or within the square's boundaries.
// 	The side length of the square can be zero.
//
// Example:
// Input: points = [[2,2],[-1,-2],[-4,4],[-3,1],[3,-3]], s = "abdca"
//
// Output: 2
//
// Explanation:
//
// The square of side length 4 covers two points points[0] and points[1].
//
// Constraints:
// 1 <= s.length, points.length <= 105
// 	points[i].length == 2
// 	-109 <= points[i][0], points[i][1] <= 109
// 	s.length == points.length
// 	points consists of distinct coordinates.
// 	s consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Sqrt Tree (array, tree, recursion, simulation)
//   • When to use: Use for efficient range queries on an array, achieving very low query complexity by leveraging a hierarchical block decomposition and specific structural properties like power-of-two block sizes.
//   • Idea: A Sqrt Tree is a hierarchical data structure designed for answering range queries on an array, achieving O(log log n) or better query time by recursively decomposing the array into blocks and layers.
//   • Invariants: Each layer of the Sqrt Tree consists of segments of equal length.; All blocks within a given layer have an equal, power-of-two size.
//   • Tips: Pad the input array with dummy elements to ensure its size is a power of two for simplified block calculations.; Ensure all block sizes on each layer are powers of two to enable efficient binary representation tricks for queries.
//   • Pitfalls: Incorrectly calculating block boundaries or segment sizes, leading to off-by-one errors or out-of-bounds access.; Overlooking the memory overhead associated with storing precomputed values for all blocks across multiple layers.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private int countPointsInSquare(int[][] points, String s, int sideLength) {
        int count = 0;
        long halfSide = sideLength / 2L;
        Set<Character> seenTags = new HashSet<>();

        for (int[] point : points) {
            int x = point[0];
            int y = point[1];
            char tag = s.charAt(count);

            if (Math.abs(x) <= halfSide && Math.abs(y) <= halfSide) {
                if (!seenTags.contains(tag)) {
                    seenTags.add(tag);
                    count++;
                }
            }
        }

        return count;
    }
    public int maxPointsInsideSquare(int[][] points, String s) {
        int n = points.length;
        int left = 0, right = (int) 1e9;
        int result = 0;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            int count = countPointsInSquare(points, s, mid);

            if (count > result) {
                result = count;
            }

            if (count == mid) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return result;          
    }
}
