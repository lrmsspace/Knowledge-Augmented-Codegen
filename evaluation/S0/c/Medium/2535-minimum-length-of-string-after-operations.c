// Source: https://leetcode.com/problems/minimum-length-of-string-after-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s.
//
// You can perform the following process on s any number of times:
//
//
// 	Choose an index i in the string such that there is at least one character to the left of index i that is equal to s[i], and at least one character to the right that is also equal to s[i].
// 	Delete the closest occurrence of s[i] located to the left of i.
// 	Delete the closest occurrence of s[i] located to the right of i.
//
//
// Return the minimum length of the final string s that you can achieve.
//
// Example:
// Input: s = "abaacbcbb"
//
// Output: 5
//
// Explanation:
// We do the following operations:
//
//
// 	Choose index 2, then remove the characters at indices 0 and 3. The resulting string is s = "bacbcbb".
// 	Choose index 3, then remove the characters at indices 0 and 5. The resulting string is s = "acbcb".
//
// Constraints:
// 1 <= s.length <= 2 * 105
// 	s consists only of lowercase English letters.
//

int minimumLength(char* s) {
    int left = 0;
    int right = strlen(s) - 1;

    while (left < right && s[left] == s[right]) {
        char currentChar = s[left];
        while (left <= right && s[left] == currentChar) {
            left++;
        }
        while (left <= right && s[right] == currentChar) {
            right--;
        }
    }

    return right - left + 1;        
}
