// Source: https://leetcode.com/problems/word-subsets/   |   Difficulty: Medium
//
// Problem Description:
// You are given two string arrays words1 and words2.
//
// A string b is a subset of string a if every letter in b occurs in a including multiplicity.
//
//
// 	For example, "wrr" is a subset of "warrior" but is not a subset of "world".
//
//
// A string a from words1 is universal if for every string b in words2, b is a subset of a.
//
// Return an array of all the universal strings in words1. You may return the answer in any order.
//
// Example:
// Input: words1 = ["amazon","apple","facebook","google","leetcode"], words2 = ["e","o"]
//
// Output: ["facebook","google","leetcode"]
//
// Constraints:
// 1 <= words1.length, words2.length <= 104
// 	1 <= words1[i].length, words2[i].length <= 10
// 	words1[i] and words2[i] consist only of lowercase English letters.
// 	All the strings of words1 are unique.
//

class Solution {
    public List<String> wordSubsets(String[] words1, String[] words2) {
        int[] maxFreq = new int[26];
        for (String b : words2) {
            int[] freq = new int[26];
            for (char c : b.toCharArray()) {
                freq[c - 'a']++;
            }
            for (int i = 0; i < 26; i++) {
                maxFreq[i] = Math.max(maxFreq[i], freq[i]);
            }
        }

        List<String> result = new ArrayList<>();
        for (String a : words1) {
            int[] freq = new int[26];
            for (char c : a.toCharArray()) {
                freq[c - 'a']++;
            }
            boolean isUniversal = true;
            for (int i = 0; i < 26; i++) {
                if (freq[i] < maxFreq[i]) {
                    isUniversal = false;
                    break;
                }
            }
            if (isUniversal) {
                result.add(a);
            }
        }

        return result;          
    }
}
