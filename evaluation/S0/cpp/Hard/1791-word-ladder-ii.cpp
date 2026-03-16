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
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        vector<vector<string>> result;
        if (wordSet.find(endWord) == wordSet.end()) return result;

        queue<vector<string>> q;
        q.push({beginWord});
        unordered_set<string> visited;
        visited.insert(beginWord);
        bool found = false;

        while (!q.empty() && !found) {
            int size = q.size();
            unordered_set<string> currentLevelVisited;

            for (int i = 0; i < size; i++) {
                vector<string> path = q.front();
                q.pop();
                string lastWord = path.back();

                for (int j = 0; j < lastWord.size(); j++) {
                    string newWord = lastWord;
                    for (char c = 'a'; c <= 'z'; c++) {
                        newWord[j] = c;
                        if (wordSet.find(newWord) != wordSet.end() && visited.find(newWord) == visited.end()) {
                            vector<string> newPath = path;
                            newPath.push_back(newWord);
                            if (newWord == endWord) {
                                result.push_back(newPath);
                                found = true;
                            } else {
                                q.push(newPath);
                                currentLevelVisited.insert(newWord);
                            }
                        }
                    }
                }
            }

            for (const string& word : currentLevelVisited) {
                visited.insert(word);
            }
        }

        return result;          
    }
};
