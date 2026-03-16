// Source: https://leetcode.com/problems/construct-target-array-with-multiple-sums/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array target of n integers. From a starting array arr consisting of n 1's, you may perform the following procedure :
//
//
// 	let x be the sum of all elements currently in your array.
// 	choose index i, such that 0 <= i < n and set the value of arr at index i to x.
// 	You may repeat this procedure as many times as needed.
//
//
// Return true if it is possible to construct the target array from arr, otherwise, return false.
//
// Example:
// Input: target = [9,3,5]
// Output: true
// Explanation: Start with arr = [1, 1, 1] 
// [1, 1, 1], sum = 3 choose index 1
// [1, 3, 1], sum = 5 choose index 2
// [1, 3, 5], sum = 9 choose index 0
// [9, 3, 5] Done
//
// Constraints:
// n == target.length
// 	1 <= n <= 5 * 104
// 	1 <= target[i] <= 109
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Maximum flow - Push-relabel method improved (graph, array, greedy, bfs)
//   • When to use: Use this for maximum flow problems on graphs where an optimized push-relabel approach is required. It improves performance by prioritizing vertices with the greatest height for push and relabel operations.
//   • Idea: This algorithm is an optimized variant of the push-relabel maximum flow method, which improves efficiency by always selecting the vertex with the greatest height that has excess flow. This specific vertex selection strategy leads to a better theoretical time complexity, typically O(V^2 * sqrt(E)) or O(V^3) depending on implementation details.
//   • Invariants: For any edge (u, v) in the residual graph, h(u) <= h(v) + 1.; The total excess flow in the network is always non-negative.
//   • Tips: Always select the active vertex with the highest current height.; Maintain a data structure (e.g., buckets or lists) to quickly find highest-height vertices.
//   • Pitfalls: Incorrectly managing the list of highest-height vertices.; Failing to update residual capacities after a push operation.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool isPossible(vector<int>& target) {
        priority_queue<long long> maxHeap;
        long long totalSum = 0;
        
        for (int num : target) {
            maxHeap.push(num);
            totalSum += num;
        }
        
        while (true) {
            long long largest = maxHeap.top();
            maxHeap.pop();
            long long restSum = totalSum - largest;
            
            if (largest == 1 || restSum == 1) {
                return true;
            }
            
            if (restSum == 0 || largest < restSum) {
                return false;
            }
            
            long long newValue = largest % restSum;
            if (newValue == 0) {
                return false;
            }
            
            maxHeap.push(newValue);
            totalSum = restSum + newValue;
        }
        
        return true; // This line is never reached          
    }
};
