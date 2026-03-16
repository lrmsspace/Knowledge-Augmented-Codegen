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

int strStr(char* haystack, char* needle) {
    if (!*needle) return 0; // If needle is an empty string, return 0

    char *h = haystack;
    char *n = needle;

    while (*h) {
        char *h_start = h;
        n = needle;

        while (*h && *n && *h == *n) {
            h++;
            n++;
        }

        if (!*n) {
            return h_start - haystack; // Found the needle, return the starting index
        }

        h = h_start + 1; // Move to the next character in haystack
    }

    return -1; // Needle not found in haystack      
}
