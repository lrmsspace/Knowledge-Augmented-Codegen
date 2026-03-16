// Source: https://leetcode.com/problems/string-matching-in-an-array/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of string words, return all strings in words that are a substring of another word. You can return the answer in any order.
//
// Example:
// Input: words = ["mass","as","hero","superhero"]
// Output: ["as","hero"]
// Explanation: "as" is substring of "mass" and "hero" is substring of "superhero".
// ["hero","as"] is also a valid answer.
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 30
// 	words[i] contains only lowercase English letters.
// 	All the strings of words are unique.
//

class Solution {
    public List<String> stringMatching(String[] words) {
        List<String> result = new ArrayList<>();
        for (int i = 0; i < words.length; i++) {
            for (int j = 0; j < words.length; j++) {
                if (i != j && words[j].contains(words[i])) {
                    result.add(words[i]);
                    break;
                }
            }
        }
        return result;          
    }
}
