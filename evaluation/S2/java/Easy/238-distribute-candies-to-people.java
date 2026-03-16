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
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Discrete Logarithm (array, number, binary-search, mod-exp)
//   • When to use: Use when solving for the exponent 'x' in the modular equation a^x = b (mod m), especially when 'm' is large and a and m are coprime. It's suitable for finding a solution within O(sqrt(m) log m) time.
//   • Idea: This algorithm, also known as Baby-step Giant-step, finds the smallest non-negative integer 'x' satisfying a^x = b (mod m) using a meet-in-the-middle approach. It achieves a time complexity of O(sqrt(m) log m).
//   • Invariants: The map stores (a^q mod m, q) for all baby steps q in [0, n-1].; For each giant step p, a^(np) mod m is correctly computed.
//   • Tips: Choose 'n' as ceil(sqrt(m)) for balanced steps.; Use a hash map to store baby steps for O(1) average lookup.
//   • Pitfalls: Incorrect choice of 'n' can lead to suboptimal time complexity.; Failure to check if 'a' and 'm' are coprime may yield no solution or incorrect results.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] distributeCandies(int candies, int num_people) {
        int[] ans = new int[num_people];
        int i = 0;
        while (candies > 0) {
            ans[i % num_people] += Math.min(candies, i + 1);
            candies -= i + 1;
            i++;
        }
        return ans;         
    }
}
