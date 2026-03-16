// Source: https://leetcode.com/problems/minimum-index-sum-of-two-lists/   |   Difficulty: Easy
//
// Problem Description:
// Given two arrays of strings list1 and list2, find the common strings with the least index sum.
//
// A common string is a string that appeared in both list1 and list2.
//
// A common string with the least index sum is a common string such that if it appeared at list1[i] and list2[j] then i + j should be the minimum value among all the other common strings.
//
// Return all the common strings with the least index sum. Return the answer in any order.
//
// Example:
// Input: list1 = ["Shogun","Tapioca Express","Burger King","KFC"], list2 = ["Piatti","The Grill at Torrey Pines","Hungry Hunter Steakhouse","Shogun"]
// Output: ["Shogun"]
// Explanation: The only common string is "Shogun".
//
// Constraints:
// 1 <= list1.length, list2.length <= 1000
// 	1 <= list1[i].length, list2[i].length <= 30
// 	list1[i] and list2[i] consist of spaces ' ' and English letters.
// 	All the strings of list1 are unique.
// 	All the strings of list2 are unique.
// 	There is at least a common string between list1 and list2.
//
// Helpful references (internal KB):
// - String Hashing (string, number, hashing)
//   • When to use: Use when needing to compare strings or substrings quickly, reducing comparison time from linear to constant. It is ideal for problems requiring frequent string equality checks or pattern matching across large texts.
//   • Idea: String hashing maps a string to an integer hash value, allowing for O(1) equality checks between strings or substrings. This technique relies on a hash function where equal strings must produce equal hashes, though the reverse is not guaranteed.
//   • Invariants: The hash of any prefix s[0...i] is correctly computed based on s[0...i-1] and s[i].; All characters processed up to the current index i contribute to the current hash value.
//   • Tips: Use a polynomial rolling hash function with a prime base and a large prime modulus.; Employ double hashing (two different bases/moduli) to significantly reduce collision probability.
//   • Pitfalls: Hash collisions: Different strings can produce the same hash, leading to false positives if not handled.; Poor choice of base or modulus can lead to more frequent collisions.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Hash Tables (array, hashing, enumeration)
//   • When to use: Use hash tables when efficient storage and retrieval of data by a key are required. They are ideal for implementing dictionaries, sets, or caches where average O(1) time complexity for operations is crucial.
//   • Idea: Hash tables store key-value pairs by mapping keys to array indices using a hash function and a collision resolution strategy. They provide average O(1) time complexity for insertion, deletion, and lookup operations.
//   • Invariants: Each key, if present, is stored at an index derived from its hash code.; If key1.equals(key2), their hash codes produce the same array index (before collision resolution).
//   • Tips: Design hash functions to distribute keys uniformly across the table.; Ensure hashCode() and equals() methods are consistent for custom objects.
//   • Pitfalls: Poor hash functions lead to excessive collisions and O(N) worst-case performance.; Inconsistent hashCode() and equals() can cause data retrieval failures.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public String[] findRestaurant(String[] list1, String[] list2) {
        Map<String, Integer> indexMap = new HashMap<>();
        for (int i = 0; i < list1.length; i++) {
            indexMap.put(list1[i], i);
        }

        List<String> result = new ArrayList<>();
        int minIndexSum = Integer.MAX_VALUE;

        for (int j = 0; j < list2.length; j++) {
            if (indexMap.containsKey(list2[j])) {
                int indexSum = j + indexMap.get(list2[j]);
                if (indexSum < minIndexSum) {
                    minIndexSum = indexSum;
                    result.clear();
                    result.add(list2[j]);
                } else if (indexSum == minIndexSum) {
                    result.add(list2[j]);
                }
            }
        }

        return result.toArray(new String[0]);           
    }
}
