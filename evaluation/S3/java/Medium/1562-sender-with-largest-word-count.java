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
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - Aho-Corasick Algorithm for Pattern Searching (string, array, aho-corasick, enumeration)
//   • When to use: Use when you need to find all occurrences of a fixed set of patterns (a dictionary) within a larger text efficiently. It is particularly effective for scenarios with many patterns or long texts where patterns might overlap.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a dictionary of patterns, then uses this automaton to search for all pattern occurrences in a text in a single pass. It achieves a time complexity of O(N + M + K) where N is text length, M is total pattern length, and K is total matches.
//   • Invariants: The trie structure correctly represents all prefixes of all patterns in the dictionary.; Each node's failure link points to the longest proper suffix of the string ending at that node which is also a prefix in the trie.
//   • Tips: Build the trie first from all patterns, marking terminal nodes.; Compute failure links using a BFS-like approach, similar to KMP's LPS array.
//   • Pitfalls: Incorrectly building failure links can lead to missed matches or infinite loops.; Forgetting to handle output links (dictionary links) will miss patterns found via failure transitions.
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
            int wordCount = messages[i].split(" ").length;
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
