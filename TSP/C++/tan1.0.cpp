//1.0只完成了将原图分为大于三个点的强联通分量

#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
int n, nt[N];
double x[N], y[N];
bool vis[N], fg[N];
vector<double> xx[100], yy[100];
//----------------------------------------------------------matlab打印
void dfs(int u, int id) {
    if (fg[u]) return;
    fg[u] = 1;
    xx[id].push_back(x[u]);
    yy[id].push_back(y[u]);
    dfs(nt[u], id);
}
void print() {//为满足matlab打印图像的需要
    int cnt = 0;
    for (int i = 1; i <= n; i++) if (!fg[i]) {
        dfs(i, ++cnt);
    }
    cout << cnt << endl;
    for (int i = 1; i <= cnt; i++) {
        cout << xx[i].size() + 1 << endl;
        for (auto j : xx[i]) cout << j << " ";
        cout << xx[i][0] << endl;
        for (auto j : yy[i]) cout << j << " ";
        cout << yy[i][0] << endl;
    }
}
//----------------------------------------------------------构建强联通分量部分
double getdis(int i, int j) {
    return sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
}
int findst() {
    int ret;
    double mn = 1e100;
    for (int i = 1; i <= n; i++) if (!vis[i]) {
        for (int j = i + 1; j <= n; j++) if (!vis[j]) {
            double dis = getdis(i, j);
            if (dis < mn) {
                mn = dis;
                ret = i;
            }
        }
    }
    return ret;
}
void greed(int u, int st, int use) {
    vis[u] = 1;
    int v;
    double mn = 1e100;
    for (int i = 1; i <= n; i++) if (!vis[i]) {
        int dis = getdis(u, i);
        if (dis < mn) {
            mn = dis;
            v = i;
        }
    }
    if (getdis(u, st) < mn && use > 2) {
        nt[u] = st;
        return;
    }
    nt[u] = v;
    greed(v, st, use + 1);
}
void work() {
    int st = findst();
    greed(st, st, 1);
}
//----------------------------------------------------------
void init() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int id;
        cin >> id >> x[i] >> y[i];
    }
}
bool chk() {
    for (int i = 1; i <= n; i++) if (!vis[i]) return true;
    return false;
}
int main() {
    freopen("16points.in", "r", stdin);
    freopen("out.out", "w", stdout);
    init();//读入
    while (chk()) work();//构建强联通分量
    print();//绘图
    return 0;
}