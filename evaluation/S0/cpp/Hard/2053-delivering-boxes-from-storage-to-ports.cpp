// Source: https://leetcode.com/problems/delivering-boxes-from-storage-to-ports/   |   Difficulty: Hard
//
// Problem Description:
// You have the task of delivering some boxes from storage to their ports using only one ship. However, this ship has a limit on the number of boxes and the total weight that it can carry.
//
// You are given an array boxes, where boxes[i] = [ports​​i​, weighti], and three integers portsCount, maxBoxes, and maxWeight.
//
//
// 	ports​​i is the port where you need to deliver the ith box and weightsi is the weight of the ith box.
// 	portsCount is the number of ports.
// 	maxBoxes and maxWeight are the respective box and weight limits of the ship.
//
//
// The boxes need to be delivered in the order they are given. The ship will follow these steps:
//
//
// 	The ship will take some number of boxes from the boxes queue, not violating the maxBoxes and maxWeight constraints.
// 	For each loaded box in order, the ship will make a trip to the port the box needs to be delivered to and deliver it. If the ship is already at the correct port, no trip is needed, and the box can immediately be delivered.
// 	The ship then makes a return trip to storage to take more boxes from the queue.
//
//
// The ship must end at storage after all the boxes have been delivered.
//
// Return the minimum number of trips the ship needs to make to deliver all boxes to their respective ports.
//
// Example:
// Input: boxes = [[1,1],[2,1],[1,1]], portsCount = 2, maxBoxes = 3, maxWeight = 3
// Output: 4
// Explanation: The optimal strategy is as follows: 
// - The ship takes all the boxes in the queue, goes to port 1, then port 2, then port 1 again, then returns to storage. 4 trips.
// So the total number of trips is 4.
// Note that the first and third boxes cannot be delivered together because the boxes need to be delivered in order (i.e. the second box needs to be delivered at port 2 before the third box).
//
// Constraints:
// 1 <= boxes.length <= 105
// 	1 <= portsCount, maxBoxes, maxWeight <= 105
// 	1 <= ports​​i <= portsCount
// 	1 <= weightsi <= maxWeight
//

class Solution {
public:
    int boxDelivering(vector<vector<int>>& boxes, int portsCount, int maxBoxes, int maxWeight) {
        int n = boxes.size();
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        
        int left = 0;
        int currWeight = 0;
        int trips = 0;
        
        for (int right = 0; right < n; ++right) {
            currWeight += boxes[right][1];
            if (right == 0 || boxes[right][0] != boxes[right - 1][0]) {
                trips++;
            }
            
            while (right - left + 1 > maxBoxes || currWeight > maxWeight) {
                currWeight -= boxes[left][1];
                if (boxes[left][0] != boxes[left + 1][0]) {
                    trips--;
                }
                left++;
            }
            
            dp[right + 1] = dp[left] + trips + 2; // +2 for return to storage
        }
        
        return dp[n];           
    }
};
