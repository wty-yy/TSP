#include <bits/stdc++.h>
#define rep(i,a,b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 1e5 + 10;
int n;
double x[N], y[N], ans = 1e300;
bool vis[N];
int getdis(int i, int j) {
    return sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
}
int st;
void dfs(int u, int cnt, double tot) {
    if (cnt == n) {
        ans = min(ans, tot + getdis(u, st));
        return;
    }
    vis[u] = 1;
    int v = 0;
    double mn;
    rep(i,1,n) if (!vis[i]) {
        if (!v) {
            v = i;
            mn = getdis(u, i);
        } else {
            double tmp = getdis(u, i);
            if (tmp < mn) {
                v = i;
                mn = tmp;
            }
        }
    }
    dfs(v, cnt + 1, tot + mn);
}
int main() {
    freopen("1002points.in", "r", stdin);
    freopen("out.out", "w", stdout);
    cin>>n;
    rep(i,1,n) {
        int id; cin>>id;
        cin>>x[i]>>y[i];
    }
    time_t start, end;
    start = clock();
    for (st = 1; st <= n; st++) {
        memset(vis, 0, sizeof(vis));
        dfs(st, 1, 0);
    }
    end = clock();
    cout << "ans= " << ans << endl;
    cout << "use time: " << 1.0 * (end - start) / CLOCKS_PER_SEC * 1000 << " ms";
    return 0;
}