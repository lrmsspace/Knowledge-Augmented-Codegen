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
// - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, stack, simulation, monotonic-stack)
//   • When to use: This technique is used to answer Range Minimum Queries efficiently on a static array by transforming them into Lowest Common Ancestor queries on a Cartesian Tree.
//   • Idea: This approach solves Range Minimum Query problems by constructing a Cartesian Tree from the input array, where the root of any subtree is its minimum element. RMQ for a given range then reduces to finding the Lowest Common Ancestor of the range's endpoints in this tree, allowing O(N) construction and O(1) query time after O(N) preprocessing.
//   • Invariants: For any node `u` in the Cartesian Tree, `value(u)` is the minimum among all values in the subtree rooted at `u`.; For any node `u`, all nodes in its left subtree have indices smaller than `index(u)`, and all nodes in its right subtree have indices larger than `index(u)`.
//   • Tips: A Cartesian Tree is a binary tree where each node's value is less than its children's values, and an in-order traversal yields the original array.; Utilize a monotonic stack to construct the Cartesian Tree in linear O(N) time.
//   • Pitfalls: Correctly implementing the monotonic stack for Cartesian Tree construction can be challenging.; Edge cases, such as an empty stack or handling the last elements during tree building, must be managed carefully.
// - Expression parsing (stack, simulation)
//   • When to use: This algorithm is used to evaluate expressions given in Reverse Polish Notation (postfix notation) to compute their final numerical value.
//   • Idea: This algorithm evaluates an expression in Reverse Polish Notation by processing elements sequentially. Numbers are pushed onto a stack, and operators pop two operands, compute, and push the result.
//   • Invariants: The stack always contains only numbers (operands or intermediate results).; For a valid RPN expression, the stack will have at least two elements when an operator is processed.
//   • Tips: Process the RPN expression from left to right, token by token.; Push numerical operands directly onto the stack.
//   • Pitfalls: Attempting to pop from an empty stack when an operator is encountered, indicating an invalid RPN expression.; Incorrect order of operands for non-commutative operations like subtraction or division.
// - Convex Hull construction (geometry, array, stack, sweep-line)
//   • When to use: Used to find the smallest convex polygon that encloses a given set of points. It is applied when the outer boundary of a point set is required.
//   • Idea: Constructs the smallest convex polygon containing all given points, typically using algorithms like Graham's scan or Monotone Chain. These algorithms achieve an optimal time complexity of O(N log N).
//   • Invariants: The points on the stack, from bottom to top, form a convex chain.; For any three consecutive points A, B, C on the stack (A below B, B below C), the turn from A to B to C is always a left turn or straight.
//   • Tips: Handle collinear points carefully, especially during sorting and turn checks.; Choose a robust orientation test (e.g., cross product) to determine turns.
//   • Pitfalls: Incorrectly handling collinear points can lead to non-convex hulls or missing points.; Floating-point precision issues can cause incorrect turn determinations.
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
        Stack<Integer> stack = new Stack<>();
        for (int i = n - 1; i >= 0; i--) {
            ans[i] = -1.0;
            while (!stack.isEmpty()) {
                int j = stack.peek();
                if (cars[i][1] <= cars[j][1]) {
                    stack.pop();
                } else {
                    double t = (double) (cars[j][0] - cars[i][0]) / (cars[i][1] - cars[j][1]);
                    if (ans[j] < 0 || t <= ans[j]) {
                        ans[i] = t;
                        break;
                    }
                    stack.pop();
                }
            }
            stack.push(i);
        }
        return ans;         
    }
}
