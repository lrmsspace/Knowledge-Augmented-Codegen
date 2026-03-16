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

/**
 * @param {string} startGene
 * @param {string} endGene
 * @param {string[]} bank
 * @return {number}
 */
var minMutation = function(startGene, endGene, bank) {
    const geneSet = new Set(bank);
    if (!geneSet.has(endGene)) return -1;
    const chars = ['A', 'C', 'G', 'T'];
    const queue = [[startGene, 0]];
    const visited = new Set();
    visited.add(startGene);
    while (queue.length > 0) {
        const [currentGene, mutations] = queue.shift(); 
        if (currentGene === endGene) {
            return mutations;
        }
        for (let i = 0; i < currentGene.length; i++) {
            for (const char of chars) {
                if (char !== currentGene[i]) {
                    const newGene = currentGene.slice(0, i) + char + currentGene.slice(i + 1);
                    if (geneSet.has(newGene) && !visited.has(newGene)) {
                        visited.add(newGene);
                        queue.push([newGene, mutations + 1]);
                    }
                }
            }
        }
    }
    return -1;      
};