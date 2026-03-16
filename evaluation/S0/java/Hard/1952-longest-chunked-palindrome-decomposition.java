// Source: https://leetcode.com/problems/longest-chunked-palindrome-decomposition/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string text. You should split it to k substrings (subtext1, subtext2, ..., subtextk) such that:
//
//
// 	subtexti is a non-empty string.
// 	The concatenation of all the substrings is equal to text (i.e., subtext1 + subtext2 + ... + subtextk == text).
// 	subtexti == subtextk - i + 1 for all valid values of i (i.e., 1 <= i <= k).
//
//
// Return the largest possible value of k.
//
// Example:
// Input: text = "ghiabcdefhelloadamhelloabcdefghi"
// Output: 7
// Explanation: We can split the string on "(ghi)(abcdef)(hello)(adam)(hello)(abcdef)(ghi)".
//
// Constraints:
// 1 <= text.length <= 1000
// 	text consists only of lowercase English characters.
//

class Solution {
    public int longestDecomposition(String text) {
        int left = 0, right = text.length() - 1;
        int count = 0;

        while (left < right) {
            int len = 1;
            boolean found = false;

            while (left + len - 1 < right - len + 1) {
                String leftSub = text.substring(left, left + len);
                String rightSub = text.substring(right - len + 1, right + 1);

                if (leftSub.equals(rightSub)) {
                    count += 2;
                    left += len;
                    right -= len;
                    found = true;
                    break;
                }
                len++;
            }

            if (!found) {
                break;
            }
        }

        if (left <= right) {
            count++;
        }

        return count;                   
    }
}
