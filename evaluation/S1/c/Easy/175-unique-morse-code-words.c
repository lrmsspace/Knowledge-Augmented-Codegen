// Source: https://leetcode.com/problems/unique-morse-code-words/   |   Difficulty: Easy
//
// Problem Description:
// International Morse Code defines a standard encoding where each letter is mapped to a series of dots and dashes, as follows:
//
//
// 	'a' maps to ".-",
// 	'b' maps to "-...",
// 	'c' maps to "-.-.", and so on.
//
//
// For convenience, the full table for the 26 letters of the English alphabet is given below:
//
//
// [".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."]
//
// Given an array of strings words where each word can be written as a concatenation of the Morse code of each letter.
//
//
// 	For example, "cab" can be written as "-.-..--...", which is the concatenation of "-.-.", ".-", and "-...". We will call such a concatenation the transformation of a word.
//
//
// Return the number of different transformations among all words we have.
//
// Example:
// Input: words = ["gin","zen","gig","msg"]
// Output: 2
// Explanation: The transformation of each word is:
// "gin" -> "--...-."
// "zen" -> "--...-."
// "gig" -> "--...--."
// "msg" -> "--...--."
// There are 2 different transformations: "--...-." and "--...--.".
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 12
// 	words[i] consists of lowercase English letters.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
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

int uniqueMorseRepresentations(char** words, int wordsSize) {
    const char* morse_map[26] = {
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", 
        ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", 
        "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
    };

    // Using a simple hash set implementation with chaining for collision resolution
    #define HASH_SIZE 2003
    typedef struct Node {
        char* code;
        struct Node* next;
    } Node;

    Node* hash_table[HASH_SIZE] = {0};

    unsigned long hash(const char* str) {
        unsigned long h = 5381;
        int c;
        while ((c = *str++))
            h = ((h << 5) + h) + c; // h * 33 + c
        return h % HASH_SIZE;
    }

    int unique_count = 0;

    for (int i = 0; i < wordsSize; i++) {
        char buffer[100] = {0};
        char* word = words[i];
        char* p = buffer;

        // Convert word to Morse code
        while (*word) {
            const char* morse_code = morse_map[*word - 'a'];
            while (*morse_code) {
                *p++ = *morse_code++;
            }
            word++;
        }
        *p = '\0';

        // Hash the Morse code
        unsigned long h = hash(buffer);
        Node* node = hash_table[h];
        int found = 0;

        // Check if already exists in the hash table
        while (node) {
            if (strcmp(node->code, buffer) == 0) {
                found = 1;
                break;
            }
            node = node->next;
        }

        // If not found, add to hash table
        if (!found) {
            Node* new_node = (Node*)malloc(sizeof(Node));
            new_node->code = strdup(buffer);
            new_node->next = hash_table[h];
            hash_table[h] = new_node;
            unique_count++;
        }
    }

    // Free allocated memory
    for (int i = 0; i < HASH_SIZE; i++) {
        Node* node = hash_table[i];
        while (node) {
            Node* temp = node;
            node = node->next;
            free(temp->code);
            free(temp);
        }
    }
    return unique_count;
}
