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
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string, string> parent;
        unordered_map<string, string> emailToName;

        function<string(const string&)> find = [&](const string& email) {
            if (parent[email] != email) {
                parent[email] = find(parent[email]);
            }
            return parent[email];
        };

        auto unionEmails = [&](const string& email1, const string& email2) {
            string root1 = find(email1);
            string root2 = find(email2);
            if (root1 != root2) {
                parent[root2] = root1;
            }
        };

        for (const auto& account : accounts) {
            const string& name = account[0];
            for (int i = 1; i < account.size(); ++i) {
                const string& email = account[i];
                if (parent.find(email) == parent.end()) {
                    parent[email] = email;
                }
                emailToName[email] = name;
                unionEmails(account[1], email);
            }
        }

        unordered_map<string, set<string>> unions;
        for (const auto& [email, _] : parent) {
            string root = find(email);
            unions[root].insert(email);
        }

        vector<vector<string>> result;
        for (const auto& [root, emails] : unions) {
            vector<string> mergedAccount;
            mergedAccount.push_back(emailToName[root]);
            mergedAccount.insert(mergedAccount.end(), emails.begin(), emails.end());
            result.push_back(mergedAccount);
        }

        return result;          
    }
};
