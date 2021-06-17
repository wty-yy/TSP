#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
struct City {double x, y;} A[N];
struct Node {
    double d; int i, j;
    Node(){}
    Node(double a, int b, int c){d = a, i = b, j = c;}
} B[N*N];
bool cmp(Node &a, Node &b) {return a.d > b.d;}
double dis(int i, int j) {
    if (i == j) return 1e18;
    return sqrt((A[i].x-A[j].x)*(A[i].x-A[j].x)+(A[i].y-A[j].y)*(A[i].y-A[j].y));
}
int n, cnt[2][N];
double ans;
bool mp[N][N];
// double dis(int i, int j) {
//     return mp[i][j];
// }
bool fg[N];
void dfs(int u) {
    fg[u] = 1;
    for (int i = 1; i <= n; i++) if(!fg[i] && !mp[u][i]) {
        dfs(i);
    }
}
bool chk() {
    memset(fg, 0, sizeof(fg));
    dfs(1);
    for (int i = 1; i <= n; i++) if (!fg[i]) return false;
    return true;
}
vector<int> v[N];
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    for (int i = 1; i <= n; i++) {
        int id;
        cin>>id>>A[i].x>>A[i].y;
        cnt[0][i] = cnt[1][i] = n;
    }
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= n; j++) {
    //         cin >> mp[i][j];
    //         if (i == j) mp[i][j] = 1e18;
    //     }
    //     cnt[0][i] = cnt[1][i] = n;
    // }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            B[(i - 1) * n + j - 1] = Node(dis(i, j), i, j);
    sort(B, B + n * n, cmp);
    // for (int i=0;i<n*n;i++)cout<<B[i].d<<endl;
    for (int i = 0; i < n * n; i++) {
        int x = B[i].i, y = B[i].j;
        if (!cnt[0][x] || !cnt[1][y]) continue;
        mp[x][y] = 1;
        --cnt[0][x];
        if (cnt[0][x] <= 1) {
            mp[x][y] = 0;
            ++cnt[0][y];
            // cnt[0][x] = cnt[1][y] = 0;
            ans += B[i].d;
            v[x].push_back(y);
            v[y].push_back(x);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < v[i].size(); j++) cout << v[i][j] << " ";
        cout << endl;
    }
    cout<<ans<<endl;
    system("pause");
    return 0;
}