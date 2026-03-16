// Source: https://leetcode.com/problems/video-stitching/   |   Difficulty: Medium
//
// Problem Description:
// You are given a series of video clips from a sporting event that lasted time seconds. These video clips can be overlapping with each other and have varying lengths.
//
// Each video clip is described by an array clips where clips[i] = [starti, endi] indicates that the ith clip started at starti and ended at endi.
//
// We can cut these clips into segments freely.
//
//
// 	For example, a clip [0, 7] can be cut into segments [0, 1] + [1, 3] + [3, 7].
//
//
// Return the minimum number of clips needed so that we can cut the clips into segments that cover the entire sporting event [0, time]. If the task is impossible, return -1.
//
// Example:
// Input: clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], time = 10
// Output: 3
// Explanation: We take the clips [0,2], [8,10], [1,9]; a total of 3 clips.
// Then, we can reconstruct the sporting event as follows:
// We cut [1,9] into segments [1,2] + [2,8] + [8,9].
// Now we have segments [0,2] + [2,8] + [8,10] which cover the sporting event [0, 10].
//
// Constraints:
// 1 <= clips.length <= 100
// 	0 <= starti <= endi <= 100
// 	1 <= time <= 100
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int time) {
        // Sort clips by start time
        sort(clips.begin(), clips.end());

        int count = 0; // Number of clips used
        int current_end = 0; // Current end of coverage
        int next_end = 0; // Next end of coverage

        for (const auto& clip : clips) {
            if (clip[0] > current_end) {
                // If the next clip starts after the current coverage, we need to use a new clip
                if (next_end <= current_end) {
                    return -1; // Cannot cover the event
                }
                current_end = next_end;
                count++;
            }
            next_end = max(next_end, clip[1]);
            if (current_end >= time) {
                return count; // Already covered the event
            }
        }

        return current_end >= time ? count : -1; // Check if we covered the event at the end            
    }
};
