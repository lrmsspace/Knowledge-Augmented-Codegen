// Source: https://leetcode.com/problems/shortest-string-that-contains-three-strings/   |   Difficulty: Medium
//
// Problem Description:
// Given three strings a, b, and c, your task is to find a string that has the minimum length and contains all three strings as substrings.
// If there are multiple such strings, return the lexicographically smallest one.
//
// Return a string denoting the answer to the problem.
//
// Notes
//
//
// 	A string a is lexicographically smaller than a string b (of the same length) if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b.
// 	A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: a = "abc", b = "bca", c = "aaa"
// Output: "aaabca"
// Explanation:  We show that "aaabca" contains all the given strings: a = ans[2...4], b = ans[3..5], c = ans[0..2]. It can be shown that the length of the resulting string would be at least 6 and "aaabca" is the lexicographically smallest one.
//
// Constraints:
// 1 <= a.length, b.length, c.length <= 100
// 	a, b, c consist only of lowercase English letters.
//

class Solution {
public:
    string minimumString(string a, string b, string c) {
        vector<string> strs = {a, b, c};
        string result;
        int n = strs.size();

        function<int(const string&, const string&)> overlap = [](const string& s1, const string& s2) {
            int maxOverlap = 0;
            int len1 = s1.length();
            int len2 = s2.length();
            for (int i = 1; i <= min(len1, len2); ++i) {
                if (s1.substr(len1 - i) == s2.substr(0, i)) {
                    maxOverlap = i;
                }
            }
            return maxOverlap;
        };

        function<string(const string&, const string&, const string&)> mergeThree = [&](const string& s1, const string& s2, const string& s3) {
            int o12 = overlap(s1, s2);
            string merged12 = s1 + s2.substr(o12);
            int o23 = overlap(merged12, s3);
            return merged12 + s3.substr(o23);
        };

        result = a + b + c; // Initialize with a large enough string

        vector<int> perm = {0, 1, 2};
        do {
            string candidate = mergeThree(strs[perm[0]], strs[perm[1]], strs[perm[2]]);
            if (candidate.length() < result.length() || (candidate.length() == result.length() && candidate < result)) {
                result = candidate;
            }
        } while (next_permutation(perm.begin(), perm.end()));

        return result;          
    }
};
