// Source: https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s consisting only of characters a, b and c.
//
// Return the number of substrings containing at least one occurrence of all these characters a, b and c.
//
// Example:
// Input: s = "abcabc"
// Output: 10
// Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again).
//
// Constraints:
// 3 <= s.length <= 5 x 10^4
// 	s only consists of a, b or c characters.
//

int numberOfSubstrings(char* s) {
    int count[3] = {0};
    int left = 0, right = 0;
    int result = 0;
    int n = strlen(s);

    while (right < n) {
        count[s[right] - 'a']++;

        while (count[0] > 0 && count[1] > 0 && count[2] > 0) {
            result += n - right;
            count[s[left] - 'a']--;
            left++;
        }
        right++;
    }

    return result;      
}
