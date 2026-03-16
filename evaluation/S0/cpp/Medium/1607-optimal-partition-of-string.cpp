// Source: https://leetcode.com/problems/optimal-partition-of-string/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, partition the string into one or more substrings such that the characters in each substring are unique. That is, no letter appears in a single substring more than once.
//
// Return the minimum number of substrings in such a partition.
//
// Note that each character should belong to exactly one substring in a partition.
//
// Example:
// Input: s = "abacaba"
// Output: 4
// Explanation:
// Two possible partitions are ("a","ba","cab","a") and ("ab","a","ca","ba").
// It can be shown that 4 is the minimum number of substrings needed.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of only English lowercase letters.
//

class Solution {
public:
    int partitionString(string s) {
        int count = 1;
        unordered_set<char> seen;

        for (char c : s) {
            if (seen.count(c)) {
                count++;
                seen.clear();
            }
            seen.insert(c);
        }

        return count;           
    }
};
