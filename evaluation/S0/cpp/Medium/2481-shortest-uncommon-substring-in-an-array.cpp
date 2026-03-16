// Source: https://leetcode.com/problems/shortest-uncommon-substring-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array arr of size n consisting of non-empty strings.
//
// Find a string array answer of size n such that:
//
//
// 	answer[i] is the shortest substring of arr[i] that does not occur as a substring in any other string in arr. If multiple such substrings exist, answer[i] should be the lexicographically smallest. And if no such substring exists, answer[i] should be an empty string.
//
//
// Return the array answer.
//
// Example:
// Input: arr = ["cab","ad","bad","c"]
// Output: ["ab","","ba",""]
// Explanation: We have the following:
// - For the string "cab", the shortest substring that does not occur in any other string is either "ca" or "ab", we choose the lexicographically smaller substring, which is "ab".
// - For the string "ad", there is no substring that does not occur in any other string.
// - For the string "bad", the shortest substring that does not occur in any other string is "ba".
// - For the string "c", there is no substring that does not occur in any other string.
//
// Constraints:
// n == arr.length
// 	2 <= n <= 100
// 	1 <= arr[i].length <= 20
// 	arr[i] consists only of lowercase English letters.
//

class Solution {
public:
    vector<string> shortestSubstrings(vector<string>& arr) {
        int n = arr.size();
        vector<unordered_map<string, int>> substringCount(n);
        
        // Count substrings for each string
        for (int i = 0; i < n; ++i) {
            const string& s = arr[i];
            int len = s.length();
            for (int start = 0; start < len; ++start) {
                for (int l = 1; l <= len - start; ++l) {
                    string sub = s.substr(start, l);
                    substringCount[i][sub]++;
                }
            }
        }
        
        vector<string> result(n, "");
        
        // Find shortest uncommon substring for each string
        for (int i = 0; i < n; ++i) {
            const string& s = arr[i];
            int len = s.length();
            string shortest = "";
            
            for (int start = 0; start < len; ++start) {
                for (int l = 1; l <= len - start; ++l) {
                    string sub = s.substr(start, l);
                    bool isUncommon = true;
                    
                    // Check if this substring occurs in any other string
                    for (int j = 0; j < n; ++j) {
                        if (j != i && substringCount[j].count(sub) > 0) {
                            isUncommon = false;
                            break;
                        }
                    }
                    
                    if (isUncommon) {
                        if (shortest == "" || sub.length() < shortest.length() || 
                            (sub.length() == shortest.length() && sub < shortest)) {
                            shortest = sub;
                        }
                    }
                }
            }
            
            result[i] = shortest;
        }
        
        return result;          
    }
};
