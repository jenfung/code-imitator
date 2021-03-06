#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<pii, int> para;
const int inf = 1e9 + 7;
const int maxN = 50;
const int M = 50;
const int N = 50;

int t, n, p;
int req[maxN], minim[maxN][maxN], arr[maxN][maxN], maxim[maxN][maxN];
bool graph[maxN][maxN];

bool przeciecie(int i, int j) {
  if (minim[1][i] == inf || minim[2][j] == inf)
    return false;
  if (minim[1][i] >= minim[2][j] && minim[1][i] <= maxim[2][j])
    return true;
  if (maxim[1][i] >= minim[2][j] && maxim[1][i] <= maxim[2][j])
    return true;
  return false;
}

// maximal bipartite matching code copied from
// http://www.geeksforgeeks.org/maximum-bipartite-matching/
bool bpm(bool bpGraph[M][N], int u, bool seen[], int matchR[]) {
  // Try every job one by one
  for (int v = 0; v < N; v++) {
    // If applicant u is interested in job v and v is
    // not visited
    if (bpGraph[u][v] && !seen[v]) {
      seen[v] = true; // Mark v as visited

      // If job 'v' is not assigned to an applicant OR
      // previously assigned applicant for job v (which is matchR[v])
      // has an alternate job available.
      // Since v is marked as visited in the above line, matchR[v]
      // in the following recursive call will not get job 'v' again
      if (matchR[v] < 0 || bpm(bpGraph, matchR[v], seen, matchR)) {
        matchR[v] = u;
        return true;
      }
    }
  }
  return false;
}

// Returns maximum number of matching from M to N
int maxBPM(bool bpGraph[M][N]) {
  // An array to keep track of the applicants assigned to
  // jobs. The value of matchR[i] is the applicant number
  // assigned to job i, the value -1 indicates nobody is
  // assigned.
  int matchR[N];

  // Initially all jobs are available
  memset(matchR, -1, sizeof(matchR));

  int result = 0; // Count of jobs assigned to applicants
  for (int u = 0; u < M; u++) {
    // Mark all jobs as not seen for next applicant.
    bool seen[N];
    memset(seen, 0, sizeof(seen));

    // Find if the applicant 'u' can get a job
    if (bpm(bpGraph, u, seen, matchR))
      result++;
  }
  return result;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin >> t;
  for (int test = (1); test <= ((t)); ++test) {
    cin >> n >> p;
    for (int i = (1); i <= ((n)); ++i) {
      cin >> req[i];
    }

    for (int x = (1); x <= ((n)); ++x)
      for (int j = (1); j <= ((p)); ++j) {
        minim[x][j] = maxim[x][j] = inf;
      }
    for (int i = (1); i <= ((40)); ++i) {
      for (int j = (1); j <= ((40)); ++j) {
        graph[i][j] = 0;
        minim[i][j] = maxim[i][j] = inf;
      }
    }
    for (int i = (1); i <= ((n)); ++i)
      for (int j = (1); j <= ((p)); ++j)
        cin >> arr[i][j];

    for (int x = (1); x <= ((n)); ++x) {
      for (int j = (1); j <= ((p)); ++j) {
        float weight = req[x];
        int cnt = 1;
        while (weight <= 2 * arr[x][j]) {
          if (arr[x][j] >= 0.9 * weight && arr[x][j] <= 1.1 * weight) {
            minim[x][j] = min(minim[x][j], cnt);
            maxim[x][j] = cnt;
          }
          weight += req[x];
          cnt++;
        }
      }
    }

    cout << "Case #" << test << ": ";
    if (n == 1) {
      int ans = 0;
      for (int j = (1); j <= ((p)); ++j) {
        if (minim[1][j] != inf)
          ans++;
      }
      cout << ans << endl;
    } else {
      for (int i = (1); i <= ((p)); ++i)
        for (int j = (1); j <= ((p)); ++j)
          if (przeciecie(i, j)) {
            graph[i][j] = 1;
            // cout<<i<<" "<<j * p + 1<<endl;
            // cout<<minim[1][i]<<" "<<maxim[1][i]<<" "<<minim[2][j]<<"
            // "<<maxim[2][j]<<endl;
          }
      /* RI(i, 30) {
              RI(j, 30) {
                      cout<<graph[i][j]<<" ";
              }
              cout<<endl;
      } */
      cout << maxBPM(graph) << endl;
    }
  }
  return 0;
}
