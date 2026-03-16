// Source: https://leetcode.com/problems/goat-latin/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string sentence that consist of words separated by spaces. Each word consists of lowercase and uppercase letters only.
//
// We would like to convert the sentence to "Goat Latin" (a made-up language similar to Pig Latin.) The rules of Goat Latin are as follows:
//
//
// 	If a word begins with a vowel ('a', 'e', 'i', 'o', or 'u'), append "ma" to the end of the word.
//
// 	
// 		For example, the word "apple" becomes "applema".
// 	
// 	
// 	If a word begins with a consonant (i.e., not a vowel), remove the first letter and append it to the end, then add "ma".
// 	
// 		For example, the word "goat" becomes "oatgma".
// 	
// 	
// 	Add one letter 'a' to the end of each word per its word index in the sentence, starting with 1.
// 	
// 		For example, the first word gets "a" added to the end, the second word gets "aa" added to the end, and so on.
// 	
// 	
//
//
// Return the final sentence representing the conversion from sentence to Goat Latin.
//
// Example:
// Input: sentence = "I speak Goat Latin"
// Output: "Imaa peaksmaaa oatGmaaaa atinLmaaaaa"
//
// Constraints:
// 1 <= sentence.length <= 150
// 	sentence consists of English letters and spaces.
// 	sentence has no leading or trailing spaces.
// 	All the words in sentence are separated by a single space.
//
// Helpful references (internal KB):
// - Manacher's Algorithm - Finding all sub-p (string, array, enumeration)
//   • When to use: Use when you need to find all palindromic substrings within a given string, or determine the longest palindromic substring, in optimal linear time.
//   • Idea: Manacher's Algorithm efficiently finds the length of the longest palindromic substring centered at each position in a given string, handling both odd and even lengths uniformly via preprocessing. It achieves this in optimal O(N) time complexity.
//   • Invariants: p[i] correctly stores the radius of the longest palindrome centered at i in the transformed string.; The right_boundary always marks the rightmost extent of the largest palindrome found so far.
//   • Tips: Preprocess the string with a unique delimiter to unify odd and even length palindromes.; Leverage the mirror property around the current center to initialize palindrome radii.
//   • Pitfalls: Off-by-one errors when converting `p` array values back to original string indices or lengths.; Incorrectly handling the boundaries of the preprocessed string.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use when you need to efficiently represent all distinct substrings of a string, or perform various string operations like counting unique substrings, finding occurrences, or string matching in an online fashion.
//   • Idea: A suffix automaton is a powerful data structure that represents all distinct substrings of a given string in a compact form, typically as a Directed Acyclic Word Graph (DAWG). It can be constructed in linear time O(N) and space O(N) for a string of length N.
//   • Invariants: Each state in the automaton represents a set of substrings that share the same end-positions in the original string.; For any state `v`, `len(v)` is the length of the longest string represented by `v`.
//   • Tips: Understand the properties of `len` (length of the longest string in a state) and `link` (suffix link to the longest proper suffix).; The construction is online, processing characters one by one from left to right.
//   • Pitfalls: Incorrectly handling the `link` updates, especially when cloning states during construction.; Forgetting to update the `last` pointer after each character addition step.
// - String Sorts (array, string, recursion)
//   • When to use: Use this algorithm to sort a collection of strings lexicographically, especially when string lengths vary or are large, and the character set is limited.
//   • Idea: This algorithm sorts an array of strings lexicographically by recursively applying a counting sort-like distribution based on characters from most significant to least significant digit. It typically achieves O(N*L + R*L) time complexity, where N is the number of strings, L is the average string length, and R is the radix size.
//   • Invariants: All strings in the current `a[lo...hi]` sub-array share a common prefix of length `d`.; After the distribution pass for character `d`, `aux` contains strings from `a[lo...hi]` stably sorted by their `d`-th character.
//   • Tips: Use an auxiliary array for stable distribution during each pass to maintain relative order.; Implement a cutoff to insertion sort for small sub-arrays to improve performance due to lower overhead.
//   • Pitfalls: Can have high overhead for small N or short strings compared to comparison sorts.; Potentially memory intensive due to the auxiliary array and recursion stack depth proportional to max string length.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* toGoatLatin(char* sentence) {
    int is_vowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
               c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
    }

    int len = 0;
    while (sentence[len]) len++;

    char* result = (char*)malloc(len * 3 + 1); // Allocate enough space
    int res_index = 0;
    int word_index = 1;
    int i = 0;

    while (i < len) {
        // Skip spaces
        while (i < len && sentence[i] == ' ') {
            result[res_index++] = sentence[i++];
        }

        if (i >= len) break;

        int start = i;
        while (i < len && sentence[i] != ' ') {
            i++;
        }
        int end = i;

        // Process the word
        if (is_vowel(sentence[start])) {
            for (int j = start; j < end; j++) {
                result[res_index++] = sentence[j];
            }
        } else {
            for (int j = start + 1; j < end; j++) {
                result[res_index++] = sentence[j];
            }
            result[res_index++] = sentence[start];
        }

        // Append "ma"
        result[res_index++] = 'm';
        result[res_index++] = 'a';

        // Append 'a's based on word index
        for (int j = 0; j < word_index; j++) {
            result[res_index++] = 'a';
        }

        word_index++;
    }

    result[res_index] = '\0'; // Null-terminate the string
    return result;      
}
