// Source: https://leetcode.com/problems/number-of-ways-to-split-a-string/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary string s, you can split s into 3 non-empty strings s1, s2, and s3 where s1 + s2 + s3 = s.
//
// Return the number of ways s can be split such that the number of ones is the same in s1, s2, and s3. Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: s = "10101"
// Output: 4
// Explanation: There are four ways to split s in 3 parts where each part contain the same number of letters '1'.
// "1|010|1"
// "1|01|01"
// "10|10|1"
// "10|1|01"
//
// Constraints:
// 3 <= s.length <= 105
// 	s[i] is either '0' or '1'.
//

class Solution {
    public int numWays(String s) {
        int mod = 1_000_000_007;
        int ones = 0;
        for (char c : s.toCharArray()) {
            if (c == '1') {
                ones++;
            }
        }

        if (ones % 3 != 0) {
            return 0;
        }

        if (ones == 0) {
            long n = s.length() - 1;
            return (int) (((n * (n - 1) / 2) % mod));
        }

        int onesPerPart = ones / 3;
        long firstCutWays = 0;
        long secondCutWays = 0;
        int countOnes = 0;

        for (char c : s.toCharArray()) {
            if (c == '1') {
                countOnes++;
            }

            if (countOnes == onesPerPart) {
                firstCutWays++;
            } else if (countOnes == 2 * onesPerPart) {
                secondCutWays++;
            }
        }

        return (int) ((firstCutWays * secondCutWays) % mod);            
    }
}
