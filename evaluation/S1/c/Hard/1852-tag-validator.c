// Source: https://leetcode.com/problems/tag-validator/   |   Difficulty: Hard
//
// Problem Description:
// Given a string representing a code snippet, implement a tag validator to parse the code and return whether it is valid.
//
// A code snippet is valid if all the following rules hold:
//
//
// 	The code must be wrapped in a valid closed tag. Otherwise, the code is invalid.
// 	A closed tag (not necessarily valid) has exactly the following format : <TAG_NAME>TAG_CONTENT</TAG_NAME>. Among them, <TAG_NAME> is the start tag, and </TAG_NAME> is the end tag. The TAG_NAME in start and end tags should be the same. A closed tag is valid if and only if the TAG_NAME and TAG_CONTENT are valid.
// 	A valid TAG_NAME only contain upper-case letters, and has length in range [1,9]. Otherwise, the TAG_NAME is invalid.
// 	A valid TAG_CONTENT may contain other valid closed tags, cdata and any characters (see note1) EXCEPT unmatched <, unmatched start and end tag, and unmatched or closed tags with invalid TAG_NAME. Otherwise, the TAG_CONTENT is invalid.
// 	A start tag is unmatched if no end tag exists with the same TAG_NAME, and vice versa. However, you also need to consider the issue of unbalanced when tags are nested.
// 	A < is unmatched if you cannot find a subsequent >. And when you find a < or </, all the subsequent characters until the next > should be parsed as TAG_NAME (not necessarily valid).
// 	The cdata has the following format : <![CDATA[CDATA_CONTENT]]>. The range of CDATA_CONTENT is defined as the characters between <![CDATA[ and the first subsequent ]]>.
// 	CDATA_CONTENT may contain any characters. The function of cdata is to forbid the validator to parse CDATA_CONTENT, so even it has some characters that can be parsed as tag (no matter valid or invalid), you should treat it as regular characters.
//
// Example:
// Input: code = "<DIV>This is the first line <![CDATA[<div>]]></DIV>"
// Output: true
// Explanation: 
// The code is wrapped in a closed tag : <DIV> and </DIV>. 
// The TAG_NAME is valid, the TAG_CONTENT consists of some characters and cdata. 
// Although CDATA_CONTENT has an unmatched start tag with invalid TAG_NAME, it should be considered as plain text, not parsed as a tag.
// So TAG_CONTENT is valid, and then the code is valid. Thus return true.
//
// Constraints:
// 1 <= code.length <= 500
// 	code consists of English letters, digits, '<', '>', '/', '!', '[', ']', '.', and ' '.
//
// Helpful references (internal KB):
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use when you need to efficiently represent all distinct substrings of a string, or perform various string operations like counting unique substrings, finding occurrences, or string matching in an online fashion.
//   • Idea: A suffix automaton is a powerful data structure that represents all distinct substrings of a given string in a compact form, typically as a Directed Acyclic Word Graph (DAWG). It can be constructed in linear time O(N) and space O(N) for a string of length N.
//   • Invariants: Each state in the automaton represents a set of substrings that share the same end-positions in the original string.; For any state `v`, `len(v)` is the length of the longest string represented by `v`.
//   • Tips: Understand the properties of `len` (length of the longest string in a state) and `link` (suffix link to the longest proper suffix).; The construction is online, processing characters one by one from left to right.
//   • Pitfalls: Incorrectly handling the `link` updates, especially when cloning states during construction.; Forgetting to update the `last` pointer after each character addition step.
// - Balanced bracket sequences (number, counting)
//   • When to use: Use this when verifying if a sequence of delimiters is correctly nested and balanced. It is also applicable for counting or generating all possible valid sequences of a given length.
//   • Idea: This algorithm involves checking if a sequence of opening and closing delimiters is properly matched and nested, or enumerating such sequences. Validation typically uses a stack in O(N) time, while generation often involves backtracking with O(Catalan(N)) complexity.
//   • Invariants: The stack contains only opening delimiters that are yet to be matched.; The balance counter (open - close) is never negative at any point during traversal.
//   • Tips: Use a stack to track unmatched opening delimiters for validation.; Maintain a balance counter (increment for open, decrement for close) for a simpler check.
//   • Pitfalls: Forgetting to check if the stack is empty after processing the entire sequence.; Allowing a closing delimiter when no matching opening delimiter is available (empty stack or mismatch).
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool isValid(char* code) {
    int n = strlen(code);
    int i = 0;
    char stack[100];
    int top = -1;

    while (i < n) {
        if (code[i] == '<') {
            if (i + 1 < n && code[i + 1] == '/') {
                // End tag
                int j = i + 2;
                while (j < n && code[j] != '>') j++;
                if (j == n || top == -1) return false;
                int len = j - (i + 2);
                if (len < 1 || len > 9) return false;
                if (strncmp(stack[top], code + i + 2, len) != 0 || stack[top][len] != '\0') return false;
                top--;
                i = j + 1;
            } else if (i + 8 < n && strncmp(code + i, "<![CDATA[", 9) == 0) {
                // CDATA
                int j = i + 9;
                while (j + 2 < n && !(code[j] == ']' && code[j + 1] == ']' && code[j + 2] == '>')) j++;
                if (j + 2 >= n) return false;
                i = j + 3;
            } else {
                // Start tag
                int j = i + 1;
                while (j < n && code[j] != '>') j++;
                if (j == n) return false;
                int len = j - (i + 1);
                if (len < 1 || len > 9) return false;
                for (int k = i + 1; k < j; k++) {
                    if (code[k] < 'A' || code[k] > 'Z') return false;
                }
                stack[++top][0] = '\0';
                strncat(stack[top], code + i + 1, len);
                stack[top][len] = '\0';
                i = j + 1;
            }
        } else {
            if (top == -1) return false;
            i++;
        }
    }
    return top == -1;       
}
