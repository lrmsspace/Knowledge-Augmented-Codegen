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
public:
    int countWords(vector<string>& words1, vector<string>& words2) {
        unordered_map<string, int> count1, count2;
        
        for (const string& word : words1) {
            count1[word]++;
        }
        
        for (const string& word : words2) {
            count2[word]++;
        }
        
        int commonCount = 0;
        
        for (const auto& [word, cnt] : count1) {
            if (cnt == 1 && count2[word] == 1) {
                commonCount++;
            }
        }
        
        return commonCount;         
    }
};
