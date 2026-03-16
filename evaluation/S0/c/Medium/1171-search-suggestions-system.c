// Source: https://leetcode.com/problems/search-suggestions-system/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of strings products and a string searchWord.
//
// Design a system that suggests at most three product names from products after each character of searchWord is typed. Suggested products should have common prefix with searchWord. If there are more than three products with a common prefix return the three lexicographically minimums products.
//
// Return a list of lists of the suggested products after each character of searchWord is typed.
//
// Example:
// Input: products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
// Output: [["mobile","moneypot","monitor"],["mobile","moneypot","monitor"],["mouse","mousepad"],["mouse","mousepad"],["mouse","mousepad"]]
// Explanation: products sorted lexicographically = ["mobile","moneypot","monitor","mouse","mousepad"].
// After typing m and mo all products match and we show user ["mobile","moneypot","monitor"].
// After typing mou, mous and mouse the system suggests ["mouse","mousepad"].
//
// Constraints:
// 1 <= products.length <= 1000
// 	1 <= products[i].length <= 3000
// 	1 <= sum(products[i].length) <= 2 * 104
// 	All the strings of products are unique.
// 	products[i] consists of lowercase English letters.
// 	1 <= searchWord.length <= 1000
// 	searchWord consists of lowercase English letters.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** suggestedProducts(char** products, int productsSize, char* searchWord, int* returnSize, int** returnColumnSizes) {
    // Sort products lexicographically
    qsort(products, productsSize, sizeof(char*), (int (*)(const void*, const void*))strcmp);

    int searchLen = strlen(searchWord);
    char*** result = (char***)malloc(searchLen * sizeof(char**));
    *returnColumnSizes = (int*)malloc(searchLen * sizeof(int));
    *returnSize = searchLen;

    for (int i = 0; i < searchLen; i++) {
        char prefix[searchLen + 1];
        strncpy(prefix, searchWord, i + 1);
        prefix[i + 1] = '\0';

        result[i] = (char**)malloc(3 * sizeof(char*));
        int count = 0;

        for (int j = 0; j < productsSize && count < 3; j++) {
            if (strncmp(products[j], prefix, i + 1) == 0) {
                result[i][count++] = products[j];
            }
        }

        *returnColumnSizes[i] = count;
    }

    return result;      
}
