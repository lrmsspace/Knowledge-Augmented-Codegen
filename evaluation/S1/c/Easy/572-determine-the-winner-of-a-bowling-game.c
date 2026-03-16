// Source: https://leetcode.com/problems/determine-the-winner-of-a-bowling-game/   |   Difficulty: Easy
//
// Problem Description:
// You are given two 0-indexed integer arrays player1 and player2, representing the number of pins that player 1 and player 2 hit in a bowling game, respectively.
//
// The bowling game consists of n turns, and the number of pins in each turn is exactly 10.
//
// Assume a player hits xi pins in the ith turn. The value of the ith turn for the player is:
//
//
// 	2xi if the player hits 10 pins in either (i - 1)th or (i - 2)th turn.
// 	Otherwise, it is xi.
//
//
// The score of the player is the sum of the values of their n turns.
//
// Return
//
//
// 	1 if the score of player 1 is more than the score of player 2,
// 	2 if the score of player 2 is more than the score of player 1, and
// 	0 in case of a draw.
//
// Example:
// Input: player1 = [5,10,3,2], player2 = [6,5,7,3]
//
// Output: 1
//
// Explanation:
//
// The score of player 1 is 5 + 10 + 2*3 + 2*2 = 25.
//
// The score of player 2 is 6 + 5 + 7 + 3 = 21.
//
// Constraints:
// n == player1.length == player2.length
// 	1 <= n <= 1000
// 	0 <= player1[i], player2[i] <= 10
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
// - Fibonacci Numbers (number, greedy, enumeration)
//   • When to use: When you need a unique, non-ambiguous binary representation of positive integers based on Fibonacci numbers, ensuring no two consecutive Fibonacci numbers are used in the sum.
//   • Idea: This algorithm encodes a positive integer into a unique binary string by greedily finding its Zeckendorf representation (sum of non-consecutive Fibonacci numbers). The encoding process typically involves iterating through Fibonacci numbers, resulting in a logarithmic time complexity relative to the input number's magnitude.
//   • Invariants: The remaining value 'n' to be encoded is always non-negative.; The partial binary code constructed so far represents a valid Zeckendorf sum of non-consecutive Fibonacci numbers.
//   • Tips: Precompute Fibonacci numbers up to a certain limit to optimize lookups.; Always start with the largest Fibonacci number less than or equal to the target value.
//   • Pitfalls: Incorrectly handling the base cases for small numbers like 1 or 2.; Forgetting to append the mandatory final '1' bit to the codeword.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int isWinner(int* player1, int player1Size, int* player2, int player2Size) {
    int score1 = 0, score2 = 0;

    for (int i = 0; i < player1Size; i++) {
        int val1 = player1[i];
        int val2 = player2[i];

        if (i > 0 && player1[i - 1] == 10) {
            val1 *= 2;
        } else if (i > 1 && player1[i - 2] == 10) {
            val1 *= 2;
        }

        if (i > 0 && player2[i - 1] == 10) {
            val2 *= 2;
        } else if (i > 1 && player2[i - 2] == 10) {
            val2 *= 2;
        }

        score1 += val1;
        score2 += val2;
    }

    if (score1 > score2) {
        return 1;
    } else if (score2 > score1) {
        return 2;
    } else {
        return 0;
    }       
}
