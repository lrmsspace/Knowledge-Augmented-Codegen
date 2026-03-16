// Source: https://leetcode.com/problems/maximum-population-year/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 2D integer array logs where each logs[i] = [birthi, deathi] indicates the birth and death years of the ith person.
//
// The population of some year x is the number of people alive during that year. The ith person is counted in year x's population if x is in the inclusive range [birthi, deathi - 1]. Note that the person is not counted in the year that they die.
//
// Return the earliest year with the maximum population.
//
// Example:
// Input: logs = [[1993,1999],[2000,2010]]
// Output: 1993
// Explanation: The maximum population is 1, and 1993 is the earliest year with this population.
//
// Constraints:
// 1 <= logs.length <= 100
// 	1950 <= birthi < deathi <= 2050
//

/**
 * @param {number[][]} logs
 * @return {number}
 */
var maximumPopulation = function(logs) {
    const yearCounts = new Array(101).fill(0); // Years from 1950 to 2050

    for (const [birth, death] of logs) {
        for (let year = birth; year < death; year++) {
            yearCounts[year - 1950]++;
        }
    }
    let maxPopulation = 0;
    let earliestYear = 1950;
    for (let i = 0; i < yearCounts.length; i++) {
        if (yearCounts[i] > maxPopulation) {
            maxPopulation = yearCounts[i];
            earliestYear = 1950 + i;
        }
    }
    return earliestYear;
};