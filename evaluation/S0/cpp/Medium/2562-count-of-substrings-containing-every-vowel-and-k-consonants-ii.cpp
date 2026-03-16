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
public:
    long long countOfSubstrings(string word, int k) {
        const int n = word.size();
        unordered_map<char, int> vowelCount;
        int left = 0, consonantCount = 0;
        long long result = 0;

        for (int right = 0; right < n; ++right) {
            char rightChar = word[right];
            if (isVowel(rightChar)) {
                vowelCount[rightChar]++;
            } else {
                consonantCount++;
            }

            while (consonantCount > k) {
                char leftChar = word[left++];
                if (isVowel(leftChar)) {
                    vowelCount[leftChar]--;
                    if (vowelCount[leftChar] == 0) {
                        vowelCount.erase(leftChar);
                    }
                } else {
                    consonantCount--;
                }
            }

            if (consonantCount == k && vowelCount.size() == 5) {
                result += countValidStarts(word, left, right);
            }
        }

        return result;          
    }
};
