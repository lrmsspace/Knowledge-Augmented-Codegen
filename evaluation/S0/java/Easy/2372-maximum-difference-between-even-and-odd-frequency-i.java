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
    public int maxDifference(String s) {
        int[] freq = new int[26];
        for (char c : s.toCharArray()) {
            freq[c - 'a']++;
        }

        int maxOdd = Integer.MIN_VALUE;
        int minEven = Integer.MAX_VALUE;

        for (int f : freq) {
            if (f % 2 == 1) {
                maxOdd = Math.max(maxOdd, f);
            } else if (f % 2 == 0 && f > 0) {
                minEven = Math.min(minEven, f);
            }
        }

        return maxOdd - minEven;            
    }
}
