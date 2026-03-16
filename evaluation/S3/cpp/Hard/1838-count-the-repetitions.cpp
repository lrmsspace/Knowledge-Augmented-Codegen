// Source: https://leetcode.com/problems/count-the-repetitions/   |   Difficulty: Hard
//
// Problem Description:
// We define str = [s, n] as the string str which consists of the string s concatenated n times.
//
//
// 	For example, str == ["abc", 3] =="abcabcabc".
//
//
// We define that string s1 can be obtained from string s2 if we can remove some characters from s2 such that it becomes s1.
//
//
// 	For example, s1 = "abc" can be obtained from s2 = "abdbec" based on our definition by removing the bolded underlined characters.
//
//
// You are given two strings s1 and s2 and two integers n1 and n2. You have the two strings str1 = [s1, n1] and str2 = [s2, n2].
//
// Return the maximum integer m such that str = [str2, m] can be obtained from str1.
//
// Example:
// Input: s1 = "acb", n1 = 4, s2 = "ab", n2 = 2
// Output: 2
//
// Constraints:
// 1 <= s1.length, s2.length <= 100
// 	s1 and s2 consist of lowercase English letters.
// 	1 <= n1, n2 <= 106
//
// Helpful references (internal KB):
// - Substring Search (string, array, two-pointers, simulation)
//   • When to use: Use KMP to efficiently find all occurrences of a pattern string within a larger text. It is particularly useful when the pattern might appear multiple times or when avoiding redundant text scans is crucial for performance.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm efficiently finds all occurrences of a pattern string within a text string by pre-processing the pattern to avoid re-scanning characters in the text. It achieves a time complexity of O(N + M), where N is text length and M is pattern length.
//   • Invariants: The `next` array is correctly pre-computed such that `next[k]` indicates the longest proper prefix of `pattern[0...k-1]` that is also a suffix of `pattern[0...k-1]`.; During the search phase, `text[i-j ... i-1]` always matches `pattern[0 ... j-1]` if `j > 0`.
//   • Tips: Pre-compute the 'next' array (also known as LPS or failure array) for the pattern.; The 'next' array stores the length of the longest proper prefix of the pattern that is also a suffix of the pattern up to that index.
//   • Pitfalls: Incorrectly building the 'next' (LPS) array, especially handling the base cases or transitions.; Off-by-one errors in array indexing for either the text or pattern pointers.
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
// - Substring Search (string, array, kmp, simulation)
//   • When to use: Use when efficiently finding all occurrences or the first occurrence of a pattern within a larger text, especially when the pattern might have repeating or overlapping prefixes.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm that avoids re-scanning characters in the text by pre-processing the pattern to build a 'longest proper prefix suffix' (LPS) array. It achieves optimal O(N + M) time complexity, where N is the text length and M is the pattern length.
//   • Invariants: The `j` pointer always indicates the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `text[0...i-1]`.; The `lps[j]` value stores the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `pattern[0...j-1]`.
//   • Tips: Pre-compute the LPS array (also known as failure function or border array) for the pattern.; The LPS array helps determine the next best match position after a mismatch, avoiding redundant comparisons.
//   • Pitfalls: Incorrectly building the LPS array can lead to wrong matches or infinite loops.; Off-by-one errors when indexing the pattern or text are common.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
    	int s1Len = (int)s1.size();
    	int s2Len = (int)s2.size();
    	int* indexs = new int[s2Len];
    	int* counts = new int[s2Len];
    	int i;
    	int j = 0;
    	int count = 0;

    	for (i = 0; i < s2Len; ++i) {
    		indexs[i] = -1;
    		counts[i] = -1;
    	}

    	for (i = 0; i < n1; ++i) {
    		for (char c : s1) {
    			if (c == s2[j]) {
    				++j;
    				if (j == s2Len) {
    					j = 0;
    					++count;
    				}
    			}
    		}

    		if (indexs[j] != -1) {
    			int preIndex = indexs[j];
    			int preCount = counts[j];
    			int patternCount = count - preCount;
    			int patternLength = i - preIndex;

    			int remainingCount = n1 - i - 1;
    			count += patternCount * (remainingCount / patternLength);
    			i += patternLength * (remainingCount / patternLength);
    		} else {
    			indexs[j] = i;
    			counts[j] = count;
    		}
    	}

    	delete[] indexs;
    	delete[] counts;

    	return count / n2;
    }
};
