// Source: https://leetcode.com/problems/minimum-number-of-days-to-eat-n-oranges/   |   Difficulty: Hard
//
// Problem Description:
// There are n oranges in the kitchen and you decided to eat some of these oranges every day as follows:
//
//
// 	Eat one orange.
// 	If the number of remaining oranges n is divisible by 2 then you can eat n / 2 oranges.
// 	If the number of remaining oranges n is divisible by 3 then you can eat 2 * (n / 3) oranges.
//
//
// You can only choose one of the actions per day.
//
// Given the integer n, return the minimum number of days to eat n oranges.
//
// Example:
// Input: n = 10
// Output: 4
// Explanation: You have 10 oranges.
// Day 1: Eat 1 orange,  10 - 1 = 9.  
// Day 2: Eat 6 oranges, 9 - 2*(9/3) = 9 - 6 = 3. (Since 9 is divisible by 3)
// Day 3: Eat 2 oranges, 3 - 2*(3/3) = 3 - 2 = 1. 
// Day 4: Eat the last orange  1 - 1  = 0.
// You need at least 4 days to eat the 10 oranges.
//
// Constraints:
// 1 <= n <= 2 * 109
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minDays(int n) {
    /* Use memoization to store results for already computed n */
    #define MAX_MEMO 2000000000
    static int *memo = NULL;
    if (!memo) {
        memo = (int*)calloc(MAX_MEMO / 2 + 1, sizeof(int));
        if (!memo) return -1; /* Memory allocation failed */
    }

    if (n <= 1) return n;
    if (n < MAX_MEMO && memo[n / 2] != 0) return memo[n / 2];

    int daysEatOne = 1 + minDays(n - 1);
    int daysEatHalf = (n % 2 == 0) ? (1 + minDays(n / 2)) : (2 + minDays(n / 2));
    int daysEatTwoThirds = (n % 3 == 0) ? (1 + minDays(n / 3)) : (2 + minDays(n / 3));

    int result = daysEatOne;
    if (daysEatHalf < result) result = daysEatHalf;
    if (daysEatTwoThirds < result) result = daysEatTwoThirds;

    if (n < MAX_MEMO) memo[n / 2] = result;

    return result;      
}
