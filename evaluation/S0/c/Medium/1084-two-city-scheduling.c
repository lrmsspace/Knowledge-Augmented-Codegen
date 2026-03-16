// Source: https://leetcode.com/problems/two-city-scheduling/   |   Difficulty: Medium
//
// Problem Description:
// A company is planning to interview 2n people. Given the array costs where costs[i] = [aCosti, bCosti], the cost of flying the ith person to city a is aCosti, and the cost of flying the ith person to city b is bCosti.
//
// Return the minimum cost to fly every person to a city such that exactly n people arrive in each city.
//
// Example:
// Input: costs = [[10,20],[30,200],[400,50],[30,20]]
// Output: 110
// Explanation: 
// The first person goes to city A for a cost of 10.
// The second person goes to city A for a cost of 30.
// The third person goes to city B for a cost of 50.
// The fourth person goes to city B for a cost of 20.
//
// The total minimum cost is 10 + 30 + 50 + 20 = 110 to have half the people interviewing in each city.
//
// Constraints:
// 2 * n == costs.length
// 	2 <= costs.length <= 100
// 	costs.length is even.
// 	1 <= aCosti, bCosti <= 1000
//

int twoCitySchedCost(int** costs, int costsSize, int* costsColSize) {
    int n = costsSize / 2;
    int totalCost = 0;

    // Calculate the difference and store it along with the original costs
    int differences[costsSize][3]; // [index, costA, costB, difference]
    for (int i = 0; i < costsSize; i++) {
        differences[i][0] = i;
        differences[i][1] = costs[i][0];
        differences[i][2] = costs[i][1];
        differences[i][3] = costs[i][0] - costs[i][1];
    }

    // Sort based on the difference
    qsort(differences, costsSize, sizeof(differences[0]), [](const void* a, const void* b) {
        return (*(int(*)[4])a)[3] - (*(int(*)[4])b)[3];
    });

    // Assign first n to city A and last n to city B
    for (int i = 0; i < n; i++) {
        totalCost += differences[i][1]; // cost to city A
    }
    for (int i = n; i < costsSize; i++) {
        totalCost += differences[i][2]; // cost to city B
    }

    return totalCost;       
}
