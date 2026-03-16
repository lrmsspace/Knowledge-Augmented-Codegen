// Source: https://leetcode.com/problems/count-of-substrings-containing-every-vowel-and-k-consonants-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string word and a non-negative integer k.
//
// Return the total number of substrings of word that contain every vowel ('a', 'e', 'i', 'o', and 'u') at least once and exactly k consonants.
//
// Example:
// Input: word = "aeioqq", k = 1
//
// Output: 0
//
// Explanation:
//
// There is no substring with every vowel.
//
// Constraints:
// 5 <= word.length <= 2 * 105
//  word consists only of lowercase English letters.
//  0 <= k <= word.length - 5
//

class Solution {
    public long countOfSubstrings(String word, int k) {
        int n = word.length();
        long result = 0;

        for (int i = 0; i < n; i++) {
            int[] vowelCount = new int[5];
            int consonantCount = 0;

            for (int j = i; j < n; j++) {
                char ch = word.charAt(j);

                if (isVowel(ch)) {
                    vowelCount[getVowelIndex(ch)]++;
                } else {
                    consonantCount++;
                }

                if (consonantCount > k) {
                    break;
                }

                if (consonantCount == k && allVowelsPresent(vowelCount)) {
                    result++;
                }
            }
        }

        return result;          
    }
}
