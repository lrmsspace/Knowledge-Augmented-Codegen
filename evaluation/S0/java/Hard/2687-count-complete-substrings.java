// Source: https://leetcode.com/problems/count-complete-substrings/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string word and an integer k.
//
// A substring s of word is complete if:
//
//
// 	Each character in s occurs exactly k times.
// 	The difference between two adjacent characters is at most 2. That is, for any two adjacent characters c1 and c2 in s, the absolute difference in their positions in the alphabet is at most 2.
//
//
// Return the number of complete substrings of word.
//
// A substring is a non-empty contiguous sequence of characters in a string.
//
// Example:
// Input: word = "igigee", k = 2
// Output: 3
// Explanation: The complete substrings where each character appears exactly twice and the difference between adjacent characters is at most 2 are: igigee, igigee, igigee.
//
// Constraints:
// 1 <= word.length <= 105
// 	word consists only of lowercase English letters.
// 	1 <= k <= word.length
//

class Solution {
    public int countCompleteSubstrings(String word, int k) {
        int n = word.length();
        int result = 0;

        for (int i = 0; i < n; i++) {
            int[] count = new int[26];
            int uniqueChars = 0;
            int maxFreq = 0;

            for (int j = i; j < n; j++) {
                char currentChar = word.charAt(j);
                int index = currentChar - 'a';

                if (j > i) {
                    char prevChar = word.charAt(j - 1);
                    if (Math.abs(currentChar - prevChar) > 2) {
                        break;
                    }
                }

                count[index]++;
                if (count[index] == 1) {
                    uniqueChars++;
                }
                maxFreq = Math.max(maxFreq, count[index]);

                if (maxFreq > k) {
                    break;
                }

                if (maxFreq == k && allCharsKTimes(count, k, uniqueChars)) {
                    result++;
                }
            }
        }

        return result;          
    }
}
