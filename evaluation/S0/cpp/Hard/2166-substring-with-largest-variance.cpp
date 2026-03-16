// Source: https://leetcode.com/problems/substring-with-largest-variance/   |   Difficulty: Hard
//
// Problem Description:
// The variance of a string is defined as the largest difference between the number of occurrences of any 2 characters present in the string. Note the two characters may or may not be the same.
//
// Given a string s consisting of lowercase English letters only, return the largest variance possible among all substrings of s.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "aababbb"
// Output: 3
// Explanation:
// All possible variances along with their respective substrings are listed below:
// - Variance 0 for substrings "a", "aa", "ab", "abab", "aababb", "ba", "b", "bb", and "bbb".
// - Variance 1 for substrings "aab", "aba", "abb", "aabab", "ababb", "aababbb", and "bab".
// - Variance 2 for substrings "aaba", "ababbb", "abbb", and "babb".
// - Variance 3 for substring "babbb".
// Since the largest possible variance is 3, we return it.
//
// Constraints:
// 1 <= s.length <= 104
//  s consists of lowercase English letters.
//

class Solution {
public:
    int largestVariance(string s) {
        int result = 0;
        for (char a = 'a'; a <= 'z'; ++a) {
            for (char b = 'a'; b <= 'z'; ++b) {
                if (a == b) continue;
                
                int countA = 0, countB = 0;
                bool hasB = false;
                for (char c : s) {
                    if (c == a) {
                        countA++;
                    } else if (c == b) {
                        countB++;
                        hasB = true;
                    }
                    
                    if (hasB) {
                        result = max(result, countA - countB);
                    }
                    
                    if (countB > countA) {
                        countA = 0;
                        countB = 0;
                        hasB = false;
                    }
                }
            }
        }
        return result;          
    }
};
