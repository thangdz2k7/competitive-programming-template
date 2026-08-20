#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 5;

int n, q, c[MAX], root, used[MAX]; 
vector <int> adj[MAX];

int siz[MAX];

int dfs_size(int u, int fa){
    siz[u] = 1;
    for (int v : adj[u]) if (v != fa && !used[v]){
        siz[u] += dfs_size(v, u);
    }
    return siz[u];
}

int get_cen(int u, int fa, int m){
    for (int v : adj[u]) if (v != fa && !used[v] && siz[v] * 2 > m)
        return get_cen(v, u, m);
    return u;
}

struct Tree{

    map <int, int> t_in, t_out;
    int timer;
    vector <int> color, st[2], state, nxt;

    void cl(){
        timer = 0;
        t_in.clear();
        t_out.clear();
        color = {0};
        st[0].clear(); st[1].clear();
        state.clear();
        nxt = {0};
    }

    void dfs(int u, int fa){
        t_in[u] = ++ timer;
        color.push_back(0);
        nxt.push_back(0);
        color[timer] = c[u];
        for (int v : adj[u]) if (v != fa && !used[v]){
            dfs(v, u);
        }
        t_out[u] = timer;
        nxt[t_in[u]] = timer;
    }

    void build(int s, int l, int r){
        if (l == r){
            st[0][s] ++;
            return;
        }

        int mid = l + r >> 1;
        build(s << 1, l, mid);
        build(s << 1 | 1, mid + 1, r);

        for (int t : {0, 1})
            st[t][s] = st[t][s << 1] + st[t][s << 1 | 1];
    }

    void update(int s, int l, int r, int u, int v){
        if (u <= l && r <= v){
            state[s] ^= 1;
            swap(st[0][s], st[1][s]);
            return;
        }

        int mid = l + r >> 1;
        if (mid >= u) update(s << 1, l, mid, u, v);
        if (mid < v) update(s << 1 | 1, mid + 1, r, u, v);

        for (int t : {0, 1})
            st[t][s] = st[t][s << 1] + st[t][s << 1 | 1];

        if (state[s]) swap(st[0][s], st[1][s]);
    }

    void Update(int u){
        update(1, 1, timer, t_in[u], t_out[u]);
    }

    void Build(){
        for (int t : {0, 1})
            st[t].resize(timer * 4, 0);
        state.resize(timer * 4, 0);

        build(1, 1, timer);
        for (int i = 1; i <= timer; ++ i){
            if (color[i]) update(1, 1, timer, i, nxt[i]);
        }
    }

    int get(int s, int l, int r, int u){
        if (l == r) return state[s];
        int mid = l + r >> 1;
        if (mid >= u) return get(s << 1, l, mid, u) ^ state[s];
        return get(s << 1 | 1, mid + 1, r, u) ^ state[s];
    }

    int get_color(int u){ 
        return get(1, 1, timer, t_in[u]);
    }

    int co(int s, int l, int r, int u, int v, int k){
        if (u <= l && r <= v) return st[k][s];
        if (r < u || l > v) return 0;
        int mid = l + r >> 1;
        return co(s << 1, l, mid, u, v, k ^ state[s]) + co(s << 1 | 1, mid + 1, r, u, v, k ^ state[s]);
    }

    int Count(int l, int r, int k){
        return co(1, 1, timer, l, r, k);
    }


} tree[MAX];

int parent[MAX], gl[MAX], gr[MAX];

void build_cen(int u, int fa, int zl = -1, int zr = -1){
    u = get_cen(u, 0, dfs_size(u, 0));
    parent[u] = fa;
    used[u] = 1;
    gl[u] = zl, gr[u] = zr;
    tree[u].dfs(u, 0);
    tree[u].Build();
    for (int v : adj[u]) if (!used[v]) build_cen(v, u, tree[u].t_in[v], tree[u].t_out[v]);
}

void fl(int x){
    int r = x;
    c[x] ^= 1;
    while (r){
        tree[r].Update(x);
        r = parent[r];
    }
}

int get_ans(){
    int x = root;
    int r = x;
    int last = 0, res = 0;

    while (r){
        int need = tree[r].get_color(x) ^ c[r] ^ 1;
        res += tree[r].st[need][1];
        if (last != 0){
            res -= tree[r].Count(gl[last], gr[last], need);
        }
        last = r;
        r = parent[r];
    }

    return res;
}

void process() {
    cin >> n >> q;
    for (int i = 1; i <= n; ++ i){
        cin >> c[i];
        used[i] = 0;
        adj[i].clear();
        tree[i].cl();
    }

    for (int i = 1; i < n; ++ i){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    build_cen(1, 0);

    root = 1;

    while (q --){
        int type, x; cin >> type >> x;
        if (type == 2) root = x;
        else fl(x);
        cout << get_ans() << "\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int t; cin >> t; while (t --)
    process();
    
    return 0;
}
