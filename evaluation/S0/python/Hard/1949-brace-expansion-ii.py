# Source: https://leetcode.com/problems/brace-expansion-ii/   |   Difficulty: Hard
#
# Problem Description:
# Under the grammar given below, strings can represent a set of lowercase words. Let R(expr) denote the set of words the expression represents.
#
# The grammar can best be understood through simple examples:
#
#
# 	Single letters represent a singleton set containing that word.
# 	
# 		R("a") = {"a"}
# 		R("w") = {"w"}
# 	
# 	
# 	When we take a comma-delimited list of two or more expressions, we take the union of possibilities.
# 	
# 		R("{a,b,c}") = {"a","b","c"}
# 		R("{{a,b},{b,c}}") = {"a","b","c"} (notice the final set only contains each word at most once)
# 	
# 	
# 	When we concatenate two expressions, we take the set of possible concatenations between two words where the first word comes from the first expression and the second word comes from the second expression.
# 	
# 		R("{a,b}{c,d}") = {"ac","ad","bc","bd"}
# 		R("a{b,c}{d,e}f{g,h}") = {"abdfg", "abdfh", "abefg", "abefh", "acdfg", "acdfh", "acefg", "acefh"}
# 	
# 	
#
#
# Formally, the three rules for our grammar:
#
#
# 	For every lowercase letter x, we have R(x) = {x}.
# 	For expressions e1, e2, ... , ek with k >= 2, we have R({e1, e2, ...}) = R(e1) ∪ R(e2) ∪ ...
# 	For expressions e1 and e2, we have R(e1 + e2) = {a + b for (a, b) in R(e1) × R(e2)}, where + denotes concatenation, and × denotes the cartesian product.
#
#
# Given an expression representing a set of words under the given grammar, return the sorted list of words that the expression represents.
#
# Example:
# Input: expression = "{a,b}{c,{d,e}}"
# Output: ["ac","ad","ae","bc","bd","be"]
#
# Constraints:
# 1 <= expression.length <= 60
# 	expression[i] consists of '{', '}', ','or lowercase English letters.
# 	The given expression represents a set of words based on the grammar given in the description.
#

class Solution(object):
    def braceExpansionII(self, expression):
        """
        :type expression: str
        :rtype: List[str]
        """
        def merge(set1, set2):
            res = set()
            for s1 in set1:
                for s2 in set2:
                    res.add(s1 + s2)
            return res

        stack = []
        curr = set()
        curr.add("")
        i = 0
        while i < len(expression):
            if expression[i] == '{':
                stack.append(curr)
                stack.append('{')
                curr = set()
                curr.add("")
                i += 1
            elif expression[i] == '}':
                temp = set()
                while stack and stack[-1] != '{':
                    prev = stack.pop()
                    temp = temp.union(prev)
                stack.pop()  # pop '{'
                prev = stack.pop()
                curr = merge(prev, curr)
                curr = curr.union(temp)
                i += 1
            elif expression[i] == ',':
                stack.append(curr)
                curr = set()
                curr.add("")
                i += 1
            else:
                j = i
                while j < len(expression) and expression[j].isalpha():
                    j += 1
                substr = expression[i:j]
                new_set = set()
                new_set.add(substr)
                curr = merge(curr, new_set)
                i = j

        while stack:
            prev = stack.pop()
            curr = merge(prev, curr)

        return sorted(list(curr))