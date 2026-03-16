// Source: https://leetcode.com/problems/determine-if-two-strings-are-close/   |   Difficulty: Medium
//
// Problem Description:
// Two strings are considered close if you can attain one from the other using the following operations:
//
//
// 	Operation 1: Swap any two existing characters.
//
// 	
// 		For example, abcde -> aecdb
// 	
// 	
// 	Operation 2: Transform every occurrence of one existing character into another existing character, and do the same with the other character.
// 	
// 		For example, aacabb -> bbcbaa (all a's turn into b's, and all b's turn into a's)
// 	
// 	
//
//
// You can use the operations on either string as many times as necessary.
//
// Given two strings, word1 and word2, return true if word1 and word2 are close, and false otherwise.
//
// Example:
// Input: word1 = "abc", word2 = "bca"
// Output: true
// Explanation: You can attain word2 from word1 in 2 operations.
// Apply Operation 1: "abc" -> "acb"
// Apply Operation 1: "acb" -> "bca"
//
// Constraints:
// 1 <= word1.length, word2.length <= 105
// 	word1 and word2 contain only lowercase English letters.
//

class Solution {
    public boolean closeStrings(String word1, String word2) {
        if (word1.length() != word2.length()) {
            return false;
        }

        int[] count1 = new int[26];
        int[] count2 = new int[26];

        for (char c : word1.toCharArray()) {
            count1[c - 'a']++;
        }

        for (char c : word2.toCharArray()) {
            count2[c - 'a']++;
        }

        for (int i = 0; i < 26; i++) {
            if ((count1[i] == 0 && count2[i] != 0) || (count1[i] != 0 && count2[i] == 0)) {
                return false;
            }
        }

        Arrays.sort(count1);
        Arrays.sort(count2);

        for (int i = 0; i < 26; i++) {
            if (count1[i] != count2[i]) {
                return false;
            }
        }

        return true;            
    }
}
