// Source: https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// One way to serialize a binary tree is to use preorder traversal. When we encounter a non-null node, we record the node's value. If it is a null node, we record using a sentinel value such as '#'.
//
// For example, the above binary tree can be serialized to the string "9,3,4,#,#,1,#,#,2,#,6,#,#", where '#' represents a null node.
//
// Given a string of comma-separated values preorder, return true if it is a correct preorder traversal serialization of a binary tree.
//
// It is guaranteed that each comma-separated value in the string must be either an integer or a character '#' representing null pointer.
//
// You may assume that the input format is always valid.
//
//
// 	For example, it could never contain two consecutive commas, such as "1,,3".
//
//
// Note: You are not allowed to reconstruct the tree.
//
// Example:
// Input: preorder = "9,3,4,#,#,1,#,#,2,#,6,#,#"
// Output: true
//
// Constraints:
// 1 <= preorder.length <= 104
// 	preorder consist of integers in the range [0, 100] and '#' separated by commas ','.
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

bool isValidSerialization(char* preorder) {
    int slots = 1; // Start with one slot for the root node
    char* token = strtok(preorder, ",");
    
    while (token != NULL) {
        if (slots == 0) {
            return false; // No slots available but still have nodes to process
        }
        
        if (strcmp(token, "#") == 0) {
            // Null node consumes one slot
            slots--;
        } else {
            // Non-null node consumes one slot but creates two new slots
            slots++; // Net effect: consume one slot and create two new ones
        }
        
        token = strtok(NULL, ",");
    }
    
    return slots == 0; // All slots should be used up for a valid serialization     
}
