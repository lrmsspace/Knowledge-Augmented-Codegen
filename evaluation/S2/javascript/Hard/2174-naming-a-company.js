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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string[]} ideas
 * @return {number}
 */
var distinctNames = function(ideas) {
    const groups = new Array(26).fill(0).map(() => new Set());
    for (const idea of ideas) {
        const index = idea.charCodeAt(0) - 'a'.charCodeAt(0);
        groups[index].add(idea.substring(1));
    }   
    let count = 0;
    for (let i = 0; i < 26; i++) {
        for (let j = 0; j < 26; j++) {
            if (i === j) continue;
            let common = 0;
            for (const suffix of groups[i]) {
                if (groups[j].has(suffix)) common++;
            }
            count += (groups[i].size - common) * (groups[j].size - common);
        }
    }
    return count;
};
