// Source: https://leetcode.com/problems/vowels-of-all-substrings/   |   Difficulty: Medium
//
// Problem Description:
// Given a string word, return the sum of the number of vowels ('a', 'e', 'i', 'o', and 'u') in every substring of word.
//
// A substring is a contiguous (non-empty) sequence of characters within a string.
//
// Note: Due to the large constraints, the answer may not fit in a signed 32-bit integer. Please be careful during the calculations.
//
// Example:
// Input: word = "aba"
// Output: 6
// Explanation: 
// All possible substrings are: "a", "ab", "aba", "b", "ba", and "a".
// - "b" has 0 vowels in it
// - "a", "ab", "ba", and "a" have 1 vowel each
// - "aba" has 2 vowels in it
// Hence, the total sum of vowels = 0 + 1 + 1 + 1 + 1 + 2 = 6.
//
// Constraints:
// 1 <= word.length <= 105
// 	word consists of lowercase English letters.
//

long long countVowels(char* word) {
    long long result = 0;
    long long length = 0;
    
    for (long long i = 0; word[i] != '\0'; i++) {
        length++;
    }
    
    for (long long i = 0; i < length; i++) {
        char c = word[i];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            long long leftOptions = i + 1;
            long long rightOptions = length - i;
            result += leftOptions * rightOptions;
        }
    }
    
    return result;      
}
