// Source: https://leetcode.com/problems/find-the-number-of-ways-to-place-people-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D array points of size n x 2 representing integer coordinates of some points on a 2D-plane, where points[i] = [xi, yi].
//
// We define the right direction as positive x-axis (increasing x-coordinate) and the left direction as negative x-axis (decreasing x-coordinate). Similarly, we define the up direction as positive y-axis (increasing y-coordinate) and the down direction as negative y-axis (decreasing y-coordinate)
//
// You have to place n people, including Alice and Bob, at these points such that there is exactly one person at every point. Alice wants to be alone with Bob, so Alice will build a rectangular fence with Alice's position as the upper left corner and Bob's position as the lower right corner of the fence (Note that the fence might not enclose any area, i.e. it can be a line). If any person other than Alice and Bob is either inside the fence or on the fence, Alice will be sad.
//
// Return the number of pairs of points where you can place Alice and Bob, such that Alice does not become sad on building the fence.
//
// Note that Alice can only build a fence with Alice's position as the upper left corner, and Bob's position as the lower right corner. For example, Alice cannot build either of the fences in the picture below with four corners (1, 1), (1, 3), (3, 1), and (3, 3), because:
//
//
// 	With Alice at (3, 3) and Bob at (1, 1), Alice's position is not the upper left corner and Bob's position is not the lower right corner of the fence.
// 	With Alice at (1, 3) and Bob at (1, 1) (as the rectangle shown in the image instead of a line), Bob's position is not the lower right corner of the fence.
//
// Example:
// Input: points = [[1,1],[2,2],[3,3]]
// Output: 0
// Explanation: There is no way to place Alice and Bob such that Alice can build a fence with Alice's position as the upper left corner and Bob's position as the lower right corner. Hence we return 0.
//
// Constraints:
// 2 <= n <= 1000
// 	points[i].length == 2
// 	-109 <= points[i][0], points[i][1] <= 109
// 	All points[i] are distinct.
//

class Solution {
public:
    int numberOfPairs(vector<vector<int>>& points) {
        int n = points.size();
        int result = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                
                int ax = points[i][0], ay = points[i][1];
                int bx = points[j][0], by = points[j][1];
                
                if (ax < bx && ay > by) {
                    bool sad = false;
                    for (int k = 0; k < n; k++) {
                        if (k == i || k == j) continue;
                        
                        int px = points[k][0], py = points[k][1];
                        
                        if (px >= ax && px <= bx && py <= ay && py >= by) {
                            sad = true;
                            break;
                        }
                    }
                    
                    if (!sad) {
                        result++;
                    }
                }
            }
        }
        
        return result;          
    }
};
