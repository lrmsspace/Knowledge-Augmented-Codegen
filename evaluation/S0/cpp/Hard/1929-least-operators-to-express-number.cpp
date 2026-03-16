// Source: https://leetcode.com/problems/least-operators-to-express-number/   |   Difficulty: Hard
//
// Problem Description:
// Given a single positive integer x, we will write an expression of the form x (op1) x (op2) x (op3) x ... where each operator op1, op2, etc. is either addition, subtraction, multiplication, or division (+, -, *, or /). For example, with x = 3, we might write 3 * 3 / 3 + 3 - 3 which is a value of 3.
//
// When writing such an expression, we adhere to the following conventions:
//
//
// 	The division operator (/) returns rational numbers.
// 	There are no parentheses placed anywhere.
// 	We use the usual order of operations: multiplication and division happen before addition and subtraction.
// 	It is not allowed to use the unary negation operator (-). For example, "x - x" is a valid expression as it only uses subtraction, but "-x + x" is not because it uses negation.
//
//
// We would like to write an expression with the least number of operators such that the expression equals the given target. Return the least number of operators used.
//
// Example:
// Input: x = 3, target = 19
// Output: 5
// Explanation: 3 * 3 + 3 * 3 + 3 / 3.
// The expression contains 5 operations.
//
// Constraints:
// 2 <= x <= 100
// 	1 <= target <= 2 * 108
//

class Solution {
public:
    int leastOpsExpressTarget(int x, int target) {
        vector<int> digits;
        while (target > 0) {
            digits.push_back(target % x);
            target /= x;
        }
        
        int n = digits.size();
        vector<vector<int>> dp(n + 1, vector<int>(2, INT_MAX));
        
        dp[0][0] = 0;  // no carry
        dp[0][1] = 2;  // carry from previous
        
        for (int i = 0; i < n; i++) {
            int d = digits[i];
            int cost = (i == 0) ? 0 : i;  // cost of using x^i
            
            // No carry
            dp[i + 1][0] = min(dp[i + 1][0], dp[i][0] + d * cost);
            dp[i + 1][1] = min(dp[i + 1][1], dp[i][0] + (x - d) * cost + 2);
            
            // With carry
            dp[i + 1][0] = min(dp[i + 1][0], dp[i][1] + (d + 1) * cost);
            dp[i + 1][1] = min(dp[i + 1][1], dp[i][1] + (x - (d + 1)) * cost + 2);
        }
        
        return dp[n][0];            
    }
};
