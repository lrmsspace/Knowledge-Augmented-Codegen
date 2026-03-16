// Source: https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and an integer k, a k duplicate removal consists of choosing k adjacent and equal letters from s and removing them, causing the left and the right side of the deleted substring to concatenate together.
//
// We repeatedly make k duplicate removals on s until we no longer can.
//
// Return the final string after all such duplicate removals have been made. It is guaranteed that the answer is unique.
//
// Example:
// Input: s = "abcd", k = 2
// Output: "abcd"
// Explanation: There's nothing to delete.
//
// Constraints:
// 1 <= s.length <= 105
// 	2 <= k <= 104
// 	s only contains lowercase English letters.
//

class Solution {
public:
    string removeDuplicates(string s, int k) {
        vector<pair<char, int>> stack; // pair of (character, current count)

        for (char c : s) {
            if (!stack.empty() && stack.back().first == c) {
                stack.back().second++;
                if (stack.back().second == k) {
                    stack.pop_back(); // Remove the last k duplicates
                }
            } else {
                stack.emplace_back(c, 1);
            }
        }

        string result;
        for (const auto& p : stack) {
            result.append(p.second, p.first);
        }

        return result;          
    }
};
