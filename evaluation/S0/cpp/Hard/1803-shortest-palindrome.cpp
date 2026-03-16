// Source: https://leetcode.com/problems/shortest-palindrome/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s. You can convert s to a palindrome by adding characters in front of it.
//
// Return the shortest palindrome you can find by performing this transformation.
//
// Example:
// Input: s = "aacecaaa"
// Output: "aaacecaaa"
//
// Constraints:
// 0 <= s.length <= 5 * 104
// 	s consists of lowercase English letters only.
//

class Solution {
public:
    string shortestPalindrome(string s) {
        string rev_s = s;
        reverse(rev_s.begin(), rev_s.end());
        string l = s + "#" + rev_s;
        
        vector<int> p(l.size(), 0);
        for (int i = 1; i < l.size(); i++) {
            int j = p[i - 1];
            while (j > 0 && l[i] != l[j]) {
                j = p[j - 1];
            }
            if (l[i] == l[j]) {
                j++;
            }
            p[i] = j;
        }
        
        string add = rev_s.substr(0, s.size() - p.back());
        return add + s;         
    }
};
