// Source: https://leetcode.com/problems/decoded-string-at-index/   |   Difficulty: Medium
//
// Problem Description:
// You are given an encoded string s. To decode the string to a tape, the encoded string is read one character at a time and the following steps are taken:
//
//
// 	If the character read is a letter, that letter is written onto the tape.
// 	If the character read is a digit d, the entire current tape is repeatedly written d - 1 more times in total.
//
//
// Given an integer k, return the kth letter (1-indexed) in the decoded string.
//
// Example:
// Input: s = "leet2code3", k = 10
// Output: "o"
// Explanation: The decoded string is "leetleetcodeleetleetcodeleetleetcode".
// The 10th letter in the string is "o".
//
// Constraints:
// 2 <= s.length <= 100
// 	s consists of lowercase English letters and digits 2 through 9.
// 	s starts with a letter.
// 	1 <= k <= 109
// 	It is guaranteed that k is less than or equal to the length of the decoded string.
// 	The decoded string is guaranteed to have less than 263 letters.
//

class Solution {
public:
    string decodeAtIndex(string s, int k) {
        long long size = 0;
        int n = s.size();

        // First, find the size of the decoded string
        for (char c : s) {
            if (isdigit(c)) {
                size *= (c - '0');
            } else {
                size++;
            }
        }

        // Now, work backwards to find the k-th character
        for (int i = n - 1; i >= 0; --i) {
            char c = s[i];
            if (isdigit(c)) {
                size /= (c - '0');
                k %= size;
            } else {
                if (k == 0 || k == size) {
                    return string(1, c);
                }
                size--;
            }
        }

        return ""; // This line should never be reached         
    }
};
