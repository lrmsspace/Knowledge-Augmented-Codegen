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
public:
    int numWays(string s) {
        const int MOD = 1e9 + 7;
        int totalOnes = count(s.begin(), s.end(), '1');

        if (totalOnes % 3 != 0) {
            return 0;
        }

        if (totalOnes == 0) {
            long long n = s.length();
            return ((n - 1) * (n - 2) / 2) % MOD;
        }

        int onesPerPart = totalOnes / 3;
        long long firstCutWays = 0, secondCutWays = 0;
        int currentOnes = 0;

        for (char c : s) {
            if (c == '1') {
                currentOnes++;
            }

            if (currentOnes == onesPerPart) {
                firstCutWays++;
            } else if (currentOnes == 2 * onesPerPart) {
                secondCutWays++;
            }
        }

        return (firstCutWays * secondCutWays) % MOD;            
    }
};
