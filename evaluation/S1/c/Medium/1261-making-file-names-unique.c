// Source: https://leetcode.com/problems/making-file-names-unique/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of strings names of size n. You will create n folders in your file system such that, at the ith minute, you will create a folder with the name names[i].
//
// Since two files cannot have the same name, if you enter a folder name that was previously used, the system will have a suffix addition to its name in the form of (k), where, k is the smallest positive integer such that the obtained name remains unique.
//
// Return an array of strings of length n where ans[i] is the actual name the system will assign to the ith folder when you create it.
//
// Example:
// Input: names = ["pes","fifa","gta","pes(2019)"]
// Output: ["pes","fifa","gta","pes(2019)"]
// Explanation: Let's see how the file system creates folder names:
// "pes" --> not assigned before, remains "pes"
// "fifa" --> not assigned before, remains "fifa"
// "gta" --> not assigned before, remains "gta"
// "pes(2019)" --> not assigned before, remains "pes(2019)"
//
// Constraints:
// 1 <= names.length <= 5 * 104
// 	1 <= names[i].length <= 20
// 	names[i] consists of lowercase English letters, digits, and/or round brackets.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Minimum stack / Minimum queue (stack, simulation)
//   • When to use: When you need to perform standard stack operations (push, pop) and also query the minimum element currently in the stack, all in constant time.
//   • Idea: Augments a standard stack by storing each element along with the minimum value encountered up to that point in the stack. This allows O(1) retrieval of the current minimum, while push and pop operations also remain O(1).
//   • Invariants: The top element's second component (minimum_so_far) always represents the minimum value currently in the entire stack.; For any element (value, min_so_far) in the stack, min_so_far is the minimum of 'value' and all elements below it.
//   • Tips: Store elements as pairs: (actual_value, minimum_at_this_level).; When pushing, the new minimum_at_this_level is min(new_value, stack.top().second) if stack is not empty, else new_value.
//   • Pitfalls: Forgetting to handle the empty stack case when calculating the minimum for a new element.; Incorrectly assuming the minimum can be tracked with a single auxiliary variable without considering pops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** getFolderNames(char** names, int namesSize, int* returnSize) {
    // Hash map to store the next available suffix number for each base name
    #define HASH_MAP_SIZE 100003
    typedef struct HashNode {
        char *key;
        int value;
        struct HashNode *next;
    } HashNode;

    HashNode* hashMap[HASH_MAP_SIZE] = {0};

    unsigned long hash(const char *str) {
        unsigned long hash = 5381;
        int c;
        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        return hash % HASH_MAP_SIZE;
    }

    void put(const char *key, int value) {
        unsigned long idx = hash(key);
        HashNode *node = hashMap[idx];
        while (node) {
            if (strcmp(node->key, key) == 0) {
                node->value = value;
                return;
            }
            node = node->next;
        }
        node = (HashNode *)malloc(sizeof(HashNode));
        node->key = strdup(key);
        node->value = value;
        node->next = hashMap[idx];
        hashMap[idx] = node;
    }

    int get(const char *key) {
        unsigned long idx = hash(key);
        HashNode *node = hashMap[idx];
        while (node) {
            if (strcmp(node->key, key) == 0) {
                return node->value;
            }
            node = node->next;
        }
        return -1; // Not found
    }

    char **result = (char **)malloc(namesSize * sizeof(char *));
    for (int i = 0; i < namesSize; i++) {
        char *name = names[i];
        int suffix = get(name);
        if (suffix == -1) {
            result[i] = strdup(name);
            put(name, 1);
        } else {
            char newName[30];
            do {
                sprintf(newName, "%s(%d)", name, suffix);
                suffix++;
            } while (get(newName) != -1);
            result[i] = strdup(newName);
            put(name, suffix);
            put(newName, 1);
        }
    }

    // Free the hash map
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        HashNode *node = hashMap[i];
        while (node) {
            HashNode *temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
    }
    *returnSize = namesSize;
    return result;
}
