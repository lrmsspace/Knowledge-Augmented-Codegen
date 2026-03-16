// Source: https://leetcode.com/problems/minimum-operations-to-make-a-special-number/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed string num representing a non-negative integer.
//
// In one operation, you can pick any digit of num and delete it. Note that if you delete all the digits of num, num becomes 0.
//
// Return the minimum number of operations required to make num special.
//
// An integer x is considered special if it is divisible by 25.
//
// Example:
// Input: num = "2245047"
// Output: 2
// Explanation: Delete digits num[5] and num[6]. The resulting number is "22450" which is special since it is divisible by 25.
// It can be shown that 2 is the minimum number of operations required to get a special number.
//
// Constraints:
// 1 <= num.length <= 100
// 	num only consists of digits '0' through '9'.
// 	num does not contain any leading zeros.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumOperations(char* num) {
    int len = 0;
    while (num[len] != '\0') {
        len++;
    }

    int min_ops = len; // Initialize with maximum possible operations

    // Check for each of the special endings: "00", "25", "50", "75"
    const char* endings[] = {"00", "25", "50", "75"};
    for (int e = 0; e < 4; e++) {
        const char* ending = endings[e];
        int ops = 0;
        int pos1 = -1, pos2 = -1;

        // Find the position of the last digit of the ending
        for (int i = len - 1; i >= 0; i--) {
            if (num[i] == ending[1]) {
                pos2 = i;
                break;
            }
        }
        if (pos2 == -1) continue; // Ending digit not found

        // Find the position of the first digit of the ending before pos2
        for (int i = pos2 - 1; i >= 0; i--) {
            if (num[i] == ending[0]) {
                pos1 = i;
                break;
            }
        }
        if (pos1 == -1) continue; // Starting digit not found

        // Calculate operations needed to bring pos1 and pos2 to the end
        ops += (len - 1 - pos2); // Move second digit to the end
        ops += (len - 2 - pos1); // Move first digit to second last position

        // Adjust for any digits that were between pos1 and pos2
        ops -= (pos2 - pos1 - 1);

        if (ops < min_ops) {
            min_ops = ops;
        }
    }

    return min_ops;     
}
