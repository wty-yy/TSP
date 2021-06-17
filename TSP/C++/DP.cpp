#include<bits/stdc++.h>
using namespace std;
const int N = 20 + 10;
double dp[N][(2<<20)+1];
// vector<int> ve[N][(2<<20)+1];
struct city{double x, y;} C[N];
double dis(int i, int j) {return sqrt((C[i].x-C[j].x)*(C[i].x-C[j].x)+(C[i].y-C[j].y)*(C[i].y-C[j].y));}
// int ddd[N][N];
// int dis(int i, int j) {return ddd[i][j];}
int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int id;
        scanf("%d %lf %lf", &id, &C[i].x, &C[i].y);
    }
    // for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) scanf("%d", &ddd[i][j]);
    memset(dp, 0x7f, sizeof(dp));
    dp[0][1] = 0;
    // ve[0][1].push_back(0);
    int m = 1 << n;
    for (int i = 1; i < m; i++) {
        if (!(i & 1)) continue;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) continue;
            for (int k = 0; k < n; k++) if (i & (1 << k)) {
                // if (dp[k][i] + dis(k, j) < dp[j][i | (1 << j)]) {
                //     ve[j][i | (1 << j)] = ve[k][i];
                //     ve[j][i | (1 << j)].push_back(j);
                // }
                dp[j][i | (1 << j)] = min(dp[k][i] + dis(k, j), dp[j][i | (1 << j)]);
            }
        }
    }
    double ans = dp[1][m - 1] + dis(1, 0);
    for (int i = 2; i < n; i++)
        ans = min(dp[i][m - 1] + dis(i, 0), ans);
    // int sz = ve[3][m - 1].size();
    // for (int i = 0; i < sz; i++) {
    //     printf("%d ", ve[3][m - 1][i]);
    // }
    printf("%f\n", ans);
    system("pause");
    return 0;
}