// Source: https://leetcode.com/problems/maximum-product-of-word-lengths/   |   Difficulty: Medium
//
// Problem Description:
// Given a string array words, return the maximum value of length(word[i]) * length(word[j]) where the two words do not share common letters. If no such two words exist, return 0.
//
// Example:
// Input: words = ["abcw","baz","foo","bar","xtfn","abcdef"]
// Output: 16
// Explanation: The two words can be "abcw", "xtfn".
//
// Constraints:
// 2 <= words.length <= 1000
// 	1 <= words[i].length <= 1000
// 	words[i] consists only of lowercase English letters.
//

int maxProduct(char** words, int wordsSize) {
    int max_product = 0;
    int* bit_masks = (int*)malloc(wordsSize * sizeof(int));

    for (int i = 0; i < wordsSize; i++) {
        int bit_mask = 0;
        for (char* p = words[i]; *p != '\0'; p++) {
            bit_mask |= 1 << (*p - 'a');
        }
        bit_masks[i] = bit_mask;
    }

    for (int i = 0; i < wordsSize; i++) {
        for (int j = i + 1; j < wordsSize; j++) {
            if ((bit_masks[i] & bit_masks[j]) == 0) {
                int product = strlen(words[i]) * strlen(words[j]);
                if (product > max_product) {
                    max_product = product;
                }
            }
        }
    }

    free(bit_masks);
    return max_product;     
}
