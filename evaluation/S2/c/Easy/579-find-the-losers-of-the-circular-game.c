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
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
// - Euler's totient function
//  (array, number, enumeration)
//   • When to use: Use when needing to count positive integers up to n that are relatively prime to n. It is also efficient for computing totient values for all numbers in a given range.
//   • Idea: Euler's totient function, φ(n), counts positive integers less than or equal to n that are relatively prime to n. It can be computed for a single n in O(sqrt(n)) using prime factorization, or for all numbers up to N in O(N log log N) using a sieve-like algorithm.
//   • Invariants: phi[i] stores the current totient value for i, which is i initially, then updated by (1 - 1/p) for each prime p dividing i.; After iterating through all primes p up to sqrt(N), phi[i] holds the correct totient value for all i <= N.
//   • Tips: For a single n, compute φ(n) using its prime factorization.; For all φ(i) up to N, use a sieve approach similar to Sieve of Eratosthenes.
//   • Pitfalls: Confusing 'relatively prime' with 'prime number'.; Applying the multiplicative property incorrectly when numbers share common factors.
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
    int* losers = (int*)malloc(n * sizeof(int));
    int* visited = (int*)calloc(n, sizeof(int)); // Track who has received the ball
    int current = 0; // Start with the first friend (0-indexed)
    int step = 1; // Step multiplier

    while (!visited[current]) {
        visited[current] = 1; // Mark the current friend as having received the ball
        current = (current + step * k) % n; // Move to the next friend
        step++; // Increment the step multiplier
    }

    // Collect losers (friends who never received the ball)
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            losers[index++] = i + 1; // Convert back to 1-indexed
        }
    }

    *returnSize = index; // Set the return size to the number of losers
    return losers;      
}
