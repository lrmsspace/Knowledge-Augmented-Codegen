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
// - Gauss method for solving system of linea (bitset, matrix, simulation)
//   • When to use: Use when determining the number of solutions (zero, one, or infinite) for a system of linear equations, or to find the unique solution if it exists. It is suitable for solving systems represented as an augmented matrix.
//   • Idea: Gaussian elimination systematically transforms an augmented matrix into row echelon form using elementary row operations to solve a system of linear equations. It determines the existence and values of solutions in O(N^3) time for an N x N system.
//   • Invariants: The submatrix formed by rows 0 to current_row - 1 is in row echelon form.; For the current column, all elements below the pivot in previous columns are zero.
//   • Tips: Use a small epsilon for floating-point comparisons to handle precision issues.; Implement partial pivoting to enhance numerical stability by selecting the largest absolute value.
//   • Pitfalls: Failing to account for floating-point precision errors can lead to incorrect results.; Improper handling of free variables can misrepresent infinite solution sets.
// - Scheduling jobs on two machines (array, number, simulation, enumeration)
//   • When to use: Use when determining the optimal sequence of jobs to minimize the total completion time (makespan) on two machines, with a fixed processing order (machine 1 then machine 2) for all jobs.
//   • Idea: This problem involves ordering N jobs, each with two processing times (one for each machine), to minimize the overall makespan. Johnson's rule provides an optimal greedy solution for this specific two-machine flow shop problem in O(N log N) or O(N) time.
//   • Invariants: All jobs processed so far maintain the optimal relative order determined by Johnson's rule.; The current makespan is the minimum possible for the jobs already scheduled.
//   • Tips: Sort jobs based on Johnson's rule criteria: jobs with min(a_i, b_i).; Prioritize jobs with shorter machine 1 times or longer machine 2 times for early scheduling.
//   • Pitfalls: Applying Johnson's rule to problems with more than two machines, where it is not optimal.; Incorrectly sorting jobs within the two partitioned sets.
// - Balanced bracket sequences (number, counting)
//   • When to use: Use when the problem asks for the total number of valid arrangements of opening and closing brackets, ensuring all pairs are matched and correctly nested. It applies to combinatorial problems requiring structured pairing.
//   • Idea: This technique counts the number of ways to form sequences of opening and closing brackets such that they are balanced and properly nested. It is a classic combinatorial problem, typically solved in O(N) or O(N^2) time.
//   • Invariants: At any point in sequence construction, the count of open brackets placed must be greater than or equal to the count of closed brackets placed.; The total number of open brackets in a complete valid sequence must exactly equal the total number of closed brackets.
//   • Tips: Recognize the connection to Catalan numbers for common variations (e.g., N pairs of parentheses).; Dynamic programming can solve more complex variations with different bracket types or constraints.
//   • Pitfalls: Forgetting the 'prefix sum' condition: the count of open brackets must always be greater than or equal to close brackets at any point.; Incorrectly applying Catalan numbers to problems with additional constraints or different bracket types.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public List<Integer> numOfBurgers(int tomatoSlices, int cheeseSlices) {
        List<Integer> result = new ArrayList<>();

        // Let x be the number of jumbo burgers and y be the number of small burgers
        // We have the following equations:
        // 4x + 2y = tomatoSlices  (1)
        // x + y = cheeseSlices     (2)

        // From equation (2), we can express y in terms of x:
        // y = cheeseSlices - x

        // Substitute y in equation (1):
        // 4x + 2(cheeseSlices - x) = tomatoSlices
        // 4x + 2cheeseSlices - 2x = tomatoSlices
        // 2x + 2cheeseSlices = tomatoSlices
        // 2x = tomatoSlices - 2cheeseSlices
        // x = (tomatoSlices - 2cheeseSlices) / 2

        // Now we can calculate x and y:
        if ((tomatoSlices - 2 * cheeseSlices) < 0 || (tomatoSlices - 2 * cheeseSlices) % 2 != 0) {
            return result; // No valid solution
        }

        int x = (tomatoSlices - 2 * cheeseSlices) / 2; // Number of jumbo burgers
        int y = cheeseSlices - x; // Number of small burgers

        if (y < 0) {
            return result; // No valid solution
        }

        result.add(x);
        result.add(y);
        return result;          
    }
}
