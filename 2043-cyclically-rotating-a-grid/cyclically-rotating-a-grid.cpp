#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int num_layers = min(m, n) / 2;
        
        for (int layer = 0; layer < num_layers; ++layer) {
            int top = layer, left = layer;
            int bottom = m - 1 - layer, right = n - 1 - layer;
            
            vector<int> elements;
            
            // 1. Collect elements of the current layer in clockwise order
            // Top row (left to right)
            for (int j = left; j <= right; ++j) {
                elements.push_back(grid[top][j]);
            }
            // Right column (top + 1 to bottom)
            for (int i = top + 1; i <= bottom; ++i) {
                elements.push_back(grid[i][right]);
            }
            // Bottom row (right - 1 down to left)
            for (int j = right - 1; j >= left; --j) {
                elements.push_back(grid[bottom][j]);
            }
            // Left column (bottom - 1 down to top + 1)
            for (int i = bottom - 1; i > top; --i) {
                elements.push_back(grid[i][left]);
            }
            
            // 2. Handle rotation efficiently using modulo
            int L = elements.size();
            int net_rotation = k % L;
            
            // 3. Put the rotated elements back into the grid
            // Moving net_rotation elements forward simulates the counter-clockwise shift
            int idx = net_rotation; 
            
            // Top row
            for (int j = left; j <= right; ++j) {
                grid[top][j] = elements[idx];
                idx = (idx + 1) % L;
            }
            // Right column
            for (int i = top + 1; i <= bottom; ++i) {
                grid[i][right] = elements[idx];
                idx = (idx + 1) % L;
            }
            // Bottom row
            for (int j = right - 1; j >= left; --j) {
                grid[bottom][j] = elements[idx];
                idx = (idx + 1) % L;
            }
            // Left column
            for (int i = bottom - 1; i > top; --i) {
                grid[i][left] = elements[idx];
                idx = (idx + 1) % L;
            }
        }
        
        return grid;
    }
};
