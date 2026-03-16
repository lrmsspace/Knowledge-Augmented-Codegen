// Source: https://leetcode.com/problems/verifying-an-alien-dictionary/   |   Difficulty: Easy
//
// Problem Description:
// In an alien language, surprisingly, they also use English lowercase letters, but possibly in a different order. The order of the alphabet is some permutation of lowercase letters.
//
// Given a sequence of words written in the alien language, and the order of the alphabet, return true if and only if the given words are sorted lexicographically in this alien language.
//
// Example:
// Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
// Output: true
// Explanation: As 'h' comes before 'l' in this language, then the sequence is sorted.
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 20
// 	order.length == 26
// 	All characters in words[i] and order are English lowercase letters.
//

bool isAlienSorted(char** words, int wordsSize, char* order) {
    int order_map[26];
    for (int i = 0; i < 26; i++) {
        order_map[order[i] - 'a'] = i;
    }

    for (int i = 0; i < wordsSize - 1; i++) {
        char* word1 = words[i];
        char* word2 = words[i + 1];
        int j = 0;

        while (word1[j] && word2[j]) {
            if (order_map[word1[j] - 'a'] < order_map[word2[j] - 'a']) {
                break;
            } else if (order_map[word1[j] - 'a'] > order_map[word2[j] - 'a']) {
                return false;
            }
            j++;
        }

        if (word1[j] && !word2[j]) {
            return false;
        }
    }

    return true;        
}
