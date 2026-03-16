# Source: https://leetcode.com/problems/remove-comments/   |   Difficulty: Medium
#
# Problem Description:
# Given a C++ program, remove comments from it. The program source is an array of strings source where source[i] is the ith line of the source code. This represents the result of splitting the original source code string by the newline character '\n'.
#
# In C++, there are two types of comments, line comments, and block comments.
#
#
# 	The string "//" denotes a line comment, which represents that it and the rest of the characters to the right of it in the same line should be ignored.
# 	The string "/*" denotes a block comment, which represents that all characters until the next (non-overlapping) occurrence of "*/" should be ignored. (Here, occurrences happen in reading order: line by line from left to right.) To be clear, the string "/*/" does not yet end the block comment, as the ending would be overlapping the beginning.
#
#
# The first effective comment takes precedence over others.
#
#
# 	For example, if the string "//" occurs in a block comment, it is ignored.
# 	Similarly, if the string "/*" occurs in a line or block comment, it is also ignored.
#
#
# If a certain line of code is empty after removing comments, you must not output that line: each string in the answer list will be non-empty.
#
# There will be no control characters, single quote, or double quote characters.
#
#
# 	For example, source = "string s = "/* Not a comment. */";" will not be a test case.
#
#
# Also, nothing else such as defines or macros will interfere with the comments.
#
# It is guaranteed that every open block comment will eventually be closed, so "/*" outside of a line or block comment always starts a new comment.
#
# Finally, implicit newline characters can be deleted by block comments. Please see the examples below for details.
#
# After removing the comments from the source code, return the source code in the same format.
#
# Example:
# Input: source = ["/*Test program */", "int main()", "{ ", "  // variable declaration ", "int a, b, c;", "/* This is a test", "   multiline  ", "   comment for ", "   testing */", "a = b + c;", "}"]
# Output: ["int main()","{ ","  ","int a, b, c;","a = b + c;","}"]
# Explanation: The line by line code is visualized as below:
# /*Test program */
# int main()
# { 
#   // variable declaration 
# int a, b, c;
# /* This is a test
#    multiline  
#    comment for 
#    testing */
# a = b + c;
# }
# The string /* denotes a block comment, including line 1 and lines 6-9. The string // denotes line 4 as comments.
# The line by line output code is visualized as below:
# int main()
# { 
#   
# int a, b, c;
# a = b + c;
# }
#
# Constraints:
# 1 <= source.length <= 100
# 	0 <= source[i].length <= 80
# 	source[i] consists of printable ASCII characters.
# 	Every open block comment is eventually closed.
# 	There are no single-quote or double-quote in the input.
#

class Solution(object):
    def removeComments(self, source):
        """
        :type source: List[str]
        :rtype: List[str]
        """
        in_block = False
        new_source = []
        buffer = ""
        
        for line in source:
            i = 0
            if not in_block:
                buffer = ""
            while i < len(line):
                if not in_block and i + 1 < len(line) and line[i] == '/' and line[i + 1] == '*':
                    in_block = True
                    i += 1
                elif in_block and i + 1 < len(line) and line[i] == '*' and line[i + 1] == '/':
                    in_block = False
                    i += 1
                elif not in_block and i + 1 < len(line) and line[i] == '/' and line[i + 1] == '/':
                    break
                elif not in_block:
                    buffer += line[i]
                i += 1
            if not in_block and buffer:
                new_source.append(buffer)
        
        return new_source