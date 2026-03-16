// Source: https://leetcode.com/problems/chalkboard-xor-game/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of integers nums represents the numbers written on a chalkboard.
//
// Alice and Bob take turns erasing exactly one number from the chalkboard, with Alice starting first. If erasing a number causes the bitwise XOR of all the elements of the chalkboard to become 0, then that player loses. The bitwise XOR of one element is that element itself, and the bitwise XOR of no elements is 0.
//
// Also, if any player starts their turn with the bitwise XOR of all the elements of the chalkboard equal to 0, then that player wins.
//
// Return true if and only if Alice wins the game, assuming both players play optimally.
//
// Example:
// Input: nums = [1,1,2]
// Output: false
// Explanation: 
// Alice has two choices: erase 1 or erase 2. 
// If she erases 1, the nums array becomes [1, 2]. The bitwise XOR of all the elements of the chalkboard is 1 XOR 2 = 3. Now Bob can remove any element he wants, because Alice will be the one to erase the last element and she will lose. 
// If Alice erases 2 first, now nums become [1, 1]. The bitwise XOR of all the elements of the chalkboard is 1 XOR 1 = 0. Alice will lose.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	0 <= nums[i] < 216
//
// Helpful references (internal KB):
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
// - Sprague-Grundy theorem. Nim (array, number, game-theory, prefix-xor)
//   • When to use: Use when analyzing impartial games with perfect information and no draws, especially to determine winning/losing states or to find a winning strategy. It's particularly useful for games that can be reduced to Nim.
//   • Idea: The Sprague-Grundy theorem states that every impartial game under the normal play convention is equivalent to a Nim pile of a certain size (its nim-value or grundy number). For Nim, a position is a winning position if and only if the XOR sum of all pile sizes is non-zero, allowing for O(N) classification.
//   • Invariants: The XOR sum of the pile sizes (nim-sum) represents the game's current nim-value.; If the nim-sum is zero, any valid move will result in a non-zero nim-sum for the opponent.
//   • Tips: Understand the definition of impartial games and their properties.; Calculate the XOR sum of game components to determine the nim-sum.
//   • Pitfalls: Confusing impartial games with partisan games where players have different moves.; Incorrectly calculating the XOR sum, leading to wrong state classifications.
// - Extended Euclidean Algorithm (number, gcd, simulation)
//   • When to use: Use this algorithm to find integer coefficients x and y that satisfy Bézout's identity (ax + by = gcd(a,b)). It is also essential for computing modular multiplicative inverses and solving linear Diophantine equations.
//   • Idea: The Extended Euclidean Algorithm computes the greatest common divisor (GCD) of two integers 'a' and 'b', and simultaneously finds integer coefficients 'x' and 'y' such that 'ax + by = gcd(a,b)'. It operates in O(log(min(a,b))) time complexity.
//   • Invariants: x * (initial a) + y * (initial b) = current_a_value; x_1 * (initial a) + y_1 * (initial b) = current_b_value
//   • Tips: Can be implemented using either a recursive or an iterative approach.; The algorithm correctly handles negative integer inputs.
//   • Pitfalls: Incorrectly defining base cases in recursive implementations can lead to errors.; Potential for integer overflow if coefficients x or y become extremely large, though uncommon.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public boolean xorGame(int[] nums) {
        int xor = 0;
        for (int num : nums) {
            xor ^= num;
        }
        return xor == 0 || nums.length % 2 == 0;            
    }
}
