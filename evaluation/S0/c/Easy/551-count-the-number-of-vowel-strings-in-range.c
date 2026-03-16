// Source: https://leetcode.com/problems/count-the-number-of-vowel-strings-in-range/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed array of string words and two integers left and right.
//
// A string is called a vowel string if it starts with a vowel character and ends with a vowel character where vowel characters are 'a', 'e', 'i', 'o', and 'u'.
//
// Return the number of vowel strings words[i] where i belongs to the inclusive range [left, right].
//
// Example:
// Input: words = ["are","amy","u"], left = 0, right = 2
// Output: 2
// Explanation: 
// - "are" is a vowel string because it starts with 'a' and ends with 'e'.
// - "amy" is not a vowel string because it does not end with a vowel.
// - "u" is a vowel string because it starts with 'u' and ends with 'u'.
// The number of vowel strings in the mentioned range is 2.
//
// Constraints:
// 1 <= words.length <= 1000
// 	1 <= words[i].length <= 10
// 	words[i] consists of only lowercase English letters.
// 	0 <= left <= right < words.length
//

int vowelStrings(char** words, int wordsSize, int left, int right) {
    int count = 0;
    for (int i = left; i <= right; i++) {
        int len = strlen(words[i]);
        char firstChar = words[i][0];
        char lastChar = words[i][len - 1];
        if ((firstChar == 'a' || firstChar == 'e' || firstChar == 'i' || firstChar == 'o' || firstChar == 'u') &&
            (lastChar == 'a' || lastChar == 'e' || lastChar == 'i' || lastChar == 'o' || lastChar == 'u')) {
            count++;
        }
    }
    return count;       
}
