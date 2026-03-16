// Source: https://leetcode.com/problems/longest-substring-of-all-vowels-in-order/   |   Difficulty: Medium
//
// Problem Description:
// A string is considered beautiful if it satisfies the following conditions:
//
//
// 	Each of the 5 English vowels ('a', 'e', 'i', 'o', 'u') must appear at least once in it.
// 	The letters must be sorted in alphabetical order (i.e. all 'a's before 'e's, all 'e's before 'i's, etc.).
//
//
// For example, strings "aeiou" and "aaaaaaeiiiioou" are considered beautiful, but "uaeio", "aeoiu", and "aaaeeeooo" are not beautiful.
//
// Given a string word consisting of English vowels, return the length of the longest beautiful substring of word. If no such substring exists, return 0.
//
// A substring is a contiguous sequence of characters in a string.
//
// Example:
// Input: word = "aeiaaioaaaaeiiiiouuuooaauuaeiu"
// Output: 13
// Explanation: The longest beautiful substring in word is "aaaaeiiiiouuu" of length 13.
//
// Constraints:
// 1 <= word.length <= 5 * 105
// 	word consists of characters 'a', 'e', 'i', 'o', and 'u'.
//

int longestBeautifulSubstring(char* word) {
    int max_len = 0;
    int curr_len = 1;
    int vowel_count = 1; // Count of distinct vowels in current substring

    for (int i = 1; word[i] != '\0'; i++) {
        if (word[i] < word[i - 1]) {
            // Vowels are not in order, reset counters
            curr_len = 1;
            vowel_count = 1;
        } else if (word[i] == word[i - 1]) {
            // Same vowel, just extend the current length
            curr_len++;
        } else {
            // New vowel found in order
            curr_len++;
            vowel_count++;
        }

        // If all 5 vowels are present, check for max length
        if (vowel_count == 5) {
            if (curr_len > max_len) {
                max_len = curr_len;
            }
        }
    }

    return max_len;     
}
