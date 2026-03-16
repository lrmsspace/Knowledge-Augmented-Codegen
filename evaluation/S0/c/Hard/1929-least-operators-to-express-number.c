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

int leastOpsExpressTarget(int x, int target) {
    int dp[40][2]; /* dp[i][0]: min ops to express target using x^i positively; dp[i][1]: negatively */
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 2; /* x = x / x */
    dp[0][1] = 1; /* 0 = x - x */

    for (int i = 1; i < 40; i++) {
        dp[i][0] = dp[i - 1][0] + 1; /* x^i = x^(i-1) * x */
        dp[i][1] = dp[i - 1][1] + 1; /* -x^i = -x^(i-1) * x */
    }

    int res = 0;
    for (int i = 39; i >= 0 && target > 0; i--) {
        int p = 1;
        for (int j = 0; j < i; j++) p *= x;
        int q = target / p;
        target %= p;

        if (q < x) {
            res += q * dp[i][0];
            if (q + 1 < x) {
                res = res < (q + 1) * dp[i][1] + (i == 0 ? 2 : i) ? res : (q + 1) * dp[i][1] + (i == 0 ? 2 : i);
            }
        } else {
            res += dp[i + 1][0];
            target -= p;
        }
    }
    return res;     
}
