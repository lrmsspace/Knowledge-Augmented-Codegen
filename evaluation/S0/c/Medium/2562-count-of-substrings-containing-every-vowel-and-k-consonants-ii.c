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

long long countOfSubstrings(char* word, int k) {
    int n = strlen(word);
    int left = 0, right = 0;
    int vowelCount[5] = {0}; // a, e, i, o, u
    int consonantCount = 0;
    long long result = 0;

    while (right < n) {
        // Expand the window by including the character at 'right'
        if (strchr("aeiou", word[right])) {
            switch (word[right]) {
                case 'a': vowelCount[0]++; break;
                case 'e': vowelCount[1]++; break;
                case 'i': vowelCount[2]++; break;
                case 'o': vowelCount[3]++; break;
                case 'u': vowelCount[4]++; break;
            }
        } else {
            consonantCount++;
        }

        // Shrink the window from the left if we have more than k consonants
        while (consonantCount > k) {
            if (strchr("aeiou", word[left])) {
                switch (word[left]) {
                    case 'a': vowelCount[0]--; break;
                    case 'e': vowelCount[1]--; break;
                    case 'i': vowelCount[2]--; break;
                    case 'o': vowelCount[3]--; break;
                    case 'u': vowelCount[4]--; break;
                }
            } else {
                consonantCount--;
            }
            left++;
        }

        // Check if we have all vowels at least once and exactly k consonants
        if (consonantCount == k &&
            vowelCount[0] > 0 && vowelCount[1] > 0 &&
            vowelCount[2] > 0 && vowelCount[3] > 0 &&
            vowelCount[4] > 0) {
            result += (left + 1); // Count valid substrings ending at 'right'
        }

        right++;
    }

    return result;      
}
