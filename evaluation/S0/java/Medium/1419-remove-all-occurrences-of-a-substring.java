// Source: https://leetcode.com/problems/remove-all-occurrences-of-a-substring/   |   Difficulty: Medium
//
// Problem Description:
// Given two strings s and part, perform the following operation on s until all occurrences of the substring part are removed:
//
//
// 	Find the leftmost occurrence of the substring part and remove it from s.
//
//
// Return s after removing all occurrences of part.
//
// A substring is a contiguous sequence of characters in a string.
//
// Example:
// Input: s = "daabcbaabcbc", part = "abc"
// Output: "dab"
// Explanation: The following operations are done:
// - s = "daabcbaabcbc", remove "abc" starting at index 2, so s = "dabaabcbc".
// - s = "dabaabcbc", remove "abc" starting at index 4, so s = "dababc".
// - s = "dababc", remove "abc" starting at index 3, so s = "dab".
// Now s has no occurrences of "abc".
//
// Constraints:
// 1 <= s.length <= 1000
// 	1 <= part.length <= 1000
// 	s​​​​​​ and part consists of lowercase English letters.
//

class Solution {
    public String removeOccurrences(String s, String part) {
        StringBuilder sb = new StringBuilder();
        int partLength = part.length();

        for (char c : s.toCharArray()) {
            sb.append(c);
            if (sb.length() >= partLength && sb.substring(sb.length() - partLength).equals(part)) {
                sb.delete(sb.length() - partLength, sb.length());
            }
        }

        return sb.toString();           
    }
}
