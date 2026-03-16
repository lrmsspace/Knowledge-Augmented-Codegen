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

class Solution {
    public String smallestNumber(String num, long t) {
        // If t contains 0 or 1, return -1
        if (t == 0 || t == 1) return "-1";

        // Factor t into its prime factors
        long[] primes = {2, 3, 5, 7};
        int[] targetCounts = new int[4];
        for (int i = 0; i < primes.length; i++) {
            while (t % primes[i] == 0) {
                targetCounts[i]++;
                t /= primes[i];
            }
        }
        if (t > 1) return "-1"; // t has prime factors greater than 7

        // DP to find the smallest number
        int n = num.length();
        String[][] dp = new String[n + 1][(targetCounts[0] + 1) * (targetCounts[1] + 1) * (targetCounts[2] + 1) * (targetCounts[3] + 1)];
        dp[0][0] = "";

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < dp[i].length; j++) {
                if (dp[i][j] == null) continue;
                for (char d = '1'; d <= '9'; d++) {
                    int[] counts = getPrimeFactorCounts(d - '0');
                    int ni = i + 1;
                    int nj = getIndex(j, counts, targetCounts);
                    if (nj == -1) continue;

                    String candidate = dp[i][j] + d;
                    if (dp[ni][nj] == null || candidate.compareTo(dp[ni][nj]) < 0) {
                        dp[ni][nj] = candidate;
                    }
                }
            }
        }

        String result = dp[n][dp[n].length - 1];
        return result != null && result.compareTo(num) >= 0 ? result : "-1";
    }
}
