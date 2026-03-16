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
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - String Hashing (string, array, hashing)
//   • When to use: Use when you need to efficiently compare strings or substrings, detect duplicates, or perform pattern matching in large text datasets. It's particularly useful for speeding up operations that would otherwise be O(N*M) or O(N^2).
//   • Idea: String hashing maps strings to numerical values, allowing for fast comparisons and operations like substring search. It typically uses a polynomial rolling hash function, achieving O(N) preprocessing and O(1) or O(log N) query time for substrings.
//   • Invariants: The hash of any prefix of the string is correctly computed based on its characters and chosen parameters.; For a rolling hash, the hash of the current window is always maintained correctly as the window slides.
//   • Tips: Choose a large prime modulus (or two) to minimize collision probability.; Select a base (prime number) larger than the alphabet size to ensure unique contributions from characters.
//   • Pitfalls: Hash collisions are possible and can lead to incorrect results if not properly handled or verified.; A poorly chosen base or modulus can significantly increase the frequency of collisions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool reportSpam(char** message, int messageSize, char** bannedWords, int bannedWordsSize) {
    // Create a hash set to store banned words for O(1) lookups
    char* bannedSet[100000]; // Assuming bannedWordsSize <= 100000
    int bannedCount = 0;

    // Insert banned words into the hash set
    for (int i = 0; i < bannedWordsSize; i++) {
        bannedSet[bannedCount++] = bannedWords[i];
    }

    int spamCount = 0;

    // Check each word in the message against the banned set
    for (int i = 0; i < messageSize; i++) {
        for (int j = 0; j < bannedCount; j++) {
            if (strcmp(message[i], bannedSet[j]) == 0) {
                spamCount++;
                if (spamCount >= 2) {
                    return true; // Found at least two matches, it's spam
                }
                break; // No need to check further for this word
            }
        }
    }

    return false; // Not enough matches, not spam       
}
