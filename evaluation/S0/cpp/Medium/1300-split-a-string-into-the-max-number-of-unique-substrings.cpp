// Source: https://leetcode.com/problems/split-a-string-into-the-max-number-of-unique-substrings/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, return the maximum number of unique substrings that the given string can be split into.
//
// You can split string s into any list of non-empty substrings, where the concatenation of the substrings forms the original string. However, you must split the substrings such that all of them are unique.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "ababccc"
// Output: 5
// Explanation: One way to split maximally is ['a', 'b', 'ab', 'c', 'cc']. Splitting like ['a', 'b', 'a', 'b', 'c', 'cc'] is not valid as you have 'a' and 'b' multiple times.
//
// Constraints:
// 1 <= s.length <= 16
// 	
// 	
// 	s contains only lower case English letters.
//

class Solution {
public:
    int maxUniqueSplit(string s) {
        int maxCount = 0;
        unordered_set<string> seen;

        function<void(int)> backtrack = [&](int start) {
            if (start == s.size()) {
                maxCount = max(maxCount, (int)seen.size());
                return;
            }

            for (int end = start + 1; end <= s.size(); ++end) {
                string substring = s.substr(start, end - start);
                if (seen.count(substring) == 0) {
                    seen.insert(substring);
                    backtrack(end);
                    seen.erase(substring);
                }
            }
        };

        backtrack(0);
        return maxCount;            
    }
};
