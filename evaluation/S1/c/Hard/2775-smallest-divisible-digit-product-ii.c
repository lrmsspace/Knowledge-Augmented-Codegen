// Source: https://leetcode.com/problems/smallest-divisible-digit-product-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string num which represents a positive integer, and an integer t.
//
// A number is called zero-free if none of its digits are 0.
//
// Return a string representing the smallest zero-free number greater than or equal to num such that the product of its digits is divisible by t. If no such number exists, return "-1".
//
// Example:
// Input: num = "1234", t = 256
//
// Output: "1488"
//
// Explanation:
//
// The smallest zero-free number that is greater than 1234 and has the product of its digits divisible by 256 is 1488, with the product of its digits equal to 256.
//
// Constraints:
// 2 <= num.length <= 2 * 105
// 	num consists only of digits in the range ['0', '9'].
// 	num does not contain leading zeros.
// 	1 <= t <= 1014
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Primality tests (number, enumeration, simulation)
//   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
//   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
//   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
//   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
//   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use to efficiently represent all suffixes of a string in a compressed form, ideal for various string problems like pattern matching or counting distinct substrings.
//   • Idea: A suffix automaton is a minimal Deterministic Finite Automaton (DFA) that accepts all suffixes of a given string, offering O(N) time construction and O(N) memory complexity.
//   • Invariants: Every state in the automaton represents a set of substrings of the original string.; Each state's longest path from the initial state corresponds to its longest string.
//   • Tips: Understand the definition of states and transitions, and their relationship to substrings.; Leverage its linear time and space complexity for efficient string processing on large inputs.
//   • Pitfalls: The construction algorithm can be complex and challenging to implement correctly.; Debugging state transitions, suffix links, and their properties requires careful attention.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* smallestNumber(char* num, long long t) {
    // Check if t has any prime factors greater than 7
    long long tempT = t;
    for (long long p = 2; p * p <= tempT; ++p) {
        if (tempT % p == 0) {
            if (p > 7) return "-1";
            while (tempT % p == 0) {
                tempT /= p;
            }
        }
    }
    if (tempT > 7) return "-1";

    // Count the required prime factors
    int count[8] = {0}; // count[2], count[3], count[5], count[7]
    tempT = t;
    while (tempT % 2 == 0) { count[2]++; tempT /= 2; }
    while (tempT % 3 == 0) { count[3]++; tempT /= 3; }
    while (tempT % 5 == 0) { count[5]++; tempT /= 5; }
    while (tempT % 7 == 0) { count[7]++; tempT /= 7; }

    // Build the smallest number from the required prime factors
    char result[200005];
    int pos = 0;

    // Function to append digit to result
    void appendDigit(int digit) {
        result[pos++] = '0' + digit;
    }

    // Use digits to cover prime factors
    while (count[7] > 0) { appendDigit(7); count[7]--; }
    while (count[5] > 0) { appendDigit(5); count[5]--; }
    while (count[3] >= 2) { appendDigit(9); count[3] -= 2; }
    while (count[3] > 0 && count[2] >= 1) { appendDigit(6); count[3]--; count[2]--; }
    while (count[3] > 0) { appendDigit(3); count[3]--; }
    while (count[2] >= 3) { appendDigit(8); count[2] -= 3; }
    while (count[2] >= 2) { appendDigit(4); count[2] -= 2; }
    while (count[2] > 0) { appendDigit(2); count[2]--; }    
    result[pos] = '\0';
    // Sort the result to get the smallest number
    qsort(result, pos, sizeof(char), (int (*)(const void*, const void*))strcmp);
    // Ensure the result is greater than or equal to num
    if (strlen(result) < strlen(num) || (strlen(result) == strlen(num)
        && strcmp(result, num) < 0)) {
        return "-1";
    }   
    char* finalResult = (char*)malloc((pos + 1) * sizeof(char));
    strcpy(finalResult, result);
    return finalResult;
}
