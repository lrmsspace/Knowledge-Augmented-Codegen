// Source: https://leetcode.com/problems/check-if-two-string-arrays-are-equivalent/   |   Difficulty: Easy
//
// Problem Description:
// Given two string arrays word1 and word2, return true if the two arrays represent the same string, and false otherwise.
//
// A string is represented by an array if the array elements concatenated in order forms the string.
//
// Example:
// Input: word1 = ["ab", "c"], word2 = ["a", "bc"]
// Output: true
// Explanation:
// word1 represents string "ab" + "c" -> "abc"
// word2 represents string "a" + "bc" -> "abc"
// The strings are the same, so return true.
//
// Constraints:
// 1 <= word1.length, word2.length <= 103
// 	1 <= word1[i].length, word2[i].length <= 103
// 	1 <= sum(word1[i].length), sum(word2[i].length) <= 103
// 	word1[i] and word2[i] consist of lowercase letters.
//

bool arrayStringsAreEqual(char** word1, int word1Size, char** word2, int word2Size) {
    int i = 0, j = 0; // indices for word1 and word2
    int p1 = 0, p2 = 0; // indices for characters within the current strings of word1 and word2

    while (i < word1Size && j < word2Size) {
        if (word1[i][p1] != word2[j][p2]) {
            return false; // characters do not match
        }

        // Move to the next character in word1
        p1++;
        if (word1[i][p1] == '\0') {
            i++; // move to the next string in word1
            p1 = 0; // reset character index for word1
        }

        // Move to the next character in word2
        p2++;
        if (word2[j][p2] == '\0') {
            j++; // move to the next string in word2
            p2 = 0; // reset character index for word2
        }
    }

    // Check if both arrays have been fully traversed
    return i == word1Size && j == word2Size;        
}
