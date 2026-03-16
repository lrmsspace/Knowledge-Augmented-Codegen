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

int maxDifference(char* s) {
    int freq[26] = {0};
    for (int i = 0; s[i] != '\0'; i++) {
        freq[s[i] - 'a']++;
    }

    int max_odd = -1;
    int min_even = 101;

    for (int i = 0; i < 26; i++) {
        if (freq[i] % 2 == 1) { // odd frequency
            if (freq[i] > max_odd) {
                max_odd = freq[i];
            }
        } else if (freq[i] % 2 == 0 && freq[i] > 0) { // even frequency
            if (freq[i] < min_even) {
                min_even = freq[i];
            }
        }
    }

    return max_odd - min_even;      
}
