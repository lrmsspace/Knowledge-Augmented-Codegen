// Source: https://leetcode.com/problems/orderly-queue/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s and an integer k. You can choose one of the first k letters of s and append it at the end of the string.
//
// Return the lexicographically smallest string you could have after applying the mentioned step any number of moves.
//
// Example:
// Input: s = "cba", k = 1
// Output: "acb"
// Explanation: 
// In the first move, we move the 1st character 'c' to the end, obtaining the string "bac".
// In the second move, we move the 1st character 'b' to the end, obtaining the final result "acb".
//
// Constraints:
// 1 <= k <= s.length <= 1000
// 	s consist of lowercase English letters.
//

class Solution {
public:
    string orderlyQueue(string s, int k) {
        if (k == 1) {
            string smallest = s;
            int n = s.size();
            for (int i = 1; i < n; i++) {
                string rotated = s.substr(i) + s.substr(0, i);
                if (rotated < smallest) {
                    smallest = rotated;
                }
            }
            return smallest;
        } else {
            sort(s.begin(), s.end());
            return s;
        }           
    }
};
