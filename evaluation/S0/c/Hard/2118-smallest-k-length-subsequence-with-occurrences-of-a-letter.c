// Source: https://leetcode.com/problems/smallest-k-length-subsequence-with-occurrences-of-a-letter/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s, an integer k, a letter letter, and an integer repetition.
//
// Return the lexicographically smallest subsequence of s of length k that has the letter letter appear at least repetition times. The test cases are generated so that the letter appears in s at least repetition times.
//
// A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
//
// A string a is lexicographically smaller than a string b if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b.
//
// Example:
// Input: s = "leet", k = 3, letter = "e", repetition = 1
// Output: "eet"
// Explanation: There are four subsequences of length 3 that have the letter 'e' appear at least 1 time:
// - "lee" (from "leet")
// - "let" (from "leet")
// - "let" (from "leet")
// - "eet" (from "leet")
// The lexicographically smallest subsequence among them is "eet".
//
// Constraints:
// 1 <= repetition <= k <= s.length <= 5 * 104
// 	s consists of lowercase English letters.
// 	letter is a lowercase English letter, and appears in s at least repetition times.
//

char* smallestSubsequence(char* s, int k, char letter, int repetition) {
    int n = strlen(s);
    int totalLetterCount = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == letter) totalLetterCount++;
    }

    char *stack = (char*)malloc((k + 1) * sizeof(char));
    int top = -1;
    int letterCountInStack = 0;
    int remainingLetterCount = totalLetterCount;

    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (c == letter) remainingLetterCount--;

        while (top >= 0 && stack[top] > c &&
               (top + 1 + n - i - 1 >= k) &&
               (letterCountInStack + remainingLetterCount >= repetition || stack[top] != letter)) {
            if (stack[top] == letter) letterCountInStack--;
            top--;
        }

        if (top + 1 < k) {
            if (c == letter) {
                stack[++top] = c;
                letterCountInStack++;
            } else {
                if (k - (top + 1) > repetition - letterCountInStack) {
                    stack[++top] = c;
                }
            }
        }
    }

    stack[k] = '\0';
    return stack;       
}
