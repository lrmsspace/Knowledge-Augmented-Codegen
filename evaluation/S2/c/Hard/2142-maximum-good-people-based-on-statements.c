// Source: https://leetcode.com/problems/maximum-good-people-based-on-statements/   |   Difficulty: Hard
//
// Problem Description:
// There are two types of persons:
//
//
// 	The good person: The person who always tells the truth.
// 	The bad person: The person who might tell the truth and might lie.
//
//
// You are given a 0-indexed 2D integer array statements of size n x n that represents the statements made by n people about each other. More specifically, statements[i][j] could be one of the following:
//
//
// 	0 which represents a statement made by person i that person j is a bad person.
// 	1 which represents a statement made by person i that person j is a good person.
// 	2 represents that no statement is made by person i about person j.
//
//
// Additionally, no person ever makes a statement about themselves. Formally, we have that statements[i][i] = 2 for all 0 <= i < n.
//
// Return the maximum number of people who can be good based on the statements made by the n people.
//
// Example:
// Input: statements = [[2,1,2],[1,2,2],[2,0,2]]
// Output: 2
// Explanation: Each person makes a single statement.
// - Person 0 states that person 1 is good.
// - Person 1 states that person 0 is good.
// - Person 2 states that person 1 is bad.
// Let's take person 2 as the key.
// - Assuming that person 2 is a good person:
//     - Based on the statement made by person 2, person 1 is a bad person.
//     - Now we know for sure that person 1 is bad and person 2 is good.
//     - Based on the statement made by person 1, and since person 1 is bad, they could be:
//         - telling the truth. There will be a contradiction in this case and this assumption is invalid.
//         - lying. In this case, person 0 is also a bad person and lied in their statement.
//     - Following that person 2 is a good person, there will be only one good person in the group.
// - Assuming that person 2 is a bad person:
//     - Based on the statement made by person 2, and since person 2 is bad, they could be:
//         - telling the truth. Following this scenario, person 0 and 1 are both bad as explained before.
//             - Following that person 2 is bad but told the truth, there will be no good persons in the group.
//         - lying. In this case person 1 is a good person.
//             - Since person 1 is a good person, person 0 is also a good person.
//             - Following that person 2 is bad and lied, there will be two good persons in the group.
// We can see that at most 2 persons are good in the best case, so we return 2.
// Note that there is more than one way to arrive at this conclusion.
//
// Constraints:
// n == statements.length == statements[i].length
// 	2 <= n <= 15
// 	statements[i][j] is either 0, 1, or 2.
// 	statements[i][i] == 2
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
// - 2-SAT (graph, scc)
//   • When to use: When a problem can be modeled as finding a satisfying assignment for a Boolean formula where each clause contains exactly two literals. It is used to determine if such an assignment exists and to construct one if it does.
//   • Idea: 2-SAT solves the Boolean satisfiability problem for formulas in conjunctive normal form where each clause has exactly two literals. It converts the formula into an implication graph and uses Strongly Connected Components (SCCs) to find a satisfying assignment or determine unsatisfiability in O(N+M) time.
//   • Invariants: Each clause (A OR B) is correctly represented by two implications: (NOT A => B) and (NOT B => A).; The implication graph correctly reflects all logical implications derived from the 2-CNF formula.
//   • Tips: Convert each clause (A OR B) into two implications: (NOT A => B) and (NOT B => A).; Represent each variable X and its negation NOT X as distinct nodes in the implication graph.
//   • Pitfalls: Incorrectly converting clauses to implications, missing one of the two directions.; Failing to handle the critical case where a variable and its negation are in the same SCC.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maximumGood(int** statements, int statementsSize, int* statementsColSize) {
    int n = statementsSize;
    int max_good = 0;

    // Iterate through all possible combinations of good and bad people
    for (int mask = 0; mask < (1 << n); mask++) {
        int good_count = 0;
        int valid = 1;

        // Check if the current combination is valid
        for (int i = 0; i < n; i++) {
            if ((mask & (1 << i)) != 0) { // If person i is good
                good_count++;
                for (int j = 0; j < n; j++) {
                    if (statements[i][j] == 1 && (mask & (1 << j)) == 0) {
                        valid = 0; // Person i says person j is good, but j is bad
                        break;
                    }
                    if (statements[i][j] == 0 && (mask & (1 << j)) != 0) {
                        valid = 0; // Person i says person j is bad, but j is good
                        break;
                    }
                }
            }
            if (!valid) {
                break;
            }
        }

        if (valid) {
            max_good = good_count > max_good ? good_count : max_good;
        }
    }

    return max_good;        
}
