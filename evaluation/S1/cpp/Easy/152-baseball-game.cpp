// Source: https://leetcode.com/problems/baseball-game/   |   Difficulty: Easy
//
// Problem Description:
// You are keeping the scores for a baseball game with strange rules. At the beginning of the game, you start with an empty record.
//
// You are given a list of strings operations, where operations[i] is the ith operation you must apply to the record and is one of the following:
//
//
// 	An integer x.
//
// 	
// 		Record a new score of x.
// 	
// 	
// 	'+'.
// 	
// 		Record a new score that is the sum of the previous two scores.
// 	
// 	
// 	'D'.
// 	
// 		Record a new score that is the double of the previous score.
// 	
// 	
// 	'C'.
// 	
// 		Invalidate the previous score, removing it from the record.
// 	
// 	
//
//
// Return the sum of all the scores on the record after applying all the operations.
//
// The test cases are generated such that the answer and all intermediate calculations fit in a 32-bit integer and that all operations are valid.
//
// Example:
// Input: ops = ["5","2","C","D","+"]
// Output: 30
// Explanation:
// "5" - Add 5 to the record, record is now [5].
// "2" - Add 2 to the record, record is now [5, 2].
// "C" - Invalidate and remove the previous score, record is now [5].
// "D" - Add 2 * 5 = 10 to the record, record is now [5, 10].
// "+" - Add 5 + 10 = 15 to the record, record is now [5, 10, 15].
// The total sum is 5 + 10 + 15 = 30.
//
// Constraints:
// 1 <= operations.length <= 1000
// 	operations[i] is "C", "D", "+", or a string representing an integer in the range [-3 * 104, 3 * 104].
// 	For operation "+", there will always be at least two previous scores on the record.
// 	For operations "C" and "D", there will always be at least one previous score on the record.
//
// Helpful references (internal KB):
// - Minimum stack / Minimum queue (stack, simulation)
//   • When to use: When you need to perform standard stack operations (push, pop) and also query the minimum element currently in the stack, all in constant time.
//   • Idea: Augments a standard stack by storing each element along with the minimum value encountered up to that point in the stack. This allows O(1) retrieval of the current minimum, while push and pop operations also remain O(1).
//   • Invariants: The top element's second component (minimum_so_far) always represents the minimum value currently in the entire stack.; For any element (value, min_so_far) in the stack, min_so_far is the minimum of 'value' and all elements below it.
//   • Tips: Store elements as pairs: (actual_value, minimum_at_this_level).; When pushing, the new minimum_at_this_level is min(new_value, stack.top().second) if stack is not empty, else new_value.
//   • Pitfalls: Forgetting to handle the empty stack case when calculating the minimum for a new element.; Incorrectly assuming the minimum can be tracked with a single auxiliary variable without considering pops.
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: When needing to efficiently represent all substrings of a given string and perform various string operations like counting distinct substrings, finding occurrences, or checking for specific patterns. It provides a compact and powerful data structure for complex string problems.
//   • Idea: A Suffix Automaton is a minimal deterministic finite automaton that recognizes all suffixes of a given string. It compactly represents all substrings of the string, with each state corresponding to an endpos-equivalence class, and can be constructed in linear time O(N).
//   • Invariants: Every state corresponds to a unique endpos-equivalence class of substrings.; For any state, all substrings ending at its endpos set are represented by that state or its ancestors via suffix links.
//   • Tips: Focus on the endpos definition for state equivalence.; Understand the incremental construction process.
//   • Pitfalls: The construction algorithm is non-trivial and prone to off-by-one errors.; Misinterpreting the role of suffix links vs. transition links.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int calPoints(vector<string>& operations) {
        vector<int> record;
        for (const string& op : operations) {
            if (op == "C") {
                if (!record.empty()) {
                    record.pop_back();
                }
            } else if (op == "D") {
                if (!record.empty()) {
                    record.push_back(2 * record.back());
                }
            } else if (op == "+") {
                int size = record.size();
                if (size >= 2) {
                    record.push_back(record[size - 1] + record[size - 2]);
                }
            } else {
                // It's a number
                record.push_back(stoi(op));
            }
        }
        
        int total = 0;
        for (int score : record) {
            total += score;
        }
        return total;           
    }
};
