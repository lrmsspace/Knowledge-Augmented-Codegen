// Source: https://leetcode.com/problems/lexicographically-smallest-string-after-substring-operation/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s consisting of lowercase English letters. Perform the following operation:
//
//
// 	Select any non-empty substring then replace every letter of the substring with the preceding letter of the English alphabet. For example, 'b' is converted to 'a', and 'a' is converted to 'z'.
//
//
// Return the lexicographically smallest string after performing the operation.
//
// Example:
// Input: s = "cbabc"
//
// Output: "baabc"
//
// Explanation:
//
// Perform the operation on the substring starting at index 0, and ending at index 1 inclusive.
//
// Constraints:
// 1 <= s.length <= 3 * 105
// 	s consists of lowercase English letters
//

class Solution {
    public String smallestString(String s) {
        char[] arr = s.toCharArray();
        int n = arr.length;
        int i = 0;

        // Find the first character that is not 'a'
        while (i < n && arr[i] == 'a') {
            i++;
        }

        // If all characters are 'a', change the last one to 'z'
        if (i == n) {
            arr[n - 1] = 'z';
            return new String(arr);
        }

        // Decrement characters until we hit an 'a' or the end of the string
        while (i < n && arr[i] != 'a') {
            arr[i] = (char)(arr[i] - 1);
            i++;
        }

        return new String(arr);         
    }
}
