// Source: https://leetcode.com/problems/longest-palindrome-by-concatenating-two-letter-words/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of strings words. Each element of words consists of two lowercase English letters.
//
// Create the longest possible palindrome by selecting some elements from words and concatenating them in any order. Each element can be selected at most once.
//
// Return the length of the longest palindrome that you can create. If it is impossible to create any palindrome, return 0.
//
// A palindrome is a string that reads the same forward and backward.
//
// Example:
// Input: words = ["lc","cl","gg"]
// Output: 6
// Explanation: One longest palindrome is "lc" + "gg" + "cl" = "lcggcl", of length 6.
// Note that "clgglc" is another longest palindrome that can be created.
//
// Constraints:
// 1 <= words.length <= 105
// 	words[i].length == 2
// 	words[i] consists of lowercase English letters.
//

int longestPalindrome(char** words, int wordsSize) {
    int count[26][26];
    memset(count, 0, sizeof(count));
    int length = 0;
    int hasOddCenter = 0;

    for (int i = 0; i < wordsSize; i++) {
        int firstCharIndex = words[i][0] - 'a';
        int secondCharIndex = words[i][1] - 'a';

        if (count[secondCharIndex][firstCharIndex] > 0) {
            length += 4;
            count[secondCharIndex][firstCharIndex]--;
        } else {
            count[firstCharIndex][secondCharIndex]++;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (count[i][i] > 0) {
            hasOddCenter = 1;
            break;
        }
    }

    return length + hasOddCenter * 2;       
}
