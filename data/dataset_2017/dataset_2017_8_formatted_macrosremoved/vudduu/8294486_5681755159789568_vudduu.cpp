// vudduu - codejam 2017 round 1 B
// Problem C
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string.h>
#include <string>
#include <utility>
#include <vector>
using namespace std;

typedef long long LL;

int N, Q;
vector<pair<double, double>> horses; // distance, speed
vector<vector<double>> G;
vector<vector<double>> Gtime;

double getBestTime(int u, int v) {
  Gtime.resize(N);
  for (int i = (0), _i = (N); i < _i; ++i) {
    Gtime[i].resize(N);
    for (int j = (0), _j = (N); j < _j; ++j)
      Gtime[i][j] = 200000000000000.0;
  }
  priority_queue<pair<pair<double, int>, pair<int, double>>>
      q; // time, horse, position, distance
  q.push(make_pair(make_pair(0, 0), make_pair(0, horses[0].first)));
  vector<bool> vis(N, false);
  while (q.size()) {
    double time = -q.top().first.first;
    int ho = q.top().first.second;
    int node = q.top().second.first;
    double rd = q.top().second.second;
    q.pop();
    if (rd < 0)
      continue;
    if (time >= Gtime[0][node])
      continue;
    if (!vis[node] && node != 0) {
      vis[node] = true;
      q.push(make_pair(make_pair(-time, node),
                       make_pair(node, horses[node].first)));
    }
    if (node == ho) {
      Gtime[0][node] = time;
    }
    for (int j = (0), _j = (N); j < _j; ++j) {
      if (G[node][j] != -1) {
        double newTime = time + (G[node][j] / horses[ho].second);
        q.push(
            make_pair(make_pair(-newTime, ho), make_pair(j, rd - G[node][j])));
      }
    }
  }
  return Gtime[0][N - 1];
}

void solve() {
  int u, v;
  cin >> N >> Q;
  horses.resize(N);
  for (int i = (0), _i = (N); i < _i; ++i)
    cin >> horses[i].first >> horses[i].second;
  G.resize(N);
  for (int i = (0), _i = (N); i < _i; ++i) {
    G[i].resize(N);
    for (int j = (0), _j = (N); j < _j; ++j) {
      cin >> G[i][j];
    }
  }
  for (int i = (0), _i = (Q); i < _i; ++i) {
    cin >> u >> v;
    if (i)
      printf(" ");
    printf("%.9lf", getBestTime(u - 1, v - 1));
  }
  printf("\n");
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; cas++) {
    printf("Case #%d: ", cas);
    solve();
  }
}
