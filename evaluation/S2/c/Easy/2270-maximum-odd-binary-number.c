// Source: https://leetcode.com/problems/maximum-odd-binary-number/   |   Difficulty: Easy
//
// Problem Description:
// You are given a binary string s that contains at least one '1'.
//
// You have to rearrange the bits in such a way that the resulting binary number is the maximum odd binary number that can be created from this combination.
//
// Return a string representing the maximum odd binary number that can be created from the given combination.
//
// Note that the resulting string can have leading zeros.
//
// Example:
// Input: s = "010"
// Output: "001"
// Explanation: Because there is just one '1', it must be in the last position. So the answer is "001".
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists only of '0' and '1'.
// 	s contains at least one '1'.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - String Sorts (array, string, number, radix-sort, recursion, counting-sort)
//   • When to use: Use when sorting a large collection of strings or integers with a limited range of character/digit values. It is particularly efficient for fixed-length keys but can be adapted for variable lengths.
//   • Idea: Radix sort is a non-comparative integer sorting algorithm that sorts data with integer keys by grouping keys by individual digits or characters which share the same significant position and value. It typically achieves O(N*W) time complexity, where N is the number of items and W is the key length.
//   • Invariants: After each pass `d`, the elements are stably sorted according to their digits up to position `d`.; The counting sort subroutine correctly places elements into their sorted positions for the current digit, preserving relative order.
//   • Tips: LSD (Least Significant Digit) is simpler for fixed-length keys.; MSD (Most Significant Digit) is better for variable-length keys or when keys are very long.
//   • Pitfalls: Not efficient for small N or very large W due to constant factors.; Requires extra space for auxiliary array and counting array.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* maximumOddBinaryNumber(char* s) {
    int count0 = 0, count1 = 0;
    for (char* p = s; *p; p++) {
        if (*p == '0') {
            count0++;
        } else {
            count1++;
        }
    }

    // The maximum odd binary number will have all '1's followed by all '0's, with one '1' at the end to ensure it's odd.
    // So we need to place all '1's except one at the beginning, then all '0's, and finally one '1' at the end.
    char* result = (char*)malloc((count0 + count1 + 1) * sizeof(char)); // +1 for null terminator
    if (!result) {
        return NULL; // Handle memory allocation failure
    }

    int index = 0;
    for (int i = 0; i < count1 - 1; i++) { // Place all but one '1'
        result[index++] = '1';
    }
    for (int i = 0; i < count0; i++) { // Place all '0's
        result[index++] = '0';
    }
    result[index++] = '1'; // Place the last '1' to ensure it's odd
    result[index] = '\0'; // Null-terminate the string

    return result;      
}
