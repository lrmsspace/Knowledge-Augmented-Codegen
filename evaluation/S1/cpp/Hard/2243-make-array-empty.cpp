// Source: https://leetcode.com/problems/make-array-empty/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums containing distinct numbers, and you can perform the following operations until the array is empty:
//
//
// 	If the first element has the smallest value, remove it
// 	Otherwise, put the first element at the end of the array.
//
//
// Return an integer denoting the number of operations it takes to make nums empty.
//
// Example:
// Input: nums = [3,4,-1]
// Output: 5
//
//
//
// 	
// 		
// 			Operation
// 			Array
// 		
// 	
// 	
// 		
// 			1
// 			[4, -1, 3]
// 		
// 		
// 			2
// 			[-1, 3, 4]
// 		
// 		
// 			3
// 			[3, 4]
// 		
// 		
// 			4
// 			[4]
// 		
// 		
// 			5
// 			[]
//
// Constraints:
// 1 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
// 	All values in nums are distinct.
//
// Helpful references (internal KB):
// - Fenwick Tree (array, bit-fenwick, difference-array)
//   • When to use: Use when an array requires frequent point updates and efficient retrieval of prefix sums or range sums. It offers logarithmic time complexity for both operations.
//   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently supports point updates and prefix sum queries on an array in O(log N) time.
//   • Invariants: Each `bit[i]` stores the sum of a contiguous range of elements from the original array.; The range length represented by `bit[i]` is determined by `i & -i` (the least significant bit).
//   • Tips: Use 1-based indexing for simpler bitwise operations (`i & -i`).; Initialize with an existing array in O(N) time using a linear construction method.
//   • Pitfalls: Directly finding range minimum/maximum is not efficient or generally supported.; Operations must be associative and preferably invertible for general range queries.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long countOperationsToEmptyArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> sortedNums(nums);
        sort(sortedNums.begin(), sortedNums.end());
        
        unordered_map<int, int> indexMap;
        for (int i = 0; i < n; ++i) {
            indexMap[sortedNums[i]] = i + 1; // 1-based index for Fenwick Tree
        }
        
        vector<int> fenwickTree(n + 1, 0);
        
        auto fenwickUpdate = [&](int idx, int delta) {
            while (idx <= n) {
                fenwickTree[idx] += delta;
                idx += idx & -idx;
            }
        };
        
        auto fenwickQuery = [&](int idx) {
            int sum = 0;
            while (idx > 0) {
                sum += fenwickTree[idx];
                idx -= idx & -idx;
            }
            return sum;
        };
        
        long long operations = 0;
        for (int num : nums) {
            int idx = indexMap[num];
            int smallerCount = fenwickQuery(idx - 1);
            operations += (n - smallerCount - 1); // Elements after current
            fenwickUpdate(idx, 1); // Mark this element as removed
        }
        
        return operations;          
    }
};
