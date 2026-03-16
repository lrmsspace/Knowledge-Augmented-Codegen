// Source: https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s and an integer k. Your task is to find the maximum difference between the frequency of two characters, freq[a] - freq[b], in a substring subs of s, such that:
//
//
// 	subs has a size of at least k.
// 	Character a has an odd frequency in subs.
// 	Character b has a non-zero even frequency in subs.
//
//
// Return the maximum difference.
//
// Note that subs can contain more than 2 distinct characters.
//
// Example:
// Input: s = "12233", k = 4
//
// Output: -1
//
// Explanation:
//
// For the substring "12233", the frequency of '1' is 1 and the frequency of '3' is 2. The difference is 1 - 2 = -1.
//
// Constraints:
// 3 <= s.length <= 3 * 104
// 	s consists only of digits '0' to '4'.
// 	The input is generated that at least one substring has a character with an even frequency and a character with an odd frequency.
// 	1 <= k <= s.length
//

class Solution {
    public int maxDifference(String s, int k) {
        int n = s.length();
        int[][] freq = new int[5][n + 1];

        for (int i = 0; i < n; i++) {
            int digit = s.charAt(i) - '0';
            for (int d = 0; d < 5; d++) {
                freq[d][i + 1] = freq[d][i] + (d == digit ? 1 : 0);
            }
        }

        int maxDiff = -1;

        for (int start = 0; start <= n - k; start++) {
            for (int end = start + k; end <= n; end++) {
                for (int a = 0; a < 5; a++) {
                    int freqA = freq[a][end] - freq[a][start];
                    if (freqA % 2 == 1) {
                        for (int b = 0; b < 5; b++) {
                            if (a != b) {
                                int freqB = freq[b][end] - freq[b][start];
                                if (freqB > 0 && freqB % 2 == 0) {
                                    maxDiff = Math.max(maxDiff, freqA - freqB);
                                }
                            }
                        }
                    }
                }
            }
        }

        return maxDiff;         
    }
}
