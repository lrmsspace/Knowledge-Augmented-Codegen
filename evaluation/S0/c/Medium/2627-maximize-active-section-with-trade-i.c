// Source: https://leetcode.com/problems/maximize-active-section-with-trade-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary string s of length n, where:
//
//
// 	'1' represents an active section.
// 	'0' represents an inactive section.
//
//
// You can perform at most one trade to maximize the number of active sections in s. In a trade, you:
//
//
// 	Convert a contiguous block of '1's that is surrounded by '0's to all '0's.
// 	Afterward, convert a contiguous block of '0's that is surrounded by '1's to all '1's.
//
//
// Return the maximum number of active sections in s after making the optimal trade.
//
// Note: Treat s as if it is augmented with a '1' at both ends, forming t = '1' + s + '1'. The augmented '1's do not contribute to the final count.
//
// Example:
// Input: s = "01"
//
// Output: 1
//
// Explanation:
//
// Because there is no block of '1's surrounded by '0's, no valid trade is possible. The maximum number of active sections is 1.
//
// Constraints:
// 1 <= n == s.length <= 105
// 	s[i] is either '0' or '1'
//

int maxActiveSectionsAfterTrade(char* s) {
    int n = strlen(s);
    int totalOnes = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            totalOnes++;
        }
    }

    int maxGain = 0;
    int currentGain = 0;
    int hasZeroBlock = 0;

    for (int i = 0; i < n; ) {
        if (s[i] == '0') {
            hasZeroBlock = 1;
            int zeroCount = 0;
            while (i < n && s[i] == '0') {
                zeroCount++;
                i++;
            }
            currentGain += zeroCount;
        } else {
            int oneCount = 0;
            while (i < n && s[i] == '1') {
                oneCount++;
                i++;
            }
            if (oneCount > 0) {
                currentGain -= oneCount;
            }
        }
        if (currentGain < 0) {
            currentGain = 0;
        }
        if (currentGain > maxGain) {
            maxGain = currentGain;
        }
    }

    if (!hasZeroBlock) {
        return totalOnes;
    }

    return totalOnes + maxGain;     
}
