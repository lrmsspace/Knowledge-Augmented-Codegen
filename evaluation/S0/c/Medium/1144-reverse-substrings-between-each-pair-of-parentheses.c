// Source: https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s that consists of lower case English letters and brackets.
//
// Reverse the strings in each pair of matching parentheses, starting from the innermost one.
//
// Your result should not contain any brackets.
//
// Example:
// Input: s = "(abcd)"
// Output: "dcba"
//
// Constraints:
// 1 <= s.length <= 2000
// 	s only contains lower case English characters and parentheses.
// 	It is guaranteed that all parentheses are balanced.
//

char* reverseParentheses(char* s) {
    int n = strlen(s);
    int stack[n], top = -1;
    char* res = (char*)malloc((n + 1) * sizeof(char));
    int res_len = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            stack[++top] = res_len;
        } else if (s[i] == ')') {
            int start = stack[top--];
            for (int j = start, k = res_len - 1; j < k; j++, k--) {
                char temp = res[j];
                res[j] = res[k];
                res[k] = temp;
            }
        } else {
            res[res_len++] = s[i];
        }
    }

    res[res_len] = '\0';
    return res;     
}
