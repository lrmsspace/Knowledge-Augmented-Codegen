// Source: https://leetcode.com/problems/kth-distinct-string-in-an-array/   |   Difficulty: Easy
//
// Problem Description:
// A distinct string is a string that is present only once in an array.
//
// Given an array of strings arr, and an integer k, return the kth distinct string present in arr. If there are fewer than k distinct strings, return an empty string "".
//
// Note that the strings are considered in the order in which they appear in the array.
//
// Example:
// Input: arr = ["d","b","c","b","c","a"], k = 2
// Output: "a"
// Explanation:
// The only distinct strings in arr are "d" and "a".
// "d" appears 1st, so it is the 1st distinct string.
// "a" appears 2nd, so it is the 2nd distinct string.
// Since k == 2, "a" is returned.
//
// Constraints:
// 1 <= k <= arr.length <= 1000
// 	1 <= arr[i].length <= 5
// 	arr[i] consists of lowercase English letters.
//
// Helpful references (internal KB):
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* kthDistinct(char** arr, int arrSize, int k) {
    // Step 1: Count the occurrences of each string using a hash map (dictionary).
    // Since C does not have built-in hash maps, we can use a simple array of pointers to store unique strings and their counts.
    char* uniqueStrings[1000]; // To store unique strings (max 1000 as per constraints)
    int counts[1000] = {0};    // To store counts of each unique string
    int uniqueCount = 0;       // Number of unique strings found

    for (int i = 0; i < arrSize; i++) {
        char* currentString = arr[i];
        int foundIndex = -1;

        // Check if the current string is already in the uniqueStrings array
        for (int j = 0; j < uniqueCount; j++) {
            if (strcmp(uniqueStrings[j], currentString) == 0) {
                foundIndex = j;
                break;
            }
        }

        if (foundIndex != -1) {
            // If found, increment the count
            counts[foundIndex]++;
        } else {
            // If not found, add it to the uniqueStrings array and set count to 1
            uniqueStrings[uniqueCount] = currentString;
            counts[uniqueCount] = 1;
            uniqueCount++;
        }
    }

    // Step 2: Find the kth distinct string
    int distinctCount = 0; // To count distinct strings encountered

    for (int i = 0; i < uniqueCount; i++) {
        if (counts[i] == 1) { // Check if it's a distinct string
            distinctCount++;
            if (distinctCount == k) {
                return uniqueStrings[i]; // Return the kth distinct string
            }
        }
    }

    return ""; // Return an empty string if there are fewer than k distinct strings     
}
