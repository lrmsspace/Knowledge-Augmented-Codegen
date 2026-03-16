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

class Solution {
    public boolean isValid(String code) {
        Deque<String> stack = new ArrayDeque<>();
        int i = 0;
        int n = code.length();

        while (i < n) {
            if (code.startsWith("<![CDATA[", i)) {
                int j = code.indexOf("]]>", i + 9);
                if (j < 0) return false;
                i = j + 3;
            } else if (code.startsWith("</", i)) {
                int j = code.indexOf(">", i + 2);
                if (j < 0) return false;
                String tagName = code.substring(i + 2, j);
                if (stack.isEmpty() || !stack.peek().equals(tagName)) return false;
                stack.pop();
                i = j + 1;
                if (stack.isEmpty() && i < n) return false;
            } else if (code.startsWith("<", i)) {
                int j = code.indexOf(">", i + 1);
                if (j < 0) return false;
                String tagName = code.substring(i + 1, j);
                if (!isValidTagName(tagName)) return false;
                stack.push(tagName);
                i = j + 1;
            } else {
                i++;
            }
        }

        return stack.isEmpty();         
    }
}
