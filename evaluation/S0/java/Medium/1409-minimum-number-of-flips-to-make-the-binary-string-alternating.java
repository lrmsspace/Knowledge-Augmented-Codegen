// Source: https://leetcode.com/problems/minimum-number-of-flips-to-make-the-binary-string-alternating/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary string s. You are allowed to perform two types of operations on the string in any sequence:
//
//
// 	Type-1: Remove the character at the start of the string s and append it to the end of the string.
// 	Type-2: Pick any character in s and flip its value, i.e., if its value is '0' it becomes '1' and vice-versa.
//
//
// Return the minimum number of type-2 operations you need to perform such that s becomes alternating.
//
// The string is called alternating if no two adjacent characters are equal.
//
//
// 	For example, the strings "010" and "1010" are alternating, while the string "0100" is not.
//
// Example:
// Input: s = "111000"
// Output: 2
// Explanation: Use the first operation two times to make s = "100011".
// Then, use the second operation on the third and sixth elements to make s = "101010".
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is either '0' or '1'.
//

class Solution {
    public int minFlips(String s) {
        int n = s.length();
        String s2 = s + s;
        char[] arr = s2.toCharArray();

        int count1 = 0; // flips to make "0101..."
        int count2 = 0; // flips to make "1010..."
        int minFlips = Integer.MAX_VALUE;

        for (int i = 0; i < arr.length; i++) {
            if (arr[i] != (i % 2 == 0 ? '0' : '1')) {
                count1++;
            }
            if (arr[i] != (i % 2 == 0 ? '1' : '0')) {
                count2++;
            }

            if (i >= n) {
                if (arr[i - n] != ((i - n) % 2 == 0 ? '0' : '1')) {
                    count1--;
                }
                if (arr[i - n] != ((i - n) % 2 == 0 ? '1' : '0')) {
                    count2--;
                }
            }

            if (i >= n - 1) {
                minFlips = Math.min(minFlips, Math.min(count1, count2));
            }
        }

        return minFlips;            
    }
}
