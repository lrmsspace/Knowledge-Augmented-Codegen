// Source: https://leetcode.com/problems/find-maximum-removals-from-source-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string source of size n, a string pattern that is a subsequence of source, and a sorted integer array targetIndices that contains distinct numbers in the range [0, n - 1].
//
// We define an operation as removing a character at an index idx from source such that:
//
//
// 	idx is an element of targetIndices.
// 	pattern remains a subsequence of source after removing the character.
//
//
// Performing an operation does not change the indices of the other characters in source. For example, if you remove 'c' from "acb", the character at index 2 would still be 'b'.
//
// Return the maximum number of operations that can be performed.
//
// Example:
// Input: source = "abbaa", pattern = "aba", targetIndices = [0,1,2]
//
// Output: 1
//
// Explanation:
//
// We can't remove source[0] but we can do either of these two operations:
//
//
// 	Remove source[1], so that source becomes "a_baa".
// 	Remove source[2], so that source becomes "ab_aa".
//
// Constraints:
// 1 <= n == source.length <= 3 * 103
// 	1 <= pattern.length <= n
// 	1 <= targetIndices.length <= n
// 	targetIndices is sorted in ascending order.
// 	The input is generated such that targetIndices contains distinct elements in the range [0, n - 1].
// 	source and pattern consist only of lowercase English letters.
// 	The input is generated such that pattern appears as a subsequence in source.
//

int maxRemovals(char* source, char* pattern, int* targetIndices, int targetIndicesSize) {
    int left = 0, right = targetIndicesSize;
    int sourceLen = strlen(source);
    int patternLen = strlen(pattern);

    while (left < right) {
        int mid = left + (right - left + 1) / 2;

        // Create a boolean array to mark removed characters
        bool removed[sourceLen];
        memset(removed, false, sizeof(removed));
        for (int i = 0; i < mid; i++) {
            removed[targetIndices[i]] = true;
        }

        // Check if pattern is still a subsequence of source after removals
        int pIndex = 0;
        for (int sIndex = 0; sIndex < sourceLen && pIndex < patternLen; sIndex++) {
            if (!removed[sIndex] && source[sIndex] == pattern[pIndex]) {
                pIndex++;
            }
        }

        if (pIndex == patternLen) {
            left = mid; // pattern is still a subsequence, try for more removals
        } else {
            right = mid - 1; // pattern is not a subsequence, try fewer removals
        }
    }

    return left;        
}
