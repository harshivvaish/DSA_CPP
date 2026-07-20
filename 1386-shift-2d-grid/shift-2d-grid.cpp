class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int p) {
        int m=grid.size();
        int n=grid[0].size();
        vector<vector<int>> ans(m,vector<int>(n,0));
        for(int i=1; i<=p; i++){
            for(int j=0; j<m; j++){
                for(int k=0; k<n; k++){
                     if(j==m-1 && k==n-1){
                        ans[0][0]=grid[j][k];
                    }
                    else if(k==n-1){
                        ans[j+1][0]=grid[j][k];
                    }
                    else{
                        ans[j][k+1]=grid[j][k];
                    }
                }
            }
            grid=ans;
        }
        return grid;
    }
};