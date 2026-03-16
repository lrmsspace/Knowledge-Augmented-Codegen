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
// - String Sorts (array, string, recursion)
//   • When to use: Use this algorithm to sort a collection of strings lexicographically, especially when string lengths vary or are large, and the character set is limited.
//   • Idea: This algorithm sorts an array of strings lexicographically by recursively applying a counting sort-like distribution based on characters from most significant to least significant digit. It typically achieves O(N*L + R*L) time complexity, where N is the number of strings, L is the average string length, and R is the radix size.
//   • Invariants: All strings in the current `a[lo...hi]` sub-array share a common prefix of length `d`.; After the distribution pass for character `d`, `aux` contains strings from `a[lo...hi]` stably sorted by their `d`-th character.
//   • Tips: Use an auxiliary array for stable distribution during each pass to maintain relative order.; Implement a cutoff to insertion sort for small sub-arrays to improve performance due to lower overhead.
//   • Pitfalls: Can have high overhead for small N or short strings compared to comparison sorts.; Potentially memory intensive due to the auxiliary array and recursion stack depth proportional to max string length.
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
// - Minkowski sum of convex polygons (geometry, array, two-pointers, sweep-line)
//   • When to use: Use this algorithm to compute the Minkowski sum of two convex polygons efficiently. It is ideal for applications requiring the union of shapes or collision detection between convex objects.
//   • Idea: This algorithm computes the Minkowski sum of two convex polygons by merging their edge vectors, sorted by polar angle, into a new sequence of edges. The resulting sum polygon is also convex and can be constructed in O(|P| + |Q|) time.
//   • Invariants: The current vertex of the resulting sum polygon is the sum of the current vertices from P and Q.; All edges processed so far from both input polygons have been added to the output in polar angle order.
//   • Tips: Pre-sort polygon vertices to start from the lowest Y-coordinate to ensure consistent orientation.; Orient both input polygons counter-clockwise for correct edge vector generation.
//   • Pitfalls: Incorrectly handling polygon orientation (e.g., mixing clockwise and counter-clockwise).; Precision issues when using floating-point numbers for angle comparisons or vector additions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* sortVowels(char* s) {
    int is_vowel[256] = {0};
    is_vowel['a'] = 1; is_vowel['e'] = 1; is_vowel['i'] = 1; is_vowel['o'] = 1; is_vowel['u'] = 1;
    is_vowel['A'] = 1; is_vowel['E'] = 1; is_vowel['I'] = 1; is_vowel['O'] = 1; is_vowel['U'] = 1;

    int n = 0;
    while (s[n]) n++;

    char* vowels = (char*)malloc((n + 1) * sizeof(char));
    int vcount = 0;

    for (int i = 0; i < n; i++) {
        if (is_vowel[(unsigned char)s[i]]) {
            vowels[vcount++] = s[i];
        }
    }

    // Simple insertion sort for vowels
    for (int i = 1; i < vcount; i++) {
        char key = vowels[i];
        int j = i - 1;
        while (j >= 0 && vowels[j] > key) {
            vowels[j + 1] = vowels[j];
            j--;
        }
        vowels[j + 1] = key;
    }

    char* result = (char*)malloc((n + 1) * sizeof(char));
    int vi = 0;

    for (int i = 0; i < n; i++) {
        if (is_vowel[(unsigned char)s[i]]) {
            result[i] = vowels[vi++];
        } else {
            result[i] = s[i];
        }
    }
    result[n] = '\0';

    free(vowels);
    return result;      
}
