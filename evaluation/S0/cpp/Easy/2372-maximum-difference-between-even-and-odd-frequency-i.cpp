// Source: https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s consisting of lowercase English letters.
//
// Your task is to find the maximum difference diff = freq(a1) - freq(a2) between the frequency of characters a1 and a2 in the string such that:
//
//
// 	a1 has an odd frequency in the string.
// 	a2 has an even frequency in the string.
//
//
// Return this maximum difference.
//
// Example:
// Input: s = "aaaaabbc"
//
// Output: 3
//
// Explanation:
//
//
// 	The character 'a' has an odd frequency of 5, and 'b' has an even frequency of 2.
// 	The maximum difference is 5 - 2 = 3.
//
// Constraints:
// 3 <= s.length <= 100
// 	s consists only of lowercase English letters.
// 	s contains at least one character with an odd frequency and one with an even frequency.
//

class Solution {
public:
    int maxDifference(string s) {
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }

        int max_odd = INT_MIN;
        int min_even = INT_MAX;

        for (int f : freq) {
            if (f % 2 == 1) { // odd frequency
                max_odd = max(max_odd, f);
            } else if (f > 0) { // even frequency
                min_even = min(min_even, f);
            }
        }

        return max_odd - min_even;          
    }
};
