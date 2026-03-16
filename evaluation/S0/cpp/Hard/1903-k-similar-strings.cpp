// Source: https://leetcode.com/problems/k-similar-strings/   |   Difficulty: Hard
//
// Problem Description:
// Strings s1 and s2 are k-similar (for some non-negative integer k) if we can swap the positions of two letters in s1 exactly k times so that the resulting string equals s2.
//
// Given two anagrams s1 and s2, return the smallest k for which s1 and s2 are k-similar.
//
// Example:
// Input: s1 = "ab", s2 = "ba"
// Output: 1
// Explanation: The two string are 1-similar because we can use one swap to change s1 to s2: "ab" --> "ba".
//
// Constraints:
// 1 <= s1.length <= 20
// 	s2.length == s1.length
// 	s1 and s2 contain only lowercase letters from the set {'a', 'b', 'c', 'd', 'e', 'f'}.
// 	s2 is an anagram of s1.
//

class Solution {
public:
    int kSimilarity(string s1, string s2) {
        int n = s1.size();
        queue<pair<string, int>> q;
        unordered_set<string> visited;
        
        q.push({s1, 0});
        visited.insert(s1);
        
        while (!q.empty()) {
            auto [curr, steps] = q.front();
            q.pop();
            
            if (curr == s2) {
                return steps;
            }
            
            int i = 0;
            while (i < n && curr[i] == s2[i]) {
                i++;
            }
            
            for (int j = i + 1; j < n; j++) {
                if (curr[j] == s2[i] && curr[j] != s2[j]) {
                    string next = curr;
                    swap(next[i], next[j]);
                    
                    if (visited.find(next) == visited.end()) {
                        visited.insert(next);
                        q.push({next, steps + 1});
                    }
                }
            }
        }
        
        return -1; // Should never reach here           
    }
};
