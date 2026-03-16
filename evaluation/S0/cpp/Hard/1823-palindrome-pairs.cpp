// Source: https://leetcode.com/problems/palindrome-pairs/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array of unique strings words.
//
// A palindrome pair is a pair of integers (i, j) such that:
//
//
//  0 <= i, j < words.length,
//  i != j, and
//  words[i] + words[j] (the concatenation of the two strings) is a palindrome.
//
//
// Return an array of all the palindrome pairs of words.
//
// You must write an algorithm with O(sum of words[i].length) runtime complexity.
//
// Example:
// Input: words = ["abcd","dcba","lls","s","sssll"]
// Output: [[0,1],[1,0],[3,2],[2,4]]
// Explanation: The palindromes are ["abcddcba","dcbaabcd","slls","llssssll"]
//
// Constraints:
// 1 <= words.length <= 5000
//  0 <= words[i].length <= 300
//  words[i] consists of lowercase English letters.
//

class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        unordered_map<string, int> wordIndex;
        for (int i = 0; i < words.size(); i++) {
            wordIndex[words[i]] = i;
        }
        
        vector<vector<int>> result;
        
        for (int i = 0; i < words.size(); i++) {
            const string& word = words[i];
            int n = word.length();
            
            for (int j = 0; j <= n; j++) {
                string left = word.substr(0, j);
                string right = word.substr(j);
                
                if (isPalindrome(left)) {
                    string revRight = right;
                    reverse(revRight.begin(), revRight.end());
                    if (wordIndex.count(revRight) && wordIndex[revRight] != i) {
                        result.push_back({wordIndex[revRight], i});
                    }
                }
                
                if (j != n && isPalindrome(right)) {
                    string revLeft = left;
                    reverse(revLeft.begin(), revLeft.end());
                    if (wordIndex.count(revLeft) && wordIndex[revLeft] != i) {
                        result.push_back({i, wordIndex[revLeft]});
                    }
                }
            }
        }
        
        return result;          
    }
};
