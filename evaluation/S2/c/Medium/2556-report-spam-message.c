// Source: https://leetcode.com/problems/report-spam-message/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of strings message and an array of strings bannedWords.
//
// An array of words is considered spam if there are at least two words in it that exactly match any word in bannedWords.
//
// Return true if the array message is spam, and false otherwise.
//
// Example:
// Input: message = ["hello","world","leetcode"], bannedWords = ["world","hello"]
//
// Output: true
//
// Explanation:
//
// The words "hello" and "world" from the message array both appear in the bannedWords array.
//
// Constraints:
// 1 <= message.length, bannedWords.length <= 105
// 	1 <= message[i].length, bannedWords[i].length <= 15
// 	message[i] and bannedWords[i] consist only of lowercase English letters.
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

bool reportSpam(char** message, int messageSize, char** bannedWords, int bannedWordsSize) {
    // Create a hash set to store the banned words
    char* bannedSet[100000]; // Assuming a maximum of 100000 banned words
    int bannedCount = 0;

    // Insert banned words into the hash set
    for (int i = 0; i < bannedWordsSize; i++) {
        bannedSet[bannedCount++] = bannedWords[i];
    }

    // Check if any word in the message is in the banned set
    int spamCount = 0;
    for (int i = 0; i < messageSize; i++) {
        for (int j = 0; j < bannedCount; j++) {
            if (strcmp(message[i], bannedSet[j]) == 0) {
                spamCount++;
                break; // No need to check further for this word
            }
        }
        if (spamCount >= 2) {
            return true; // Found at least two spam words
        }
    }

    return false; // Not enough spam words found        
}
