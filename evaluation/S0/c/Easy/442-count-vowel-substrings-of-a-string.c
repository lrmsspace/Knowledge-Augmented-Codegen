// Source: https://leetcode.com/problems/count-vowel-substrings-of-a-string/   |   Difficulty: Easy
//
// Problem Description:
// A substring is a contiguous (non-empty) sequence of characters within a string.
//
// A vowel substring is a substring that only consists of vowels ('a', 'e', 'i', 'o', and 'u') and has all five vowels present in it.
//
// Given a string word, return the number of vowel substrings in word.
//
// Example:
// Input: word = "aeiouu"
// Output: 2
// Explanation: The vowel substrings of word are as follows (underlined):
// - "aeiouu"
// - "aeiouu"
//
// Constraints:
// 1 <= word.length <= 100
// 	word consists of lowercase English letters only.
//

int countVowelSubstrings(char* word) {
    int count = 0;
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        if (strchr("aeiou", word[i]) == NULL) {
            continue;
        }
        int vowels[5] = {0}; // a, e, i, o, u
        for (int j = i; j < len; j++) {
            if (strchr("aeiou", word[j]) == NULL) {
                break;
            }
            switch (word[j]) {
                case 'a': vowels[0]++; break;
                case 'e': vowels[1]++; break;
                case 'i': vowels[2]++; break;
                case 'o': vowels[3]++; break;
                case 'u': vowels[4]++; break;
            }
            if (vowels[0] > 0 && vowels[1] > 0 && vowels[2] > 0 && vowels[3] > 0 && vowels[4] > 0) {
                count++;
            }
        }
    }
    return count;       
}
