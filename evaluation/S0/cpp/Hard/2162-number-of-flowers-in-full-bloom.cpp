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

class Solution {
public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {
        vector<pair<int, int>> events; // (time, type) type: 1=start, -1=end
        for (const auto& flower : flowers) {
            events.emplace_back(flower[0], 1);
            events.emplace_back(flower[1] + 1, -1); // end + 1 for inclusive range
        }
        
        for (int i = 0; i < people.size(); ++i) {
            events.emplace_back(people[i], 0); // 0 for query
        }
        
        sort(events.begin(), events.end());
        
        vector<int> result(people.size());
        int bloomCount = 0;
        
        for (const auto& event : events) {
            if (event.second == 1) {
                bloomCount++;
            } else if (event.second == -1) {
                bloomCount--;
            } else {
                // Query event
                int personIdx = lower_bound(people.begin(), people.end(), event.first) - people.begin();
                // There might be multiple people arriving at the same time
                while (personIdx < people.size() && people[personIdx] == event.first) {
                    result[personIdx] = bloomCount;
                    personIdx++;
                }
            }
        }
        
        return result;          
    }
};
