// Source: https://leetcode.com/problems/accounts-merge/   |   Difficulty: Medium
//
// Problem Description:
// Given a list of accounts where each element accounts[i] is a list of strings, where the first element accounts[i][0] is a name, and the rest of the elements are emails representing emails of the account.
//
// Now, we would like to merge these accounts. Two accounts definitely belong to the same person if there is some common email to both accounts. Note that even if two accounts have the same name, they may belong to different people as people could have the same name. A person can have any number of accounts initially, but all of their accounts definitely have the same name.
//
// After merging the accounts, return the accounts in the following format: the first element of each account is the name, and the rest of the elements are emails in sorted order. The accounts themselves can be returned in any order.
//
// Example:
// Input: accounts = [["John","johnsmith@mail.com","john_newyork@mail.com"],["John","johnsmith@mail.com","john00@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
// Output: [["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
// Explanation:
// The first and second John's are the same person as they have the common email "johnsmith@mail.com".
// The third John and Mary are different people as none of their email addresses are used by other accounts.
// We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'], 
// ['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.
//
// Constraints:
// 1 <= accounts.length <= 1000
// 	2 <= accounts[i].length <= 10
// 	1 <= accounts[i][j].length <= 30
// 	accounts[i][0] consists of English letters.
// 	accounts[i][j] (for j > 0) is a valid email.
//

class Solution {
    public List<List<String>> accountsMerge(List<List<String>> accounts) {
        Map<String, String> emailToName = new HashMap<>();
        Map<String, Set<String>> graph = new HashMap<>();

        // Build the graph
        for (List<String> account : accounts) {
            String name = account.get(0);
            for (int i = 1; i < account.size(); i++) {
                String email = account.get(i);
                emailToName.put(email, name);
                graph.putIfAbsent(email, new HashSet<>());
                if (i == 1) continue;
                String prevEmail = account.get(i - 1);
                graph.get(email).add(prevEmail);
                graph.get(prevEmail).add(email);
            }
        }

        Set<String> visited = new HashSet<>();
        List<List<String>> mergedAccounts = new ArrayList<>();

        // DFS to find connected components
        for (String email : graph.keySet()) {
            if (!visited.contains(email)) {
                List<String> emails = new ArrayList<>();
                dfs(email, graph, visited, emails);
                Collections.sort(emails);
                emails.add(0, emailToName.get(email));
                mergedAccounts.add(emails);
            }
        }

        return mergedAccounts;          
    }
}
