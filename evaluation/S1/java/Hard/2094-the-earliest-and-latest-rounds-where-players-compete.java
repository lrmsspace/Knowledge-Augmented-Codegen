// Source: https://leetcode.com/problems/the-earliest-and-latest-rounds-where-players-compete/   |   Difficulty: Hard
//
// Problem Description:
// There is a tournament where n players are participating. The players are standing in a single row and are numbered from 1 to n based on their initial standing position (player 1 is the first player in the row, player 2 is the second player in the row, etc.).
//
// The tournament consists of multiple rounds (starting from round number 1). In each round, the ith player from the front of the row competes against the ith player from the end of the row, and the winner advances to the next round. When the number of players is odd for the current round, the player in the middle automatically advances to the next round.
//
//
// 	For example, if the row consists of players 1, 2, 4, 6, 7
//
// 	
// 		Player 1 competes against player 7.
// 		Player 2 competes against player 6.
// 		Player 4 automatically advances to the next round.
// 	
// 	
//
//
// After each round is over, the winners are lined back up in the row based on the original ordering assigned to them initially (ascending order).
//
// The players numbered firstPlayer and secondPlayer are the best in the tournament. They can win against any other player before they compete against each other. If any two other players compete against each other, either of them might win, and thus you may choose the outcome of this round.
//
// Given the integers n, firstPlayer, and secondPlayer, return an integer array containing two values, the earliest possible round number and the latest possible round number in which these two players will compete against each other, respectively.
//
// Example:
// Input: n = 11, firstPlayer = 2, secondPlayer = 4
// Output: [3,4]
// Explanation:
// One possible scenario which leads to the earliest round number:
// First round: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
// Second round: 2, 3, 4, 5, 6, 11
// Third round: 2, 3, 4
// One possible scenario which leads to the latest round number:
// First round: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
// Second round: 1, 2, 3, 4, 5, 6
// Third round: 1, 2, 4
// Fourth round: 2, 4
//
// Constraints:
// 2 <= n <= 28
// 	1 <= firstPlayer < secondPlayer <= n
//
// Helpful references (internal KB):
// - Games on arbitrary graphs (graph, array, dfs, game-theory)
//   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
//   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
//   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
//   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
//   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Scheduling jobs on two machines (array, number, simulation, enumeration)
//   • When to use: Use when determining the optimal sequence of jobs to minimize the total completion time (makespan) on two machines, with a fixed processing order (machine 1 then machine 2) for all jobs.
//   • Idea: This problem involves ordering N jobs, each with two processing times (one for each machine), to minimize the overall makespan. Johnson's rule provides an optimal greedy solution for this specific two-machine flow shop problem in O(N log N) or O(N) time.
//   • Invariants: All jobs processed so far maintain the optimal relative order determined by Johnson's rule.; The current makespan is the minimum possible for the jobs already scheduled.
//   • Tips: Sort jobs based on Johnson's rule criteria: jobs with min(a_i, b_i).; Prioritize jobs with shorter machine 1 times or longer machine 2 times for early scheduling.
//   • Pitfalls: Applying Johnson's rule to problems with more than two machines, where it is not optimal.; Incorrectly sorting jobs within the two partitioned sets.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] earliestAndLatest(int n, int firstPlayer, int secondPlayer) {
        int earliest = 1, latest = 1;
        int left = firstPlayer - 1;
        int right = n - secondPlayer;

        while (left + right + 1 > 1) {
            if (left + right + 1 <= 2) {
                break;
            }

            int totalMatches = (left + right + 1) / 2;
            int mid = (left + right + 1) % 2;

            int newLeft = Math.min(left, totalMatches - 1);
            int newRight = Math.min(right, totalMatches - 1);

            earliest++;
            left = newLeft;
            right = newRight;
        }

        left = firstPlayer - 1;
        right = n - secondPlayer;

        while (left + right + 1 > 1) {
            int totalMatches = (left + right + 1) / 2;
            int mid = (left + right + 1) % 2;

            int newLeft = Math.min(left, totalMatches - 1);
            int newRight = Math.min(right, totalMatches - 1);

            latest++;
            left = newLeft;
            right = newRight;
        }

        return new int[]{earliest, latest};         
    }
}
