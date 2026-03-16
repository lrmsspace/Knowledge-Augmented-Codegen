// Source: https://leetcode.com/problems/sum-game/   |   Difficulty: Medium
//
// Problem Description:
// Alice and Bob take turns playing a game, with Alice starting first.
//
// You are given a string num of even length consisting of digits and '?' characters. On each turn, a player will do the following if there is still at least one '?' in num:
//
//
// 	Choose an index i where num[i] == '?'.
// 	Replace num[i] with any digit between '0' and '9'.
//
//
// The game ends when there are no more '?' characters in num.
//
// For Bob to win, the sum of the digits in the first half of num must be equal to the sum of the digits in the second half. For Alice to win, the sums must not be equal.
//
//
// 	For example, if the game ended with num = "243801", then Bob wins because 2+4+3 = 8+0+1. If the game ended with num = "243803", then Alice wins because 2+4+3 != 8+0+3.
//
//
// Assuming Alice and Bob play optimally, return true if Alice will win and false if Bob will win.
//
// Example:
// Input: num = "5023"
// Output: false
// Explanation: There are no moves to be made.
// The sum of the first half is equal to the sum of the second half: 5 + 0 = 2 + 3.
//
// Constraints:
// 2 <= num.length <= 105
// 	num.length is even.
// 	num consists of only digits and '?'.
//
// Helpful references (internal KB):
// - Finding repetitions (string, array, z-function, enumeration)
//   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
//   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
//   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
//   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
//   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool sumGame(char* num) {
    int n = strlen(num);
    int leftSum = 0, rightSum = 0, leftQ = 0, rightQ = 0;

    for (int i = 0; i < n / 2; i++) {
        if (num[i] == '?') {
            leftQ++;
        } else {
            leftSum += num[i] - '0';
        }
    }

    for (int i = n / 2; i < n; i++) {
        if (num[i] == '?') {
            rightQ++;
        } else {
            rightSum += num[i] - '0';
        }
    }

    // Alice wins if the difference in sums cannot be balanced by the remaining '?' characters
    return (leftSum + leftQ * 9) != (rightSum + rightQ * 9);        
}
