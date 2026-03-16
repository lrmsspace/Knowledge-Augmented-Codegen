// Source: https://leetcode.com/problems/naming-a-company/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of strings ideas that represents a list of names to be used in the process of naming a company. The process of naming a company is as follows:
//
//
// 	Choose 2 distinct names from ideas, call them ideaA and ideaB.
// 	Swap the first letters of ideaA and ideaB with each other.
// 	If both of the new names are not found in the original ideas, then the name ideaA ideaB (the concatenation of ideaA and ideaB, separated by a space) is a valid company name.
// 	Otherwise, it is not a valid name.
//
//
// Return the number of distinct valid names for the company.
//
// Example:
// Input: ideas = ["coffee","donuts","time","toffee"]
// Output: 6
// Explanation: The following selections are valid:
// - ("coffee", "donuts"): The company name created is "doffee conuts".
// - ("donuts", "coffee"): The company name created is "conuts doffee".
// - ("donuts", "time"): The company name created is "tonuts dime".
// - ("donuts", "toffee"): The company name created is "tonuts doffee".
// - ("time", "donuts"): The company name created is "dime tonuts".
// - ("toffee", "donuts"): The company name created is "doffee tonuts".
// Therefore, there are a total of 6 distinct company names.
//
// The following are some examples of invalid selections:
// - ("coffee", "time"): The name "toffee" formed after swapping already exists in the original array.
// - ("time", "toffee"): Both names are still the same after swapping and exist in the original array.
// - ("coffee", "toffee"): Both names formed after swapping already exist in the original array.
//
// Constraints:
// 2 <= ideas.length <= 5 * 104
// 	1 <= ideas[i].length <= 10
// 	ideas[i] consists of lowercase English letters.
// 	All the strings in ideas are unique.
//

/**
 * @param {string[]} ideas
 * @return {number}
 */
var distinctNames = function(ideas) {
    const suffixes = new Array(26).fill(0).map(() => new Set());
    for (const idea of ideas) {
        const index = idea.charCodeAt(0) - 'a'.charCodeAt(0);
        suffixes[index].add(idea.slice(1));
    }
    let result = 0;
    for (let i = 0; i < 26; i++) {
        for (let j = i + 1; j < 26; j++) {
            let commonCount = 0;
            for (const suffix of suffixes[i]) {
                if (suffixes[j].has(suffix)) {
                    commonCount++;
                }
            }
            const uniqueInI = suffixes[i].size - commonCount;
            const uniqueInJ = suffixes[j].size - commonCount;
            result += uniqueInI * uniqueInJ * 2; // Each pair can be swapped in two ways
        }
    }
    return result;
};
