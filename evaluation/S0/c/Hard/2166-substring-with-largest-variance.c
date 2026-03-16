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

int largestVariance(char* s) {
    int freq[26] = {0};
    for (char *p = s; *p; ++p) {
        freq[*p - 'a']++;
    }

    int result = 0;
    for (int major = 0; major < 26; ++major) {
        for (int minor = 0; minor < 26; ++minor) {
            if (major == minor || freq[major] == 0 || freq[minor] == 0) continue;

            int majorCount = 0, minorCount = 0;
            int restMinor = freq[minor];

            for (char *p = s; *p; ++p) {
                if (*p - 'a' == major) {
                    majorCount++;
                }
                if (*p - 'a' == minor) {
                    minorCount++;
                    restMinor--;
                }

                if (minorCount > 0) {
                    if (result < majorCount - minorCount) {
                        result = majorCount - minorCount;
                    }
                } else {
                    if (restMinor > 0 && result < majorCount - 1) {
                        result = majorCount - 1;
                    }
                }

                if (majorCount < minorCount) {
                    majorCount = 0;
                    minorCount = 0;
                }
            }
        }
    }
    return result;      
}
