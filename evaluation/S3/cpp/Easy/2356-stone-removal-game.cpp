// Source: https://leetcode.com/problems/stone-removal-game/   |   Difficulty: Easy
//
// Problem Description:
// Alice and Bob are playing a game where they take turns removing stones from a pile, with Alice going first.
//
//
// 	Alice starts by removing exactly 10 stones on her first turn.
// 	For each subsequent turn, each player removes exactly 1 fewer stone than the previous opponent.
//
//
// The player who cannot make a move loses the game.
//
// Given a positive integer n, return true if Alice wins the game and false otherwise.
//
// Example:
// Input: n = 12
//
// Output: true
//
// Explanation:
//
//
// 	Alice removes 10 stones on her first turn, leaving 2 stones for Bob.
// 	Bob cannot remove 9 stones, so Alice wins.
//
// Constraints:
// 1 <= n <= 50
//
// Helpful references (internal KB):
// - Josephus Problem (number, simulation, recursion)
//   • When to use: Use when determining the survivor's position in a circular game where every k-th person is eliminated, especially for large N where direct simulation is too slow.
//   • Idea: This algorithm finds the position of the last remaining person in the Josephus problem by iteratively reducing the problem size using a recursive formula and modulo arithmetic. It achieves an optimized time complexity of O(k log n).
//   • Invariants: The number of remaining elements decreases in each recursive step.; The relative order of the remaining elements is preserved throughout the process.
//   • Tips: Handle the base case where n < k separately to avoid infinite loops or incorrect calculations.; Use 0-indexing for simpler modulo arithmetic in the recursive formulas.
//   • Pitfalls: Incorrectly handling index shifts after elements are removed can lead to wrong results.; Forgetting the base case n < k can lead to infinite recursion or incorrect behavior.
// - Josephus Problem (number, recursion, counting)
//   • When to use: Use when simulating a circular elimination process with a fixed step size, especially when seeking the survivor's position. It's particularly efficient for specific step sizes like two.
//   • Idea: The Josephus Problem determines the last remaining position in a circular arrangement after elements are eliminated at fixed intervals. The recursive solution for a step size of two has a logarithmic time complexity, O(log N), due to its divide-and-conquer nature.
//   • Invariants: The number of participants N is always positive in each recursive subproblem.; The returned position is always within the valid range [0, current N-1] (or [1, current N]).
//   • Tips: Base cases are crucial for recursive solutions, typically for N=1.; Observe patterns for specific step sizes, especially k=2, which has a simpler formula.
//   • Pitfalls: Off-by-one errors when converting between 0-indexed and 1-indexed results.; Incorrectly applying the position 'shift' after elements are eliminated in subproblems.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool canAliceWin(int n) {
        // Alice can win if the number of stones is 10 or less, as she can take all and win immediately.
        if (n <= 10) {
            return true;
        }
        // For n > 10, we need to determine if Alice can force a win by leaving Bob with a losing position.
        // The sequence of stones removed is: 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 (Alice's moves)
        // Bob's moves will be: 9, 8, 7, 6, 5, 4, 3, 2, 1 (Bob's moves)
        // After Alice's first move of taking 10 stones, the game reduces to a smaller problem where Bob starts with n-10 stones.
        // If Bob can win from n-10 stones by following the same pattern (taking one less than Alice), then Alice loses.
        // This creates a pattern where Alice wins if n-10 is not a winning position for Bob.
        
        // We can simulate the game or use a mathematical approach to determine the winning positions.
        
        // A simple simulation approach:
        int aliceStones = 10; // Alice takes 10 on her first move
        int bobStones = aliceStones - 1; // Bob takes one less than Alice
        int currentPlayer = -1; // -1 for Alice's turn after the first move
        
        while (n > aliceStones) {
            n -= aliceStones; // Alice takes her turn
            if (n <= bobStones) {
                return true; // Bob cannot take his turn, Alice wins
            }
            n -= bobStones; // Bob takes his turn
            if (n <= aliceStones) {
                return false; // Alice cannot take her next turn, Bob wins
            }
            aliceStones--; // Next time Alice will take one less
            bobStones--;   // Next time Bob will take one less
        }
        
        return false; // If we exit the loop without returning, it means Bob wins           
    }
};
