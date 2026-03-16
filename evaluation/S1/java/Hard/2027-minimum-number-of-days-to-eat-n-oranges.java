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
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minDays(int n) {
        Map<Integer, Integer> memo = new HashMap<>();
        return helper(n, memo);
    }
    private int helper(int n, Map<Integer, Integer> memo) {
        if (n <= 1) {
            return n;
        }
        if (memo.containsKey(n)) {
            return memo.get(n);
        }
        int daysBy2 = n % 2 + helper(n / 2, memo);
        int daysBy3 = n % 3 + helper(n / 3, memo);
        int result = 1 + Math.min(daysBy2, daysBy3);
        memo.put(n, result);
        return result;  
    }
}
