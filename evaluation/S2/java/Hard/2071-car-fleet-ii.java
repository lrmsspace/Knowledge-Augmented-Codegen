// Source: https://leetcode.com/problems/car-fleet-ii/   |   Difficulty: Hard
//
// Problem Description:
// There are n cars traveling at different speeds in the same direction along a one-lane road. You are given an array cars of length n, where cars[i] = [positioni, speedi] represents:
//
//
// 	positioni is the distance between the ith car and the beginning of the road in meters. It is guaranteed that positioni < positioni+1.
// 	speedi is the initial speed of the ith car in meters per second.
//
//
// For simplicity, cars can be considered as points moving along the number line. Two cars collide when they occupy the same position. Once a car collides with another car, they unite and form a single car fleet. The cars in the formed fleet will have the same position and the same speed, which is the initial speed of the slowest car in the fleet.
//
// Return an array answer, where answer[i] is the time, in seconds, at which the ith car collides with the next car, or -1 if the car does not collide with the next car. Answers within 10-5 of the actual answers are accepted.
//
// Example:
// Input: cars = [[1,2],[2,1],[4,3],[7,2]]
// Output: [1.00000,-1.00000,3.00000,-1.00000]
// Explanation: After exactly one second, the first car will collide with the second car, and form a car fleet with speed 1 m/s. After exactly 3 seconds, the third car will collide with the fourth car, and form a car fleet with speed 2 m/s.
//
// Constraints:
// 1 <= cars.length <= 105
// 	1 <= positioni, speedi <= 106
// 	positioni < positioni+1
//
// Helpful references (internal KB):
// - Finding intersection of two segments (geometry, array, enumeration, two-pointers)
//   • When to use: Use this to determine if two line segments intersect and, if so, find the intersection point or the overlapping segment. It is useful for collision detection and computational geometry problems.
//   • Idea: This algorithm determines the intersection of two line segments by first handling parallel or collinear cases, then calculating the intersection point if lines are not parallel. It typically involves O(1) time complexity for a fixed number of segments.
//   • Invariants: Before checking for intersection, both segments are valid (non-degenerate or single points).; For non-parallel lines, the intersection point of their infinite extensions is uniquely determined.
//   • Tips: Handle general line intersection using parametric equations or cross products.; Project segments onto X and Y axes to check for overlap in collinear cases.
//   • Pitfalls: Incorrectly handling edge cases like segments sharing an endpoint or being single points.; Failing to distinguish between parallel and collinear segments.
// - Finding a negative cycle in the graph (graph, matrix, floyd-warshall)
//   • When to use: Use when you need to find if a negative cycle exists in a graph, especially when dealing with all-pairs shortest paths or when edge weights can be negative. It is suitable for dense graphs.
//   • Idea: The Floyd-Warshall algorithm can detect negative cycles by checking if any vertex has a negative distance to itself after all iterations. It computes all-pairs shortest paths in O(V^3) time.
//   • Invariants: After k iterations, dist[i][j] stores the shortest path from i to j using only intermediate vertices from 0 to k-1.; For any i, dist[i][i] remains 0 unless a negative cycle involving i is found.
//   • Tips: Initialize distance matrix with edge weights or infinity for non-existent edges.; Set dist[i][i] to 0 for all i initially.
//   • Pitfalls: Incorrect initialization of the distance matrix, especially dist[i][i].; Forgetting to check the main diagonal for negative values after computation.
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public double[] getCollisionTimes(int[][] cars) {
        int n = cars.length;
        double[] ans = new double[n];
        Arrays.fill(ans, -1);
        Deque<Integer> stack = new ArrayDeque<>();
        for (int i = n - 1; i >= 0; i--) {
            while (!stack.isEmpty()) {
                int j = stack.peek();
                if (cars[i][1] <= cars[j][1]) {
                    stack.pop();
                } else {
                    double t = (double)(cars[j][0] - cars[i][0]) / (cars[i][1] - cars[j][1]);
                    if (ans[j] < 0 || t <= ans[j]) {
                        ans[i] = t;
                        break;
                    } else {
                        stack.pop();
                    }
                }
            }
            stack.push(i);
        }
        return ans;         
    }
}
