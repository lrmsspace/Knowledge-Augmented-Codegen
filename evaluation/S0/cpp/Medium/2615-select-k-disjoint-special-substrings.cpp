// Source: https://leetcode.com/problems/select-k-disjoint-special-substrings/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s of length n and an integer k, determine whether it is possible to select k disjoint special substrings.
//
// A special substring is a substring where:
//
//
// 	Any character present inside the substring should not appear outside it in the string.
// 	The substring is not the entire string s.
//
//
// Note that all k substrings must be disjoint, meaning they cannot overlap.
//
// Return true if it is possible to select k such disjoint special substrings; otherwise, return false.
//
// Example:
// Input: s = "abcdbaefab", k = 2
//
// Output: true
//
// Explanation:
//
//
// 	We can select two disjoint special substrings: "cd" and "ef".
// 	"cd" contains the characters 'c' and 'd', which do not appear elsewhere in s.
// 	"ef" contains the characters 'e' and 'f', which do not appear elsewhere in s.
//
// Constraints:
// 2 <= n == s.length <= 5 * 104
// 	0 <= k <= 26
// 	s consists only of lowercase English letters.
//

class Solution {
public:
    bool maxSubstringLength(string s, int k) {
        vector<int> firstIndex(26, -1);
        vector<int> lastIndex(26, -1);
        
        for (int i = 0; i < s.size(); ++i) {
            int charIdx = s[i] - 'a';
            if (firstIndex[charIdx] == -1) {
                firstIndex[charIdx] = i;
            }
            lastIndex[charIdx] = i;
        }
        
        int count = 0;
        int i = 0;
        
        while (i < s.size()) {
            int charIdx = s[i] - 'a';
            int end = lastIndex[charIdx];
            bool isSpecial = true;
            
            for (int j = i; j <= end; ++j) {
                int innerCharIdx = s[j] - 'a';
                if (firstIndex[innerCharIdx] < i || lastIndex[innerCharIdx] > end) {
                    isSpecial = false;
                    break;
                }
                end = max(end, lastIndex[innerCharIdx]);
            }
            
            if (isSpecial && end > i) {
                count++;
                i = end + 1;
            } else {
                i++;
            }
        }
        
        return count >= k;          
    }
};
