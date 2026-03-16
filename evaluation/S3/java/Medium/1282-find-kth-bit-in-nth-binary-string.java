// Source: https://leetcode.com/problems/find-kth-bit-in-nth-binary-string/   |   Difficulty: Medium
//
// Problem Description:
// Given two positive integers n and k, the binary string Sn is formed as follows:
//
//
// 	S1 = "0"
// 	Si = Si - 1 + "1" + reverse(invert(Si - 1)) for i > 1
//
//
// Where + denotes the concatenation operation, reverse(x) returns the reversed string x, and invert(x) inverts all the bits in x (0 changes to 1 and 1 changes to 0).
//
// For example, the first four strings in the above sequence are:
//
//
// 	S1 = "0"
// 	S2 = "011"
// 	S3 = "0111001"
// 	S4 = "011100110110001"
//
//
// Return the kth bit in Sn. It is guaranteed that k is valid for the given n.
//
// Example:
// Input: n = 3, k = 1
// Output: "0"
// Explanation: S3 is "0111001".
// The 1st bit is "0".
//
// Constraints:
// 1 <= n <= 20
// 	1 <= k <= 2n - 1
//
// Helpful references (internal KB):
// - Gray code (number, simulation)
//   • When to use: Use when generating a sequence of numbers where adjacent values must differ by only one bit, or for error detection in digital systems. It is also useful for certain combinatorial problems.
//   • Idea: Gray code is a binary numeral system where two successive values differ in exactly one bit position. It can be generated efficiently using bitwise operations in O(1) time per code, or O(N) for N codes.
//   • Invariants: The number of bits in the generated Gray code G(n) is equal to the number of bits in the input binary n.; G(0) is always 0, and G(1) is always 1.
//   • Tips: The most common formula for converting binary n to Gray code G(n) is G(n) = n ^ (n >> 1).; To convert Gray code G(n) back to binary n, use a series of XOR operations: n = G(n) ^ (G(n) >> 1) ^ (G(n) >> 2) ^ ... until zero.
//   • Pitfalls: Confusing Gray code with standard binary representation, which can have multiple bit changes between successive numbers.; Incorrectly implementing the conversion formulas, especially the Gray to binary conversion.
// - Josephus Problem (number, recursion, counting)
//   • When to use: Use when simulating a circular elimination process with a fixed step size, especially when seeking the survivor's position. It's particularly efficient for specific step sizes like two.
//   • Idea: The Josephus Problem determines the last remaining position in a circular arrangement after elements are eliminated at fixed intervals. The recursive solution for a step size of two has a logarithmic time complexity, O(log N), due to its divide-and-conquer nature.
//   • Invariants: The number of participants N is always positive in each recursive subproblem.; The returned position is always within the valid range [0, current N-1] (or [1, current N]).
//   • Tips: Base cases are crucial for recursive solutions, typically for N=1.; Observe patterns for specific step sizes, especially k=2, which has a simpler formula.
//   • Pitfalls: Off-by-one errors when converting between 0-indexed and 1-indexed results.; Incorrectly applying the position 'shift' after elements are eliminated in subproblems.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public char findKthBit(int n, int k) {
        if (n == 1) {
            return '0';
        }
        int mid = (1 << (n - 1)) / 2; // Length of S(n-1) is 2^(n-1) - 1, so mid is (length + 1) / 2
        if (k == mid) {
            return '1'; // The middle character is always '1'
        } else if (k < mid) {
            return findKthBit(n - 1, k); // The first half is S(n-1)
        } else {
            // The second half is reverse(invert(S(n-1)))
            // To find the corresponding character in S(n-1), we need to calculate the index
            int correspondingIndex = mid - (k - mid); // This gives us the index in S(n-1)
            char correspondingChar = findKthBit(n - 1, correspondingIndex);
            return correspondingChar == '0' ? '1' : '0'; // Invert the character
        }           
    }
}
