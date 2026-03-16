// Source: https://leetcode.com/problems/maximum-multiplication-score/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array a of size 4 and another integer array b of size at least 4.
//
// You need to choose 4 indices i0, i1, i2, and i3 from the array b such that i0 < i1 < i2 < i3. Your score will be equal to the value a[0] * b[i0] + a[1] * b[i1] + a[2] * b[i2] + a[3] * b[i3].
//
// Return the maximum score you can achieve.
//
// Example:
// Input: a = [3,2,5,6], b = [2,-6,4,-5,-3,2,-7]
//
// Output: 26
//
// Explanation:
// We can choose the indices 0, 1, 2, and 5. The score will be 3 * 2 + 2 * (-6) + 5 * 4 + 6 * 2 = 26.
//
// Constraints:
// a.length == 4
// 	4 <= b.length <= 105
// 	-105 <= a[i], b[i] <= 105
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
// - Operations on polynomials and series (array, recursion)
//   • When to use: Use when counting combinations or permutations with specific sum constraints, or when analyzing discrete probability distributions through polynomial multiplication.
//   • Idea: This technique represents combinatorial problems as coefficients of polynomials or formal power series. Solutions involve operations like polynomial multiplication and exponentiation, often with a time complexity dependent on the degree of the polynomials.
//   • Invariants: The degree of the product polynomial is the sum of the degrees of the input polynomials.; The coefficient of x^k in the product is the sum of A[i]*B[j] for all i+j=k.
//   • Tips: Represent individual choices as polynomial terms.; Multiply polynomials to combine independent events.
//   • Pitfalls: Incorrectly forming the initial generating function.; Naive polynomial multiplication can be computationally expensive.
// - Check if two segments intersect (geometry, number, simulation)
//   • When to use: Use this when determining if two line segments in a 2D plane share any common points, especially when floating-point precision issues need to be avoided.
//   • Idea: This algorithm determines if two line segments intersect by handling collinear and non-collinear cases separately, primarily using integer arithmetic to avoid precision errors. It typically runs in O(1) time.
//   • Invariants: If segments are collinear, their 1D projections on both axes must overlap for intersection.; If segments are not collinear, each segment's endpoints must lie on opposite sides of the line containing the other segment.
//   • Tips: Handle collinear segments as a distinct special case.; Utilize cross products for efficient orientation checks.
//   • Pitfalls: Failing to correctly identify and handle collinear segments.; Introducing floating-point errors by using division for slopes.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} a
 * @param {number[]} b
 * @return {number}
 */
var maxScore = function(a, b) {
    const sortedB = b.slice().sort((x, y) => y - x);
    const sortedA = a.slice().sort((x, y) => y - x);
    let maxScore = 0;
    for (let i = 0; i < 4; i++) {
        maxScore += sortedA[i] * sortedB[i];
    }
    return maxScore;
};
