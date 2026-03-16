// Source: https://leetcode.com/problems/word-ladder/   |   Difficulty: Hard
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
// Given two words, beginWord and endWord, and a dictionary wordList, return the number of words in the shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.
//
// Example:
// Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
// Output: 5
// Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", which is 5 words long.
//
// Constraints:
// 1 <= beginWord.length <= 10
// 	endWord.length == beginWord.length
// 	1 <= wordList.length <= 5000
// 	wordList[i].length == beginWord.length
// 	beginWord, endWord, and wordList[i] consist of lowercase English letters.
// 	beginWord != endWord
// 	All the words in wordList are unique.
//

int ladderLength(char* beginWord, char* endWord, char** wordList, int wordListSize) {
    int wordLen = strlen(beginWord);
    int foundEnd = 0;
    for (int i = 0; i < wordListSize; ++i) {
        if (strcmp(wordList[i], endWord) == 0) {
            foundEnd = 1;
            break;
        }
    }
    if (!foundEnd) return 0;

    /* BFS setup */
    int queueCap = wordListSize + 1;
    char **queue = (char**)malloc(queueCap * sizeof(char*));
    int *visited = (int*)calloc(wordListSize, sizeof(int));
    if (!queue || !visited) {
        free(queue); free(visited);
        return 0;
    }
    int front = 0, back = 0;
    queue[back++] = beginWord;
    int level = 1;

    while (front < back) {
        int levelSize = back - front;
        for (int i = 0; i < levelSize; ++i) {
            char *currWord = queue[front++];
            if (strcmp(currWord, endWord) == 0) {
                free(queue); free(visited);
                return level;
            }
            for (int j = 0; j < wordListSize; ++j) {
                if (visited[j]) continue;
                int diffCount = 0;
                for (int k = 0; k < wordLen; ++k) {
                    if (currWord[k] != wordList[j][k]) {
                        diffCount++;
                        if (diffCount > 1) break;
                    }
                }
                if (diffCount == 1) {
                    visited[j] = 1;
                    queue[back++] = wordList[j];
                }
            }
        }
        level++;
    }

    free(queue); free(visited);
    return 0;       
}
