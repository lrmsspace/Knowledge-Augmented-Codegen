// Source: https://leetcode.com/problems/shortest-uncommon-substring-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array arr of size n consisting of non-empty strings.
//
// Find a string array answer of size n such that:
//
//
// 	answer[i] is the shortest substring of arr[i] that does not occur as a substring in any other string in arr. If multiple such substrings exist, answer[i] should be the lexicographically smallest. And if no such substring exists, answer[i] should be an empty string.
//
//
// Return the array answer.
//
// Example:
// Input: arr = ["cab","ad","bad","c"]
// Output: ["ab","","ba",""]
// Explanation: We have the following:
// - For the string "cab", the shortest substring that does not occur in any other string is either "ca" or "ab", we choose the lexicographically smaller substring, which is "ab".
// - For the string "ad", there is no substring that does not occur in any other string.
// - For the string "bad", the shortest substring that does not occur in any other string is "ba".
// - For the string "c", there is no substring that does not occur in any other string.
//
// Constraints:
// n == arr.length
// 	2 <= n <= 100
// 	1 <= arr[i].length <= 20
// 	arr[i] consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - String Hashing (string, array, hashing)
//   • When to use: Use when you need to efficiently compare strings or substrings, detect duplicates, or perform pattern matching in large text datasets. It's particularly useful for speeding up operations that would otherwise be O(N*M) or O(N^2).
//   • Idea: String hashing maps strings to numerical values, allowing for fast comparisons and operations like substring search. It typically uses a polynomial rolling hash function, achieving O(N) preprocessing and O(1) or O(log N) query time for substrings.
//   • Invariants: The hash of any prefix of the string is correctly computed based on its characters and chosen parameters.; For a rolling hash, the hash of the current window is always maintained correctly as the window slides.
//   • Tips: Choose a large prime modulus (or two) to minimize collision probability.; Select a base (prime number) larger than the alphabet size to ensure unique contributions from characters.
//   • Pitfalls: Hash collisions are possible and can lead to incorrect results if not properly handled or verified.; A poorly chosen base or modulus can significantly increase the frequency of collisions.
// - Aho-Corasick Algorithm for Pattern Searching (string, array, aho-corasick, enumeration)
//   • When to use: Use when you need to find all occurrences of a fixed set of patterns (a dictionary) within a larger text efficiently. It is particularly effective for scenarios with many patterns or long texts where patterns might overlap.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a dictionary of patterns, then uses this automaton to search for all pattern occurrences in a text in a single pass. It achieves a time complexity of O(N + M + K) where N is text length, M is total pattern length, and K is total matches.
//   • Invariants: The trie structure correctly represents all prefixes of all patterns in the dictionary.; Each node's failure link points to the longest proper suffix of the string ending at that node which is also a prefix in the trie.
//   • Tips: Build the trie first from all patterns, marking terminal nodes.; Compute failure links using a BFS-like approach, similar to KMP's LPS array.
//   • Pitfalls: Incorrectly building failure links can lead to missed matches or infinite loops.; Forgetting to handle output links (dictionary links) will miss patterns found via failure transitions.
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
char** shortestSubstrings(char** arr, int arrSize, int* returnSize) {
    // Step 1: Create a hash map to store all substrings and their counts
    typedef struct {
        char substring[21]; // Max length of arr[i] is 20 + 1 for null terminator
        int count; // Count of how many strings contain this substring
    } SubstringCount;
    
    SubstringCount hashMap[10000]; // A simple hash map with a fixed size
    int hashMapSize = 0; // Current size of the hash map
    
    // Function to compute a simple hash for a substring
    unsigned long hashFunction(const char* str) {
        unsigned long hash = 5381;
        int c;
        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        return hash % 10000; // Modulo to fit into our hash map
    }
    
    // Step 2: Populate the hash map with all substrings from all strings in arr
    for (int i = 0; i < arrSize; i++) {
        char* str = arr[i];
        int len = strlen(str);
        for (int start = 0; start < len; start++) {
            for (int end = start + 1; end <= len; end++) {
                char substring[21];
                strncpy(substring, str + start, end - start);
                substring[end - start] = '\0'; // Null-terminate the substring
                
                unsigned long hashIndex = hashFunction(substring);
                int found = 0;
                
                // Check if the substring is already in the hash map
                for (int j = 0; j < hashMapSize; j++) {
                    if (strcmp(hashMap[j].substring, substring) == 0) {
                        hashMap[j].count++; // Increment count if found
                        found = 1;
                        break;
                    }
                }
                
                // If not found, add it to the hash map
                if (!found && hashMapSize < 10000) {
                    strcpy(hashMap[hashMapSize].substring, substring);
                    hashMap[hashMapSize].count = 1;
                    hashMapSize++;
                }
            }
        }
    }
    
    // Step 3: For each string in arr, find the shortest unique substring
    char** result = (char**)malloc(arrSize * sizeof(char*));
    for (int i = 0; i < arrSize; i++) {
        result[i] = NULL; // Initialize result for this string
        char* str = arr[i];
        int len = strlen(str);
        
        for (int start = 0; start < len && result[i] == NULL; start++) {
            for (int end = start + 1; end <= len && result[i] == NULL; end++) {
                char substring[21];
                strncpy(substring, str + start, end - start);
                substring[end - start] = '\0'; // Null-terminate the substring
                
                // Check if this substring is unique (count == 1)
                for (int j = 0; j < hashMapSize; j++) {
                    if (strcmp(hashMap[j].substring, substring) == 0 && hashMap[j].count == 1) {
                        // If it's unique, check if it's the shortest or lexicographically smaller
                        if (result[i] == NULL || strlen(substring) < strlen(result[i]) || 
                            (strlen(substring) == strlen(result[i]) && strcmp(substring, result[i]) < 0)) {
                            free(result[i]); // Free previous result if it exists
                            result[i] = strdup(substring); // Store the new unique substring
                        }
                    }
                }
            }
        }
        
        // If no unique substring found, set it to an empty string
        if (result[i] == NULL) {
            result[i] = strdup("");
        }
    }   
    *returnSize = arrSize;
    return result;
}
