// Source: https://leetcode.com/problems/finding-3-digit-even-numbers/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array digits, where each element is a digit. The array may contain duplicates.
//
// You need to find all the unique integers that follow the given requirements:
//
//
// 	The integer consists of the concatenation of three elements from digits in any arbitrary order.
// 	The integer does not have leading zeros.
// 	The integer is even.
//
//
// For example, if the given digits were [1, 2, 3], integers 132 and 312 follow the requirements.
//
// Return a sorted array of the unique integers.
//
// Example:
// Input: digits = [2,1,3,0]
// Output: [102,120,130,132,210,230,302,310,312,320]
// Explanation: All the possible integers that follow the requirements are in the output array. 
// Notice that there are no odd integers or integers with leading zeros.
//
// Constraints:
// 3 <= digits.length <= 100
// 	0 <= digits[i] <= 9
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - bucket-sort (array, linked-list, bucket-sort)
//   • When to use: Use when sorting elements, especially floating-point numbers, that are uniformly distributed over a range. It offers linear time complexity on average for such distributions.
//   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket individually using another sorting algorithm, and then concatenates the sorted buckets. It achieves an average time complexity of O(N+K), where N is the number of elements and K is the number of buckets.
//   • Invariants: Before sorting any bucket, all elements are correctly placed in their respective buckets based on their range.; After sorting each individual bucket, all elements within that bucket are in sorted order.
//   • Tips: Use a stable sorting algorithm like Insertion Sort for individual buckets to maintain overall stability.; The number of buckets should be chosen carefully, often proportional to N, to optimize performance.
//   • Pitfalls: Performance degrades significantly with non-uniform data distributions, potentially becoming O(N^2).; Requires extra space for the buckets, which can be substantial for many buckets or large elements.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} digits
 * @return {number[]}
 */
var findEvenNumbers = function(digits) {
    const count = new Array(10).fill(0);
    for (const digit of digits) {
        count[digit]++;
    }
    
    const result = [];
    
    for (let i = 100; i <= 999; i += 2) {
        const d1 = Math.floor(i / 100);
        const d2 = Math.floor((i % 100) / 10);
        const d3 = i % 10;
        
        if (count[d1] > 0 && count[d2] > 0 && count[d3] > 0) {
            // Decrease the count for each digit to check if we can form the number
            count[d1]--;
            count[d2]--;
            count[d3]--;
            
            // If all counts are still non-negative, we can form this number
            if (count[d1] >= 0 && count[d2] >= 0 && count[d3] >= 0) {
                result.push(i);
            }
            
            // Restore the counts
            count[d1]++;
            count[d2]++;
            count[d3]++;
        }
    }
    
    return result;
};
