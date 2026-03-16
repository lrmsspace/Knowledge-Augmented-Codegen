// Source: https://leetcode.com/problems/number-of-flowers-in-full-bloom/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array flowers, where flowers[i] = [starti, endi] means the ith flower will be in full bloom from starti to endi (inclusive). You are also given a 0-indexed integer array people of size n, where people[i] is the time that the ith person will arrive to see the flowers.
//
// Return an integer array answer of size n, where answer[i] is the number of flowers that are in full bloom when the ith person arrives.
//
// Example:
// Input: flowers = [[1,6],[3,7],[9,12],[4,13]], people = [2,3,7,11]
// Output: [1,2,2,2]
// Explanation: The figure above shows the times when the flowers are in full bloom and when the people arrive.
// For each person, we return the number of flowers in full bloom during their arrival.
//
// Constraints:
// 1 <= flowers.length <= 5 * 104
// 	flowers[i].length == 2
// 	1 <= starti <= endi <= 109
// 	1 <= people.length <= 5 * 104
// 	1 <= people[i] <= 109
//

/**
 * @param {number[][]} flowers
 * @param {number[]} people
 * @return {number[]}
 */
var fullBloomFlowers = function(flowers, people) {
    const events = [];
    for (const [start, end] of flowers) {
        events.push([start, 1]);
        events.push([end + 1, -1]);
    }
    events.sort((a, b) => a[0] - b[0]);
    const result = new Array(people.length);
    const peopleWithIndex = people.map((time, index) => [time, index]);
    peopleWithIndex.sort((a, b) => a[0] - b[0]);

    let bloomCount = 0;
    let eventIndex = 0;
    for (const [time, index] of peopleWithIndex) {
        while (eventIndex < events.length && events[eventIndex][0] <= time) {
            bloomCount += events[eventIndex][1];
            eventIndex++;
        }
        result[index] = bloomCount;
    }
    return result;
};
