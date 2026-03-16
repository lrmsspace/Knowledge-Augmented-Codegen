// Source: https://leetcode.com/problems/count-of-substrings-containing-every-vowel-and-k-consonants-i/   |   Difficulty: Medium
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
// 5 <= word.length <= 250
// 	word consists only of lowercase English letters.
// 	0 <= k <= word.length - 5
//

int countOfSubstrings(char* word, int k) {
    int n = strlen(word);
    int count = 0;

    for (int i = 0; i < n; i++) {
        int vowelCount[5] = {0}; // a, e, i, o, u
        int consonantCount = 0;

        for (int j = i; j < n; j++) {
            char ch = word[j];

            if (ch == 'a') vowelCount[0]++;
            else if (ch == 'e') vowelCount[1]++;
            else if (ch == 'i') vowelCount[2]++;
            else if (ch == 'o') vowelCount[3]++;
            else if (ch == 'u') vowelCount[4]++;
            else consonantCount++;

            if (consonantCount > k) break;

            if (vowelCount[0] > 0 && vowelCount[1] > 0 && vowelCount[2] > 0 &&
                vowelCount[3] > 0 && vowelCount[4] > 0 && consonantCount == k) {
                count++;
            }
        }
    }

    return count;       
}
