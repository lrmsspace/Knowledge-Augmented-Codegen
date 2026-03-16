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
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool isValid(char* code) {
    int n = strlen(code);
    if (n == 0 || code[0] != '<' || code[n - 1] != '>') {
        return false;
    }

    char stack[100]; // Stack to hold tag names
    int top = -1; // Stack pointer

    for (int i = 0; i < n; ) {
        if (code[i] == '<') {
            if (i + 1 < n && code[i + 1] == '!') { // CDATA section
                if (i + 9 >= n || strncmp(code + i, "<![CDATA[", 9) != 0) {
                    return false; // Invalid CDATA start
                }
                i += 9; // Move past "<![CDATA["
                while (i + 2 >= n || strncmp(code + i, "]]>", 3) != 0) {
                    if (i >= n) {
                        return false; // Unmatched CDATA
                    }
                    i++;
                }
                i += 3; // Move past "]]>"
            } else if (i + 1 < n && code[i + 1] == '/') { // End tag
                int j = i + 2;
                while (j < n && code[j] != '>') {
                    j++;
                }
                if (j >= n || top < 0 || strncmp(stack[top], code + i + 2, j - i - 2) != 0) {
                    return false; // Unmatched end tag
                }
                top--; // Pop the stack
                i = j + 1; // Move past the end tag
            } else { // Start tag
                int j = i + 1;
                while (j < n && code[j] != '>') {
                    j++;
                }
                if (j >= n || j - i - 1 < 1 || j - i - 1 > 9) {
                    return false; // Invalid start tag length
                }
                for (int k = i + 1; k < j; k++) {
                    if (!isupper(code[k])) {
                        return false; // Invalid character in tag name
                    }
                }
                stack[++top][0] = '\0'; // Push the tag name onto the stack
                strncat(stack[top], code + i + 1, j - i - 1);
                i = j + 1; // Move past the start tag
            }
        } else { // Regular character
            if (top < 0) {
                return false; // Characters outside of any tag
            }
            i++;
        }
        
    }
    return top == -1; // Return true if all tags are properly closed
}
