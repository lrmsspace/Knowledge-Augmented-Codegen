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
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public String largestWordCount(String[] messages, String[] senders) {
        Map<String, Integer> wordCountMap = new HashMap<>();

        for (int i = 0; i < messages.length; i++) {
            String sender = senders[i];
            String message = messages[i];
            int wordCount = message.split(" ").length;

            wordCountMap.put(sender, wordCountMap.getOrDefault(sender, 0) + wordCount);
        }

        String resultSender = "";
        int maxWordCount = 0;

        for (Map.Entry<String, Integer> entry : wordCountMap.entrySet()) {
            String sender = entry.getKey();
            int count = entry.getValue();

            if (count > maxWordCount || (count == maxWordCount && sender.compareTo(resultSender) > 0)) {
                maxWordCount = count;
                resultSender = sender;
            }
        }

        return resultSender;            
    }
}
