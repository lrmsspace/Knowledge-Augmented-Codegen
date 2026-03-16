// Source: https://leetcode.com/problems/query-kth-smallest-trimmed-number/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array of strings nums, where each string is of equal length and consists of only digits.
//
// You are also given a 0-indexed 2D integer array queries where queries[i] = [ki, trimi]. For each queries[i], you need to:
//
//
// 	Trim each number in nums to its rightmost trimi digits.
// 	Determine the index of the kith smallest trimmed number in nums. If two trimmed numbers are equal, the number with the lower index is considered to be smaller.
// 	Reset each number in nums to its original length.
//
//
// Return an array answer of the same length as queries, where answer[i] is the answer to the ith query.
//
// Note:
//
//
// 	To trim to the rightmost x digits means to keep removing the leftmost digit, until only x digits remain.
// 	Strings in nums may contain leading zeros.
//
// Example:
// Input: nums = ["102","473","251","814"], queries = [[1,1],[2,3],[4,2],[1,2]]
// Output: [2,2,1,0]
// Explanation:
// 1. After trimming to the last digit, nums = ["2","3","1","4"]. The smallest number is 1 at index 2.
// 2. Trimmed to the last 3 digits, nums is unchanged. The 2nd smallest number is 251 at index 2.
// 3. Trimmed to the last 2 digits, nums = ["02","73","51","14"]. The 4th smallest number is 73.
// 4. Trimmed to the last 2 digits, the smallest number is 2 at index 0.
//    Note that the trimmed number "02" is evaluated as 2.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i].length <= 100
// 	nums[i] consists of only digits.
// 	All nums[i].length are equal.
// 	1 <= queries.length <= 100
// 	queries[i].length == 2
// 	1 <= ki <= nums.length
// 	1 <= trimi <= nums[i].length
//
//
//  
// Follow up: Could you use the Radix Sort Algorithm to solve this problem? What will be the complexity of that solution?
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: When counting numbers within a given range [A, B] that satisfy certain digit-based properties, or calculating a sum of such properties.
//   • Idea: Digit DP is a dynamic programming technique used to count numbers or calculate sums of properties for numbers within a given range, based on their digits. It typically involves a recursive function with memoization, processing digits from most significant to least significant, achieving a time complexity of O(log(N) * S * T) where S is sum/state range and T is tight constraint.
//   • Invariants: The `idx` parameter always represents the current digit position being processed, from most significant to least significant.; The `tight` boolean parameter accurately indicates if the current digit choice is restricted by the original number's corresponding digit.
//   • Tips: Handle leading zeros carefully, often with a dedicated boolean state in the DP function.; Use a 'tight' or 'limit' boolean parameter to manage the upper bound constraint imposed by the original number.
//   • Pitfalls: Incorrectly handling the 'tight' constraint can lead to overcounting or undercounting.; Forgetting to reset the memoization table for each new query or test case, especially in competitive programming.
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] smallestTrimmedNumbers(String[] nums, int[][] queries) {
        int n = nums.length, m = nums[0].length(), q = queries.length;
        int[] ans = new int[q];
        for (int i = 0; i < q; i++) {
            int k = queries[i][0], trim = queries[i][1];
            String[] trimmed = new String[n];
            for (int j = 0; j < n; j++) {
                trimmed[j] = nums[j].substring(m - trim);
            }
            Integer[] idxs = new Integer[n];
            for (int j = 0; j < n; j++) {
                idxs[j] = j;
            }
            Arrays.sort(idxs, (a, b) -> {
                if (!trimmed[a].equals(trimmed[b])) {
                    return trimmed[a].compareTo(trimmed[b]);
                }
                return a - b;
            });
            ans[i] = idxs[k - 1];
        }
        return ans;         
    }
}
