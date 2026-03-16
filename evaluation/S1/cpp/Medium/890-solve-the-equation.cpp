// Source: https://leetcode.com/problems/solve-the-equation/   |   Difficulty: Medium
//
// Problem Description:
// Solve a given equation and return the value of 'x' in the form of a string "x=#value". The equation contains only '+', '-' operation, the variable 'x' and its coefficient. You should return "No solution" if there is no solution for the equation, or "Infinite solutions" if there are infinite solutions for the equation.
//
// If there is exactly one solution for the equation, we ensure that the value of 'x' is an integer.
//
// Example:
// Input: equation = "x+5-3+x=6+x-2"
// Output: "x=2"
//
// Constraints:
// 3 <= equation.length <= 1000
// 	equation has exactly one '='.
// 	equation consists of integers with an absolute value in the range [0, 100] without any leading zeros, and the variable 'x'.
// 	The input is generated that if there is a single solution, it will be an integer.
//
// Helpful references (internal KB):
// - Linear Diophantine Equation (number, interval, enumeration)
//   • When to use: Use when you need to find or count all integer solutions (x, y) for a linear Diophantine equation ax + by = c, especially when solutions are constrained within specific intervals for x and y.
//   • Idea: This method finds all integer solutions to a linear Diophantine equation ax + by = c within given x and y intervals. It first finds a particular solution, then uses properties of the general solution to determine the valid range for x, and enumerates solutions in O(N) time where N is the number of solutions.
//   • Invariants: The current (x, y) pair always satisfies the linear Diophantine equation ax + by = c.; The current x value is an integer and satisfies the effective bounds l_x <= x <= r_x.
//   • Tips: Pre-divide coefficients a, b, c by gcd(a, b) to simplify the equation.; Use the Extended Euclidean Algorithm to find an initial particular solution (x0, y0).
//   • Pitfalls: Failing to check if c is divisible by gcd(a, b) before proceeding, leading to incorrect results.; Incorrectly applying the shifting logic for x and y bounds, resulting in an invalid solution range.
// - Gauss method for solving system of linea (bitset, matrix, simulation)
//   • When to use: Use when determining the number of solutions (zero, one, or infinite) for a system of linear equations, or to find the unique solution if it exists. It is suitable for solving systems represented as an augmented matrix.
//   • Idea: Gaussian elimination systematically transforms an augmented matrix into row echelon form using elementary row operations to solve a system of linear equations. It determines the existence and values of solutions in O(N^3) time for an N x N system.
//   • Invariants: The submatrix formed by rows 0 to current_row - 1 is in row echelon form.; For the current column, all elements below the pivot in previous columns are zero.
//   • Tips: Use a small epsilon for floating-point comparisons to handle precision issues.; Implement partial pivoting to enhance numerical stability by selecting the largest absolute value.
//   • Pitfalls: Failing to account for floating-point precision errors can lead to incorrect results.; Improper handling of free variables can misrepresent infinite solution sets.
// - Check if two segments intersect (geometry, number, simulation)
//   • When to use: Use this when determining if two line segments in a 2D plane share any common points, especially when floating-point precision issues need to be avoided.
//   • Idea: This algorithm determines if two line segments intersect by handling collinear and non-collinear cases separately, primarily using integer arithmetic to avoid precision errors. It typically runs in O(1) time.
//   • Invariants: If segments are collinear, their 1D projections on both axes must overlap for intersection.; If segments are not collinear, each segment's endpoints must lie on opposite sides of the line containing the other segment.
//   • Tips: Handle collinear segments as a distinct special case.; Utilize cross products for efficient orientation checks.
//   • Pitfalls: Failing to correctly identify and handle collinear segments.; Introducing floating-point errors by using division for slopes.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    string solveEquation(string equation) {
        int lhs_x = 0, lhs_const = 0;
        int rhs_x = 0, rhs_const = 0;
        int sign = 1; // 1 for LHS, -1 for RHS
        int i = 0;
        int n = equation.size();

        while (i < n) {
            if (equation[i] == '=') {
                sign = -1;
                i++;
                continue;
            }

            int coeff_sign = 1;
            if (equation[i] == '+') {
                coeff_sign = 1;
                i++;
            } else if (equation[i] == '-') {
                coeff_sign = -1;
                i++;
            }

            int coeff = 0;
            bool is_x_term = false;

            while (i < n && isdigit(equation[i])) {
                coeff = coeff * 10 + (equation[i] - '0');
                i++;
            }

            if (i < n && equation[i] == 'x') {
                is_x_term = true;
                i++;
            }

            if (is_x_term) {
                if (coeff == 0) coeff = 1; // handle cases like "x" or "-x"
                if (sign == 1) {
                    lhs_x += coeff_sign * coeff;
                } else {
                    rhs_x += coeff_sign * coeff;
                }
            } else {
                if (sign == 1) {
                    lhs_const += coeff_sign * coeff;
                } else {
                    rhs_const += coeff_sign * coeff;
                }
            }
        }

        int total_x = lhs_x - rhs_x;
        int total_const = rhs_const - lhs_const;

        if (total_x == 0) {
            if (total_const == 0) {
                return "Infinite solutions";
            } else {
                return "No solution";
            }
        } else {
            int x_value = total_const / total_x;
            return "x=" + to_string(x_value);
        }           
    }
};
