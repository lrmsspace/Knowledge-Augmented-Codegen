// Source: https://leetcode.com/problems/distribute-candies-to-people/   |   Difficulty: Easy
//
// Problem Description:
// We distribute some number of candies, to a row of n = num_people people in the following way:
//
// We then give 1 candy to the first person, 2 candies to the second person, and so on until we give n candies to the last person.
//
// Then, we go back to the start of the row, giving n + 1 candies to the first person, n + 2 candies to the second person, and so on until we give 2 * n candies to the last person.
//
// This process repeats (with us giving one more candy each time, and moving to the start of the row after we reach the end) until we run out of candies.  The last person will receive all of our remaining candies (not necessarily one more than the previous gift).
//
// Return an array (of length num_people and sum candies) that represents the final distribution of candies.
//
// Example:
// Input: candies = 7, num_people = 4
// Output: [1,2,3,1]
// Explanation:
// On the first turn, ans[0] += 1, and the array is [1,0,0,0].
// On the second turn, ans[1] += 2, and the array is [1,2,0,0].
// On the third turn, ans[2] += 3, and the array is [1,2,3,0].
// On the fourth turn, ans[3] += 1 (because there is only one candy left), and the final array is [1,2,3,1].
//
// Constraints:
// 1 <= candies <= 10^9
// 	1 <= num_people <= 1000
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Continued fractions (number, array, enumeration)
//   • When to use: Use when representing real numbers as a sequence of integers for rational approximation, or when analyzing properties of irrational numbers. It's also useful for solving certain Diophantine equations and Pell's equation.
//   • Idea: Continued fractions represent a real number as a sum of an integer and the reciprocal of another number, which is then represented in the same way. This process generates a sequence of integers, and its complexity depends on the desired precision or the number's nature.
//   • Invariants: The current integer term `a_i` is `floor(x_i)`, where `x_i` is the current real value being expanded.; The next real value `x_{i+1}` is `1 / (x_i - a_i)` if `x_i - a_i` is non-zero.
//   • Tips: Understand the recursive definition of continued fractions.; The Euclidean algorithm forms the basis for computing finite continued fractions.
//   • Pitfalls: Floating-point precision issues can severely limit accuracy for irrational numbers.; Misinterpreting convergents as exact values instead of approximations.
// - Josephus Problem (number, simulation, recursion)
//   • When to use: Use when determining the survivor's position in a circular game where every k-th person is eliminated, especially for large N where direct simulation is too slow.
//   • Idea: This algorithm finds the position of the last remaining person in the Josephus problem by iteratively reducing the problem size using a recursive formula and modulo arithmetic. It achieves an optimized time complexity of O(k log n).
//   • Invariants: The number of remaining elements decreases in each recursive step.; The relative order of the remaining elements is preserved throughout the process.
//   • Tips: Handle the base case where n < k separately to avoid infinite loops or incorrect calculations.; Use 0-indexing for simpler modulo arithmetic in the recursive formulas.
//   • Pitfalls: Incorrectly handling index shifts after elements are removed can lead to wrong results.; Forgetting the base case n < k can lead to infinite recursion or incorrect behavior.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] distributeCandies(int candies, int num_people) {
        int[] distribution = new int[num_people];
        int candyCount = 1;
        int index = 0;

        while (candies > 0) {
            distribution[index] += Math.min(candyCount, candies);
            candies -= candyCount;
            candyCount++;
            index = (index + 1) % num_people; // Move to the next person
        }

        return distribution;            
    }
}
