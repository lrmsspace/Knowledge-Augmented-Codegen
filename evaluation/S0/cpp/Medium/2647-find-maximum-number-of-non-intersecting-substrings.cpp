// Source: https://leetcode.com/problems/find-maximum-number-of-non-intersecting-substrings/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string word.
//
// Return the maximum number of non-intersecting substrings of word that are at least four characters long and start and end with the same letter.
//
// Example:
// Input: word = "abcdeafdef"
//
// Output: 2
//
// Explanation:
//
// The two substrings are "abcdea" and "fdef".
//
// Constraints:
// 1 <= word.length <= 2 * 105
// 	word consists only of lowercase English letters.
//

class Solution {
public:
    int maxSubstrings(string word) {
        vector<pair<int, int>> intervals(26, {-1, -1});
        int n = word.size();

        for (int i = 0; i < n; ++i) {
            int c = word[i] - 'a';
            if (intervals[c].first == -1) {
                intervals[c] = {i, i};
            } else {
                intervals[c].second = i;
            }
        }

        vector<pair<int, int>> validIntervals;
        for (const auto& interval : intervals) {
            if (interval.first != -1) {
                int start = interval.first;
                int end = interval.second;
                bool valid = true;

                for (int j = start; j <= end; ++j) {
                    int c = word[j] - 'a';
                    if (intervals[c].first < start || intervals[c].second > end) {
                        valid = false;
                        break;
                    }
                }

                if (valid) {
                    validIntervals.push_back({start, end});
                }
            }
        }

        sort(validIntervals.begin(), validIntervals.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second < b.second;
        });

        int count = 0;
        int lastEnd = -1;

        for (const auto& interval : validIntervals) {
            if (interval.first > lastEnd) {
                count++;
                lastEnd = interval.second;
            }
        }

        return count;           
    }
};
