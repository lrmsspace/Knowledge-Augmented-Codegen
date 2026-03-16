// Source: https://leetcode.com/problems/minimum-time-to-make-array-sum-at-most-x/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed integer arrays nums1 and nums2 of equal length. Every second, for all indices 0 <= i < nums1.length, value of nums1[i] is incremented by nums2[i]. After this is done, you can do the following operation:
//
//
//  Choose an index 0 <= i < nums1.length and make nums1[i] = 0.
//
//
// You are also given an integer x.
//
// Return the minimum time in which you can make the sum of all elements of nums1 to be less than or equal to x, or -1 if this is not possible.
//
// Example:
// Input: nums1 = [1,2,3], nums2 = [1,2,3], x = 4
// Output: 3
// Explanation: 
// For the 1st second, we apply the operation on i = 0. Therefore nums1 = [0,2+2,3+3] = [0,4,6]. 
// For the 2nd second, we apply the operation on i = 1. Therefore nums1 = [0+1,0,6+3] = [1,0,9]. 
// For the 3rd second, we apply the operation on i = 2. Therefore nums1 = [1+1,0+2,0] = [2,2,0]. 
// Now sum of nums1 = 4. It can be shown that these operations are optimal, so we return 3.
//
// Constraints:
// 1 <= nums1.length <= 103
//  1 <= nums1[i] <= 103
//  0 <= nums2[i] <= 103
//  nums1.length == nums2.length
//  0 <= x <= 106
//
// Helpful references (internal KB):
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
//   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
//   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
//   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
//   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
// - Minkowski sum of convex polygons (geometry, array, two-pointers)
//   • When to use: When needing to compute the sum of two convex polygons, or efficiently determine the minimum distance or intersection between them.
//   • Idea: The Minkowski sum of two convex polygons P and Q is a new convex polygon formed by vector addition of all points from P and Q. It can be computed in O(|P| + |Q|) time by merging their edge vectors.
//   • Invariants: The current edge added to the Minkowski sum is the one with the smallest angle among the remaining edges from both polygons.; The sequence of edges in the Minkowski sum maintains convexity.
//   • Tips: The vertices of P+Q are sums of vertices of P and Q.; The edges of P+Q are the edges of P and Q, sorted by angle.
//   • Pitfalls: Incorrectly handling edge cases like collinear edges or degenerate polygons.; Floating point precision issues in geometric calculations.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumTime(int* nums1, int nums1Size, int* nums2, int nums2Size, int x) {
    // Step 1: Calculate the initial sum of nums1
    int sum = 0;
    for (int i = 0; i < nums1Size; i++) {
        sum += nums1[i];
    }
    
    // If the initial sum is already less than or equal to x, return 0
    if (sum <= x) {
        return 0;
    }
    
    // Step 2: Create an array of pairs (increment, index) and sort it by increment in descending order
    typedef struct {
        int increment;
        int index;
    } Pair;
    
    Pair* pairs = (Pair*)malloc(nums1Size * sizeof(Pair));
    for (int i = 0; i < nums1Size; i++) {
        pairs[i].increment = nums2[i];
        pairs[i].index = i;
    }
    
    // Sort pairs by increment in descending order
    for (int i = 0; i < nums1Size - 1; i++) {
        for (int j = 0; j < nums1Size - i - 1; j++) {
            if (pairs[j].increment < pairs[j + 1].increment) {
                Pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
    
    // Step 3: Increment time and apply operations until the sum is less than or equal to x
    int time = 0;
    for (int i = 0; i < nums1Size; i++) {
        time++;
        sum += pairs[i].increment; // Increment all elements by their respective increments
        
        // Apply the operation on the current index
        sum -= nums1[pairs[i].index]; // Subtract the original value at the index
        nums1[pairs[i].index] = 0; // Set it to zero
        
        if (sum <= x) {
            free(pairs);
            return time;
        }
    }
    
    free(pairs);
    return -1; // If we exhaust all operations and still can't reduce the sum to x or less      
}
