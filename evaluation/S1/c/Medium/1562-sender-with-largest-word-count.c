// Source: https://leetcode.com/problems/sender-with-largest-word-count/   |   Difficulty: Medium
//
// Problem Description:
// You have a chat log of n messages. You are given two string arrays messages and senders where messages[i] is a message sent by senders[i].
//
// A message is list of words that are separated by a single space with no leading or trailing spaces. The word count of a sender is the total number of words sent by the sender. Note that a sender may send more than one message.
//
// Return the sender with the largest word count. If there is more than one sender with the largest word count, return the one with the lexicographically largest name.
//
// Note:
//
//
// 	Uppercase letters come before lowercase letters in lexicographical order.
// 	"Alice" and "alice" are distinct.
//
// Example:
// Input: messages = ["Hello userTwooo","Hi userThree","Wonderful day Alice","Nice day userThree"], senders = ["Alice","userTwo","userThree","Alice"]
// Output: "Alice"
// Explanation: Alice sends a total of 2 + 3 = 5 words.
// userTwo sends a total of 2 words.
// userThree sends a total of 3 words.
// Since Alice has the largest word count, we return "Alice".
//
// Constraints:
// n == messages.length == senders.length
// 	1 <= n <= 104
// 	1 <= messages[i].length <= 100
// 	1 <= senders[i].length <= 10
// 	messages[i] consists of uppercase and lowercase English letters and ' '.
// 	All the words in messages[i] are separated by a single space.
// 	messages[i] does not have leading or trailing spaces.
// 	senders[i] consists of uppercase and lowercase English letters only.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
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

char* largestWordCount(char** messages, int messagesSize, char** senders, int sendersSize) {
    // Hash map to store word counts for each sender
    #define MAX_SENDERS 10000
    #define MAX_NAME_LEN 11

    typedef struct {
        char name[MAX_NAME_LEN];
        int word_count;
    } SenderInfo;

    SenderInfo sender_map[MAX_SENDERS];
    int sender_count = 0;

    for (int i = 0; i < messagesSize; i++) {
        // Count words in the message
        int word_count = 1;
        for (char* p = messages[i]; *p; p++) {
            if (*p == ' ') {
                word_count++;
            }
        }

        // Find or add sender in the map
        int found = 0;
        for (int j = 0; j < sender_count; j++) {
            if (strcmp(sender_map[j].name, senders[i]) == 0) {
                sender_map[j].word_count += word_count;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(sender_map[sender_count].name, senders[i]);
            sender_map[sender_count].word_count = word_count;
            sender_count++;
        }
    }

    // Find sender with largest word count
    char* result = NULL;
    int max_word_count = -1;

    for (int i = 0; i < sender_count; i++) {
        if (sender_map[i].word_count > max_word_count ||
            (sender_map[i].word_count == max_word_count && strcmp(sender_map[i].name, result) > 0)) {
            max_word_count = sender_map[i].word_count;
            result = sender_map[i].name;
        }
    }

    return result;      
}
