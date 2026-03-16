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
// - Expression parsing (stack, simulation)
//   • When to use: This algorithm is used to evaluate expressions given in Reverse Polish Notation (postfix notation) to compute their final numerical value.
//   • Idea: This algorithm evaluates an expression in Reverse Polish Notation by processing elements sequentially. Numbers are pushed onto a stack, and operators pop two operands, compute, and push the result.
//   • Invariants: The stack always contains only numbers (operands or intermediate results).; For a valid RPN expression, the stack will have at least two elements when an operator is processed.
//   • Tips: Process the RPN expression from left to right, token by token.; Push numerical operands directly onto the stack.
//   • Pitfalls: Attempting to pop from an empty stack when an operator is encountered, indicating an invalid RPN expression.; Incorrect order of operands for non-commutative operations like subtraction or division.
// - Linked-list implementations of collections (linked-list, stack, simulation)
//   • When to use: Use when a Last-In, First-Out (LIFO) data structure is required, and dynamic size with efficient O(1) push and pop operations is crucial, especially without a fixed capacity.
//   • Idea: This describes implementing a stack using a singly linked list, where elements are added and removed from the head of the list. Both push and pop operations achieve O(1) time complexity.
//   • Invariants: The 'first' pointer always points to the top element of the stack, or is null if the stack is empty.; Each node's 'next' pointer correctly links to the subsequent element in the stack, maintaining the LIFO order.
//   • Tips: Maintain a 'first' pointer to the head of the linked list, representing the stack's top.; Push operation involves creating a new node, linking it to the current 'first', then updating 'first'.
//   • Pitfalls: Forgetting to handle the empty stack case for pop, leading to `NoSuchElementException`.; Incorrectly updating the 'first' pointer during push or pop, which can break the list structure.
// - Deleting from a data structure in_log_n (ds, segment-tree, dfs, recursion)
//   • When to use: Use when processing a sequence of additions, deletions, and queries offline, where elements have specific time intervals of existence. It efficiently handles dynamic data structure operations by leveraging a segment tree over time.
//   • Idea: This technique uses a segment tree over the timeline of queries to manage elements with varying lifespans. Queries are processed offline via DFS, adding elements upon entering a node and undoing additions upon exiting, achieving O(T(n) log n) deletion complexity.
//   • Invariants: When entering a segment tree node, all elements associated with that node's time range are added to the active data structure.; When exiting a segment tree node, all elements added upon entry are removed, restoring the data structure to its state before entering.
//   • Tips: Ensure the base data structure supports efficient addition and undo operations.; Carefully manage element additions and removals during DFS traversal.
//   • Pitfalls: Forgetting to undo changes when backtracking from a segment tree node.; Incorrectly mapping element lifespans to segment tree nodes.
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
        vector<int> res(n, 0);
        stack<pair<int, int>> st; // {function_id, start_time}

        for (const auto& log : logs) {
            auto pos1 = log.find(':');
            auto pos2 = log.rfind(':');
            int id = stoi(log.substr(0, pos1));
            string type = log.substr(pos1 + 1, pos2 - pos1 - 1);
            int time = stoi(log.substr(pos2 + 1));

            if (type == "start") {
                if (!st.empty()) {
                    res[st.top().first] += time - st.top().second; // Update the exclusive time of the current function
                }
                st.push({id, time}); // Start a new function
            } else { // type == "end"
                auto [func_id, start_time] = st.top();
                st.pop();
                res[func_id] += time - start_time + 1; // Update the exclusive time of the ended function
                if (!st.empty()) {
                    st.top().second = time + 1; // Update the start time for the next function on the stack
                }
            }
        }

        return res;         
    }
};
