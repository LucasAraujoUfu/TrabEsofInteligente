#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef __int128 lll;

const ull CAP = 4e18 + 1; // saturar

ull safeAdd(ull a, ull b){
    if(a > CAP - b) return CAP;
    return a + b;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ull N, K;
    cin >> N >> K;

    // Determinar inv* e K' (1-indexed dentro do grupo inv*)
    // f[inv] = número de permutações de N elementos com inv inversões
    // Calcular iterativamente

    // Máximo de inversões possíveis: N*(N-1)/2
    // Mas inv* é pequeno (≤ ~100 para K ≤ 4e18)
    
    int MAX_INV = 300; // suficiente para K ≤ 4e18
    // Verificar: f(N, inv) para N=200000 cresce muito rápido

    // f[n][inv]: DP
    // f[1][0] = 1
    // f[n][inv] = Σ_{r=0}^{min(n-1,inv)} f[n-1][inv-r]
    //           = f[n-1][inv] + f[n-1][inv-1] + ... + f[n-1][max(0,inv-n+1)]
    // Usar prefix sums para eficiência

    // Como inv* ≤ MAX_INV, só precisamos f[n][0..MAX_INV] para cada n
    // Mas n vai até N=2e5 → O(N * MAX_INV) = O(2e5 * 300) = 6e7 → ok

    vector<ull> f(MAX_INV+1, 0);
    f[0] = 1; // f[1][0] = 1, f[1][inv>0] = 0

    // Escalar de n=1 até n=N
    for(ull n = 2; n <= N; n++){
        // f_new[inv] = Σ_{r=0}^{min(n-1,inv)} f[inv-r]
        //            = prefix_f[inv] - prefix_f[max(0,inv-n)]
        // onde prefix_f[i] = Σ_{j=0}^{i} f[j]
        vector<ull> pref(MAX_INV+2, 0);
        for(int i = 0; i <= MAX_INV; i++)
            pref[i+1] = safeAdd(pref[i], f[i]);

        vector<ull> fnew(MAX_INV+1, 0);
        for(int inv = 0; inv <= MAX_INV; inv++){
            // soma f[inv-r] para r=0..min(n-1,inv)
            // = Σ f[j] para j=max(0,inv-(n-1)) .. inv
            int lo = max(0LL, (long long)inv - (long long)(n-1));
            // pref[inv+1] - pref[lo]
            fnew[inv] = pref[inv+1] - pref[lo];
            if(fnew[inv] > CAP) fnew[inv] = CAP;
        }
        f = fnew;
    }

    // Achar inv*: menor inv tal que Σ_{i=0}^{inv} f[i] >= K
    ull cum = 0;
    int inv_star = -1;
    ull K_prime = K; // posição dentro do grupo inv*

    for(int inv = 0; inv <= MAX_INV; inv++){
        ull prev_cum = cum;
        cum = safeAdd(cum, f[inv]);
        if(cum >= K){
            inv_star = inv;
            K_prime = K - prev_cum; // 1-indexed
            break;
        }
    }

    if(inv_star == -1){
        // K > total permutações com ≤ MAX_INV inversões → aumentar MAX_INV
        // Não deveria acontecer para K ≤ 4e18
        cout << -1 << "\n";
        return 0;
    }

    // Construir a K'-ésima permutação (1-indexed) de {1..N} com inv_star inversões
    // Greedy: para cada posição, escolher o menor valor disponível v_j (j-ésimo, 0-indexed)
    // tal que ao escolher j inversões para essa posição:
    //   f_{n-1}[inv_star - j] >= K' (existem permutações suficientes)
    //   onde f_{n-1} é a tabela para n-1 elementos

    // Precisamos reconstruir as tabelas f para n=N-1, N-2, ...
    // Isso requer armazenar todas as tabelas → O(N * MAX_INV) memória = 6e7 ull's = 480MB → muita!

    // Abordagem: recalcular a tabela para n atual a cada passo
    // Mas isso é O(N² * MAX_INV) → TLE

    // Melhor: armazenar todas as tabelas
    // Mas memória é problema.

    // SOLUÇÃO: Observar que durante a construção, n decresce de N para 1.
    // Podemos recalcular a tabela de n para n-1 à medida que construímos.
    // Mas precisamos das tabelas em ordem decrescente (N, N-1, ..., 1).

    // Abordagem: pré-computar e armazenar apenas a tabela atual f[n] e
    // "desescalar" de n para n-1.

    // Desescalar: dado f[n], obter f[n-1]:
    // f[n][inv] = Σ_{r=0}^{min(n-1,inv)} f[n-1][inv-r]
    // f[n-1][inv] = f[n][inv] - f[n-1][inv-n+1] (se inv >= n-1, subtrair o termo extra)
    // Recorrência inversa... complexo.

    // SOLUÇÃO MELHOR: Recalcular do zero para cada posição.
    // A cada posição i (restam n = N-i elementos), precisamos f[n][0..inv_rem].
    // Como inv_rem decresce, e n decresce, podemos manter a tabela.

    // Estratégia: armazenar a tabela f[n] e a cada passo obter f[n-1] via "downscale".

    // Downscale de f[n] para f[n-1]:
    // f[n][inv] = Σ_{r=0}^{min(n-1,inv)} f[n-1][inv-r]
    // = Σ_{j=max(0,inv-n+1)}^{inv} f[n-1][j]
    // Esta é uma relação de convolução. Inverter:
    // f[n-1][inv] = f[n][inv] - f[n-1][inv-n+1] para inv >= n-1
    //             = f[n][inv]                    para inv < n-1
    // Prova: f[n][inv] = f[n-1][inv] + f[n-1][inv-1] + ... + f[n-1][inv-(n-1)]
    //       f[n][inv-1] = f[n-1][inv-1] + ... + f[n-1][inv-n]
    // (se inv >= n): f[n][inv] - f[n][inv-1] = f[n-1][inv] - f[n-1][inv-n]
    // → f[n-1][inv] = f[n][inv] - f[n][inv-1] + f[n-1][inv-n]
    // Esta é uma relação de recorrência para f[n-1] dado f[n].

    // Mas com inversões saturadas (CAP), a aritmética inversa não funciona diretamente!
    // Se f[n][inv] foi saturado em CAP, não podemos recuperar f[n-1][inv].

    // SOLUÇÃO ROBUSTA: Recalcular f[n] do zero para cada n durante a construção.
    // Custo: O(N * MAX_INV) por posição × N posições = O(N² * MAX_INV) → TLE para N=2e5.

    // SOLUÇÃO EFICIENTE FINAL:
    // Observar que durante a construção, inv_rem ≤ inv* ≤ ~100.
    // Para a posição i (restam n=N-i elementos), a tabela f[n][0..inv_rem] é necessária.
    // Como n decresce e inv_rem decresce, podemos manter a tabela "de trás para frente".

    // Calcular e armazenar todas as tabelas antecipadamente:
    // f_tables[n][inv] para n=1..N e inv=0..MAX_INV
    // Memória: N * MAX_INV = 2e5 * 300 = 6e7 ull's = 480MB → não cabe!

    // INSIGHT FINAL: Só precisamos da tabela para n atual.
    // Como n decresce de N para 1, e podemos obter f[n-1] de f[n] via downscale,
    // vamos implementar o downscale (com cuidado para valores saturados).

    // Para downscale, em vez de inverter a convolução (que não funciona com saturação),
    // recalculamos f[n-1] a partir de f[1]:
    // Cada vez que precisamos da tabela para n' < n, reconstruir do zero.
    // Mas isso é O(n * MAX_INV) por passo → O(N² * MAX_INV) → TLE.

    // A SOLUÇÃO CORRETA usa a relação:
    // f[n-1][inv] pode ser obtido de f[n][inv] sem reconstrução do zero,
    // usando a recorrência inversa, MAS apenas se os valores não foram saturados.
    // Se inv_rem ≤ inv* ≤ ~100 e n é grande, f[n][inv] é saturado para quase todo inv.
    // Mas f[n-1][inv] para inv ≤ inv_rem pode não ser saturado!

    // Para inv ≤ inv_rem ≤ ~100 e n grande:
    // f[n][inv] = Σ_{r=0}^{inv} f[n-1][inv-r] (pois n-1 >> inv)
    // f[n-1][inv] = f[n][inv] - f[n][inv-1]  (!)
    // Pois: f[n][inv] - f[n][inv-1] = f[n-1][inv] - f[n-1][inv-n]
    //                               = f[n-1][inv] (pois inv-n < 0 para n > inv)
    // ✓ Esta relação vale quando n > inv!

    // Downscale (válido quando n > inv_rem):
    // f[n-1][0] = f[n][0]
    // f[n-1][inv] = f[n][inv] - f[n][inv-1]  para 1 ≤ inv ≤ inv_rem

    // Quando n ≤ inv_rem, usar relação mais cuidadosa:
    // f[n-1][inv] = f[n][inv] - f[n][inv-1] + f[n-1][inv-n]
    // Mas n ≤ inv_rem ≤ 100, então n é pequeno e recalcular do zero é barato!

    // ALGORITMO COMPLETO:
    // 1. Escalar de n=1 a n=N para obter f[N] → já feito
    // 2. Durante construção (n de N a 1):
    //    a. Se n > inv_rem: downscale simples f[n-1][inv] = f[n][inv] - f[n][inv-1]
    //    b. Se n ≤ inv_rem (≤ 100): recalcular f[n-1] do zero em O(n * inv_rem) = O(100²) = 10⁴

    int inv_rem = inv_star;
    // f agora tem f[N]

    // Construção da permutação
    // Usar BIT/Fenwick para encontrar o j-ésimo elemento disponível
    // Elementos disponíveis: {1, 2, ..., N} inicialmente

    // Fenwick Tree para ordem estatística
    vector<int> bit(N+2, 0);
    auto bit_update = [&](int i, int val){
        for(; i <= (int)N; i += i&(-i)) bit[i] += val;
    };
    auto bit_query = [&](int i) -> int {
        int s=0; for(;i>0;i-=i&(-i)) s+=bit[i]; return s;
    };
    auto kth = [&](int k) -> int { // 1-indexed k
        int lo=1, hi=(int)N;
        while(lo<hi){
            int mid=(lo+hi)/2;
            if(bit_query(mid)>=k) hi=mid;
            else lo=mid+1;
        }
        return lo;
    };

    for(int i=1;i<=(int)N;i++) bit_update(i,1);

    vector<int> perm;
    ull cur_inv_rem = inv_rem;
    ull K_cur = K_prime; // 1-indexed

    // f atualmente é f[N]
    // n = N (elementos restantes)
    ull n = N;

    for(ull pos = 0; pos < N; pos++){
        // Escolher o j-ésimo elemento disponível (0-indexed j)
        // j contribui j inversões
        // Precisamos da tabela f[n-1]

        // Downscale f[n] → f[n-1]
        if(n > 1){
            if(n-1 > (ull)MAX_INV){
                // n-1 > inv_rem → downscale simples
                // f[n-1][inv] = f[n][inv] - f[n][inv-1]
                vector<ull> fnew(MAX_INV+1, 0);
                fnew[0] = f[0];
                for(int inv=1;inv<=MAX_INV;inv++)
                    fnew[inv] = (f[inv] >= f[inv-1]) ? f[inv]-f[inv-1] : 0;
                f = fnew;
            } else {
                // n-1 ≤ MAX_INV → recalcular do zero
                vector<ull> f2(MAX_INV+1, 0);
                f2[0] = 1;
                for(ull nn=2;nn<=n-1;nn++){
                    vector<ull> pref(MAX_INV+2,0);
                    for(int i=0;i<=MAX_INV;i++) pref[i+1]=safeAdd(pref[i],f2[i]);
                    vector<ull> fnew(MAX_INV+1,0);
                    for(int inv=0;inv<=MAX_INV;inv++){
                        int lo2=max(0LL,(long long)inv-(long long)(nn-1));
                        fnew[inv]=pref[inv+1]-pref[lo2];
                        if(fnew[inv]>CAP) fnew[inv]=CAP;
                    }
                    f2=fnew;
                }
                f=f2;
            }
        }
        n--;

        // Agora f = f[n] (n elementos restantes)
        // Escolher j (0-indexed) mínimo tal que:
        // Σ_{r=0}^{j-1} f[cur_inv_rem - r] < K_cur ≤ Σ_{r=0}^{j} f[cur_inv_rem - r]
        // (com f[<0] = 0)

        ull cum2 = 0;
        int j = 0;
        for(j = 0; j <= (int)cur_inv_rem; j++){
            ull cnt_j = (cur_inv_rem - j >= 0) ? f[cur_inv_rem - j] : 0;
            if(safeAdd(cum2, cnt_j) >= K_cur) break;
            cum2 = safeAdd(cum2, cnt_j);
        }
        K_cur -= cum2;
        cur_inv_rem -= j;

        // j-ésimo menor disponível
        int val = kth(j+1);
        perm.push_back(val);
        bit_update(val, -1);
    }

    for(int i=0;i<(int)N;i++){
        if(i) cout<<" ";
        cout<<perm[i];
    }
    cout<<"\n";
    return 0;
}
