// Source: https://leetcode.com/problems/minimum-genetic-mutation/   |   Difficulty: Medium
//
// Problem Description:
// A gene string can be represented by an 8-character long string, with choices from 'A', 'C', 'G', and 'T'.
//
// Suppose we need to investigate a mutation from a gene string startGene to a gene string endGene where one mutation is defined as one single character changed in the gene string.
//
//
// 	For example, "AACCGGTT" --> "AACCGGTA" is one mutation.
//
//
// There is also a gene bank bank that records all the valid gene mutations. A gene must be in bank to make it a valid gene string.
//
// Given the two gene strings startGene and endGene and the gene bank bank, return the minimum number of mutations needed to mutate from startGene to endGene. If there is no such a mutation, return -1.
//
// Note that the starting point is assumed to be valid, so it might not be included in the bank.
//
// Example:
// Input: startGene = "AACCGGTT", endGene = "AACCGGTA", bank = ["AACCGGTA"]
// Output: 1
//
// Constraints:
// 0 <= bank.length <= 10
// 	startGene.length == endGene.length == bank[i].length == 8
// 	startGene, endGene, and bank[i] consist of only the characters ['A', 'C', 'G', 'T'].
//

class Solution {
public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        unordered_set<string> bankSet(bank.begin(), bank.end());
        if (bankSet.find(endGene) == bankSet.end()) {
            return -1;
        }

        vector<char> genes = {'A', 'C', 'G', 'T'};
        queue<pair<string, int>> q;
        q.push({startGene, 0});
        unordered_set<string> visited;
        visited.insert(startGene);

        while (!q.empty()) {
            auto [currentGene, mutations] = q.front();
            q.pop();

            if (currentGene == endGene) {
                return mutations;
            }

            for (int i = 0; i < currentGene.size(); ++i) {
                char originalChar = currentGene[i];
                for (char gene : genes) {
                    if (gene == originalChar) continue;

                    currentGene[i] = gene;
                    if (bankSet.find(currentGene) != bankSet.end() &&
                        visited.find(currentGene) == visited.end()) {
                        visited.insert(currentGene);
                        q.push({currentGene, mutations + 1});
                    }
                }
                currentGene[i] = originalChar; // revert the change
            }
        }

        return -1;          
    }
};
