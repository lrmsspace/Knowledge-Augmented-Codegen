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
    public int takeCharacters(String s, int k) {
        int n = s.length();
        int[] totalCount = new int[3];
        for (char ch : s.toCharArray()) {
            totalCount[ch - 'a']++;
        }
        if (totalCount[0] < k || totalCount[1] < k || totalCount[2] < k) {
            return -1;
        }

        int left = 0, right = 0;
        int[] windowCount = new int[3];
        int maxWindowSize = 0;

        while (right < n) {
            windowCount[s.charAt(right) - 'a']++;
            right++;

            while (left < n && (totalCount[0] - windowCount[0] >= k &&
                                totalCount[1] - windowCount[1] >= k &&
                                totalCount[2] - windowCount[2] >= k)) {
                maxWindowSize = Math.max(maxWindowSize, right - left);
                windowCount[s.charAt(left) - 'a']--;
                left++;
            }
        }

        return n - maxWindowSize;           
    }
}
