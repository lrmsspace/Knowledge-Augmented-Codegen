// Source: https://leetcode.com/problems/group-anagrams/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of strings strs, group the anagrams together. You can return the answer in any order.
//
// Example:
// Input: strs = ["eat","tea","tan","ate","nat","bat"]
//
// Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
//
// Explanation:
//
//
// 	There is no string in strs that can be rearranged to form "bat".
// 	The strings "nat" and "tan" are anagrams as they can be rearranged to form each other.
// 	The strings "ate", "eat", and "tea" are anagrams as they can be rearranged to form each other.
//
// Constraints:
// 1 <= strs.length <= 104
// 	0 <= strs[i].length <= 100
// 	strs[i] consists of lowercase English letters.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - String Sorts (array, string, number, radix-sort, counting-sort)
//   • When to use: Use when sorting a large collection of fixed-length strings or integers, especially when the key range (alphabet size) is small. It is efficient for data with uniform key lengths.
//   • Idea: LSD Radix Sort sorts elements by processing digits or characters from the least significant to the most significant, using a stable counting sort for each position. It achieves a time complexity of O(W * (N + R)), where W is the key length, N is the number of items, and R is the radix.
//   • Invariants: After each pass 'd' (from 'w-1' down to '0'), the array 'a' is stably sorted based on characters from position 'd' to 'w-1'.; The 'count' array accurately reflects the frequency of each character at the current digit 'd' before cumulation.
//   • Tips: Utilize counting sort as the stable inner sorting algorithm for each digit pass.; Process characters or digits from right to left (least significant to most significant).
//   • Pitfalls: Inefficient for variable-length strings without proper padding or specialized handling.; Can be slower than comparison sorts for small input sizes or very large radix (R).
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    // Hash map to store grouped anagrams
    #define HASH_MAP_SIZE 10007

    typedef struct AnagramNode {
        char* key;
        char** anagrams;
        int count;
        int capacity;
        struct AnagramNode* next;
    } AnagramNode;

    AnagramNode* hashMap[HASH_MAP_SIZE] = {0};

    unsigned long hashFunction(const char* str) {
        unsigned long hash = 5381;
        int c;
        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        return hash % HASH_MAP_SIZE;
    }

    char* getKey(char* str) {
        int count[26] = {0};
        for (char* p = str; *p; p++) {
            count[*p - 'a']++;
        }
        static char key[27];
        for (int i = 0; i < 26; i++) {
            key[i] = count[i] + 'a';
        }
        key[26] = '\0';
        return key;
    }

    for (int i = 0; i < strsSize; i++) {
        char* key = getKey(strs[i]);
        unsigned long hashIndex = hashFunction(key);

        AnagramNode* node = hashMap[hashIndex];
        while (node) {
            if (strcmp(node->key, key) == 0) {
                break;
            }
            node = node->next;
        }

        if (!node) {
            node = (AnagramNode*)malloc(sizeof(AnagramNode));
            node->key = strdup(key);
            node->anagrams = (char**)malloc(2 * sizeof(char*));
            node->count = 0;
            node->capacity = 2;
            node->next = hashMap[hashIndex];
            hashMap[hashIndex] = node;
        }

        if (node->count >= node->capacity) {
            node->capacity *= 2;
            node->anagrams = (char**)realloc(node->anagrams, node->capacity * sizeof(char*));
        }
        node->anagrams[node->count++] = strs[i];
    }

    char*** result = (char***)malloc(strsSize * sizeof(char**));
    int* colSizes = (int*)malloc(strsSize * sizeof(int));
    int resultSize = 0;
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        AnagramNode* node = hashMap[i];
        while (node) {
            result[resultSize] = node->anagrams;
            colSizes[resultSize] = node->count;
            resultSize++;
            AnagramNode* temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
    }
    *returnSize = resultSize;
    *returnColumnSizes = colSizes;
    return result;
}
