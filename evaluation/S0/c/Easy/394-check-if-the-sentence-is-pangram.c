// Source: https://leetcode.com/problems/check-if-the-sentence-is-pangram/   |   Difficulty: Easy
//
// Problem Description:
// A pangram is a sentence where every letter of the English alphabet appears at least once.
//
// Given a string sentence containing only lowercase English letters, return true if sentence is a pangram, or false otherwise.
//
// Example:
// Input: sentence = "thequickbrownfoxjumpsoverthelazydog"
// Output: true
// Explanation: sentence contains at least one of every letter of the English alphabet.
//
// Constraints:
// 1 <= sentence.length <= 1000
// 	sentence consists of lowercase English letters.
//

bool checkIfPangram(char* sentence) {
    int letters[26] = {0};
    int unique_count = 0;

    for (int i = 0; sentence[i] != '\0'; i++) {
        int index = sentence[i] - 'a';
        if (letters[index] == 0) {
            letters[index] = 1;
            unique_count++;
            if (unique_count == 26) {
                return true;
            }
        }
    }

    return false;       
}
