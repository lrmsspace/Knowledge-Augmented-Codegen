// Source: https://leetcode.com/problems/largest-multiple-of-three/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of digits digits, return the largest multiple of three that can be formed by concatenating some of the given digits in any order. If there is no answer return an empty string.
//
// Since the answer may not fit in an integer data type, return the answer as a string. Note that the returning answer must not contain unnecessary leading zeros.
//
// Example:
// Input: digits = [8,1,9]
// Output: "981"
//
// Constraints:
// 1 <= digits.length <= 104
// 	0 <= digits[i] <= 9
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
// - Linear Diophantine Equation (number, greedy)
//   • When to use: Use when a problem can be solved by making the locally optimal choice at each step, hoping this leads to a globally optimal solution. This strategy is often simpler and faster than dynamic programming.
//   • Idea: The greedy algorithm makes the best choice at each stage with the hope of finding a global optimum, without reconsidering previous choices. Its time complexity is typically O(N log N) or O(N).
//   • Invariants: At each step, the chosen element is the best available according to the greedy criterion.; The partial solution constructed so far remains optimal for the subproblem considered.
//   • Tips: Prove correctness by exchange argument or induction.; Sort input data if it helps identify the greedy choice.
//   • Pitfalls: Failing to prove the greedy choice property.; Making a locally optimal choice that prevents a global optimum.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* largestMultipleOfThree(int* digits, int digitsSize) {
    int count[10] = {0};
    int sum = 0;
    for (int i = 0; i < digitsSize; ++i) {
        count[digits[i]]++;
        sum += digits[i];
    }

    int mod = sum % 3;
    if (mod != 0) {
        /* Try to remove one digit with mod == mod */
        for (int d = mod; d <= 9; d += 3) {
            if (count[d] > 0) {
                count[d]--;
                mod = 0;
                break;
            }
        }
        /* If not possible, remove two digits with mod == 3 - mod */
        if (mod != 0) {
            int toRemove = 2;
            for (int d = 3 - mod; d <= 9; d += 3) {
                while (count[d] > 0 && toRemove > 0) {
                    count[d]--;
                    toRemove--;
                }
                if (toRemove == 0) break;
            }
        }
    }

    /* Construct the result string */
    char *result = (char*)malloc((digitsSize + 1) * sizeof(char));
    if (!result) return NULL;
    int pos = 0;
    for (int d = 9; d >= 0; --d) {
        while (count[d] > 0) {
            result[pos++] = '0' + d;
            count[d]--;
        }
    }
    if (pos == 0) {
        free(result);
        return "";
    }
    result[pos] = '\0';

    /* Handle leading zeros */
    if (result[0] == '0') {
        result[1] = '\0';
    }

    return result;      
}
