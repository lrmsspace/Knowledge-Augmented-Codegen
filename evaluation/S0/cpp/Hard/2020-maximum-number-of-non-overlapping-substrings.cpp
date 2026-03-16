// Source: https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s of lowercase letters, you need to find the maximum number of non-empty substrings of s that meet the following conditions:
//
//
// 	The substrings do not overlap, that is for any two substrings s[i..j] and s[x..y], either j < x or i > y is true.
// 	A substring that contains a certain character c must also contain all occurrences of c.
//
//
// Find the maximum number of substrings that meet the above conditions. If there are multiple solutions with the same number of substrings, return the one with minimum total length. It can be shown that there exists a unique solution of minimum total length.
//
// Notice that you can return the substrings in any order.
//
// Example:
// Input: s = "adefaddaccc"
// Output: ["e","f","ccc"]
// Explanation: The following are all the possible substrings that meet the conditions:
// [
//   "adefaddaccc"
//   "adefadda",
//   "ef",
//   "e",
//   "f",
//   "ccc",
// ]
// If we choose the first string, we cannot choose anything else and we'd get only 1. If we choose "adefadda", we are left with "ccc" which is the only one that doesn't overlap, thus obtaining 2 substrings. Notice also, that it's not optimal to choose "ef" since it can be split into two. Therefore, the optimal way is to choose ["e","f","ccc"] which gives us 3 substrings. No other solution of the same number of substrings exist.
//
// Constraints:
// 1 <= s.length <= 105
// 	s contains only lowercase English letters.
//

class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.size();
        vector<int> left(26, n), right(26, -1);
        
        // Find leftmost and rightmost positions for each character
        for (int i = 0; i < n; i++) {
            left[s[i] - 'a'] = min(left[s[i] - 'a'], i);
            right[s[i] - 'a'] = max(right[s[i] - 'a'], i);
        }
        
        vector<pair<int, int>> intervals;
        
        // Create intervals for each character
        for (int i = 0; i < 26; i++) {
            if (right[i] == -1) continue;  // character not in string
            
            int l = left[i], r = right[i];
            bool valid = true;
            
            // Expand interval to include all occurrences of characters within it
            for (int j = l; j <= r; j++) {
                int c = s[j] - 'a';
                if (left[c] < l) {
                    valid = false;
                    break;
                }
                r = max(r, right[c]);
            }
            
            if (valid) {
                intervals.push_back({l, r});
            }
        }
        
        // Sort intervals by end position
        sort(intervals.begin(), intervals.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second < b.second;
        });
        
        vector<string> result;
        int prevEnd = -1;
        
        // Select non-overlapping intervals
        for (const auto& interval : intervals) {
            if (interval.first > prevEnd) {
                result.push_back(s.substr(interval.first, interval.second - interval.first + 1));
                prevEnd = interval.second;
            }
        }
        
        return result;          
    }
};
