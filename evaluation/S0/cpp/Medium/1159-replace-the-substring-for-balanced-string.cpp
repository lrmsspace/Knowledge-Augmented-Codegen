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

class Solution {
public:
    int balancedString(string s) {
        int n = s.size();
        int target = n / 4;
        unordered_map<char, int> count;
        for (char c : s) {
            count[c]++;
        }

        if (count['Q'] == target && count['W'] == target && count['E'] == target && count['R'] == target) {
            return 0;
        }

        int left = 0, right = 0;
        int minLength = n;

        while (right < n) {
            count[s[right]]--;
            right++;

            while (left < n && count['Q'] <= target && count['W'] <= target && count['E'] <= target && count['R'] <= target) {
                minLength = min(minLength, right - left);
                count[s[left]]++;
                left++;
            }
        }

        return minLength;           
    }
};
