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

int maximumPopulation(int** logs, int logsSize, int* logsColSize) {
    int yearCount[101] = {0}; // Array to hold population counts for years 1950 to 2050

    // Count the population for each year based on birth and death years
    for (int i = 0; i < logsSize; i++) {
        int birthYear = logs[i][0];
        int deathYear = logs[i][1];
        for (int year = birthYear; year < deathYear; year++) {
            yearCount[year - 1950]++;
        }
    }

    // Find the year with the maximum population
    int maxPopulation = 0;
    int earliestYear = 1950;
    for (int year = 0; year <= 100; year++) {
        if (yearCount[year] > maxPopulation) {
            maxPopulation = yearCount[year];
            earliestYear = year + 1950;
        }
    }

    return earliestYear;        
}
