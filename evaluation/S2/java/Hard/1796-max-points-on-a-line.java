// Source: https://leetcode.com/problems/max-points-on-a-line/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane, return the maximum number of points that lie on the same straight line.
//
// Example:
// Input: points = [[1,1],[2,2],[3,3]]
// Output: 3
//
// Constraints:
// 1 <= points.length <= 300
// 	points[i].length == 2
// 	-104 <= xi, yi <= 104
// 	All the points are unique.
//
// Helpful references (internal KB):
// - Finding the equation of a line for a segment (geometry, number, enumeration)
//   • When to use: Use when the problem asks to count or list all possible combinations, permutations, or arrangements of elements. It's suitable when a brute-force check of all possibilities is feasible.
//   • Idea: Enumeration systematically generates and examines all possible solutions to a problem. This approach guarantees finding the correct answer if one exists, typically with exponential time complexity O(k^N) or O(N!).
//   • Invariants: At each step, the current partial solution is valid according to problem constraints.; All previously explored partial solutions have been processed or discarded.
//   • Tips: Clearly define the search space and the properties of valid solutions.; Use recursion or iterative loops to explore all branches of the solution space.
//   • Pitfalls: Overlooking edge cases or constraints that limit the search space.; Generating duplicate solutions if not handled carefully.
// - Minimum Enclosing Circle (geometry, number, simulation)
//   • When to use: When you need to find the smallest circle that contains all given points in a 2D plane, often with a requirement for expected linear time complexity.
//   • Idea: This algorithm iteratively constructs the Minimum Enclosing Circle (MEC) by considering points one by one, potentially updating the circle if a new point lies outside. It achieves an expected linear time complexity, O(N), through randomization.
//   • Invariants: The current circle C is the MEC for the subset of points processed so far.; If C is defined by 1 point p_i, it is the MEC of points processed so far that passes through p_i.
//   • Tips: Randomly shuffle input points to achieve expected linear time complexity.; The Minimum Enclosing Circle is always defined by 2 or 3 points on its boundary.
//   • Pitfalls: A naive implementation without randomization can lead to O(N^3) worst-case time complexity.; Floating-point precision issues can arise in geometric calculations, requiring careful handling.
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maxPoints(int[][] points) {
        if (points.length < 3) {
            return points.length;
        }

        int maxPointsOnLine = 1;

        for (int i = 0; i < points.length; i++) {
            Map<String, Integer> slopeCount = new HashMap<>();
            int duplicatePoints = 1;

            for (int j = i + 1; j < points.length; j++) {
                int dx = points[j][0] - points[i][0];
                int dy = points[j][1] - points[i][1];

                if (dx == 0 && dy == 0) {
                    duplicatePoints++;
                    continue;
                }

                int gcd = gcd(dx, dy);
                dx /= gcd;
                dy /= gcd;

                String slopeKey = dx + "/" + dy;
                slopeCount.put(slopeKey, slopeCount.getOrDefault(slopeKey, 0) + 1);
            }

            int currentMax = duplicatePoints;
            for (int count : slopeCount.values()) {
                currentMax = Math.max(currentMax, count + duplicatePoints);
            }
            maxPointsOnLine = Math.max(maxPointsOnLine, currentMax);
        }

        return maxPointsOnLine;         
    }
}
