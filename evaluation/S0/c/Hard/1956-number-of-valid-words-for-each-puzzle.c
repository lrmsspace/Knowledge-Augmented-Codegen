// Source: https://leetcode.com/problems/number-of-valid-words-for-each-puzzle/   |   Difficulty: Hard
//
// Problem Description:
// With respect to a given puzzle string, a word is valid if both the following conditions are satisfied:
//
// 	word contains the first letter of puzzle.
// 	For each letter in word, that letter is in puzzle.
// 	
// 		For example, if the puzzle is "abcdefg", then valid words are "faced", "cabbage", and "baggage", while
// 		invalid words are "beefed" (does not include 'a') and "based" (includes 's' which is not in the puzzle).
// 	
// 	
//
// Return an array answer, where answer[i] is the number of words in the given word list words that is valid with respect to the puzzle puzzles[i].
//
// Example:
// Input: words = ["aaaa","asas","able","ability","actt","actor","access"], puzzles = ["aboveyz","abrodyz","abslute","absoryz","actresz","gaswxyz"]
// Output: [1,1,3,2,4,0]
// Explanation: 
// 1 valid word for "aboveyz" : "aaaa" 
// 1 valid word for "abrodyz" : "aaaa"
// 3 valid words for "abslute" : "aaaa", "asas", "able"
// 2 valid words for "absoryz" : "aaaa", "asas"
// 4 valid words for "actresz" : "aaaa", "asas", "actt", "access"
// There are no valid words for "gaswxyz" cause none of the words in the list contains letter 'g'.
//
// Constraints:
// 1 <= words.length <= 105
// 	4 <= words[i].length <= 50
// 	1 <= puzzles.length <= 104
// 	puzzles[i].length == 7
// 	words[i] and puzzles[i] consist of lowercase English letters.
// 	Each puzzles[i] does not contain repeated characters.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findNumOfValidWords(char** words, int wordsSize, char** puzzles, int puzzlesSize, int* returnSize) {
    if (!returnSize) return NULL;
    int *res = (int*)calloc(puzzlesSize, sizeof(int));
    if (!res) return NULL;

    /* Preprocess words into bitmask frequency map */
    #define MAX_MASKS (1 << 26)
    int *freq = (int*)calloc(MAX_MASKS, sizeof(int));
    if (!freq) { free(res); return NULL; }

    for (int i = 0; i < wordsSize; ++i) {
        int mask = 0;
        for (char *p = words[i]; *p; ++p) {
            mask |= 1 << (*p - 'a');
        }
        /* Only consider words with up to 7 unique letters */
        if (__builtin_popcount(mask) <= 7) {
            freq[mask]++;
        }
    }

    /* Process each puzzle */
    for (int i = 0; i < puzzlesSize; ++i) {
        int firstCharMask = 1 << (puzzles[i][0] - 'a');
        int puzzleMask = 0;
        for (int j = 0; j < 7; ++j) {
            puzzleMask |= 1 << (puzzles[i][j] - 'a');
        }

        /* Enumerate all subsets of puzzleMask that include firstCharMask */
        int submask = puzzleMask;
        while (submask) {
            if ((submask & firstCharMask) == firstCharMask) {
                res[i] += freq[submask];
            }
            submask = (submask - 1) & puzzleMask;
        }
    }

    free(freq);
    *returnSize = puzzlesSize;
    return res;     
}
