// Source: https://leetcode.com/problems/word-ladder-ii/   |   Difficulty: Hard
//
// Problem Description:
// A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:
//
//
// 	Every adjacent pair of words differs by a single letter.
// 	Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
// 	sk == endWord
//
//
// Given two words, beginWord and endWord, and a dictionary wordList, return all the shortest transformation sequences from beginWord to endWord, or an empty list if no such sequence exists. Each sequence should be returned as a list of the words [beginWord, s1, s2, ..., sk].
//
// Example:
// Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
// Output: [["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]]
// Explanation: There are 2 shortest transformation sequences:
// "hit" -> "hot" -> "dot" -> "dog" -> "cog"
// "hit" -> "hot" -> "lot" -> "log" -> "cog"
//
// Constraints:
// 1 <= beginWord.length <= 5
// 	endWord.length == beginWord.length
// 	1 <= wordList.length <= 500
// 	wordList[i].length == beginWord.length
// 	beginWord, endWord, and wordList[i] consist of lowercase English letters.
// 	beginWord != endWord
// 	All the words in wordList are unique.
// 	The sum of all shortest transformation sequences does not exceed 105.
//

class Solution {
    public List<List<String>> findLadders(String beginWord, String endWord, List<String> wordList) {
        Set<String> wordSet = new HashSet<>(wordList);
        List<List<String>> res = new ArrayList<>();
        if (!wordSet.contains(endWord)) return res;

        Map<String, List<String>> graph = new HashMap<>();
        Map<String, Integer> distance = new HashMap<>();
        bfs(beginWord, endWord, wordSet, graph, distance);

        List<String> path = new ArrayList<>();
        dfs(beginWord, endWord, graph, distance, path, res);
        return res;         
    }
}
