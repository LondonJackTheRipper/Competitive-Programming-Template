/*
Sample problem to solve: L. Subway Lines (2018-2019 ACM-ICPC Brazil Subregional Programming Contest)
Link: https://codeforces.com/gym/101908/problem/L
Idea: add 1 to path (A, B), then the result is the sum of values on path (C, D), then add -1 to path (A, B) for next query
*/

#include <bits/stdc++.h>
using namespace std;

/*
  Ben Watson
  Handle codeforces : quangminh98

  Mua Code nhu mua Florentino !!
*/

#define ll long long

const string name = "test";

void solve();
signed main()
{
    if (fopen((name + ".inp").c_str(), "r"))
    {
        freopen((name + ".inp").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    solve();

    return 0;
}

// main program
const int maxn = 1e5 + 1;

struct SegmentTree
{
    struct Node
    {
        int sum, lazy;

        Node() : sum(0), lazy(0) {};
        Node operator + (const Node& other) const
        {
            Node res;
            res.sum = sum + other.sum;
            return res;
        }
    };
    vector<Node> st;
    int n;

    SegmentTree (int n) : n(n) { st.resize(4 * n + 1); }

    void pass(int head, int l, int r)
    {
        if (st[head].lazy == 0)
            return;

        st[head].sum += (r - l + 1) * st[head].lazy;
        if (l != r)
        {
            st[head << 1].lazy += st[head].lazy;
            st[head << 1 | 1].lazy += st[head].lazy;
        }

        st[head].lazy = 0;
    }

    void update(int head, int l, int r, int u, int v, int val)
    {
        pass(head, l, r);
        if (l > v || r < u) return;
        if (u <= l && r <= v)
        {
            st[head].lazy += val;
            pass(head, l, r);
            return;
        }

        int mid = l + r >> 1;
        update(head << 1, l, mid, u, v, val);
        update(head << 1 | 1, mid + 1, r, u, v, val);

        st[head] = st[head << 1] + st[head << 1 | 1];
    }
    void update(int u, int v, int val) { update(1, 1, n, u, v, val); }

    int query(int head, int l, int r, int u,  int v)
    {
        pass(head, l, r);
        if (l > v || r < u) return 0;
        if (u <= l && r <= v)
            return st[head].sum;

        int mid = l + r >> 1;
        return query(head << 1, l, mid, u, v) + query(head << 1 | 1, mid + 1, r, u, v);
    }
    int query(int u, int v) { return query(1, 1, n, u, v); }
};

int n, q;
vector<int> adj[maxn];
int par[maxn], d[maxn], heavy[maxn], id[maxn], pos[maxn];
SegmentTree st(maxn);

int DFS(int u)
{
    int sz = 1, mx_sz = 0;
    for (int v : adj[u])
    {
        if (v == par[u])
            continue;

        par[v] = u;
        d[v] = d[u] + 1;
        int sub_sz = DFS(v);
        sz += sub_sz;
        if (sub_sz > mx_sz)
        {
            heavy[u] = v;
            mx_sz = sub_sz;
        }
    }
    return sz;
}

int cur = 0;
void decompose(int u, int head)
{
    id[u] = head;
    pos[u] = ++cur;
    if (heavy[u] != 0)
        decompose(heavy[u], head);
    for (int v : adj[u])
    {
        if (v == par[u] || v == heavy[u])
            continue;

        decompose(v, v);
    }
}

int query(int u, int v, int ops)
{
    int res = 0;
    for (; id[u] != id[v]; v = par[id[v]])
    {
        if (d[id[u]] > d[id[v]])
            swap(u, v);

        if (ops == 2)
            res += st.query(pos[id[v]], pos[v]);
        else
            st.update(pos[id[v]], pos[v], (ops == 1 ? 1 : -1));
    }
    if (d[u] > d[v])
        swap(u, v);
    if (ops == 2)
        res += st.query(pos[u], pos[v]);
    else
        st.update(pos[u], pos[v], (ops == 1 ? 1 : -1));
    return res;
}

void solve()
{
    cin >> n >> q;
    for (int i = 1; i < n; i++)
    {
        int u, v; cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    DFS(1);
    decompose(1, 1);

    while (q--)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        query(a, b, 1);
        cout << query(c, d, 2) << '\n';
        query(a, b, 3);
    }
}
