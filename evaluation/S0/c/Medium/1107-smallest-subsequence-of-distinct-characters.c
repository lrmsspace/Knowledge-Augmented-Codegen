// Source: https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, return the lexicographically smallest subsequence of s that contains all the distinct characters of s exactly once.
//
// Example:
// Input: s = "bcabc"
// Output: "abc"
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consists of lowercase English letters.
//
//
//  
// Note: This question is the same as 316: https://leetcode.com/problems/remove-duplicate-letters/
//

char* smallestSubsequence(char* s) {
    int last_occurrence[26] = {0};
    int in_stack[26] = {0};
    int len = 0;
    while (s[len]) {
        last_occurrence[s[len] - 'a'] = len;
        len++;
    }

    char* stack = (char*)malloc((len + 1) * sizeof(char));
    int stack_size = 0;

    for (int i = 0; i < len; i++) {
        char c = s[i];
        if (in_stack[c - 'a']) {
            continue;
        }
        while (stack_size > 0 && stack[stack_size - 1] > c && last_occurrence[stack[stack_size - 1] - 'a'] > i) {
            in_stack[stack[--stack_size] - 'a'] = 0;
        }
        stack[stack_size++] = c;
        in_stack[c - 'a'] = 1;
    }
    stack[stack_size] = '\0';
    return stack;       
}
