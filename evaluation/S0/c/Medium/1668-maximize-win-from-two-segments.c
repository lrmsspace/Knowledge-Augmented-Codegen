// Source: https://leetcode.com/problems/maximize-win-from-two-segments/   |   Difficulty: Medium
//
// Problem Description:
// There are some prizes on the X-axis. You are given an integer array prizePositions that is sorted in non-decreasing order, where prizePositions[i] is the position of the ith prize. There could be different prizes at the same position on the line. You are also given an integer k.
//
// You are allowed to select two segments with integer endpoints. The length of each segment must be k. You will collect all prizes whose position falls within at least one of the two selected segments (including the endpoints of the segments). The two selected segments may intersect.
//
//
// 	For example if k = 2, you can choose segments [1, 3] and [2, 4], and you will win any prize i that satisfies 1 <= prizePositions[i] <= 3 or 2 <= prizePositions[i] <= 4.
//
//
// Return the maximum number of prizes you can win if you choose the two segments optimally.
//
// Example:
// Input: prizePositions = [1,1,2,2,3,3,5], k = 2
// Output: 7
// Explanation: In this example, you can win all 7 prizes by selecting two segments [1, 3] and [3, 5].
//
// Constraints:
// 1 <= prizePositions.length <= 105
// 	1 <= prizePositions[i] <= 109
// 	0 <= k <= 109 
// 	prizePositions is sorted in non-decreasing order.
//
//
//  
// .spoilerbutton {display:block; border:dashed; padding: 0px 0px; margin:10px 0px; font-size:150%; font-weight: bold; color:#000000; background-color:cyan; outline:0; 
// }
// .spoiler {overflow:hidden;}
// .spoiler > div {-webkit-transition: all 0s ease;-moz-transition: margin 0s ease;-o-transition: all 0s ease;transition: margin 0s ease;}
// .spoilerbutton[value="Show Message"] + .spoiler > div {margin-top:-500%;}
// .spoilerbutton[value="Hide Message"] + .spoiler {padding:5px;}
//

int maximizeWin(int* prizePositions, int prizePositionsSize, int k) {
    int left[prizePositionsSize];
    int right[prizePositionsSize];
    int l = 0, r = 0;
    int max_left = 0, max_right = 0;
    int result = 0;

    for (int i = 0; i < prizePositionsSize; i++) {
        while (prizePositions[i] - prizePositions[l] > k) {
            l++;
        }
        left[i] = i - l + 1;
        if (left[i] > max_left) {
            max_left = left[i];
        }
    }

    for (int i = prizePositionsSize - 1; i >= 0; i--) {
        while (prizePositions[r] - prizePositions[i] > k) {
            r++;
        }
        right[i] = r - i + 1;
        if (right[i] > max_right) {
            max_right = right[i];
        }
        r++;
    }

    result = max_left; // Case when both segments overlap completely

    for (int i = 0; i < prizePositionsSize - 1; i++) {
        int total = left[i] + right[i + 1];
        if (total > result) {
            result = total;
        }
    }

    return result;      
}
