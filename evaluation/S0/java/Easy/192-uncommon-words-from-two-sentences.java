// Source: https://leetcode.com/problems/uncommon-words-from-two-sentences/   |   Difficulty: Easy
//
// Problem Description:
// A sentence is a string of single-space separated words where each word consists only of lowercase letters.
//
// A word is uncommon if it appears exactly once in one of the sentences, and does not appear in the other sentence.
//
// Given two sentences s1 and s2, return a list of all the uncommon words. You may return the answer in any order.
//
// Example:
// Input: s1 = "this apple is sweet", s2 = "this apple is sour"
//
// Output: ["sweet","sour"]
//
// Explanation:
//
// The word "sweet" appears only in s1, while the word "sour" appears only in s2.
//
// Constraints:
// 1 <= s1.length, s2.length <= 200
// 	s1 and s2 consist of lowercase English letters and spaces.
// 	s1 and s2 do not have leading or trailing spaces.
// 	All the words in s1 and s2 are separated by a single space.
//

class Solution {
    public String[] uncommonFromSentences(String s1, String s2) {
        String[] words1 = s1.split(" ");
        String[] words2 = s2.split(" ");

        Map<String, Integer> wordCount = new HashMap<>();

        for (String word : words1) {
            wordCount.put(word, wordCount.getOrDefault(word, 0) + 1);
        }

        for (String word : words2) {
            wordCount.put(word, wordCount.getOrDefault(word, 0) + 1);
        }

        List<String> uncommonWords = new ArrayList<>();
        for (Map.Entry<String, Integer> entry : wordCount.entrySet()) {
            if (entry.getValue() == 1) {
                uncommonWords.add(entry.getKey());
            }
        }

        return uncommonWords.toArray(new String[0]);            
    }
}
