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
public:
    int maximumPopulation(vector<vector<int>>& logs) {
        vector<int> population(101, 0); // To store population changes from year 1950 to 2050

        // Update population changes based on birth and death years
        for (const auto& log : logs) {
            int birth = log[0];
            int death = log[1];
            population[birth - 1950]++;   // Increment population at birth year
            population[death - 1950]--;   // Decrement population at death year
        }

        int maxPopulation = 0;
        int currentPopulation = 0;
        int earliestYear = 1950;

        // Calculate the maximum population and the earliest year it occurs
        for (int year = 0; year <= 100; ++year) {
            currentPopulation += population[year];
            if (currentPopulation > maxPopulation) {
                maxPopulation = currentPopulation;
                earliestYear = year + 1950; // Convert index back to year
            }
        }

        return earliestYear;            
    }
};
