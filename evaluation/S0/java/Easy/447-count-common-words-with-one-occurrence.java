// Source: https://leetcode.com/problems/count-common-words-with-one-occurrence/   |   Difficulty: Easy
//
// Problem Description:
// Given two string arrays words1 and words2, return the number of strings that appear exactly once in each of the two arrays.
//
// Example:
// Input: words1 = ["leetcode","is","amazing","as","is"], words2 = ["amazing","leetcode","is"]
// Output: 2
// Explanation:
// - "leetcode" appears exactly once in each of the two arrays. We count this string.
// - "amazing" appears exactly once in each of the two arrays. We count this string.
// - "is" appears in each of the two arrays, but there are 2 occurrences of it in words1. We do not count this string.
// - "as" appears once in words1, but does not appear in words2. We do not count this string.
// Thus, there are 2 strings that appear exactly once in each of the two arrays.
//
// Constraints:
// 1 <= words1.length, words2.length <= 1000
// 	1 <= words1[i].length, words2[j].length <= 30
// 	words1[i] and words2[j] consists only of lowercase English letters.
//

class Solution {
    public int countWords(String[] words1, String[] words2) {
        Map<String, Integer> map1 = new HashMap<>();
        Map<String, Integer> map2 = new HashMap<>();

        for (String word : words1) {
            map1.put(word, map1.getOrDefault(word, 0) + 1);
        }

        for (String word : words2) {
            map2.put(word, map2.getOrDefault(word, 0) + 1);
        }

        int count = 0;
        for (String word : map1.keySet()) {
            if (map1.get(word) == 1 && map2.getOrDefault(word, 0) == 1) {
                count++;
            }
        }

        return count;           
    }
}
