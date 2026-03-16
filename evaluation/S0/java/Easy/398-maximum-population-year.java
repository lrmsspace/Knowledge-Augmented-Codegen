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

class Solution {
    public int maximumPopulation(int[][] logs) {
        int[] populationChanges = new int[101]; // From year 1950 to 2050

        for (int[] log : logs) {
            int birthYear = log[0];
            int deathYear = log[1];
            populationChanges[birthYear - 1950]++; // Person is born
            populationChanges[deathYear - 1950]--; // Person dies
        }

        int maxPopulation = 0;
        int currentPopulation = 0;
        int earliestYear = 1950;

        for (int year = 0; year <= 100; year++) {
            currentPopulation += populationChanges[year];
            if (currentPopulation > maxPopulation) {
                maxPopulation = currentPopulation;
                earliestYear = year + 1950;
            }
        }

        return earliestYear;            
    }
}
