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

class Solution {
    public String decodeMessage(String key, String message) {
        char[] map = new char[26];
        boolean[] seen = new boolean[26];
        int index = 0;

        for (char c : key.toCharArray()) {
            if (c == ' ') {
                continue;
            }
            int pos = c - 'a';
            if (!seen[pos]) {
                seen[pos] = true;
                map[pos] = (char) ('a' + index);
                index++;
            }
        }

        StringBuilder decodedMessage = new StringBuilder();
        for (char c : message.toCharArray()) {
            if (c == ' ') {
                decodedMessage.append(' ');
            } else {
                decodedMessage.append(map[c - 'a']);
            }
        }

        return decodedMessage.toString();           
    }
}
