// Source: https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/   |   Difficulty: Easy
//
// Problem Description:
// Given two strings needle and haystack, return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
//
// Example:
// Input: haystack = "sadbutsad", needle = "sad"
// Output: 0
// Explanation: "sad" occurs at index 0 and 6.
// The first occurrence is at index 0, so we return 0.
//
// Constraints:
// 1 <= haystack.length, needle.length <= 104
// 	haystack and needle consist of only lowercase English characters.
//

class Solution {
public:
    int strStr(string haystack, string needle) {
        size_t pos = haystack.find(needle);
        if (pos != string::npos) {
            return static_cast<int>(pos);
        } else {
            return -1;
        }           
    }
};
