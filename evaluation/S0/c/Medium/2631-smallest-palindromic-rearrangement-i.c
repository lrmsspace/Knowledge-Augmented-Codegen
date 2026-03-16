// Source: https://leetcode.com/problems/smallest-palindromic-rearrangement-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a palindromic string s.
//
// Return the lexicographically smallest palindromic permutation of s.
//
// Example:
// Input: s = "z"
//
// Output: "z"
//
// Explanation:
//
// A string of only one character is already the lexicographically smallest palindrome.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
// 	s is guaranteed to be palindromic.
//

char* smallestPalindrome(char* s) {
    int count[26] = {0};
    for (int i = 0; s[i]; i++) {
        count[s[i] - 'a']++;
    }

    int n = 0;
    for (int i = 0; i < 26; i++) {
        n += count[i];
    }

    char* result = (char*)malloc((n + 1) * sizeof(char));
    int left = 0;
    int right = n - 1;

    for (int i = 0; i < 26; i++) {
        while (count[i] > 1) {
            result[left++] = 'a' + i;
            result[right--] = 'a' + i;
            count[i] -= 2;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (count[i] == 1) {
            result[left] = 'a' + i;
            break;
        }
    }

    result[n] = '\0';
    return result;      
}
