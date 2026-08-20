// vir_tree

int mark[MaxN + 5], sz[MaxN + 5];
vi virE[MaxN + 5];

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define fd(sr, x) (lower_bound(sr.begin(), sr.end(), x) - sr.begin())
#define uq(sr) (sr).erase(unique(all((sr))), (sr).end())

void dfs(int u){
    sz[u] = mark[u];
    for (int v : virE[u]){
        dfs(v); sz[u] += sz[v];
    }
}

void solve(vector <int> s){
    for (int u : s) mark[u] = 1; int n = s.size();
    sort(all(s), [&](int u, int v){
        return tree.t_in[u] < tree.t_in[v];
    });
    uq(s); for (int i = 1; i < n; ++ i) s.pb(tree.get(s[i], s[i - 1]));
    sort(rall(s), [&](int u, int v){
        return tree.t_in[u] < tree.t_in[v];
    });
    uq(s); vector <int> stk;
    for (int u : s){
        while (stk.size() && tree.check(u, stk.back())){
            virE[u].pb(stk.back());
            stk.pop_back();
        }
        stk.pb(u);
    }

    dfs(stk[0]);

    // clear();
    for (int u : s){
        mark[u] = 0; sz[u] = 0; virE[u].clear();
    }
}
