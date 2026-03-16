// Source: https://leetcode.com/problems/maximum-number-of-removable-characters/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings s and p where p is a subsequence of s. You are also given a distinct 0-indexed integer array removable containing a subset of indices of s (s is also 0-indexed).
//
// You want to choose an integer k (0 <= k <= removable.length) such that, after removing k characters from s using the first k indices in removable, p is still a subsequence of s. More formally, you will mark the character at s[removable[i]] for each 0 <= i < k, then remove all marked characters and check if p is still a subsequence.
//
// Return the maximum k you can choose such that p is still a subsequence of s after the removals.
//
// A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
//
// Example:
// Input: s = "abcacb", p = "ab", removable = [3,1,0]
// Output: 2
// Explanation: After removing the characters at indices 3 and 1, "abcacb" becomes "accb".
// "ab" is a subsequence of "accb".
// If we remove the characters at indices 3, 1, and 0, "abcacb" becomes "ccb", and "ab" is no longer a subsequence.
// Hence, the maximum k is 2.
//
// Constraints:
// 1 <= p.length <= s.length <= 105
// 	0 <= removable.length < s.length
// 	0 <= removable[i] < s.length
// 	p is a subsequence of s.
// 	s and p both consist of lowercase English letters.
// 	The elements in removable are distinct.
//

int maximumRemovals(char* s, char* p, int* removable, int removableSize) {
    int left = 0, right = removableSize, mid;
    int s_len = strlen(s);
    int p_len = strlen(p);

    while (left < right) {
        mid = left + (right - left + 1) / 2;

        // Mark characters to be removed
        char* temp_s = (char*)malloc((s_len + 1) * sizeof(char));
        strcpy(temp_s, s);
        for (int i = 0; i < mid; i++) {
            temp_s[removable[i]] = '#'; // Mark removed characters
        }

        // Check if p is still a subsequence of temp_s
        int p_index = 0;
        for (int i = 0; i < s_len && p_index < p_len; i++) {
            if (temp_s[i] == p[p_index]) {
                p_index++;
            }
        }

        free(temp_s);

        if (p_index == p_len) {
            left = mid; // p is still a subsequence, try for a larger k
        } else {
            right = mid - 1; // p is not a subsequence, try for a smaller k
        }
    }

    return left;        
}
