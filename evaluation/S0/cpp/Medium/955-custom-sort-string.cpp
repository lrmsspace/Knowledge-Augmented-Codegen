// Source: https://leetcode.com/problems/custom-sort-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings order and s. All the characters of order are unique and were sorted in some custom order previously.
//
// Permute the characters of s so that they match the order that order was sorted. More specifically, if a character x occurs before a character y in order, then x should occur before y in the permuted string.
//
// Return any permutation of s that satisfies this property.
//
// Example:
// Input:   order = "cba", s = "abcd" 
//
// Output:   "cbad" 
//
// Explanation:  "a", "b", "c" appear in order, so the order of "a", "b", "c" should be "c", "b", and "a".
//
// Since "d" does not appear in order, it can be at any position in the returned string. "dcba", "cdba", "cbda" are also valid outputs.
//
// Constraints:
// 1 <= order.length <= 26
// 	1 <= s.length <= 200
// 	order and s consist of lowercase English letters.
// 	All the characters of order are unique.
//

class Solution {
public:
    string customSortString(string order, string s) {
        unordered_map<char, int> orderMap;
        for (int i = 0; i < order.size(); ++i) {
            orderMap[order[i]] = i;
        }

        sort(s.begin(), s.end(), [&](char a, char b) {
            int orderA = orderMap.count(a) ? orderMap[a] : 26;
            int orderB = orderMap.count(b) ? orderMap[b] : 26;
            return orderA < orderB;
        });

        return s;           
    }
};
