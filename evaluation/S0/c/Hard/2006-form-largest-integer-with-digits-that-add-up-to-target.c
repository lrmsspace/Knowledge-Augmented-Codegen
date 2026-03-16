// Source: https://leetcode.com/problems/form-largest-integer-with-digits-that-add-up-to-target/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of integers cost and an integer target, return the maximum integer you can paint under the following rules:
//
//
// 	The cost of painting a digit (i + 1) is given by cost[i] (0-indexed).
// 	The total cost used must be equal to target.
// 	The integer does not have 0 digits.
//
//
// Since the answer may be very large, return it as a string. If there is no way to paint any integer given the condition, return "0".
//
// Example:
// Input: cost = [4,3,2,5,6,7,2,5,5], target = 9
// Output: "7772"
// Explanation: The cost to paint the digit '7' is 2, and the digit '2' is 3. Then cost("7772") = 2*3+ 3*1 = 9. You could also paint "977", but "7772" is the largest number.
// Digit    cost
//   1  ->   4
//   2  ->   3
//   3  ->   2
//   4  ->   5
//   5  ->   6
//   6  ->   7
//   7  ->   2
//   8  ->   5
//   9  ->   5
//
// Constraints:
// cost.length == 9
// 	1 <= cost[i], target <= 5000
//

char* largestNumber(int* cost, int costSize, int target) {
    int dp[target + 1];
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;

    for (int t = 1; t <= target; ++t) {
        for (int d = 9; d >= 1; --d) {
            int c = cost[d - 1];
            if (t >= c && dp[t - c] != -1) {
                int candidate = dp[t - c] + 1;
                if (candidate > dp[t]) {
                    dp[t] = candidate;
                }
            }
        }
    }

    if (dp[target] == -1) {
        char *res = (char*)malloc(2 * sizeof(char));
        strcpy(res, "0");
        return res;
    }

    char *res = (char*)malloc((dp[target] + 1) * sizeof(char));
    res[dp[target]] = '\0';
    int t = target;
    for (int i = 0; i < dp[target]; ++i) {
        for (int d = 9; d >= 1; --d) {
            int c = cost[d - 1];
            if (t >= c && dp[t - c] == dp[t] - 1) {
                res[i] = '0' + d;
                t -= c;
                break;
            }
        }
    }

    return res;     
}
