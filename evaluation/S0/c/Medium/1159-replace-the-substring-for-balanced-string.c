// Source: https://leetcode.com/problems/replace-the-substring-for-balanced-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s of length n containing only four kinds of characters: 'Q', 'W', 'E', and 'R'.
//
// A string is said to be balanced if each of its characters appears n / 4 times where n is the length of the string.
//
// Return the minimum length of the substring that can be replaced with any other string of the same length to make s balanced. If s is already balanced, return 0.
//
// Example:
// Input: s = "QWER"
// Output: 0
// Explanation: s is already balanced.
//
// Constraints:
// n == s.length
// 	4 <= n <= 105
// 	n is a multiple of 4.
// 	s contains only 'Q', 'W', 'E', and 'R'.
//

int balancedString(char* s) {
    int count[128] = {0};
    int n = 0;
    for (char* p = s; *p; ++p, ++n) {
        ++count[(int)(*p)];
    }
    int target = n / 4;
    if (count['Q'] == target && count['W'] == target && count['E'] == target && count['R'] == target) {
        return 0;
    }

    int left = 0;
    int min_len = n;
    for (int right = 0; s[right]; ++right) {
        --count[(int)(s[right])];
        while (left < n && count['Q'] <= target && count['W'] <= target && count['E'] <= target && count['R'] <= target) {
            min_len = (right - left + 1 < min_len) ? (right - left + 1) : min_len;
            ++count[(int)(s[left])];
            ++left;
        }
    }
    return min_len;     
}
