// Source: https://leetcode.com/problems/sort-the-people/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of strings names, and an array heights that consists of distinct positive integers. Both arrays are of length n.
//
// For each index i, names[i] and heights[i] denote the name and height of the ith person.
//
// Return names sorted in descending order by the people's heights.
//
// Example:
// Input: names = ["Mary","John","Emma"], heights = [180,165,170]
// Output: ["Mary","Emma","John"]
// Explanation: Mary is the tallest, followed by Emma and John.
//
// Constraints:
// n == names.length == heights.length
// 	1 <= n <= 103
// 	1 <= names[i].length <= 20
// 	1 <= heights[i] <= 105
// 	names[i] consists of lower and upper case English letters.
// 	All the values of heights are distinct.
//

/**
 * @param {string[]} names
 * @param {number[]} heights
 * @return {string[]}
 */
var sortPeople = function(names, heights) {
    const people = names.map((name, index) => ({ name, height: heights[index] }));
    people.sort((a, b) => b.height - a.height);
    return people.map(person => person.name);   
};
