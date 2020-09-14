#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

struct T_node{
    vector <pair<int, int> > way;
    vector <int> arrow;
    int exi = 1;
};

int main(){
    string s;
    getline(cin, s);
    vector <char> letters;
    vector <vector <pair<int, int> > > words;
    int k = 1;
    while(true){
        if(s[k] == ' ') break;
        letters.push_back(s[k]);
        k += 3;
    };
    k++;
    words.push_back({});
    while(true){
        if(s[k] == '>') break;
        if(s[k] == ','){
            k += 2;
            words.push_back({});
        };
        if(s[k] == '^'){
            k += 5;
            words[words.size() - 1][words[words.size() - 1].size() - 1].second = -1;
            continue;
        };
        int t = 0;
        while(letters[t] != s[k]) t++;
        words[words.size() - 1].push_back({t, 1});
        k++;
    };
    int ws = words.size();
    for(int i = 0; i < ws; i++){
        words.push_back(words[i]);
        for(int j = words[i].size() - 1; j + 1; j--){
            words[words.size() - 1][words[i].size() - 1 - j].first = words[i][j].first;
            words[words.size() - 1][words[i].size() - 1 - j].second = -words[i][j].second;
        };
    };
    srand(time(0));
    vector <T_node> arr(1);
    arr[0].way = {};
    arr[0].arrow = {};
    int bgn = 0;
    int count;
    cin >> count;
    for(int j = 0; j < count; j++){
        int fin = arr.size();
        for(int ij = bgn; ij < fin; ij++){
            for(int ii = 0; ii < letters.size(); ii++){
                if(arr[ij].way.size() && arr[ij].way[arr[ij].way.size() - 1] == pair<int, int>(ii, -1)) continue;
                int flag = 0;
                vector <pair<int, int> > cop = arr[ij].way;
                cop.push_back({ii, 1});
                if(arr[ij].way.size() && arr[ij].way[arr[ij].way.size() - 1] == pair<int, int>(ii, -1)){
                    cop.pop_back();
                    cop.pop_back();
                };
                for(int jj = 0; jj < words.size(); jj++) if(cop == words[jj]){
                    if(ij != 0){
                        arr[ij].arrow.push_back(0);
                        arr[0].arrow.push_back(ij);
                    };
                    flag = 1;
                    break;
                };
                if(flag) continue;
                for(int jj = 1; jj < arr.size(); jj++){
                    vector <pair<int, int> > copy = arr[ij].way;
                    if(arr[jj].way[arr[jj].way.size() - 1] == pair<int, int>(ii, 1)) copy.push_back({ii, 1});
                    for(int ji = arr[jj].way.size() - 2; ji + 1; ji--) copy.push_back({arr[jj].way[ji].first, -arr[jj].way[ji].second});
                    for(int ji = 0; ji < words.size(); ji++) if(copy == words[ji]){
                        flag = 1;
                        if(ij != jj){
                            arr[ij].arrow.push_back(jj);
                            arr[jj].arrow.push_back(ij);
                        };
                        break;
                    };
                    if(flag) break;
                };
                if(flag) continue;
                arr.push_back(arr[ij]);
                arr[arr.size() - 1].way.push_back({ii, 1});
                arr[arr.size() - 1].arrow.clear();
                arr[arr.size() - 1].arrow.push_back(ij);
                arr[ij].arrow.push_back(arr.size() - 1);
            };
        };
        bgn = fin;
    };
    while(true){
        int flag = 1;
        for(int i = 0; i < arr.size(); i++) if(arr[i].exi) if(arr[i].arrow.size() == 1){
            flag = 0;
            arr[i].exi = 0;
            int ttemp = 0;
            while(arr[arr[i].arrow[0]].arrow[ttemp] != i) ttemp++;
            arr[arr[i].arrow[0]].arrow[ttemp] = arr[arr[i].arrow[0]].arrow[arr[arr[i].arrow[0]].arrow.size() - 1];
            arr[arr[i].arrow[0]].arrow.pop_back();
        };
        if(flag) break;
    };
    cout << "digraph G {" << endl;
    cout << "node [shape=\"point\"];" << endl;
    for(int i = 0; i < arr.size(); i++) if(arr[i].arrow.size() != 1){
        string nam = "";
        for(int j = 0; j < arr[i].way.size(); j++){
            nam += letters[arr[i].way[j].first];
            if(arr[i].way[j].second == -1) nam += "^(-1)";
        };
        cout << "V" << i << " [label=\"" << nam << "\"];" << endl;
    };
    for(int i = 0; i < arr.size(); i++) if(arr[i].arrow.size() != 1) for(int j = 0; j < arr[i].arrow.size(); j++) if(arr[arr[i].arrow[j]].arrow.size() != 1){
        if(arr[i].way.size() < arr[arr[i].arrow[j]].way.size() && arr[arr[i].arrow[j]].way[arr[arr[i].arrow[j]].way.size() - 1].second == 1){
            cout << "V" << i << " -> V" << arr[i].arrow[j] << " [label=\"" << letters[arr[arr[i].arrow[j]].way[arr[arr[i].arrow[j]].way.size() - 1].first] << "\"];" << endl;
        };
        if(arr[i].way.size() < arr[arr[i].arrow[j]].way.size() && arr[arr[i].arrow[j]].way[arr[arr[i].arrow[j]].way.size() - 1].second == -1){
            cout << "V" << arr[i].arrow[j] << " -> V" << i << " [label=\"" << letters[arr[arr[i].arrow[j]].way[arr[arr[i].arrow[j]].way.size() - 1].first] << "\"];" << endl;
        };
    };
    cout << "}";
    return 0;
};
