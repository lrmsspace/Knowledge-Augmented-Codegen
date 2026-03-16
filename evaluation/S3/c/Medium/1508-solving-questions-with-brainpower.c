// Source: https://leetcode.com/problems/solving-questions-with-brainpower/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed 2D integer array questions where questions[i] = [pointsi, brainpoweri].
//
// The array describes the questions of an exam, where you have to process the questions in order (i.e., starting from question 0) and make a decision whether to solve or skip each question. Solving question i will earn you pointsi points but you will be unable to solve each of the next brainpoweri questions. If you skip question i, you get to make the decision on the next question.
//
//
// 	For example, given questions = [[3, 2], [4, 3], [4, 4], [2, 5]]:
//
// 	
// 		If question 0 is solved, you will earn 3 points but you will be unable to solve questions 1 and 2.
// 		If instead, question 0 is skipped and question 1 is solved, you will earn 4 points but you will be unable to solve questions 2 and 3.
// 	
// 	
//
//
// Return the maximum points you can earn for the exam.
//
// Example:
// Input: questions = [[3,2],[4,3],[4,4],[2,5]]
// Output: 5
// Explanation: The maximum points can be earned by solving questions 0 and 3.
// - Solve question 0: Earn 3 points, will be unable to solve the next 2 questions
// - Unable to solve questions 1 and 2
// - Solve question 3: Earn 2 points
// Total points earned: 3 + 2 = 5. There is no other way to earn 5 or more points.
//
// Constraints:
// 1 <= questions.length <= 105
// 	questions[i].length == 2
// 	1 <= pointsi, brainpoweri <= 105
//
// Helpful references (internal KB):
// - Introduction to Dynamic Programming (array, dp-1d)
//   • When to use: When a problem can be broken down into smaller, overlapping subproblems and an optimal solution to the larger problem can be constructed from optimal solutions to its subproblems. It's suitable for optimizing recursive solutions with repeated computations.
//   • Idea: Dynamic Programming (DP) solves complex problems by breaking them into simpler overlapping subproblems and storing the results to avoid redundant computations. It typically achieves polynomial time complexity, often O(N) or O(N^2) for 1D DP, by trading space for time.
//   • Invariants: dp[i] stores the optimal solution for the subproblem ending at index i.; All dp[j] for j < i have been correctly computed before dp[i] is calculated.
//   • Tips: Clearly define the DP state and its meaning.; Identify the base cases for the recurrence relation.
//   • Pitfalls: Incorrectly defining the DP state or recurrence relation.; Missing or incorrect base cases leading to infinite recursion or wrong results.
// - Knapsack Problem (array, knapsack, dp-1d, dp-2d)
//   • When to use: Use when selecting items, each with a weight and value, to maximize total value within a limited capacity, where each item can be chosen multiple times. It is suitable for problems exhibiting optimal substructure and overlapping subproblems.
//   • Idea: The Knapsack Problem involves selecting items to maximize total value within a fixed capacity. The complete knapsack variant, where items can be taken multiple times, is typically solved using dynamic programming in O(nW) time and O(W) space.
//   • Invariants: For 2D DP `f[i][j]`, it represents the maximum value obtainable using only the first `i` items with a total weight not exceeding `j`.; For 1D DP `dp[j]`, after processing item `i`, it stores the maximum value obtainable with a total weight not exceeding `j`, considering all items up to `i`.
//   • Tips: For the complete knapsack, iterate capacity `j` forwards (from `w_i` to `W`) when using 1D DP to allow multiple selections of the current item.; The 1D DP array `dp[j]` stores the maximum value achievable for exactly capacity `j`.
//   • Pitfalls: Confusing 0-1 knapsack with complete knapsack, especially in the 1D DP iteration direction for capacity.; Incorrectly initializing the DP array, leading to incorrect base cases or propagation.
// - interval-dp (array, interval-dp)
//   • When to use: When a problem involves finding an optimal value for a contiguous range of elements, and solutions for larger ranges can be derived by merging optimal solutions of smaller sub-ranges.
//   • Idea: An extension of dynamic programming where subproblems are defined over contiguous intervals, solving for dp[i][j] by iterating through all possible split points k within [i, j]. This often results in O(N^3) time complexity.
//   • Invariants: dp[i][j] represents the optimal solution for the interval [i, j].; When computing dp[i][j], all subproblems dp[x][y] where y - x + 1 < j - i + 1 are already solved.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length, then by start index.
//   • Pitfalls: Off-by-one errors in interval boundaries or split points.; Incorrect iteration order, leading to uncomputed subproblems.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long mostPoints(int** questions, int questionsSize, int* questionsColSize) {
    long long* dp = (long long*)malloc(sizeof(long long) * questionsSize);
    for (int i = questionsSize - 1; i >= 0; i--) {
        int points = questions[i][0];
        int brainpower = questions[i][1];
        int nextIndex = i + brainpower + 1;
        long long solvePoints = points + (nextIndex < questionsSize ? dp[nextIndex] : 0);
        long long skipPoints = (i + 1 < questionsSize) ? dp[i + 1] : 0;
        dp[i] = solvePoints > skipPoints ? solvePoints : skipPoints;
    }
    long long result = dp[0];
    free(dp);
    return result;      
}
