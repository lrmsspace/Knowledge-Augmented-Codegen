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

class Solution {
    public String kthDistinct(String[] arr, int k) {
        Map<String, Integer> frequencyMap = new HashMap<>();

        // Count the frequency of each string in the array
        for (String str : arr) {
            frequencyMap.put(str, frequencyMap.getOrDefault(str, 0) + 1);
        }

        // Iterate through the array to find the k-th distinct string
        for (String str : arr) {
            if (frequencyMap.get(str) == 1) {
                k--;
                if (k == 0) {
                    return str;
                }
            }
        }

        // If there are fewer than k distinct strings, return an empty string
        return "";          
    }
}
