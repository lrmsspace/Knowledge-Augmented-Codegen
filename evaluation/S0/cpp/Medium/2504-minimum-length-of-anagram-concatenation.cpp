// Source: https://leetcode.com/problems/minimum-length-of-anagram-concatenation/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s, which is known to be a concatenation of anagrams of some string t.
//
// Return the minimum possible length of the string t.
//
// An anagram is formed by rearranging the letters of a string. For example, "aab", "aba", and, "baa" are anagrams of "aab".
//
// Example:
// Input: s = "abba"
//
// Output: 2
//
// Explanation:
//
// One possible string t could be "ba".
//
// Constraints:
// 1 <= s.length <= 105
// 	s consist only of lowercase English letters.
//

class Solution {
public:
    int minAnagramLength(string s) {
        vector<int> charCount(26, 0);
        for (char c : s) {
            charCount[c - 'a']++;
        }

        int gcdCount = 0;
        for (int count : charCount) {
            if (count > 0) {
                if (gcdCount == 0) {
                    gcdCount = count;
                } else {
                    gcdCount = std::gcd(gcdCount, count);
                }
            }
        }

        int minLength = 0;
        for (int count : charCount) {
            if (count > 0) {
                minLength += count / gcdCount;
            }
        }

        return minLength;           
    }
};
