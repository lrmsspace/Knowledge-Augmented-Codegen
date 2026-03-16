// Source: https://leetcode.com/problems/exclusive-time-of-functions/   |   Difficulty: Medium
//
// Problem Description:
// On a single-threaded CPU, we execute a program containing n functions. Each function has a unique ID between 0 and n-1.
//
// Function calls are stored in a call stack: when a function call starts, its ID is pushed onto the stack, and when a function call ends, its ID is popped off the stack. The function whose ID is at the top of the stack is the current function being executed. Each time a function starts or ends, we write a log with the ID, whether it started or ended, and the timestamp.
//
// You are given a list logs, where logs[i] represents the ith log message formatted as a string "{function_id}:{"start" | "end"}:{timestamp}". For example, "0:start:3" means a function call with function ID 0 started at the beginning of timestamp 3, and "1:end:2" means a function call with function ID 1 ended at the end of timestamp 2. Note that a function can be called multiple times, possibly recursively.
//
// A function's exclusive time is the sum of execution times for all function calls in the program. For example, if a function is called twice, one call executing for 2 time units and another call executing for 1 time unit, the exclusive time is 2 + 1 = 3.
//
// Return the exclusive time of each function in an array, where the value at the ith index represents the exclusive time for the function with ID i.
//
// Example:
// Input: n = 2, logs = ["0:start:0","1:start:2","1:end:5","0:end:6"]
// Output: [3,4]
// Explanation:
// Function 0 starts at the beginning of time 0, then it executes 2 for units of time and reaches the end of time 1.
// Function 1 starts at the beginning of time 2, executes for 4 units of time, and ends at the end of time 5.
// Function 0 resumes execution at the beginning of time 6 and executes for 1 unit of time.
// So function 0 spends 2 + 1 = 3 units of total time executing, and function 1 spends 4 units of total time executing.
//
// Constraints:
// 1 <= n <= 100
// 	2 <= logs.length <= 500
// 	0 <= function_id < n
// 	0 <= timestamp <= 109
// 	No two start events will happen at the same timestamp.
// 	No two end events will happen at the same timestamp.
// 	Each function has an "end" log for each "start" log.
//
// Helpful references (internal KB):
// - Minimum stack / Minimum queue (queue, stack, simulation)
//   • When to use: Use when needing to efficiently query the minimum element of a stack or queue in O(1) average time. Also applicable for finding minimums in all fixed-length subarrays using a sliding window.
//   • Idea: This technique augments a stack or queue to support O(1) average time retrieval of its minimum element, typically by storing minimums alongside data or using auxiliary structures. It achieves amortized constant time for all operations.
//   • Invariants: For a minimum stack, the auxiliary minimum stack's top element is always the minimum of all elements currently in the main stack.; For a minimum queue implemented with two stacks, the output stack is only refilled from the input stack when the output stack becomes empty.
//   • Tips: For a minimum stack, use an auxiliary stack to store minimums encountered so far.; Only push to the auxiliary minimum stack if the new element is less than or equal to its current top.
//   • Pitfalls: Forgetting to pop from the auxiliary minimum stack when the main stack's top is removed.; Incorrectly handling the transfer logic between the two stacks for a minimum queue.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
//   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
//   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
//   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
//   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
// - Primality tests (number, enumeration, simulation)
//   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
//   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
//   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
//   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
//   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> result(n, 0);
        stack<int> callStack;
        int prevTime = 0;

        for (const string& log : logs) {
            size_t firstColon = log.find(':');
            size_t secondColon = log.find(':', firstColon + 1);

            int functionId = stoi(log.substr(0, firstColon));
            string type = log.substr(firstColon + 1, secondColon - firstColon - 1);
            int timestamp = stoi(log.substr(secondColon + 1));

            if (type == "start") {
                if (!callStack.empty()) {
                    result[callStack.top()] += timestamp - prevTime;
                }
                callStack.push(functionId);
                prevTime = timestamp;
            } else { // type == "end"
                result[callStack.top()] += timestamp - prevTime + 1;
                callStack.pop();
                prevTime = timestamp + 1;
            }
        }

        return result;          
    }
};
