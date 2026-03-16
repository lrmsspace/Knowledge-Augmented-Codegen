// Source: https://leetcode.com/problems/delete-duplicate-folders-in-system/   |   Difficulty: Hard
//
// Problem Description:
// Due to a bug, there are many duplicate folders in a file system. You are given a 2D array paths, where paths[i] is an array representing an absolute path to the ith folder in the file system.
//
//
// 	For example, ["one", "two", "three"] represents the path "/one/two/three".
//
//
// Two folders (not necessarily on the same level) are identical if they contain the same non-empty set of identical subfolders and underlying subfolder structure. The folders do not need to be at the root level to be identical. If two or more folders are identical, then mark the folders as well as all their subfolders.
//
//
// 	For example, folders "/a" and "/b" in the file structure below are identical. They (as well as their subfolders) should all be marked:
//
// 	
// 		/a
// 		/a/x
// 		/a/x/y
// 		/a/z
// 		/b
// 		/b/x
// 		/b/x/y
// 		/b/z
// 	
// 	
// 	However, if the file structure also included the path "/b/w", then the folders "/a" and "/b" would not be identical. Note that "/a/x" and "/b/x" would still be considered identical even with the added folder.
//
//
// Once all the identical folders and their subfolders have been marked, the file system will delete all of them. The file system only runs the deletion once, so any folders that become identical after the initial deletion are not deleted.
//
// Return the 2D array ans containing the paths of the remaining folders after deleting all the marked folders. The paths may be returned in any order.
//
// Example:
// Input: paths = [["a"],["c"],["d"],["a","b"],["c","b"],["d","a"]]
// Output: [["d"],["d","a"]]
// Explanation: The file structure is as shown.
// Folders "/a" and "/c" (and their subfolders) are marked for deletion because they both contain an empty
// folder named "b".
//
// Constraints:
// 1 <= paths.length <= 2 * 104
// 	1 <= paths[i].length <= 500
// 	1 <= paths[i][j].length <= 10
// 	1 <= sum(paths[i][j].length) <= 2 * 105
// 	path[i][j] consists of lowercase English letters.
// 	No two paths lead to the same folder.
// 	For any folder not at the root level, its parent folder will also be in the input.
//

class Solution {
public:
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {
        struct Node {
            unordered_map<string, Node*> children;
            string serial;
            bool toDelete = false;
        };
        
        Node* root = new Node();
        
        // Build the folder tree
        for (const auto& path : paths) {
            Node* curr = root;
            for (const auto& folder : path) {
                if (!curr->children.count(folder)) {
                    curr->children[folder] = new Node();
                }
                curr = curr->children[folder];
            }
        }
        
        unordered_map<string, vector<Node*>> serialMap;
        
        // Serialize the tree and mark duplicates
        function<string(Node*)> serialize = [&](Node* node) {
            if (node->children.empty()) return "";
            
            vector<string> parts;
            for (auto& [name, child] : node->children) {
                parts.push_back(name + "(" + serialize(child) + ")");
            }
            sort(parts.begin(), parts.end());
            
            string serial = "";
            for (const auto& part : parts) {
                serial += part;
            }
            node->serial = serial;
            serialMap[serial].push_back(node);
            return serial;
        };
        
        serialize(root);
        
        // Mark nodes to delete
        for (const auto& [serial, nodes] : serialMap) {
            if (nodes.size() > 1) {
                for (auto node : nodes) {
                    node->toDelete = true;
                }
            }
        }
        
        vector<vector<string>> result;
        
        // DFS to collect remaining paths
        function<void(Node*, vector<string>&)> dfs = [&](Node* node, vector<string>& path) {
            for (auto& [name, child] : node->children) {
                if (!child->toDelete) {
                    path.push_back(name);
                    result.push_back(path);
                    dfs(child, path);
                    path.pop_back();
                }
            }
        };
        
        vector<string> currentPath;
        dfs(root, currentPath);
        
        return result;          
    }
};
