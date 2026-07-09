#include <bits/stdc++.h>
using namespace std;

int main() {
    bool present[5] = {false,false,false,false,false};
    for (int i = 0; i < 10; i++) {
        int d;
        scanf("%d", &d);
        present[d] = true;
    }
    int missing = 0;
    for (int lvl = 1; lvl <= 4; lvl++) {
        if (!present[lvl]) missing++;
    }
    printf("%d\n", missing);
    return 0;
}
