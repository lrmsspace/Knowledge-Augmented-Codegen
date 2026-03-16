// Source: https://leetcode.com/problems/remove-letter-to-equalize-frequency/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed string word, consisting of lowercase English letters. You need to select one index and remove the letter at that index from word so that the frequency of every letter present in word is equal.
//
// Return true if it is possible to remove one letter so that the frequency of all letters in word are equal, and false otherwise.
//
// Note:
//
//
// 	The frequency of a letter x is the number of times it occurs in the string.
// 	You must remove exactly one letter and cannot choose to do nothing.
//
// Example:
// Input: word = "abcc"
// Output: true
// Explanation: Select index 3 and delete it: word becomes "abc" and each character has a frequency of 1.
//
// Constraints:
// 2 <= word.length <= 100
// 	word consists of lowercase English letters only.
//

bool equalFrequency(char* word) {
    int freq[26] = {0};
    for (int i = 0; word[i]; i++) {
        freq[word[i] - 'a']++;
    }

    for (int i = 0; i < 26; i++) {
        if (freq[i] == 0) continue;

        freq[i]--;

        int target = -1;
        bool valid = true;
        for (int j = 0; j < 26; j++) {
            if (freq[j] == 0) continue;
            if (target == -1) {
                target = freq[j];
            } else if (freq[j] != target) {
                valid = false;
                break;
            }
        }

        if (valid) return true;

        freq[i]++;
    }

    return false;       
}
