// Source: https://leetcode.com/problems/number-of-burgers-with-no-waste-of-ingredients/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers tomatoSlices and cheeseSlices. The ingredients of different burgers are as follows:
//
//
// 	Jumbo Burger: 4 tomato slices and 1 cheese slice.
// 	Small Burger: 2 Tomato slices and 1 cheese slice.
//
//
// Return [total_jumbo, total_small] so that the number of remaining tomatoSlices equal to 0 and the number of remaining cheeseSlices equal to 0. If it is not possible to make the remaining tomatoSlices and cheeseSlices equal to 0 return [].
//
// Example:
// Input: tomatoSlices = 16, cheeseSlices = 7
// Output: [1,6]
// Explantion: To make one jumbo burger and 6 small burgers we need 4*1 + 2*6 = 16 tomato and 1 + 6 = 7 cheese.
// There will be no remaining ingredients.
//
// Constraints:
// 0 <= tomatoSlices, cheeseSlices <= 107
//
// Helpful references (internal KB):
// - Gauss method for solving system of linea (matrix, number, simulation)
//   • When to use: Use to solve systems of linear equations, determine matrix rank, or find matrix inverses. It helps analyze if a system has unique, infinite, or no solutions.
//   • Idea: Gaussian elimination transforms an augmented matrix into row echelon form using elementary row operations to solve linear systems. Gauss-Jordan extends this to reduced row echelon form for direct solutions, typically with O(N^3) complexity.
//   • Invariants: The solution set of the system of equations remains unchanged after each elementary row operation.; After processing column k, all elements below the pivot in that column are zero.
//   • Tips: Use partial pivoting to improve numerical stability and avoid division by zero.; Handle floating-point precision issues carefully, using a small epsilon for comparisons.
//   • Pitfalls: Encountering division by zero if a pivot element is zero and no pivoting is applied.; Numerical instability and accumulation of floating-point errors, especially without pivoting.
// - Gauss method for solving system of linea (matrix, number, simulation)
//   • When to use: Use when solving systems of linear equations, including those over finite fields (modulo p), to find unique, multiple, or no solutions.
//   • Idea: Gauss-Jordan elimination systematically transforms a system of linear equations into an equivalent, simpler form (row echelon or reduced row echelon) using elementary row operations to find solutions. This process typically has a time complexity of O(N^2 * M) for an N x M matrix.
//   • Invariants: After k steps, the first k columns form an identity submatrix (or a column with 1 at pivot and 0s elsewhere) in the upper-left kxk block.; The system of equations represented by the augmented matrix remains equivalent to the original system.
//   • Tips: Always perform row operations on the augmented matrix (A|b) to ensure consistency.; Choose a pivot with the largest absolute value to improve numerical stability and reduce error propagation.
//   • Pitfalls: Division by zero if a pivot element is zero and no suitable row swap is found.; Numerical instability with floating-point numbers if pivots are very small, leading to precision issues.
// - Gauss method for solving system of linea (bitset, matrix, simulation)
//   • When to use: Use when determining the number of solutions (zero, one, or infinite) for a system of linear equations, or to find the unique solution if it exists. It is suitable for solving systems represented as an augmented matrix.
//   • Idea: Gaussian elimination systematically transforms an augmented matrix into row echelon form using elementary row operations to solve a system of linear equations. It determines the existence and values of solutions in O(N^3) time for an N x N system.
//   • Invariants: The submatrix formed by rows 0 to current_row - 1 is in row echelon form.; For the current column, all elements below the pivot in previous columns are zero.
//   • Tips: Use a small epsilon for floating-point comparisons to handle precision issues.; Implement partial pivoting to enhance numerical stability by selecting the largest absolute value.
//   • Pitfalls: Failing to account for floating-point precision errors can lead to incorrect results.; Improper handling of free variables can misrepresent infinite solution sets.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} tomatoSlices
 * @param {number} cheeseSlices
 * @return {number[]}
 */
var numOfBurgers = function(tomatoSlices, cheeseSlices) {
    // Let x be the number of Jumbo Burgers and y be the number of Small Burgers
    // We have the following equations:
    // 4x + 2y = tomatoSlices  (1)
    // x + y = cheeseSlices     (2)
    // Solving for x and y:
    // From (2): y = cheeseSlices - x
    // Substituting in (1): 4x + 2(cheeseSlices - x) = tomatoSlices
    // Simplifying: 4x + 2*cheeseSlices - 2x = tomatoSlices
    // Further simplifying: 2x = tomatoSlices - 2*cheeseSlices
    // So: x = (tomatoSlices - 2*cheeseSlices) / 2
    // And: y = cheeseSlices - x
    
    const x = (tomatoSlices - 2 * cheeseSlices) / 2;
    const y = cheeseSlices - x;
    
    if (x < 0 || y < 0 || !Number.isInteger(x)) {
        return [];
    }
    
    return [x, y];
};
