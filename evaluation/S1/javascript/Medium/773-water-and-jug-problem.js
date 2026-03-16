// Source: https://leetcode.com/problems/water-and-jug-problem/   |   Difficulty: Medium
//
// Problem Description:
// You are given two jugs with capacities x liters and y liters. You have an infinite water supply. Return whether the total amount of water in both jugs may reach target using the following operations:
//
//
// 	Fill either jug completely with water.
// 	Completely empty either jug.
// 	Pour water from one jug into another until the receiving jug is full, or the transferring jug is empty.
//
// Example:
// Input:   x = 3, y = 5, target = 4 
//
// Output:   true 
//
// Explanation:
//
// Follow these steps to reach a total of 4 liters:
//
//
// 	Fill the 5-liter jug (0, 5).
// 	Pour from the 5-liter jug into the 3-liter jug, leaving 2 liters (3, 2).
// 	Empty the 3-liter jug (0, 2).
// 	Transfer the 2 liters from the 5-liter jug to the 3-liter jug (2, 0).
// 	Fill the 5-liter jug again (2, 5).
// 	Pour from the 5-liter jug into the 3-liter jug until the 3-liter jug is full. This leaves 4 liters in the 5-liter jug (3, 4).
// 	Empty the 3-liter jug. Now, you have exactly 4 liters in the 5-liter jug (0, 4).
//
//
// Reference: The Die Hard example.
//
// Constraints:
// 1 <= x, y, target <= 103
//
// Helpful references (internal KB):
// - Euclidean algorithm for computing the greatest common divisor (number, gcd)
//   • When to use: Use this algorithm to efficiently find the greatest common divisor of two or more integers, or as a subroutine for tasks like simplifying fractions or finding the least common multiple.
//   • Idea: The Euclidean algorithm is an efficient method for computing the greatest common divisor (GCD) of two non-negative integers by repeatedly applying the division algorithm. It operates in logarithmic time complexity, O(log min(a, b)).
//   • Invariants: The greatest common divisor of the current pair (a, b) remains constant and equal to the GCD of the original inputs.; The second number (b) is always non-negative.
//   • Tips: Handle the base case where one of the numbers is zero; gcd(a, 0) = a.; The algorithm works for any order of inputs; if a < b, the first step swaps them effectively.
//   • Pitfalls: Forgetting to take absolute values if negative inputs are possible, as GCD is typically defined for non-negative integers.; Incorrectly handling the zero input case, which can lead to infinite loops or incorrect results.
// - Stars and bars (number, counting)
//   • When to use: Use when counting the number of ways to distribute identical items into distinct bins, or finding the number of non-negative integer solutions to a linear equation. It is also applicable for problems with lower bounds on variables.
//   • Idea: Stars and bars is a combinatorial technique used to count the number of ways to place 'n' identical items into 'k' distinct bins, or equivalently, to find the number of non-negative integer solutions to x1 + ... + xk = n.
//   • Invariants: The total number of 'stars' (items) remains constant throughout any transformation.; The number of 'bars' (separators) is always one less than the number of bins (variables).
//   • Tips: Visualize items as 'stars' and separators as 'bars' to understand the arrangement.; Transform problems with lower bounds (x_i >= a_i) into non-negative solutions (x_i' >= 0).
//   • Pitfalls: Confusing identical items with distinct items, which requires a different counting method.; Incorrectly applying the formula when variables have lower bounds other than zero without transformation.
// - Linear Diophantine Equation (number, interval, enumeration)
//   • When to use: Use when you need to find or count all integer solutions (x, y) for a linear Diophantine equation ax + by = c, especially when solutions are constrained within specific intervals for x and y.
//   • Idea: This method finds all integer solutions to a linear Diophantine equation ax + by = c within given x and y intervals. It first finds a particular solution, then uses properties of the general solution to determine the valid range for x, and enumerates solutions in O(N) time where N is the number of solutions.
//   • Invariants: The current (x, y) pair always satisfies the linear Diophantine equation ax + by = c.; The current x value is an integer and satisfies the effective bounds l_x <= x <= r_x.
//   • Tips: Pre-divide coefficients a, b, c by gcd(a, b) to simplify the equation.; Use the Extended Euclidean Algorithm to find an initial particular solution (x0, y0).
//   • Pitfalls: Failing to check if c is divisible by gcd(a, b) before proceeding, leading to incorrect results.; Incorrectly applying the shifting logic for x and y bounds, resulting in an invalid solution range.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} x
 * @param {number} y
 * @param {number} target
 * @return {boolean}
 */
var canMeasureWater = function(x, y, target) {
	const gcd = (a, b) => {
		while (b !== 0) {
			const temp = b;
			b = a % b;
			a = temp;
		}
		return a;
	};

	const g = gcd(x, y);
	return target % g === 0 && target <= x + y;
};
