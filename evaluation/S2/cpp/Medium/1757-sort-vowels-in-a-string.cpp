// Source: https://leetcode.com/problems/sort-vowels-in-a-string/   |   Difficulty: Medium
//
// Problem Description:
// Given a 0-indexed string s, permute s to get a new string t such that:
//
//
// 	All consonants remain in their original places. More formally, if there is an index i with 0 <= i < s.length such that s[i] is a consonant, then t[i] = s[i].
// 	The vowels must be sorted in the nondecreasing order of their ASCII values. More formally, for pairs of indices i, j with 0 <= i < j < s.length such that s[i] and s[j] are vowels, then t[i] must not have a higher ASCII value than t[j].
//
//
// Return the resulting string.
//
// The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in lowercase or uppercase. Consonants comprise all letters that are not vowels.
//
// Example:
// Input: s = "lEetcOde"
// Output: "lEOtcede"
// Explanation: 'E', 'O', and 'e' are the vowels in s; 'l', 't', 'c', and 'd' are all consonants. The vowels are sorted according to their ASCII values, and the consonants remain in the same places.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists only of letters of the English alphabet in uppercase and lowercase.
//
// Helpful references (internal KB):
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
// - bucket-sort (array, linked-list, bucket-sort)
//   • When to use: Use when sorting elements, especially floating-point numbers, that are uniformly distributed over a range. It offers linear time complexity on average for such distributions.
//   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket individually using another sorting algorithm, and then concatenates the sorted buckets. It achieves an average time complexity of O(N+K), where N is the number of elements and K is the number of buckets.
//   • Invariants: Before sorting any bucket, all elements are correctly placed in their respective buckets based on their range.; After sorting each individual bucket, all elements within that bucket are in sorted order.
//   • Tips: Use a stable sorting algorithm like Insertion Sort for individual buckets to maintain overall stability.; The number of buckets should be chosen carefully, often proportional to N, to optimize performance.
//   • Pitfalls: Performance degrades significantly with non-uniform data distributions, potentially becoming O(N^2).; Requires extra space for the buckets, which can be substantial for many buckets or large elements.
// - String Sorts (array, string, recursion)
//   • When to use: Use this algorithm to sort a collection of strings lexicographically, especially when string lengths vary or are large, and the character set is limited.
//   • Idea: This algorithm sorts an array of strings lexicographically by recursively applying a counting sort-like distribution based on characters from most significant to least significant digit. It typically achieves O(N*L + R*L) time complexity, where N is the number of strings, L is the average string length, and R is the radix size.
//   • Invariants: All strings in the current `a[lo...hi]` sub-array share a common prefix of length `d`.; After the distribution pass for character `d`, `aux` contains strings from `a[lo...hi]` stably sorted by their `d`-th character.
//   • Tips: Use an auxiliary array for stable distribution during each pass to maintain relative order.; Implement a cutoff to insertion sort for small sub-arrays to improve performance due to lower overhead.
//   • Pitfalls: Can have high overhead for small N or short strings compared to comparison sorts.; Potentially memory intensive due to the auxiliary array and recursion stack depth proportional to max string length.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    string sortVowels(string s) {
        string vowels;
        for (char c : s) {
            if (isVowel(c)) {
                vowels += c;
            }
        }

        sort(vowels.begin(), vowels.end());

        int index = 0;
        for (char& c : s) {
            if (isVowel(c)) {
                c = vowels[index++];
            }
        }

        return s;           
    }
};
