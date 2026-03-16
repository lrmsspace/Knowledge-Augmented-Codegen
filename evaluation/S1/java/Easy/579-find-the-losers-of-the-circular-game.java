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
// - Submask Enumeration
//  (number, bitset, enumeration)
//   • When to use: When you need to iterate through all possible submasks of a given bitmask efficiently, typically for problems involving subsets or combinations represented by bits.
//   • Idea: This algorithm efficiently iterates through all submasks of a given bitmask in descending order using a clever bitwise trick. It processes each submask in O(1) time, leading to an overall complexity of O(2^k) where k is the number of set bits in the original mask.
//   • Invariants: Each `s` generated is a valid submask of the original mask `m`.; The value of `s` strictly decreases in each iteration until it reaches 0 (or the loop terminates).
//   • Tips: Always consider processing the submask 0 separately if it's a valid case for your problem.; The iteration naturally generates submasks in strictly descending numerical order.
//   • Pitfalls: Forgetting that the standard loop structure `for (int s = m; s > 0; s = (s - 1) & m)` omits submask 0.; Incorrectly assuming the iteration order is ascending; it is always descending.
// - Minimum Enclosing Circle (geometry, number, simulation)
//   • When to use: When you need to find the smallest circle that contains all given points in a 2D plane, often with a requirement for expected linear time complexity.
//   • Idea: This algorithm iteratively constructs the Minimum Enclosing Circle (MEC) by considering points one by one, potentially updating the circle if a new point lies outside. It achieves an expected linear time complexity, O(N), through randomization.
//   • Invariants: The current circle C is the MEC for the subset of points processed so far.; If C is defined by 1 point p_i, it is the MEC of points processed so far that passes through p_i.
//   • Tips: Randomly shuffle input points to achieve expected linear time complexity.; The Minimum Enclosing Circle is always defined by 2 or 3 points on its boundary.
//   • Pitfalls: A naive implementation without randomization can lead to O(N^3) worst-case time complexity.; Floating-point precision issues can arise in geometric calculations, requiring careful handling.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] circularGameLosers(int n, int k) {
        boolean[] hasReceived = new boolean[n];
        int currentPlayer = 0;
        int step = 1;

        while (!hasReceived[currentPlayer]) {
            hasReceived[currentPlayer] = true;
            currentPlayer = (currentPlayer + step * k) % n;
            step++;
        }

        int losersCount = 0;
        for (boolean received : hasReceived) {
            if (!received) {
                losersCount++;
            }
        }

        int[] losers = new int[losersCount];
        int index = 0;
        for (int i = 0; i < n; i++) {
            if (!hasReceived[i]) {
                losers[index++] = i + 1; // Convert to 1-based index
            }
        }

        return losers;          
    }
}
