// Source: https://leetcode.com/problems/count-pairs-of-similar-strings/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed string array words.
//
// Two strings are similar if they consist of the same characters.
//
//
// 	For example, "abca" and "cba" are similar since both consist of characters 'a', 'b', and 'c'.
// 	However, "abacba" and "bcfd" are not similar since they do not consist of the same characters.
//
//
// Return the number of pairs (i, j) such that 0 <= i < j <= word.length - 1 and the two strings words[i] and words[j] are similar.
//
// Example:
// Input: words = ["aba","aabb","abcd","bac","aabc"]
// Output: 2
// Explanation: There are 2 pairs that satisfy the conditions:
// - i = 0 and j = 1 : both words[0] and words[1] only consist of characters 'a' and 'b'. 
// - i = 3 and j = 4 : both words[3] and words[4] only consist of characters 'a', 'b', and 'c'.
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 100
// 	words[i] consist of only lowercase English letters.
//

int similarPairs(char** words, int wordsSize) {
    int count = 0;
    for (int i = 0; i < wordsSize - 1; i++) {
        for (int j = i + 1; j < wordsSize; j++) {
            int charSet1[26] = {0};
            int charSet2[26] = {0};
            for (int k = 0; words[i][k] != '\0'; k++) {
                charSet1[words[i][k] - 'a'] = 1;
            }
            for (int k = 0; words[j][k] != '\0'; k++) {
                charSet2[words[j][k] - 'a'] = 1;
            }
            int similar = 1;
            for (int k = 0; k < 26; k++) {
                if (charSet1[k] != charSet2[k]) {
                    similar = 0;
                    break;
                }
            }
            if (similar) {
                count++;
            }
        }
    }
    return count;       
}
