// Source: https://leetcode.com/problems/decode-the-message/   |   Difficulty: Easy
//
// Problem Description:
// You are given the strings key and message, which represent a cipher key and a secret message, respectively. The steps to decode message are as follows:
//
//
// 	Use the first appearance of all 26 lowercase English letters in key as the order of the substitution table.
// 	Align the substitution table with the regular English alphabet.
// 	Each letter in message is then substituted using the table.
// 	Spaces ' ' are transformed to themselves.
//
//
//
// 	For example, given key = "happy boy" (actual key would have at least one instance of each letter in the alphabet), we have the partial substitution table of ('h' -> 'a', 'a' -> 'b', 'p' -> 'c', 'y' -> 'd', 'b' -> 'e', 'o' -> 'f').
//
//
// Return the decoded message.
//
// Example:
// Input: key = "the quick brown fox jumps over the lazy dog", message = "vkbs bs t suepuv"
// Output: "this is a secret"
// Explanation: The diagram above shows the substitution table.
// It is obtained by taking the first appearance of each letter in "the quick brown fox jumps over the lazy dog".
//
// Constraints:
// 26 <= key.length <= 2000
// 	key consists of lowercase English letters and ' '.
// 	key contains every letter in the English alphabet ('a' to 'z') at least once.
// 	1 <= message.length <= 2000
// 	message consists of lowercase English letters and ' '.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* decodeMessage(char* key, char* message) {
    char mapping[26] = {0}; // Mapping from 'a' to 'z'
    char *decoded = (char *)malloc(strlen(message) + 1); // Allocate memory for decoded message
    int mapIndex = 0; // Index for mapping

    // Create the mapping based on the key
    for (int i = 0; key[i] != '\0'; i++) {
        char c = key[i];
        if (c >= 'a' && c <= 'z') {
            if (mapping[c - 'a'] == 0) { // If this character hasn't been mapped yet
                mapping[c - 'a'] = 'a' + mapIndex; // Map to the next available letter
                mapIndex++;
            }
        }
    }

    // Decode the message using the mapping
    for (int i = 0; message[i] != '\0'; i++) {
        char c = message[i];
        if (c >= 'a' && c <= 'z') {
            decoded[i] = mapping[c - 'a']; // Substitute using the mapping
        } else {
            decoded[i] = c; // Keep spaces as they are
        }
    }
    decoded[strlen(message)] = '\0'; // Null-terminate the decoded string

    return decoded;     
}
