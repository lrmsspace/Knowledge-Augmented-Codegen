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

char* kthDistinct(char** arr, int arrSize, int k) {
    int count[1000] = {0};
    for (int i = 0; i < arrSize; i++) {
        for (int j = 0; j < arrSize; j++) {
            if (i != j && strcmp(arr[i], arr[j]) == 0) {
                count[i]++;
            }
        }
    }
    for (int i = 0; i < arrSize; i++) {
        if (count[i] == 0) {
            k--;
            if (k == 0) {
                return arr[i];
            }
        }
    }
    return "";      
}
