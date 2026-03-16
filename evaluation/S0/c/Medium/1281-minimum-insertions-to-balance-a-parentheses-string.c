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

int minInsertions(char* s) {
    int insertions = 0;
    int balance = 0; // Number of ')' needed

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            balance += 2;
            if (balance % 2 != 0) { // If balance is odd
                insertions++;
                balance--; // Insert one ')'
            }
        } else { // s[i] == ')'
            balance--;
            if (balance < 0) { // More ')' than needed
                insertions++;
                balance += 2; // Insert one '('
            }
        }
    }

    insertions += balance; // Add remaining needed ')'
    return insertions;      
}
