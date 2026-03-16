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

class Solution {
public:
    int shortestMatchingSubstring(string s, string p) {
        int n = s.size();
        int m = p.size();
        
        // Split pattern p into three parts: prefix, middle, suffix
        int firstStar = p.find('*');
        int secondStar = p.find('*', firstStar + 1);
        
        string prefix = p.substr(0, firstStar);
        string middle = p.substr(firstStar + 1, secondStar - firstStar - 1);
        string suffix = p.substr(secondStar + 1);
        
        int minLength = INT_MAX;
        
        // Try every possible starting position for the prefix
        for (int i = 0; i <= n - prefix.size(); i++) {
            if (s.substr(i, prefix.size()) == prefix) {
                // Found a match for the prefix
                int start = i + prefix.size();
                
                // Now find the middle part
                int midPos = s.find(middle, start);
                if (midPos != string::npos) {
                    // Found a match for the middle part
                    int end = midPos + middle.size();
                    
                    // Now find the suffix part
                    int sufPos = s.find(suffix, end);
                    if (sufPos != string::npos) {
                        // Found a match for the suffix part
                        int totalLength = sufPos + suffix.size() - i;
                        minLength = min(minLength, totalLength);
                    }
                }
            }
        }
        
        return (minLength == INT_MAX) ? -1 : minLength;         
    }
};
