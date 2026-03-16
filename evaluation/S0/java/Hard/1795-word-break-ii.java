// Source: https://leetcode.com/problems/word-break-ii/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s and a dictionary of strings wordDict, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences in any order.
//
// Note that the same word in the dictionary may be reused multiple times in the segmentation.
//
// Example:
// Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
// Output: ["cats and dog","cat sand dog"]
//
// Constraints:
// 1 <= s.length <= 20
// 	1 <= wordDict.length <= 1000
// 	1 <= wordDict[i].length <= 10
// 	s and wordDict[i] consist of only lowercase English letters.
// 	All the strings of wordDict are unique.
// 	Input is generated in a way that the length of the answer doesn't exceed 105.
//

class Solution {
    public List<String> wordBreak(String s, List<String> wordDict) {
        Set<String> wordSet = new HashSet<>(wordDict);
        Map<Integer, List<String>> memo = new HashMap<>();
        return backtrack(s, 0, wordSet, memo);          
    }
}
