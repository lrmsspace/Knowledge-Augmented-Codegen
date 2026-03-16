// Source: https://leetcode.com/problems/remove-duplicate-letters/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, remove duplicate letters so that every letter appears once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.
//
// Example:
// Input: s = "bcabc"
// Output: "abc"
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of lowercase English letters.
//
//
//  
// Note: This question is the same as 1081: https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/
//

char* removeDuplicateLetters(char* s) {
    int last_occurrence[26] = {0};
    int visited[26] = {0};
    int len = 0;
    while (s[len]) {
        last_occurrence[s[len] - 'a'] = len;
        len++;
    }

    char* stack = (char*)malloc((len + 1) * sizeof(char));
    int top = -1;

    for (int i = 0; i < len; i++) {
        int index = s[i] - 'a';
        if (visited[index]) {
            continue;
        }

        while (top >= 0 && stack[top] > s[i] && last_occurrence[stack[top] - 'a'] > i) {
            visited[stack[top] - 'a'] = 0;
            top--;
        }

        stack[++top] = s[i];
        visited[index] = 1;
    }

    stack[top + 1] = '\0';
    return stack;       
}
