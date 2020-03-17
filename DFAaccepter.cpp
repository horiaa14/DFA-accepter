#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<unordered_map>
#include<cstdlib>
#define MAX_VERTICES 10000 // numarul maxim de stari
#define SIGMA 300 // lungimea alfabetului
#define MAX_WORDS 1000 // numarul maxim de cuvinte testate
using namespace std;

vector<pair<int, char>> g[MAX_VERTICES];
string P[MAX_WORDS];
set<char> alphabet;
bool isFinal[MAX_VERTICES];
int n, m, start, k, l;

void readAutomata() {
    char ch;
    int x, y;
    cout << "Introduceti numarul de stari : ";
    cin >> n;
    cout << "Introduceti numarul de caractere din alfabet : ";
    cin >> m;
    cout << "Introduceti cele " << m << " caractere ale alfabetului : ";
    for(int i = 0; i < m; ++i) {
        cin >> ch;
        alphabet.insert(ch);
    }
    cout << "Starea initiala este : ";
    cin >> start;
    cout << "Numarul de starti finale este : ";
    cin >> k;
    cout << "Cele " << k << " stari finale sunt : ";
    for(int i = 0; i < k; ++i) {
        cin >> x;
        isFinal[x] = true;
    }
    cout << "Numarul de tranzitii este : ";
    cin >> l;
    cout << "Introduceti cele " << l << " tranzitii : ";
    for(int i = 0; i < l; ++i) {
        cin >> x >> ch >> y;
        if(x < 0 || x > n - 1 || y < 0 || y > n - 1) {
            cout << "Incercati sa introduceti o muchie invalida!!!\n";
            exit(1);
        }
        if(alphabet.find(ch) != alphabet.end())
            g[x].push_back(make_pair(y, ch));
        else {
            cout << "Caracterul introdus nu exista in alfabet!!!\n";
            exit(1);
        }
    }
}

bool evaluate(string word) {
    int len = word.size();
    int currentNode, nextNode;
    vector<pair<int, char> >::iterator it;
    currentNode = start;
    for(int i = 0; i < len; ++i) {
        nextNode = -1;
        for(it = g[currentNode].begin(); it != g[currentNode].end() && nextNode == -1; ++it) {
            if((*it).second == word[i]) // exista o muchie etichetata cu caracterul word[i]
                nextNode = (*it).first; // setez urmatorul nod din parcurgere
        }
        if(nextNode == -1) // daca nu exista muchii care sa contina caracterul word[i]
            return false; // returnam false
        else currentNode = nextNode; // altfel continuam parcurgerea
    }
    if(isFinal[currentNode]) // la final verificam daca ne aflam intr-o stare finala
        return true;
    return false;
}

int main() {
    unordered_map<bool, string> umap;
    umap[0] = "FALSE";
    umap[1] = "TRUE";
    int nrwords;
    readAutomata();
    cout << "Introduceti numarul de cuvinte : ";
    cin >> nrwords;
    cout << "Introduceti cele " << nrwords << " cuvinte :\n";
    for(int i = 0; i < nrwords; ++i)
        cin >> P[i];
    for(int i = 0; i < nrwords; ++i) {
        cout << P[i] << " " << umap[evaluate(P[i])] << "\n";
    }
    return 0;
}
