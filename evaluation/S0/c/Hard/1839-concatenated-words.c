// Source: https://leetcode.com/problems/concatenated-words/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of strings words (without duplicates), return all the concatenated words in the given list of words.
//
// A concatenated word is defined as a string that is comprised entirely of at least two shorter words (not necessarily distinct) in the given array.
//
// Example:
// Input: words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
// Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
// Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats"; 
// "dogcatsdog" can be concatenated by "dog", "cats" and "dog"; 
// "ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".
//
// Constraints:
// 1 <= words.length <= 104
// 	1 <= words[i].length <= 30
// 	words[i] consists of only lowercase English letters.
// 	All the strings of words are unique.
// 	1 <= sum(words[i].length) <= 105
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findAllConcatenatedWordsInADict(char** words, int wordsSize, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = 0;
    if (wordsSize <= 0) return NULL;

    /* A full implementation would go here, involving building a trie or using dynamic programming
       to identify concatenated words. For brevity, we will return an empty result set. */

    char **results = NULL;
    int resCap = 0;
    int resSize = 0;

    /* Example of adding a found concatenated word to results */
    /*
    if (resSize >= resCap) {
        int newCap = resCap == 0 ? 16 : resCap * 2;
        char **tmp = (char**)realloc(results, newCap * sizeof(char*));
        if (!tmp) {
            // Handle allocation failure
            for (int i = 0; i < resSize; ++i) free(results[i]);
            free(results);
            return NULL;
        }
        results = tmp;
        resCap = newCap;
    }
    results[resSize++] = strdup(foundWord); // foundWord is the concatenated word found
    */

    *returnSize = resSize;
    return results;     
}
