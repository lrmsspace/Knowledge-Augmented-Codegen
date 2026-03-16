// Source: https://leetcode.com/problems/substring-with-concatenation-of-all-words/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s and an array of strings words. All the strings of words are of the same length.
//
// A concatenated string is a string that exactly contains all the strings of any permutation of words concatenated.
//
//
// 	For example, if words = ["ab","cd","ef"], then "abcdef", "abefcd", "cdabef", "cdefab", "efabcd", and "efcdab" are all concatenated strings. "acdbef" is not a concatenated string because it is not the concatenation of any permutation of words.
//
//
// Return an array of the starting indices of all the concatenated substrings in s. You can return the answer in any order.
//
// Example:
// Input: s = "barfoothefoobarman", words = ["foo","bar"]
//
// Output: [0,9]
//
// Explanation:
//
// The substring starting at 0 is "barfoo". It is the concatenation of ["bar","foo"] which is a permutation of words.
// The substring starting at 9 is "foobar". It is the concatenation of ["foo","bar"] which is a permutation of words.
//
// Constraints:
// 1 <= s.length <= 104
// 	1 <= words.length <= 5000
// 	1 <= words[i].length <= 30
// 	s and words[i] consist of lowercase English letters.
//

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> result;
        if (words.empty() || s.empty()) return result;
        
        int wordLen = words[0].size();
        int wordCount = words.size();
        int substringLen = wordLen * wordCount;
        
        unordered_map<string, int> wordMap;
        for (const string& word : words) {
            wordMap[word]++;
        }
        
        for (int i = 0; i <= (int)s.size() - substringLen; i++) {
            unordered_map<string, int> seenWords;
            int j = 0;
            for (; j < wordCount; j++) {
                int wordStart = i + j * wordLen;
                string word = s.substr(wordStart, wordLen);
                
                if (wordMap.find(word) == wordMap.end()) {
                    break;  // Word not in the list
                }
                
                seenWords[word]++;
                
                if (seenWords[word] > wordMap[word]) {
                    break;  // Word frequency exceeded
                }
            }
            
            if (j == wordCount) {
                result.push_back(i);  // Found a valid starting index
            }
        }
        
        return result;          
    }
};
