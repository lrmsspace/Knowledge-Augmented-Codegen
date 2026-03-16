// Source: https://leetcode.com/problems/apply-operations-to-make-string-empty/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s.
//
// Consider performing the following operation until s becomes empty:
//
//
// 	For every alphabet character from 'a' to 'z', remove the first occurrence of that character in s (if it exists).
//
//
// For example, let initially s = "aabcbbca". We do the following operations:
//
//
// 	Remove the underlined characters s = "aabcbbca". The resulting string is s = "abbca".
// 	Remove the underlined characters s = "abbca". The resulting string is s = "ba".
// 	Remove the underlined characters s = "ba". The resulting string is s = "".
//
//
// Return the value of the string s right before applying the last operation. In the example above, answer is "ba".
//
// Example:
// Input: s = "aabcbbca"
// Output: "ba"
// Explanation: Explained in the statement.
//
// Constraints:
// 1 <= s.length <= 5 * 105
// 	s consists only of lowercase English letters.
//

char* lastNonEmptyString(char* s) {
    int len = strlen(s);
    int count[26] = {0};
    for (int i = 0; i < len; i++) {
        count[s[i] - 'a']++;
    }

    int rounds = len / 26;
    int remainder = len % 26;

    char* result = (char*)malloc((remainder + 1) * sizeof(char));
    int index = 0;

    for (int i = 0; i < 26; i++) {
        if (count[i] > rounds) {
            result[index++] = 'a' + i;
        }
    }
    result[index] = '\0';

    return result;      
}
