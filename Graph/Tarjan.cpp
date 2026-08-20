struct Tarjan{

  vector <int> adj[MAX];
  int low[MAX], num[MAX], cnt, com[MAX], nc;

  void init(){
    cnt = nc = 0;
    for (int i = 0; i < n; ++ i){
      adj[i].clear();
      low[i] = num[i] = 0;
    }
  }

  void add(int u, int v){
    adj[u].push_back(v);
  }

  vector <int> stk;

  void dfs(int u){
    low[u] = num[u] = ++ cnt;
    stk.push_back(u);

    for (int v : adj[u]){
      if (num[v]) low[u] = min(low[u], num[v]);
      else {
        dfs(v);
        low[u] = min(low[u], low[v]);
      }
    }

    if (low[u] == num[u]){
      ++ nc;
      int v;
      do {
        v = stk.back();
        stk.pop_back();
        com[v] = nc;
        low[v] = num[v] = inf;
      } while (v != u);
    }
  }

} t1, t2;
