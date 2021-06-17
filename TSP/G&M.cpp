//1.0只完成了将原图分为大于三个点的强联通分量
//2.0完成接下来的构图，缩点，建边所有操作
//2.5优化过长的边，优化单点处理时对边的选择
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, nt[N];
double x[N], y[N], ans;
bool vis[N], fg[N<<1];
vector<double> xx[100], yy[100];
double getdis(int i, int j) {
    return sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
}
//判断有无其他中间点----------------------------------------------------------
int bel[N];
bool inmid(int u, int v, int mid) {
    return x[mid]>=min(x[u],x[v]) && x[mid]<=max(x[u],x[v]) && y[mid]>=min(y[u],y[v]) && y[mid]<=max(y[u],y[v]);
}
bool chkmid(int u, int v, int st) {
    for (int i = 1; i <= n; i++) if (bel[i] && bel[i] != st && i != u && i != v) {
        if (inmid(u, v, i)) return 1;
    }
    return 0;
}
//构图----------------------------------------------------------
struct Edge{int b, nt;} e[N<<1];
int head[N], e_num = 1;
bool cut[N<<1];
void aedge(int u, int v) {
    e[++e_num].b = v;
    e[e_num].nt = head[u];
    head[u] = e_num;
}
void makemap() {
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++) if (!vis[i] && nt[i] && nt[i] != i) {
        vis[i] = 1;
        aedge(i, nt[i]); aedge(nt[i], i);
        for (int j = nt[i]; j != i; j = nt[j]) {
            vis[j] = 1;
            aedge(j, nt[j]); aedge(nt[j], j);
        }
    }
}
//处理单点single_dot----------------------------------------------------------
double mn;
int x1, x2, edg;
void link_dot(int u, int sg) {
    if (chkmid(u, sg, bel[u])) return;
    for (int i = head[u]; i; i = e[i].nt) if (!cut[i]) {
        int v = e[i].b;
        if (chkmid(v, sg, bel[v])) continue;
        double w = getdis(u, sg) + getdis(v, sg);
        if (w < mn) {
            mn = w;
            x1 = u, x2 = v;
            edg = i;
        }
    }
}
void single() {
    for (int i = 1; i <= n; i++) if (!nt[i] || nt[i] == i) {
        mn = 1e100;
        memset(vis, 0, sizeof(vis));
        vis[i] = 1;
        for (int j = 1; j <= n; j++) if (!vis[j]) link_dot(j, i);
        aedge(x1, i), aedge(i, x1);
        aedge(x2, i), aedge(i, x2);
        cut[edg] = cut[edg ^ 1] = 1;
    }
}
//matlab打印----------------------------------------------------------
int last;
void dfs(int u, int id) {
    last = u;
    vis[u] = 1;
    xx[id].push_back(x[u]);
    yy[id].push_back(y[u]);
    for (int i = head[u]; i; i = e[i].nt) if (!cut[i]) {
        int v = e[i].b;
        if (vis[v]) continue;
        ans += getdis(u, v);
        dfs(v, id);
    }
}
void print() {
    memset(vis, 0, sizeof(vis));
    int cnt = 0;
    ans = 0;
    for (int i = 1; i <= n; i++) if (!vis[i]) {
        xx[++cnt].clear();
        yy[cnt].clear();
        dfs(i, cnt);
        ans += getdis(last, i);
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
//贪心构建强联通分量部分----------------------------------------------------------
int findst() {
    int ret = 0;
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
    if (!ret)
        for (int i = 1; i <= n; i++) if (!vis[i]) {vis[i] = 1; break;}
    return ret;
}
void greed(int u, int st, int use) {
    vis[u] = 1; bel[u] = st;
    int v;
    double mn = 1e100;
    for (int i = 1; i <= n; i++) if (!vis[i]) {
        int dis = getdis(u, i);
        if (dis < mn) {
            mn = dis;
            v = i;
        }
    }
    if ((getdis(u, st) < mn && use > 2) || chkmid(u, v, st)) {//这里允许由两个点构成一个强连通分量
        nt[u] = st;
        return;
    }
    nt[u] = v;
    greed(v, st, use + 1);
}
void work() {
    int st = findst();
    if (!st) return;
    greed(st, st, 1);
}
//缩点shrink_dots----------------------------------------------------------
vector<int> U[N];
int u_num;
map<pair<int, int>, int> hsh;
map<int, pair<int, int>> anti;
void dfs1(int u, int id) {
    vis[u] = 1;
    U[id].push_back(u);
    for (int i = head[u]; i; i = e[i].nt) if (!cut[i]) {
        int v = e[i].b;
        hsh[make_pair(u, v)] = i;
        anti[i] = make_pair(u, v);
        if (vis[v]) continue;
        dfs1(v, id);
    }
}
bool shrink() {
    hsh.clear(); anti.clear();
    u_num = 0;
    memset(vis, 0, sizeof(vis));
    for (int u = 1; u <= n; u++) if (!vis[u]) {
        U[++u_num].clear();
        dfs1(u, u_num);
        U[u_num].push_back(u);
    }
    if (u_num == 1) return 0;
    return 1;
}
//建边build_edge----------------------------------------------------------
int n_num;
struct Node {
    int fu, fv;
    int u, v; double w;
    Node(){}
    Node(int f1, int f2, int a, int b, double c) {fu =  f1, fv = f2, u = a, v = b, w = c;}
} A[N];
double getmin(int a1, int a2, int b1, int b2) {
    double d1 = getdis(a1, b1) + getdis(a2, b2);
    double d2 = getdis(a1, b2) + getdis(a2, b1);
    return min(d1, d2);
}
void build() {
    n_num = 0;
    for (int i = 1; i <= u_num; i++) {
        for (int j = i + 1; j <= u_num; j++) {
            double mn = 1e100;
            int u, v;
            int sz1 = U[i].size();
            for (int ii = 0; ii < sz1 - 1; ii++) {
                int a1 = U[i][ii], a2 = U[i][ii + 1];
                int sz2 = U[j].size();
                for (int jj = 0; jj < sz2 - 1; jj++) {
                    int b1 = U[j][jj], b2 = U[j][jj + 1];
                    double w = getmin(a1, a2, b1, b2) - getdis(a1, a2) - getdis(b1, b2);
                    if (w < mn) {
                        mn = w;
                        u = hsh[make_pair(a1, a2)];
                        v = hsh[make_pair(b1, b2)];
                    }
                }
            }
            A[++n_num] = Node(i, j, u, v, mn);
        }
    }
}
//最小生成树Kruskal_minimum_spanning_tree----------------------------------------------------------
int fa[N];
int getfa(int x) {
    if (fa[x] == x) return x;
    fa[x] = getfa(fa[x]);
    return fa[x];
}
bool cmp(Node &a, Node &b) {return a.w < b.w;}
void build_and_cut(int u, int v) {
    pair<int, int> p1 = anti[u], p2 = anti[v];
    int a1 = p1.first, a2 = p1.second, b1 = p2.first, b2 = p2.second;
    if (abs(getdis(a1, b1) + getdis(a2, b2) - getmin(a1, a2, b1, b2)) > 1e-7)
        swap(b1, b2);
    aedge(a1, b1), aedge(b1, a1);
    aedge(a2, b2), aedge(b2, a2);
    cut[u] = cut[u ^ 1] = 1;
    cut[v] = cut[v ^ 1] = 1;
}
void Kruskal() {
    memset(fg, 0, sizeof(fg));
    for (int i = 1; i <= u_num; i++) fa[i] = i;
    sort(A + 1, A + 1 + n_num, cmp);
    for (int i = 1; i <= n_num; i++) {
        int fu = A[i].fu, fv = A[i].fv;
        int u = A[i].u, v = A[i].v;
        if (getfa(fu) != getfa(fv)) {
            fa[getfa(fu)] = getfa(fv);
            if (!fg[u] && !fg[v]) {
                fg[u] = fg[v] = 1;
                build_and_cut(u, v);
            }
        }
    }
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
    freopen("1002points.in", "r", stdin);
    freopen("out.out", "w", stdout);
    time_t st, en;
    st = clock();
    init();//读入
    while (chk()) work();//贪心构建强联通分量
    makemap();
    single();
    //print();
    while (shrink()) {
        build();
        Kruskal();
        //print();
    }
    en = clock();
    print();
    cout << "ans: " << ans << endl;
    cout << "use time: " << 1.0 * (en - st) / CLOCKS_PER_SEC * 1000 << " ms";
    return 0;
}
//29points有单点问题
