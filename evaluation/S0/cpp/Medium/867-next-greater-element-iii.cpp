// Source: https://leetcode.com/problems/next-greater-element-iii/   |   Difficulty: Medium
//
// Problem Description:
// Given a positive integer n, find the smallest integer which has exactly the same digits existing in the integer n and is greater in value than n. If no such positive integer exists, return -1.
//
// Note that the returned integer should fit in 32-bit integer, if there is a valid answer but it does not fit in 32-bit integer, return -1.
//
// Example:
// Input: n = 12
// Output: 21
//
// Constraints:
// 1 <= n <= 231 - 1
//

class Solution {
public:
    int nextGreaterElement(int n) {
        string s = to_string(n);
        int i = s.size() - 2;

        // Step 1: Find the first decreasing element from the right
        while (i >= 0 && s[i] >= s[i + 1]) {
            i--;
        }

        // If no such element is found, return -1
        if (i < 0) {
            return -1;
        }

        // Step 2: Find the smallest element on right side of i which is larger than s[i]
        int j = s.size() - 1;
        while (s[j] <= s[i]) {
            j--;
        }

        // Step 3: Swap elements at i and j
        swap(s[i], s[j]);

        // Step 4: Reverse the elements after index i
        reverse(s.begin() + i + 1, s.end());

        // Convert back to integer and check for overflow
        long long result = stoll(s);
        return (result > INT_MAX) ? -1 : static_cast<int>(result);          
    }
};
