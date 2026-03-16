// Source: https://leetcode.com/problems/take-k-of-each-character-from-left-and-right/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s consisting of the characters 'a', 'b', and 'c' and a non-negative integer k. Each minute, you may take either the leftmost character of s, or the rightmost character of s.
//
// Return the minimum number of minutes needed for you to take at least k of each character, or return -1 if it is not possible to take k of each character.
//
// Example:
// Input: s = "aabaaaacaabc", k = 2
// Output: 8
// Explanation: 
// Take three characters from the left of s. You now have two 'a' characters, and one 'b' character.
// Take five characters from the right of s. You now have four 'a' characters, two 'b' characters, and two 'c' characters.
// A total of 3 + 5 = 8 minutes is needed.
// It can be proven that 8 is the minimum number of minutes needed.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of only the letters 'a', 'b', and 'c'.
// 	0 <= k <= s.length
//

int takeCharacters(char* s, int k) {
    int n = strlen(s);
    int count[3] = {0};
    for (int i = 0; i < n; i++) {
        count[s[i] - 'a']++;
    }
    if (count[0] < k || count[1] < k || count[2] < k) {
        return -1;
    }

    int left = 0, right = 0;
    int need[3] = {k, k, k};
    int min_len = n + 1;

    while (right < n) {
        need[s[right] - 'a']--;
        right++;

        while (need[0] <= 0 && need[1] <= 0 && need[2] <= 0) {
            min_len = fmin(min_len, n - (right - left));
            need[s[left] - 'a']++;
            left++;
        }
    }

    return min_len == n + 1 ? -1 : min_len;     
}
