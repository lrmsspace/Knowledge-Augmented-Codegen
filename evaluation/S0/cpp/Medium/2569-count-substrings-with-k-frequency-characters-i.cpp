// Source: https://leetcode.com/problems/count-substrings-with-k-frequency-characters-i/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s and an integer k, return the total number of substrings of s where at least one character appears at least k times.
//
// Example:
// Input: s = "abacb", k = 2
//
// Output: 4
//
// Explanation:
//
// The valid substrings are:
//
//
// 	"aba" (character 'a' appears 2 times).
// 	"abac" (character 'a' appears 2 times).
// 	"abacb" (character 'a' appears 2 times).
// 	"bacb" (character 'b' appears 2 times).
//
// Constraints:
// 1 <= s.length <= 3000
// 	1 <= k <= s.length
// 	s consists only of lowercase English letters.
//

class Solution {
public:
    int numberOfSubstrings(string s, int k) {
        int n = s.size();
        int result = 0;

        for (int start = 0; start < n; ++start) {
            vector<int> charCount(26, 0);
            for (int end = start; end < n; ++end) {
                charCount[s[end] - 'a']++;
                if (charCount[s[end] - 'a'] == k) {
                    result += (n - end);
                    break;
                }
            }
        }

        return result;          
    }
};
