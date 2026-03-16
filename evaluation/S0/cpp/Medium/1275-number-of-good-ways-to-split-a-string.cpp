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
public:
    int numSplits(string s) {
        vector<int> leftCount(26, 0);
        vector<int> rightCount(26, 0);
        int leftDistinct = 0;
        int rightDistinct = 0;
        int goodSplits = 0;

        // Count distinct characters in the entire string for the right side
        for (char c : s) {
            if (rightCount[c - 'a'] == 0) {
                rightDistinct++;
            }
            rightCount[c - 'a']++;
        }

        // Iterate through the string and update counts for left and right sides
        for (int i = 0; i < s.length() - 1; ++i) {
            char c = s[i];

            // Update left side
            if (leftCount[c - 'a'] == 0) {
                leftDistinct++;
            }
            leftCount[c - 'a']++;

            // Update right side
            rightCount[c - 'a']--;
            if (rightCount[c - 'a'] == 0) {
                rightDistinct--;
            }

            // Check if the split is good
            if (leftDistinct == rightDistinct) {
                goodSplits++;
            }
        }

        return goodSplits;          
    }
};
