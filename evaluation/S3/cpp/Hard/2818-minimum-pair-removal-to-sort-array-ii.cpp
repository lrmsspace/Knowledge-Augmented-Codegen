// Source: https://leetcode.com/problems/minimum-pair-removal-to-sort-array-ii/   |   Difficulty: Hard
//
// Problem Description:
// Given an array nums, you can perform the following operation any number of times:
//
//
// 	Select the adjacent pair with the minimum sum in nums. If multiple such pairs exist, choose the leftmost one.
// 	Replace the pair with their sum.
//
//
// Return the minimum number of operations needed to make the array non-decreasing.
//
// An array is said to be non-decreasing if each element is greater than or equal to its previous element (if it exists).
//
// Example:
// Input: nums = [5,2,3,1]
//
// Output: 2
//
// Explanation:
//
//
// 	The pair (3,1) has the minimum sum of 4. After replacement, nums = [5,2,4].
// 	The pair (2,4) has the minimum sum of 6. After replacement, nums = [5,6].
//
//
// The array nums became non-decreasing in two operations.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
// - Minimum stack / Minimum queue (queue, deque, monotonic-queue)
//   • When to use: Use this technique when you need to perform standard queue or stack operations while also querying the minimum (or maximum) element in O(1) time. It is ideal for problems involving sliding windows or dynamic collections where min/max queries are frequent.
//   • Idea: This technique augments a queue or stack with an auxiliary data structure, typically a deque, to maintain elements in monotonic order. This allows for O(1) retrieval of the minimum (or maximum) element, with standard operations achieving amortized O(1) time complexity.
//   • Invariants: The auxiliary deque stores elements in non-decreasing order from front to back.; The element at the front of the auxiliary deque is the minimum of all elements currently in the main queue/stack.
//   • Tips: Utilize a deque for the auxiliary structure to efficiently add and remove from both ends.; For a minimum queue, maintain the auxiliary deque in non-decreasing order from front to back.
//   • Pitfalls: Incorrectly handling removals when the element to be removed from the main structure is not the current minimum.; Forgetting to remove elements from the auxiliary deque when they are no longer relevant (e.g., out of window bounds).
// - Minimum stack / Minimum queue (stack, simulation)
//   • When to use: When you need to perform standard stack operations (push, pop) and also query the minimum element currently in the stack, all in constant time.
//   • Idea: Augments a standard stack by storing each element along with the minimum value encountered up to that point in the stack. This allows O(1) retrieval of the current minimum, while push and pop operations also remain O(1).
//   • Invariants: The top element's second component (minimum_so_far) always represents the minimum value currently in the entire stack.; For any element (value, min_so_far) in the stack, min_so_far is the minimum of 'value' and all elements below it.
//   • Tips: Store elements as pairs: (actual_value, minimum_at_this_level).; When pushing, the new minimum_at_this_level is min(new_value, stack.top().second) if stack is not empty, else new_value.
//   • Pitfalls: Forgetting to handle the empty stack case when calculating the minimum for a new element.; Incorrectly assuming the minimum can be tracked with a single auxiliary variable without considering pops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();    
        int operations = 0;
        stack<pair<long long, int>> st;
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && st.top().first > nums[i]) {
                st.pop();
                operations++;
            }
            st.push({nums[i], i});
        }
        return operations;
    }
};
