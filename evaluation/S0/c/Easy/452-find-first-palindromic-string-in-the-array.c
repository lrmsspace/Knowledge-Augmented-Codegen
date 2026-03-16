// Source: https://leetcode.com/problems/find-first-palindromic-string-in-the-array/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of strings words, return the first palindromic string in the array. If there is no such string, return an empty string "".
//
// A string is palindromic if it reads the same forward and backward.
//
// Example:
// Input: words = ["abc","car","ada","racecar","cool"]
// Output: "ada"
// Explanation: The first string that is palindromic is "ada".
// Note that "racecar" is also palindromic, but it is not the first.
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 100
// 	words[i] consists only of lowercase English letters.
//

char* firstPalindrome(char** words, int wordsSize) {
    for (int i = 0; i < wordsSize; i++) {
        char* word = words[i];
        int left = 0;
        int right = strlen(word) - 1;
        int is_palindrome = 1;

        while (left < right) {
            if (word[left] != word[right]) {
                is_palindrome = 0;
                break;
            }
            left++;
            right--;
        }

        if (is_palindrome) {
            return word;
        }
    }

    return "";      
}
