// Source: https://leetcode.com/problems/group-anagrams/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of strings strs, group the anagrams together. You can return the answer in any order.
//
// Example:
// Input: strs = ["eat","tea","tan","ate","nat","bat"]
//
// Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
//
// Explanation:
//
//
// 	There is no string in strs that can be rearranged to form "bat".
// 	The strings "nat" and "tan" are anagrams as they can be rearranged to form each other.
// 	The strings "ate", "eat", and "tea" are anagrams as they can be rearranged to form each other.
//
// Constraints:
// 1 <= strs.length <= 104
// 	0 <= strs[i].length <= 100
// 	strs[i] consists of lowercase English letters.
//

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> anagramMap;
        for (const string& str : strs) {
            string sortedStr = str;
            sort(sortedStr.begin(), sortedStr.end());
            anagramMap[sortedStr].push_back(str);
        }

        vector<vector<string>> result;
        for (auto& entry : anagramMap) {
            result.push_back(move(entry.second));
        }

        return result;          
    }
};
