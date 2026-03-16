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
    public int maxUniqueSplit(String s) {
        return backtrack(s, 0, new HashSet<>());            
    }
}
