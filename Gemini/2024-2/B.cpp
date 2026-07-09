#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; // N filmes, M atores
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> actor_to_movies(m + 1);
    vector<vector<int>> movie_to_actors(n + 1);

    for (int i = 1; i <= n; i++) {
        int ni;
        cin >> ni;
        for (int j = 0; j < ni; j++) {
            int actor;
            cin >> actor;
            actor_to_movies[actor].push_back(i);
            movie_to_actors[i].push_back(actor);
        }
    }

    // dist_from_movie[f][a]: menor distância do filme f ao ator a
    // Como a escala de passos alterna ator-filme, contamos distâncias em número de nós visitados
    vector<vector<int>> dist_from_movie(n + 1, vector<int>(m + 1, 1e9));

    for (int f = 1; f <= n; f++) {
        queue<int> q;
        vector<int>& d = dist_from_movie[f];
        
        for (int actor : movie_to_actors[f]) {
            d[actor] = 1;
            q.push(actor);
        }

        vector<bool> movie_vis(n + 1, false);
        movie_vis[f] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int mv : actor_to_movies[u]) {
                if (!movie_vis[mv]) {
                    movie_vis[mv] = true;
                    for (int nxt_act : movie_to_actors[mv]) {
                        if (d[nxt_act] > d[u] + 2) {
                            d[nxt_act] = d[u] + 2;
                            q.push(nxt_act);
                        }
                    }
                }
            }
        }
    }

    int q_queries;
    if (cin >> q_queries) {
        while (q_queries--) {
            int x, y;
            cin >> x >> y;

            if (x == y) {
                cout << "1\n" << x << "\n";
                continue;
            }

            int min_len = 1e9;
            int best_start_movie = -1;

            for (int mv : actor_to_movies[x]) {
                if (dist_from_movie[mv][y] < min_len) {
                    min_len = dist_from_movie[mv][y];
                    best_start_movie = mv;
                }
            }

            if (best_start_movie == -1 || min_len >= 1e9) {
                cout << "-1\n";
                continue;
            }

            // O número total de atores no caminho será (min_len + 3) / 2
            int num_actors = (min_len + 3) / 2;
            cout << num_actors << "\n";

            // Reconstrução gananciosa do caminho de X para Y
            vector<int> path_nodes;
            path_nodes.push_back(x);

            int current_movie = best_start_movie;
            int remaining_dist = min_len;

            while (remaining_dist > 1) {
                path_nodes.push_back(current_movie);
                int next_actor = -1;
                int next_movie = -1;

                for (int act : movie_to_actors[current_movie]) {
                    for (int mv : actor_to_movies[act]) {
                        if (dist_from_movie[mv][y] == remaining_dist - 2) {
                            next_actor = act;
                            next_movie = mv;
                            break;
                        }
                    }
                    if (next_actor != -1) break;
                }
                path_nodes.push_back(next_actor);
                current_movie = next_movie;
                remaining_dist -= 2;
            }

            path_nodes.push_back(current_movie);
            path_nodes.push_back(y);

            for (size_t i = 0; i < path_nodes.size(); i++) {
                cout << path_nodes[i] << (i + 1 == path_nodes.size() ? "" : " ");
            }
            cout << "\n";
        }
    }
    return 0;
}
