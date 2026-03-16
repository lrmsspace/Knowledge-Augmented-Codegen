// Source: https://leetcode.com/problems/reverse-only-letters/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, reverse the string according to the following rules:
//
//
// 	All the characters that are not English letters remain in the same position.
// 	All the English letters (lowercase or uppercase) should be reversed.
//
//
// Return s after reversing it.
//
// Example:
// Input: s = "ab-cd"
// Output: "dc-ba"
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists of characters with ASCII values in the range [33, 122].
// 	s does not contain '\"' or '\\'.
//

char* reverseOnlyLetters(char* s) {
    int left = 0;
    int right = strlen(s) - 1;

    while (left < right) {
        if (!((s[left] >= 'a' && s[left] <= 'z') || (s[left] >= 'A' && s[left] <= 'Z'))) {
            left++;
        } else if (!((s[right] >= 'a' && s[right] <= 'z') || (s[right] >= 'A' && s[right] <= 'Z'))) {
            right--;
        } else {
            char temp = s[left];
            s[left] = s[right];
            s[right] = temp;
            left++;
            right--;
        }
    }

    return s;       
}
