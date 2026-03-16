// Source: https://leetcode.com/problems/replace-all-s-to-avoid-consecutive-repeating-characters/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s containing only lowercase English letters and the '?' character, convert all the '?' characters into lowercase letters such that the final string does not contain any consecutive repeating characters. You cannot modify the non '?' characters.
//
// It is guaranteed that there are no consecutive repeating characters in the given string except for '?'.
//
// Return the final string after all the conversions (possibly zero) have been made. If there is more than one solution, return any of them. It can be shown that an answer is always possible with the given constraints.
//
// Example:
// Input: s = "?zs"
// Output: "azs"
// Explanation: There are 25 solutions for this problem. From "azs" to "yzs", all are valid. Only "z" is an invalid modification as the string will consist of consecutive repeating characters in "zzs".
//
// Constraints:
// 1 <= s.length <= 100
// 	s consist of lowercase English letters and '?'.
//

char* modifyString(char* s) {
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        if (s[i] == '?') {
            for (char c = 'a'; c <= 'z'; c++) {
                if ((i > 0 && s[i - 1] == c) || (i < len - 1 && s[i + 1] == c)) {
                    continue;
                }
                s[i] = c;
                break;
            }
        }
    }
    return s;       
}
