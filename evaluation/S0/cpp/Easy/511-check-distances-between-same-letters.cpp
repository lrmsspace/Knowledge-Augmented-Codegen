// Source: https://leetcode.com/problems/check-distances-between-same-letters/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed string s consisting of only lowercase English letters, where each letter in s appears exactly twice. You are also given a 0-indexed integer array distance of length 26.
//
// Each letter in the alphabet is numbered from 0 to 25 (i.e. 'a' -> 0, 'b' -> 1, 'c' -> 2, ... , 'z' -> 25).
//
// In a well-spaced string, the number of letters between the two occurrences of the ith letter is distance[i]. If the ith letter does not appear in s, then distance[i] can be ignored.
//
// Return true if s is a well-spaced string, otherwise return false.
//
// Example:
// Input: s = "abaccb", distance = [1,3,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
// Output: true
// Explanation:
// - 'a' appears at indices 0 and 2 so it satisfies distance[0] = 1.
// - 'b' appears at indices 1 and 5 so it satisfies distance[1] = 3.
// - 'c' appears at indices 3 and 4 so it satisfies distance[2] = 0.
// Note that distance[3] = 5, but since 'd' does not appear in s, it can be ignored.
// Return true because s is a well-spaced string.
//
// Constraints:
// 2 <= s.length <= 52
// 	s consists only of lowercase English letters.
// 	Each letter appears in s exactly twice.
// 	distance.length == 26
// 	0 <= distance[i] <= 50
//

class Solution {
public:
    bool checkDistances(string s, vector<int>& distance) {
        unordered_map<char, int> first_occurrence;

        for (int i = 0; i < s.length(); ++i) {
            char ch = s[i];
            if (first_occurrence.find(ch) == first_occurrence.end()) {
                first_occurrence[ch] = i;
            } else {
                int expected_distance = distance[ch - 'a'];
                int actual_distance = i - first_occurrence[ch] - 1;
                if (expected_distance != actual_distance) {
                    return false;
                }
            }
        }

        return true;            
    }
};
