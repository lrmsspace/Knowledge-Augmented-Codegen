// Source: https://leetcode.com/problems/shortest-matching-substring/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s and a pattern string p, where p contains exactly two '*' characters.
//
// The '*' in p matches any sequence of zero or more characters.
//
// Return the length of the shortest substring in s that matches p. If there is no such substring, return -1.
// Note: The empty substring is considered valid.
//
// Example:
// Input: s = "abaacbaecebce", p = "ba*c*ce"
//
// Output: 8
//
// Explanation:
//
// The shortest matching substring of p in s is "baecebce".
//
// Constraints:
// 1 <= s.length <= 105
// 	2 <= p.length <= 105
// 	s contains only lowercase English letters.
// 	p contains only lowercase English letters and exactly two '*'.
//

int shortestMatchingSubstring(char* s, char* p) {
    int sLen = strlen(s);
    int pLen = strlen(p);
    int firstStar = -1, secondStar = -1;
    for (int i = 0; i < pLen; i++) {
        if (p[i] == '*') {
            if (firstStar == -1) firstStar = i;
            else if (secondStar == -1) secondStar = i;
        }
    }
    int preLen = firstStar;
    int midLen = secondStar - firstStar - 1;
    int sufLen = pLen - secondStar - 1;
    if (preLen + sufLen > sLen) return -1;

    int minLen = -1;
    for (int i = 0; i <= sLen - (preLen + sufLen); i++) {
        if (strncmp(s + i, p, preLen) == 0) {
            for (int j = i + preLen; j <= sLen - sufLen; j++) {
                if (strncmp(s + j, p + secondStar + 1, sufLen) == 0) {
                    int totalLen = (j + sufLen) - i;
                    if (minLen == -1 || totalLen < minLen) {
                        minLen = totalLen;
                    }
                    break; // Found the shortest for this prefix match
                }
            }
        }
    }
    return minLen;      
}
