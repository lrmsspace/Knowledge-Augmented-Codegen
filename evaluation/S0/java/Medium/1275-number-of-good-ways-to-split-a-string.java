// Source: https://leetcode.com/problems/number-of-good-ways-to-split-a-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s.
//
// A split is called good if you can split s into two non-empty strings sleft and sright where their concatenation is equal to s (i.e., sleft + sright = s) and the number of distinct letters in sleft and sright is the same.
//
// Return the number of good splits you can make in s.
//
// Example:
// Input: s = "aacaba"
// Output: 2
// Explanation: There are 5 ways to split "aacaba" and 2 of them are good. 
// ("a", "acaba") Left string and right string contains 1 and 3 different letters respectively.
// ("aa", "caba") Left string and right string contains 1 and 3 different letters respectively.
// ("aac", "aba") Left string and right string contains 2 and 2 different letters respectively (good split).
// ("aaca", "ba") Left string and right string contains 2 and 2 different letters respectively (good split).
// ("aacab", "a") Left string and right string contains 3 and 1 different letters respectively.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of only lowercase English letters.
//

class Solution {
    public int numSplits(String s) {
        int n = s.length();
        int[] leftCount = new int[n];
        int[] rightCount = new int[n];

        boolean[] leftSeen = new boolean[26];
        boolean[] rightSeen = new boolean[26];

        int distinctLeft = 0;
        int distinctRight = 0;

        // Count distinct characters from the left
        for (int i = 0; i < n; i++) {
            char ch = s.charAt(i);
            if (!leftSeen[ch - 'a']) {
                distinctLeft++;
                leftSeen[ch - 'a'] = true;
            }
            leftCount[i] = distinctLeft;
        }

        // Count distinct characters from the right
        for (int i = n - 1; i >= 0; i--) {
            char ch = s.charAt(i);
            if (!rightSeen[ch - 'a']) {
                distinctRight++;
                rightSeen[ch - 'a'] = true;
            }
            rightCount[i] = distinctRight;
        }

        // Count good splits
        int goodSplits = 0;
        for (int i = 0; i < n - 1; i++) {
            if (leftCount[i] == rightCount[i + 1]) {
                goodSplits++;
            }
        }

        return goodSplits;          
    }
}
