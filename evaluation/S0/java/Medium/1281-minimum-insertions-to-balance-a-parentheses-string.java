// Source: https://leetcode.com/problems/minimum-insertions-to-balance-a-parentheses-string/   |   Difficulty: Medium
//
// Problem Description:
// Given a parentheses string s containing only the characters '(' and ')'. A parentheses string is balanced if:
//
//
// 	Any left parenthesis '(' must have a corresponding two consecutive right parenthesis '))'.
// 	Left parenthesis '(' must go before the corresponding two consecutive right parenthesis '))'.
//
//
// In other words, we treat '(' as an opening parenthesis and '))' as a closing parenthesis.
//
//
// 	For example, "())", "())(())))" and "(())())))" are balanced, ")()", "()))" and "(()))" are not balanced.
//
//
// You can insert the characters '(' and ')' at any position of the string to balance it if needed.
//
// Return the minimum number of insertions needed to make s balanced.
//
// Example:
// Input: s = "(()))"
// Output: 1
// Explanation: The second '(' has two matching '))', but the first '(' has only ')' matching. We need to add one more ')' at the end of the string to be "(())))" which is balanced.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of '(' and ')' only.
//

class Solution {
    public int minInsertions(String s) {
        int insertions = 0;
        int balance = 0; // number of ')' needed

        for (char c : s.toCharArray()) {
            if (c == '(') {
                // Each '(' requires two ')'
                balance += 2;

                // If balance is odd, we need one more ')' to make it even
                if (balance % 2 == 1) {
                    insertions++;
                    balance--; // Adjust balance since we added one ')'
                }
            } else { // c == ')'
                balance--; // One ')' found

                if (balance < 0) {
                    // We need an extra '(' to balance
                    insertions++;
                    balance += 2; // Now we need two more ')'
                }
            }
        }

        // Add any remaining needed ')'
        insertions += balance;

        return insertions;          
    }
}
