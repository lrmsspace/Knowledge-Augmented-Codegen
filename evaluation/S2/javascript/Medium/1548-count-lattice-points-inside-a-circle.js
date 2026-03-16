// Source: https://leetcode.com/problems/count-lattice-points-inside-a-circle/   |   Difficulty: Medium
//
// Problem Description:
// Given a 2D integer array circles where circles[i] = [xi, yi, ri] represents the center (xi, yi) and radius ri of the ith circle drawn on a grid, return the number of lattice points that are present inside at least one circle.
//
// Note:
//
//
// 	A lattice point is a point with integer coordinates.
// 	Points that lie on the circumference of a circle are also considered to be inside it.
//
// Example:
// Input: circles = [[2,2,1]]
// Output: 5
// Explanation:
// The figure above shows the given circle.
// The lattice points present inside the circle are (1, 2), (2, 1), (2, 2), (2, 3), and (3, 2) and are shown in green.
// Other points such as (1, 1) and (1, 3), which are shown in red, are not considered inside the circle.
// Hence, the number of lattice points present inside at least one circle is 5.
//
// Constraints:
// 1 <= circles.length <= 200
// 	circles[i].length == 3
// 	1 <= xi, yi <= 100
// 	1 <= ri <= min(xi, yi)
//
// Helpful references (internal KB):
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
// - Finding common tangents to two circles (geometry, number, enumeration, simulation)
//   • When to use: When needing to find lines that are tangent to two given circles simultaneously. This method is suitable for problems requiring precise geometric line calculations.
//   • Idea: This algorithm finds common tangent lines to two circles by formulating the problem as a system of algebraic equations based on distance constraints. It involves solving a quadratic equation for line coefficients, typically resulting in constant time complexity after initial setup.
//   • Invariants: The distance from the line ax + by + c = 0 to the first circle's center is r1.; The distance from the line ax + by + c = 0 to the second circle's center is r2.
//   • Tips: Normalize the line equation (a^2 + b^2 = 1) to ensure unique representations.; Shift one circle to the origin for simpler calculations, then shift the resulting lines back.
//   • Pitfalls: Forgetting to normalize the line equation can lead to non-unique solutions.; Incorrectly handling the modulus signs (±r1, ±r2) can miss valid tangents.
// - Lattice points inside non-lattice polygon (number, recursion, counting, gcd)
//   • When to use: Use when counting pairs or elements satisfying divisibility or GCD conditions. Also applicable for summing functions over pairs using number theory properties.
//   • Idea: This approach leverages number theoretic properties like GCD, LCM, and prime factorization to efficiently count elements or pairs satisfying specific criteria. It often involves iterating through divisors or multiples, achieving complexities like O(N log N) or O(sqrt N) per query.
//   • Invariants: All numbers processed so far have their relevant number-theoretic properties (e.g., prime factors, divisors) correctly determined.; The current count or sum accurately reflects all valid combinations found up to the current iteration.
//   • Tips: Precompute primes or divisors using a sieve for efficiency.; Utilize properties of GCD and LCM, such as gcd(a,b) * lcm(a,b) = a * b.
//   • Pitfalls: Overcounting or undercounting when using inclusion-exclusion.; Integer overflow with large products or sums.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} circles
 * @return {number}
 */
var countLatticePoints = function(circles) {
    const points = new Set();
    for (const [x, y, r] of circles) {
        for (let i = x - r; i <= x + r; i++) {
            for (let j = y - r; j <= y + r; j++) {
                if ((i - x) ** 2 + (j - y) ** 2 <= r ** 2) {
                    points.add(`${i},${j}`);
                }
            }
        }
    }
    return points.size;
};
