// Source: https://leetcode.com/problems/people-whose-list-of-favorite-companies-is-not-a-subset-of-another-list/   |   Difficulty: Medium
//
// Problem Description:
// Given the array favoriteCompanies where favoriteCompanies[i] is the list of favorites companies for the ith person (indexed from 0).
//
// Return the indices of people whose list of favorite companies is not a subset of any other list of favorites companies. You must return the indices in increasing order.
//
// Example:
// Input: favoriteCompanies = [["leetcode","google","facebook"],["google","microsoft"],["google","facebook"],["google"],["amazon"]]
// Output: [0,1,4] 
// Explanation: 
// Person with index=2 has favoriteCompanies[2]=["google","facebook"] which is a subset of favoriteCompanies[0]=["leetcode","google","facebook"] corresponding to the person with index 0. 
// Person with index=3 has favoriteCompanies[3]=["google"] which is a subset of favoriteCompanies[0]=["leetcode","google","facebook"] and favoriteCompanies[1]=["google","microsoft"]. 
// Other lists of favorite companies are not a subset of another list, therefore, the answer is [0,1,4].
//
// Constraints:
// 1 <= favoriteCompanies.length <= 100
// 	1 <= favoriteCompanies[i].length <= 500
// 	1 <= favoriteCompanies[i][j].length <= 20
// 	All strings in favoriteCompanies[i] are distinct.
// 	All lists of favorite companies are distinct, that is, If we sort alphabetically each list then favoriteCompanies[i] != favoriteCompanies[j].
// 	All strings consist of lowercase English letters only.
//

class Solution {
public:
    vector<int> peopleIndexes(vector<vector<string>>& favoriteCompanies) {
        int n = favoriteCompanies.size();
        vector<unordered_set<string>> favSets(n);
        for (int i = 0; i < n; ++i) {
            for (const string& company : favoriteCompanies[i]) {
                favSets[i].insert(company);
            }
        }

        vector<int> result;
        for (int i = 0; i < n; ++i) {
            bool isSubset = false;
            for (int j = 0; j < n; ++j) {
                if (i != j && favSets[i].size() <= favSets[j].size()) {
                    bool subsetCheck = true;
                    for (const string& company : favSets[i]) {
                        if (favSets[j].find(company) == favSets[j].end()) {
                            subsetCheck = false;
                            break;
                        }
                    }
                    if (subsetCheck) {
                        isSubset = true;
                        break;
                    }
                }
            }
            if (!isSubset) {
                result.push_back(i);
            }
        }

        return result;          
    }
};
