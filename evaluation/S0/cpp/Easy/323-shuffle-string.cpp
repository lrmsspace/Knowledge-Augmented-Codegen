// Source: https://leetcode.com/problems/shuffle-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s and an integer array indices of the same length. The string s will be shuffled such that the character at the ith position moves to indices[i] in the shuffled string.
//
// Return the shuffled string.
//
// Example:
// Input: s = "codeleet", indices = [4,5,6,7,0,2,1,3]
// Output: "leetcode"
// Explanation: As shown, "codeleet" becomes "leetcode" after shuffling.
//
// Constraints:
// s.length == indices.length == n
// 	1 <= n <= 100
// 	s consists of only lowercase English letters.
// 	0 <= indices[i] < n
// 	All values of indices are unique.
//

class Solution {
public:
    string restoreString(string s, vector<int>& indices) {
        string shuffled(s.size(), ' ');
        for (size_t i = 0; i < s.size(); ++i) {
            shuffled[indices[i]] = s[i];
        }
        return shuffled;            
    }
};
