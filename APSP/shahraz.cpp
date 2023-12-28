#include <iostream>
#include <vector>
using namespace std;
class Solution
{

public:
    vector<int> shortest_distance(vector<vector<int>> &matrix, int threshHold)
    {
        int n = matrix.size();

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (matrix[i][j] == -1)
                {
                    matrix[i][j] = 1e9;
                }
            }
        }

        for (int k = 1; k <= n; k++)
        {
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    if (matrix[k][j] != 1e9 && matrix[i][k] != 1e9 && matrix[i][j] > (matrix[i][k] + matrix[k][j]))
                    {
                        matrix[i][j] = matrix[i][k] + matrix[k][j];
                    }
                }
            }
        }

        int min = 1e9;
        for (int i = 1; i <= n; i++)
        {
            int temp = 0;
            for (int j = 1; j <= n; j++)
            {
                /* code */
                if (matrix[i][j] <= threshHold)
                {
                    temp++;
                }
            }
            if (temp < min)
            {
                min = temp;
            }
        }
        vector<int> ans;
        for (int i = 1; i <= n; i++)
        {
            int temp = 0;
            for (int j = 1; j <= n; j++)
            {
                /* code */
                if (matrix[i][j] <= threshHold)
                {
                    temp++;
                }
            }
            if (temp == min)
            {
                ans.push_back(i);
            }
        }
        return ans;
    }
};


int main()
{
    Solution solution;

    int n, m;
    cin >> n >> m;

    vector<vector<int>> matrix(n+1, vector<int>(n+1, -1)); 

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
       
        matrix[u][v] = w; 
        matrix[v][u] = w; 
       // matrix[i][i]=0;

    }

    for(int i=1; i<=n; i++){
        matrix[i][i]=0;
    }

    int threshold;
    cin >> threshold;

    vector<int> result = solution.shortest_distance(matrix, threshold);

    for (int i : result)
    {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}