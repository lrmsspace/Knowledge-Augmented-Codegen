// Source: https://leetcode.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/   |   Difficulty: Medium
//
// Problem Description:
// A happy string is a string that:
//
//
// 	consists only of letters of the set ['a', 'b', 'c'].
// 	s[i] != s[i + 1] for all values of i from 1 to s.length - 1 (string is 1-indexed).
//
//
// For example, strings "abc", "ac", "b" and "abcbabcbcb" are all happy strings and strings "aa", "baa" and "ababbc" are not happy strings.
//
// Given two integers n and k, consider a list of all happy strings of length n sorted in lexicographical order.
//
// Return the kth string of this list or return an empty string if there are less than k happy strings of length n.
//
// Example:
// Input: n = 1, k = 3
// Output: "c"
// Explanation: The list ["a", "b", "c"] contains all happy strings of length 1. The third string is "c".
//
// Constraints:
// 1 <= n <= 10
// 	1 <= k <= 100
//

class Solution {
    public String getHappyString(int n, int k) {
        int totalHappyStrings = 3 * (int) Math.pow(2, n - 1);
        if (k > totalHappyStrings) {
            return "";
        }

        StringBuilder happyString = new StringBuilder();
        char[] chars = new char[] {'a', 'b', 'c'};
        int index = (k - 1) / (int) Math.pow(2, n - 1);
        happyString.append(chars[index]);

        k = k - index * (int) Math.pow(2, n - 1);

        for (int i = 1; i < n; i++) {
            int blockSize = (int) Math.pow(2, n - i - 1);
            index = (k - 1) / blockSize;
            char lastChar = happyString.charAt(happyString.length() - 1);
            char nextChar = getNextChar(lastChar, index);
            happyString.append(nextChar);
            k = k - index * blockSize;
        }

        return happyString.toString();          
    }
}
