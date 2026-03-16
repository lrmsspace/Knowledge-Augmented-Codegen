// Source: https://leetcode.com/problems/check-if-point-is-reachable/   |   Difficulty: Hard
//
// Problem Description:
// There exists an infinitely large grid. You are currently at point (1, 1), and you need to reach the point (targetX, targetY) using a finite number of steps.
//
// In one step, you can move from point (x, y) to any one of the following points:
//
//
// 	(x, y - x)
// 	(x - y, y)
// 	(2 * x, y)
// 	(x, 2 * y)
//
//
// Given two integers targetX and targetY representing the X-coordinate and Y-coordinate of your final position, return true if you can reach the point from (1, 1) using some number of steps, and false otherwise.
//
// Example:
// Input: targetX = 6, targetY = 9
// Output: false
// Explanation: It is impossible to reach (6,9) from (1,1) using any sequence of moves, so false is returned.
//
// Constraints:
// 1 <= targetX, targetY <= 109
//
// Helpful references (internal KB):
// - Lattice points inside non-lattice polygon (number, recursion, counting, gcd)
//   • When to use: Use when counting pairs or elements satisfying divisibility or GCD conditions. Also applicable for summing functions over pairs using number theory properties.
//   • Idea: This approach leverages number theoretic properties like GCD, LCM, and prime factorization to efficiently count elements or pairs satisfying specific criteria. It often involves iterating through divisors or multiples, achieving complexities like O(N log N) or O(sqrt N) per query.
//   • Invariants: All numbers processed so far have their relevant number-theoretic properties (e.g., prime factors, divisors) correctly determined.; The current count or sum accurately reflects all valid combinations found up to the current iteration.
//   • Tips: Precompute primes or divisors using a sieve for efficiency.; Utilize properties of GCD and LCM, such as gcd(a,b) * lcm(a,b) = a * b.
//   • Pitfalls: Overcounting or undercounting when using inclusion-exclusion.; Integer overflow with large products or sums.
// - Finding the equation of a line for a segment (number, geometry, gcd)
//   • When to use: Use this method when you need to represent a line segment's equation using integer coefficients, especially to avoid floating-point inaccuracies in geometric computations.
//   • Idea: This method derives the general form of a line equation (Ax + By + C = 0) from two points, ensuring integer coefficients if input coordinates are integers. It then normalizes these coefficients using GCD to achieve a unique representation, typically in O(log(max(|A|,|B|,|C|))) time due to GCD.
//   • Invariants: The calculated coefficients A, B, C always satisfy A*Px + B*Py + C = 0 for point P(Px, Py).; After GCD division, the absolute values of A, B, C are coprime (unless all are zero).
//   • Tips: Always compute A, B, C using the given formulas for P(Px, Py) and Q(Qx, Qy).; Use absolute values of A, B, C when calculating their greatest common divisor.
//   • Pitfalls: Forgetting to normalize coefficients leads to non-unique representations for the same line.; Incorrectly handling signs during the final normalization step can result in inconsistent forms.
// - Finding the nearest pair of points (geometry, array, divide-and-conquer)
//   • When to use: Use this algorithm to efficiently find the pair of points with the minimum Euclidean distance among a given set of N points in a 2D plane. It is particularly effective for large datasets where an O(N^2) approach is too slow.
//   • Idea: This divide-and-conquer algorithm finds the closest pair of points in a 2D plane by recursively splitting the set of points and merging results. It achieves an optimal time complexity of O(N log N).
//   • Invariants: At the start of any recursive call, the input point set is sorted by X-coordinate.; The returned minimum distance 'd' for a subproblem is the true minimum distance among its points.
//   • Tips: Initial sorting by X-coordinate is crucial for efficient division of the point set.; Handle base cases (e.g., 2 or 3 points) with a simple brute-force distance calculation.
//   • Pitfalls: Forgetting to sort points by Y-coordinate within the central strip can degrade performance to O(N^2).; Incorrectly defining the strip width or comparison range in the merge step can lead to incorrect results.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} targetX
 * @param {number} targetY
 * @return {boolean}
 */
var isReachable = function(targetX, targetY) {
    if (targetX < 1 || targetY < 1) return false;

    while (targetX > 1 || targetY > 1) {
        if (targetX === targetY) return false;
        if (targetX > targetY) {
            if (targetY === 1) return true;
            targetX %= targetY;
        } else {
            if (targetX === 1) return true;
            targetY %= targetX;
        }
    }

    return true;
};
