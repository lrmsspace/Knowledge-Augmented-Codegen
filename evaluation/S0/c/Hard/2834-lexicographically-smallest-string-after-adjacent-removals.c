// Source: https://leetcode.com/problems/lexicographically-smallest-string-after-adjacent-removals/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s consisting of lowercase English letters.
//
// You can perform the following operation any number of times (including zero):
//
//
// 	Remove any pair of adjacent characters in the string that are consecutive in the alphabet, in either order (e.g., 'a' and 'b', or 'b' and 'a').
// 	Shift the remaining characters to the left to fill the gap.
//
//
// Return the lexicographically smallest string that can be obtained after performing the operations optimally.
//
// Note: Consider the alphabet as circular, thus 'a' and 'z' are consecutive.
//
// Example:
// Input: s = "abc"
//
// Output: "a"
//
// Explanation:
//
//
// 	Remove "bc" from the string, leaving "a" as the remaining string.
// 	No further operations are possible. Thus, the lexicographically smallest string after all possible removals is "a".
//
// Constraints:
// 1 <= s.length <= 250
// 	s consists only of lowercase English letters.
//

char* lexicographicallySmallestString(char* s) {
    int len = strlen(s);
    int changed;
    do {
        changed = 0;
        char *dst = s;
        for (int i = 0; i < len; ) {
            if (i + 1 < len && (s[i] + 1 == s[i + 1] || s[i] - 1 == s[i + 1] ||
                               (s[i] == 'a' && s[i + 1] == 'z') || (s[i] == 'z' && s[i + 1] == 'a'))) {
                changed = 1;
                i += 2; /* skip both characters */
            } else {
                *dst++ = s[i++];
            }
        }
        *dst = '\0';
        len = dst - s;
    } while (changed);
    return s;       
}
