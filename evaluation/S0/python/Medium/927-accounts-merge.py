# Source: https://leetcode.com/problems/accounts-merge/   |   Difficulty: Medium
#
# Problem Description:
# Given a list of accounts where each element accounts[i] is a list of strings, where the first element accounts[i][0] is a name, and the rest of the elements are emails representing emails of the account.
#
# Now, we would like to merge these accounts. Two accounts definitely belong to the same person if there is some common email to both accounts. Note that even if two accounts have the same name, they may belong to different people as people could have the same name. A person can have any number of accounts initially, but all of their accounts definitely have the same name.
#
# After merging the accounts, return the accounts in the following format: the first element of each account is the name, and the rest of the elements are emails in sorted order. The accounts themselves can be returned in any order.
#
# Example:
# Input: accounts = [["John","johnsmith@mail.com","john_newyork@mail.com"],["John","johnsmith@mail.com","john00@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
# Output: [["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
# Explanation:
# The first and second John's are the same person as they have the common email "johnsmith@mail.com".
# The third John and Mary are different people as none of their email addresses are used by other accounts.
# We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'], 
# ['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.
#
# Constraints:
# 1 <= accounts.length <= 1000
# 	2 <= accounts[i].length <= 10
# 	1 <= accounts[i][j].length <= 30
# 	accounts[i][0] consists of English letters.
# 	accounts[i][j] (for j > 0) is a valid email.
#

class Solution(object):
    def accountsMerge(self, accounts):
        """
        :type accounts: List[List[str]]
        :rtype: List[List[str]]
        """
        from collections import defaultdict

        email_to_name = {}
        graph = defaultdict(set)

        # Build the graph
        for account in accounts:
            name = account[0]
            first_email = account[1]
            for email in account[1:]:
                graph[first_email].add(email)
                graph[email].add(first_email)
                email_to_name[email] = name

        visited = set()
        merged_accounts = []

        def dfs(email, emails):
            visited.add(email)
            emails.append(email)
            for neighbor in graph[email]:
                if neighbor not in visited:
                    dfs(neighbor, emails)

        # Perform DFS to find connected components
        for email in email_to_name:
            if email not in visited:
                emails = []
                dfs(email, emails)
                merged_accounts.append([email_to_name[email]] + sorted(emails))

        return merged_accounts