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

class Solution {
public:
    int takeCharacters(string s, int k) {
        int n = s.size();
        vector<int> totalCount(3, 0);
        for (char c : s) {
            totalCount[c - 'a']++;
        }
        if (totalCount[0] < k || totalCount[1] < k || totalCount[2] < k) {
            return -1;
        }

        vector<int> countInWindow(3, 0);
        int left = 0, maxWindowSize = 0;
        for (int right = 0; right < n; ++right) {
            countInWindow[s[right] - 'a']++;
            while (left <= right && (totalCount[0] - countInWindow[0] < k ||
                                    totalCount[1] - countInWindow[1] < k ||
                                    totalCount[2] - countInWindow[2] < k)) {
                countInWindow[s[left] - 'a']--;
                left++;
            }
            if (totalCount[0] - countInWindow[0] >= k &&
                totalCount[1] - countInWindow[1] >= k &&
                totalCount[2] - countInWindow[2] >= k) {
                maxWindowSize = max(maxWindowSize, right - left + 1);
            }
        }

        return n - maxWindowSize;           
    }
};
