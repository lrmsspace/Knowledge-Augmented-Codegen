// Source: https://leetcode.com/problems/rearrange-words-in-a-sentence/   |   Difficulty: Medium
//
// Problem Description:
// Given a sentence text (A sentence is a string of space-separated words) in the following format:
//
//
// 	First letter is in upper case.
// 	Each word in text are separated by a single space.
//
//
// Your task is to rearrange the words in text such that all words are rearranged in an increasing order of their lengths. If two words have the same length, arrange them in their original order.
//
// Return the new text following the format shown above.
//
// Example:
// Input: text = "Leetcode is cool"
// Output: "Is cool leetcode"
// Explanation: There are 3 words, "Leetcode" of length 8, "is" of length 2 and "cool" of length 4.
// Output is ordered by length and the new first word starts with capital letter.
//
// Constraints:
// text begins with a capital letter and then contains lowercase letters and single space between words.
// 	1 <= text.length <= 10^5
//
// Helpful references (internal KB):
// - String Sorts (array, string, recursion)
//   • When to use: Use this algorithm to sort a collection of strings lexicographically, especially when string lengths vary or are large, and the character set is limited.
//   • Idea: This algorithm sorts an array of strings lexicographically by recursively applying a counting sort-like distribution based on characters from most significant to least significant digit. It typically achieves O(N*L + R*L) time complexity, where N is the number of strings, L is the average string length, and R is the radix size.
//   • Invariants: All strings in the current `a[lo...hi]` sub-array share a common prefix of length `d`.; After the distribution pass for character `d`, `aux` contains strings from `a[lo...hi]` stably sorted by their `d`-th character.
//   • Tips: Use an auxiliary array for stable distribution during each pass to maintain relative order.; Implement a cutoff to insertion sort for small sub-arrays to improve performance due to lower overhead.
//   • Pitfalls: Can have high overhead for small N or short strings compared to comparison sorts.; Potentially memory intensive due to the auxiliary array and recursion stack depth proportional to max string length.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* arrangeWords(char* text) {
    // Split the sentence into words
    char* words[10000];
    int wordCount = 0;
    char* token = strtok(text, " ");
    while (token != NULL) {
        words[wordCount++] = token;
        token = strtok(NULL, " ");
    }

    // Sort words by length using a stable sort (Insertion Sort)
    for (int i = 1; i < wordCount; i++) {
        char* key = words[i];
        int j = i - 1;
        while (j >= 0 && strlen(words[j]) > strlen(key)) {
            words[j + 1] = words[j];
            j--;
        }
        words[j + 1] = key;
    }

    // Reconstruct the sentence
    char* result = (char*)malloc(100000 * sizeof(char));
    result[0] = '\0';
    for (int i = 0; i < wordCount; i++) {
        if (i > 0) {
            strcat(result, " ");
        }
        strcat(result, words[i]);
    }

    // Capitalize the first letter and lowercase the rest
    result[0] = toupper(result[0]);
    for (int i = 1; result[i] != '\0'; i++) {
        result[i] = tolower(result[i]);
    }

    return result;      
}
