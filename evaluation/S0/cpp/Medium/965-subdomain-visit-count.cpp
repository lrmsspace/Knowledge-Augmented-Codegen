// Source: https://leetcode.com/problems/subdomain-visit-count/   |   Difficulty: Medium
//
// Problem Description:
// A website domain "discuss.leetcode.com" consists of various subdomains. At the top level, we have "com", at the next level, we have "leetcode.com" and at the lowest level, "discuss.leetcode.com". When we visit a domain like "discuss.leetcode.com", we will also visit the parent domains "leetcode.com" and "com" implicitly.
//
// A count-paired domain is a domain that has one of the two formats "rep d1.d2.d3" or "rep d1.d2" where rep is the number of visits to the domain and d1.d2.d3 is the domain itself.
//
//
// 	For example, "9001 discuss.leetcode.com" is a count-paired domain that indicates that discuss.leetcode.com was visited 9001 times.
//
//
// Given an array of count-paired domains cpdomains, return an array of the count-paired domains of each subdomain in the input. You may return the answer in any order.
//
// Example:
// Input: cpdomains = ["9001 discuss.leetcode.com"]
// Output: ["9001 leetcode.com","9001 discuss.leetcode.com","9001 com"]
// Explanation: We only have one website domain: "discuss.leetcode.com".
// As discussed above, the subdomain "leetcode.com" and "com" will also be visited. So they will all be visited 9001 times.
//
// Constraints:
// 1 <= cpdomain.length <= 100
// 	1 <= cpdomain[i].length <= 100
// 	cpdomain[i] follows either the "repi d1i.d2i.d3i" format or the "repi d1i.d2i" format.
// 	repi is an integer in the range [1, 104].
// 	d1i, d2i, and d3i consist of lowercase English letters.
//

class Solution {
public:
    vector<string> subdomainVisits(vector<string>& cpdomains) {
        unordered_map<string, int> domainCount;

        for (const string& cpdomain : cpdomains) {
            size_t spacePos = cpdomain.find(' ');
            int count = stoi(cpdomain.substr(0, spacePos));
            string domain = cpdomain.substr(spacePos + 1);

            // Process all subdomains
            while (true) {
                domainCount[domain] += count;
                size_t dotPos = domain.find('.');
                if (dotPos == string::npos) {
                    break;
                }
                domain = domain.substr(dotPos + 1);
            }
        }

        vector<string> result;
        for (const auto& entry : domainCount) {
            result.push_back(to_string(entry.second) + " " + entry.first);
        }

        return result;          
    }
};
