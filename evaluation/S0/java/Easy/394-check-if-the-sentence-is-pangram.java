// Source: https://leetcode.com/problems/check-if-the-sentence-is-pangram/   |   Difficulty: Easy
//
// Problem Description:
// A pangram is a sentence where every letter of the English alphabet appears at least once.
//
// Given a string sentence containing only lowercase English letters, return true if sentence is a pangram, or false otherwise.
//
// Example:
// Input: sentence = "thequickbrownfoxjumpsoverthelazydog"
// Output: true
// Explanation: sentence contains at least one of every letter of the English alphabet.
//
// Constraints:
// 1 <= sentence.length <= 1000
// 	sentence consists of lowercase English letters.
//

class Solution {
    public boolean checkIfPangram(String sentence) {
        boolean[] seen = new boolean[26];
        int uniqueCount = 0;

        for (char ch : sentence.toCharArray()) {
            int index = ch - 'a';
            if (!seen[index]) {
                seen[index] = true;
                uniqueCount++;
                if (uniqueCount == 26) {
                    return true;
                }
            }
        }

        return uniqueCount == 26;           
    }
}
