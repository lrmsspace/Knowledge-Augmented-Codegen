// Source: https://leetcode.com/problems/maximum-profit-in-job-scheduling/   |   Difficulty: Hard
//
// Problem Description:
// We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i], obtaining a profit of profit[i].
//
// You're given the startTime, endTime and profit arrays, return the maximum profit you can take such that there are no two jobs in the subset with overlapping time range.
//
// If you choose a job that ends at time X you will be able to start another job that starts at time X.
//
// Example:
// Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
// Output: 120
// Explanation: The subset chosen is the first and fourth job. 
// Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.
//
// Constraints:
// 1 <= startTime.length == endTime.length == profit.length <= 5 * 104
// 	1 <= startTime[i] < endTime[i] <= 109
// 	1 <= profit[i] <= 104
//
// Helpful references (internal KB):
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this algorithm to find the maximum length of a subsequence where elements are strictly increasing. It is particularly efficient when optimizing the O(N^2) dynamic programming solution to O(N log N) using binary search.
//   • Idea: This algorithm determines the longest subsequence of a given sequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search.
//   • Invariants: The 'tails' array always stores the smallest ending element for increasing subsequences of various lengths.; The 'tails' array is always sorted in strictly increasing order.
//   • Tips: The O(N log N) approach maintains an array 'tails' where 'tails[i]' is the smallest ending element of an increasing subsequence of length 'i+1'.; Utilize binary search (e.g., `std::lower_bound`) to find the correct position for the current element in the 'tails' array.
//   • Pitfalls: Confusing a subsequence with a contiguous subarray, which is a common mistake.; Incorrectly updating the 'tails' array, leading to non-increasing subsequences or incorrect lengths.
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int jobScheduling(int* startTime, int startTimeSize, int* endTime, int endTimeSize, int* profit, int profitSize) {
    typedef struct {
        int start;
        int end;
        int profit;
    } Job;

    int cmpJob(const void *a, const void *b) {
        Job *jobA = (Job*)a;
        Job *jobB = (Job*)b;
        return jobA->end - jobB->end;
    }

    Job *jobs = (Job*)malloc(startTimeSize * sizeof(Job));
    for (int i = 0; i < startTimeSize; i++) {
        jobs[i].start = startTime[i];
        jobs[i].end = endTime[i];
        jobs[i].profit = profit[i];
    }

    qsort(jobs, startTimeSize, sizeof(Job), cmpJob);

    int *dp = (int*)calloc(startTimeSize + 1, sizeof(int));
    for (int i = 1; i <= startTimeSize; i++) {
        dp[i] = dp[i - 1];
        int l = 0, r = i - 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (jobs[mid].end <= jobs[i - 1].start) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        dp[i] = dp[i] > dp[l] + jobs[i - 1].profit ? dp[i] : dp[l] + jobs[i - 1].profit;
    }

    int result = dp[startTimeSize];
    free(jobs);
    free(dp);
    return result;      
}
