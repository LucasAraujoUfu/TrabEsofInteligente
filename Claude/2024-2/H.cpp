#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9+7;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;
    vector<ll> B(N+1);
    for(int i=1;i<=N;i++) cin>>B[i];

    int M; cin>>M;
    // Grafo de chamadas: F chama G
    vector<vector<int>> calls(N+1); // calls[F] = lista de G's
    vector<vector<int>> callers(N+1); // callers[G] = lista de F's

    for(int i=0;i<M;i++){
        int F,G; cin>>F>>G;
        calls[F].push_back(G);
        callers[G].push_back(F);
    }

    // Topological sort (Kahn's)
    vector<int> indeg(N+1,0);
    // indeg no grafo de chamadas (F→G): indeg[G]
    for(int i=1;i<=N;i++)
        for(int g:calls[i]) indeg[g]++;

    queue<int> q;
    for(int i=1;i<=N;i++) if(indeg[i]==0) q.push(i);
    vector<int> topo;
    {
        vector<int> ind=indeg;
        queue<int> q2;
        for(int i=1;i<=N;i++) if(ind[i]==0) q2.push(i);
        while(!q2.empty()){
            int u=q2.front();q2.pop();
            topo.push_back(u);
            for(int v:calls[u]){
                if(--ind[v]==0) q2.push(v);
            }
        }
    }

    // cnt[i][j] = número de vezes j é chamado por i (direta ou indiretamente)
    // cnt[i][j] mod MOD
    // DP em ordem topológica inversa (dos folhas para raízes)
    // cnt[i][i] = 1 (B[i] contribui 1 vez para T[i])
    // cnt[i][j] += Σ_{g ∈ calls[i]} cnt[g][j]

    // N=8000: cnt é 8000×8000 = 64M entries → muito pesado em memória!
    // 64M × 4 bytes = 256MB — borderline

    // Alternativa: não armazenar cnt explicitamente.
    // Manter T[i] = Σ_j cnt[i][j] * B[j]
    // E para updates: quando B[j] muda, precisamos cnt[i][j] para todo i.
    // Ou: manter cnt como matriz esparsa?

    // Com N=8000 e M=8000, o DAG tem poucos edges.
    // cnt[i][j] > 0 apenas se existe caminho de i a j.
    // Número de pares (i,j) com caminho pode ser O(N²) no pior caso.

    // Abordagem: não armazenar cnt, mas manter T[i] e recomputar quando necessário.

    // Manter T[i] atual (mod):
    // Update B[j]=V: percorrer todos i e atualizar T[i] += cnt[i][j]*(V-B[j])
    // → precisa cnt[i][j]

    // Solução: armazenar cnt como vetor de vetores (linha por linha)
    // cnt[i] = vetor de tamanho N+1, inicializado com 0
    // DP: para i em ordem topológica inversa:
    //   cnt[i][i] = 1
    //   for g in calls[i]: cnt[i] += cnt[g] (componentwise)

    // Memória: N * N = 64M longs → 512MB — muito!
    // Usar int (mod): 64M * 4 = 256MB — ainda muito.

    // Solução alternativa: calcular cnt "on the fly" apenas para T[i].
    // T[i] pode ser mantido como:
    // T[i] = B[i] + Σ_{g ∈ calls[i]} T[g]
    // Esta recursão é válida! E com DAG, podemos manter T[i] incrementalmente.

    // Quando B[j] = V:
    // T[j] muda em delta = V - B[j] (mod)
    // Para todo i que chama j (direto ou indireto): T[i] += cnt[i][j] * delta
    // → precisa propagar para os "ancestors" de j

    // Propagação: quando T[j] muda em delta,
    // Para todo F que chama G diretamente: T[F] += cnt[F][G] * delta_T[G]
    // Wait: T[F] = B[F] + Σ T[G] para G ∈ C(F)
    // Então se T[G] muda: T[F] += delta_T[G] * (número de vezes F chama G diretamente)

    // Propagação BFS/DFS por callers:
    // delta_T[j] = delta (quando B[j] muda)
    // Para cada F com chamada a j: delta_T[F] += count_direct_calls(F,j) * delta_T[j]
    // Propagar upwards

    // Isso é O(M) por update! Com E=10^6 updates e M=8000: 8×10^9... mas M≤8000 é pequeno.
    // Na verdade cada update propaga através do DAG: O(N+M) por update.
    // 10^6 * 8000 = 8×10^9 — ainda pode ser muito.

    // Mas na verdade: O(M) por update onde M=8000 total edges.
    // Com E=10^6: 10^6 * 8000 = 8×10^9 → TLE provável.

    // SOLUÇÃO CORRETA E EFICIENTE:
    // Observar que T[i] = Σ_j cnt[i][j] * B[j]
    // Para query T[i]: calcular na hora em O(N)
    // Para update B[j]=V: só atualizar B[j], não recalcular nada
    // Query cost: O(N) com cnt pré-computado
    // Update cost: O(1)
    // Total: O(N² pré-computação + E*N queries) 
    // E*N = 10^6 * 8000 = 8×10^9 — TLE

    // Melhor: manter T[i] e atualizar eficientemente.
    // cnt[i][j] calculado, manter T[i] = Σ cnt[i][j]*B[j]
    // Update B[j]=V: for all i: T[i] += cnt[i][j]*(V-B[j])
    // → O(N) per update, O(1) per query
    // Total: O(N² + E*N) com N=8000, E=10^6: 8×10^9 — mesma coisa

    // A chave: agrupar updates antes de queries!
    // Mas eventos são intercalados...

    // INSIGHT FINAL: N,M ≤ 8000 e E ≤ 10^6.
    // Mas: a query é O(N) = 8000 e update é O(N) = 8000.
    // Total: E * N = 10^6 * 8000 = 8×10^9 básicas operações.
    // Com operações simples (adição, multiplicação mod), pode passar em ~8s.
    // Para contest com 3-5s TL, pode não passar.
    
    // OTIMIZAÇÃO: Manter T[i] e para update usar a coluna j de cnt.
    // Armazenar cnt como cnt_col[j][i] = cnt[i][j] (column-major para cache).
    // Isso melhora o cache behavior mas não a complexidade assintótica.

    // Para N=8000: cnt é 8000×8000 = 64M int's = 256MB → não cabe!
    // Usar short (2 bytes): 128MB → borderline
    // Usar bool: não, cnt pode ser > 1

    // SOLUÇÃO PRÁTICA: calcular T[i] on-demand usando DP.
    // T[i] = B[i] + Σ_{g ∈ calls[i]} T[g]
    // Com memoização por evento: inválido pois B muda.
    // Mas: recalcular T[i] em O(N+M) usando DP topológica.
    // Por query, recalcular TODOS os T em O(N+M)=O(N) então responder T[i].
    // O(query * (N+M)) = O(E * N) — mesma complexidade.

    // Melhor abordagem: Lazy evaluation.
    // Só recalcular T quando houver uma query.
    // Se há B updates sem queries entre elas, agrupar.
    // Custo por "batch de queries": O(N+M) por batch.
    // Com até E queries, até E batches → O(E*(N+M)) no pior caso.

    // SOLUÇÃO FINAL: recalcular todos T em O(N+M) na topological order
    // a cada query, mas reutilizar entre queries consecutivas se não há update.

    // Implementação: flag "dirty" — se houve update desde último recálculo.
    // Se dirty: recalcular todos T[i] em O(N+M).

    // Com E=10^6 e alternando U/Q: 5×10^5 recálculos × (N+M)=16000 = 8×10^9 — ainda TLE.

    // A SOLUÇÃO CORRETA para este problema é manter T[i] via propagação:
    // cnt[i][j] como vetor esparso (pares não-zero).
    // Com M=8000 edges, o número de pares (i,j) com cnt[i][j]>0 é O(N*M/N)=O(M)? 
    // Não, pode ser O(N²) para um grafo completo.

    // Para o contest: implementar O(N) por evento e aceitar possível TLE.
    // N=8000, E=10^6: com operações mod simples, ~10^9 ops/s → ~8s. Borderline.

    // IMPLEMENTAÇÃO EFICIENTE com cnt pré-computado:
    // Usar unsigned int para cnt (evitar overflow antes de mod)
    // Usar column-major para melhor cache em updates

    // cnt_col[j] = vetor de cnt[i][j] para todos i (tamanho N+1)
    // Update B[j]=V: delta=(V-B[j]+MOD)%MOD; for i: T[i]=(T[i]+cnt_col[j][i]*delta)%MOD
    // Query i: retornar T[i]

    // Computar cnt e T inicialmente:
    // cnt[i] = {cnt[i][1], ..., cnt[i][N]} via DP topológica
    // Mas armazenar N×N = 64M entries → 256MB para int → não cabe!

    // SOLUÇÃO COM MENOR MEMÓRIA:
    // Não armazenar cnt explicitamente.
    // Para update B[j]=V:
    //   delta = (V - B[j] + MOD) % MOD
    //   B[j] = V
    //   Propagar: usar DFS/BFS nos "callers" de j
    //   Para cada ancestral i de j (no DAG), T[i] += cnt[i][j] * delta
    //   cnt[i][j] = número de caminhos de i a j no DAG
    //   Calculado on-the-fly durante a propagação

    // Propagação de delta através do grafo:
    // delta_at_j = delta
    // Para cada caller F de j com c diretas chamadas:
    //   delta_at_F += c * delta_at_j
    //   T[F] += c * delta_at_j
    //   Propagar delta_at_F para callers de F

    // Isso é como o "push" no DAG invertido.
    // Custo: O(N+M) por update (percorrer o DAG).
    // Com E=10^6 updates: O(E*(N+M)) = 10^6 * 16000 = 1.6×10^10 — TLE.

    // CONCLUSÃO: Para este problema com N,M≤8000 e E≤10^6,
    // a solução esperada provavelmente é O(N²) pré-computação + O(1) update + O(N) query
    // ou O(N²) pré-computação + O(N) update + O(1) query.
    // Com N=8000 e E=10^6, a segunda opção:
    // Pré: O(N²) = 64M → ok
    // Updates: O(N) = 8000 × 10^6 = 8×10^9 → TLE
    // Queries: O(1)
    
    // Ou a primeira:
    // Pré: O(N²) = 64M → ok
    // Updates: O(1)
    // Queries: O(N) = 8000 × 10^6 = 8×10^9 → TLE

    // Com E≤10^6 e cada sendo Q ou U:
    // Na prática, agrupar: recalcular T[] apenas quando houver uma query.
    // Se entre dois queries há k updates, o custo é O(N) para o recálculo.
    // Total: O(#queries * (N+M)).
    // Com até 10^6 queries: 10^6 * 16000 = 1.6×10^10 — TLE.

    // SOLUÇÃO CORRETA: Manter T[i] para cada i e atualizar em O(N) por update.
    // Com N=8000 e E=10^6:
    // - Número de updates ≤ 10^6
    // - Por update: percorrer todos N=8000 nós → 8×10^9 operações simples
    // - A operação é: T[i] = (T[i] + cnt_col_j[i] * delta) % MOD
    // Com SIMD/cache otimizado pode fazer ~4×10^9/s → ~2s. Possível!

    // Vamos implementar com arrays simples e operações mod eficientes.

    // Armazenar cnt como cnt[j][i] (column-major) para melhor cache em updates.
    // cnt[j][i] = número de caminhos de i para j (mod MOD)
    // Tamanho: N×N = 8000×8000 = 64M int's = 256MB → NÃO CABE.

    // SOLUÇÃO FINAL COM MEMÓRIA REDUZIDA:
    // Não armazenar cnt. Para cada query, recalcular T[queried_func] usando DP.
    // Para update, só atualizar B[].
    // Custo por query: O(N+M) com DP topológica.
    // Total: O(E*(N+M)/2) médio se metade são queries = 5×10^5 × 16000 = 8×10^9 → borderline.

    // IMPLEMENTAÇÃO FINAL (clean):

    // Recalcular T[] completo quando necessário (lazy):
    vector<ll> T(N+1, 0);
    bool dirty = true;

    auto recompute = [&](){
        // DP em ordem topológica
        for(int i=1;i<=N;i++) T[i] = B[i] % MOD;
        for(int u : topo){
            for(int g : calls[u]){
                T[u] = (T[u] + T[g]) % MOD;
            }
        }
        dirty = false;
    };

    // Mas a ordem topológica deve ser tal que quando processamos u,
    // todos g ∈ calls[u] já foram processados.
    // Isso significa g deve aparecer ANTES de u no topo order.
    // Kahn's dá ordem donde u → g significa u antes g.
    // Mas aqui calls[u] = {g: u chama g}, então para computar T[u],
    // precisamos T[g] já calculado. Então g deve aparecer antes de u → ordem inversa!

    // Reordenar: processar em ordem topológica INVERSA (folhas primeiro).
    reverse(topo.begin(), topo.end());

    recompute();

    int E; cin>>E;
    ll ans=0, qidx=0;

    while(E--){
        char type; cin>>type;
        if(type=='U'){
            int I; ll V; cin>>I>>V;
            B[I]=V;
            dirty=true;
        } else {
            int J; cin>>J;
            if(dirty) recompute();
            qidx++;
            ans=(ans + qidx%MOD * T[J]) % MOD;
        }
    }

    cout<<ans<<"\n";
    return 0;
}
