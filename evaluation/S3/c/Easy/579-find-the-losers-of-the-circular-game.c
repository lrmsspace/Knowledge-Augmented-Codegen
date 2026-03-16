// Source: https://leetcode.com/problems/find-the-losers-of-the-circular-game/   |   Difficulty: Easy
//
// Problem Description:
// There are n friends that are playing a game. The friends are sitting in a circle and are numbered from 1 to n in clockwise order. More formally, moving clockwise from the ith friend brings you to the (i+1)th friend for 1 <= i < n, and moving clockwise from the nth friend brings you to the 1st friend.
//
// The rules of the game are as follows:
//
// 1st friend receives the ball.
//
//
// 	After that, 1st friend passes it to the friend who is k steps away from them in the clockwise direction.
// 	After that, the friend who receives the ball should pass it to the friend who is 2 * k steps away from them in the clockwise direction.
// 	After that, the friend who receives the ball should pass it to the friend who is 3 * k steps away from them in the clockwise direction, and so on and so forth.
//
//
// In other words, on the ith turn, the friend holding the ball should pass it to the friend who is i * k steps away from them in the clockwise direction.
//
// The game is finished when some friend receives the ball for the second time.
//
// The losers of the game are friends who did not receive the ball in the entire game.
//
// Given the number of friends, n, and an integer k, return the array answer, which contains the losers of the game in the ascending order.
//
// Example:
// Input: n = 5, k = 2
// Output: [4,5]
// Explanation: The game goes as follows:
// 1) Start at 1st friend and pass the ball to the friend who is 2 steps away from them - 3rd friend.
// 2) 3rd friend passes the ball to the friend who is 4 steps away from them - 2nd friend.
// 3) 2nd friend passes the ball to the friend who is 6 steps away from them  - 3rd friend.
// 4) The game ends as 3rd friend receives the ball for the second time.
//
// Constraints:
// 1 <= k <= n <= 50
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
// - Josephus Problem (number, dp-1d, recursion)
//   • When to use: Used to determine the position of the last remaining person in a circle where every k-th person is eliminated until only one remains. It models sequential removal processes in a circular arrangement.
//   • Idea: The Josephus Problem determines the position of the survivor in a circle of N people, where every K-th person is eliminated. The standard solution uses a recursive relation or dynamic programming, typically achieving O(N) time complexity.
//   • Invariants: The result J(n, k) represents the survivor's original 0-indexed position among n people.; Each recursive step J(n, k) correctly transforms the result from J(n-1, k) based on the k-th elimination.
//   • Tips: Use 0-indexing for a simpler and more elegant recursive formula.; Establish the base case for N=1 (the survivor is always 0 or 1).
//   • Pitfalls: Off-by-one errors when switching between 0-indexing and 1-indexing.; Incorrectly applying the modulo operator, especially with negative results in some languages.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* circularGameLosers(int n, int k, int* returnSize) {
    int* losers = (int*)malloc(n * sizeof(int)); // Allocate maximum possible size
    int* visited = (int*)calloc(n, sizeof(int)); // Track visited friends
    int current = 0; // Start from the first friend (0-indexed)
    int step = 1; // Initial step multiplier

    while (!visited[current]) {
        visited[current] = 1; // Mark current friend as visited
        current = (current + step * k) % n; // Move to the next friend
        step++; // Increment step multiplier
    }

    // Collect losers (friends who were not visited)
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            losers[count++] = i + 1; // Store 1-indexed friend number
        }
    }

    free(visited); // Free the visited array
    *returnSize = count; // Set the return size to the number of losers
    return losers; // Return the array of losers        
}
