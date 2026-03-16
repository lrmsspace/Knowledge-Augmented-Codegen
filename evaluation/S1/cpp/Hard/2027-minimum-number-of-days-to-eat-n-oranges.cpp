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
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minDays(int n) {
        unordered_map<int, int> memo;

        function<int(int)> dfs = [&](int oranges) -> int {
            if (oranges <= 1) return oranges;
            if (memo.count(oranges)) return memo[oranges];

            int daysBy2 = oranges % 2 + dfs(oranges / 2);
            int daysBy3 = oranges % 3 + dfs(oranges / 3);

            int result = 1 + min(daysBy2, daysBy3);
            memo[oranges] = result;
            return result;
        };

        return dfs(n);          
    }
};
