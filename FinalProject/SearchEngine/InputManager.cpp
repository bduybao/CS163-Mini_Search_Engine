#include"Trie.h"
#include"Tool.h"
#include"InputManager.h"

#include<string>
#include<queue>
#include<fstream>
#include<unordered_map>
#include<iostream>
#include<algorithm>
#include<sstream>
#include<queue>

vector<string> SenFilter(string sen) {
    vector<string> v;
    string word;
    for (int i = 0; i < sen.length(); i++) {
        if (sen[i] == ' ') {
            v.push_back(word);
            word = "";
        }
        else {
            word = word + sen[i];
        }
    }
    return v;
}

void InputFile(string filename, unordered_map<string, Trie>& data){
    ifstream in;
    in.open("dataset\\" + filename);
    string sen;
    int place = 1;
    if(in.is_open()){
        while(!in.eof()){
            getline(in ,sen);
            vector<string> v = SenFilter(sen);
            if(!data[filename].root) data[filename].root = getNode();
            for (int i = 0; i < v.size(); i++) {
                //cout << v[i];
                insert(data[filename].root, v[i], place, false);
                ++place;
            }
               
        }
    }
    in.close();
}

void InputListFile(string filename, unordered_map<string, Trie> &data){
    ifstream fin;
    fin.open(filename);

    string line;
    int n = 0;
    if(fin.is_open()){
        while (n < 1001) {
            getline(fin, line);
            InputFile(line, data);
            n++;
        }
    }
    else {
        cout << "Cant open file";
    }
    fin.close();

}

void OuputResult(unordered_map<string, Trie> data) {
    int n = 1;
    priority_queue<pair<string, Trie>, vector<pair<string, Trie>>, cmp> pq;
    
    for (auto it : data) {
        pq.push(it);
    }
    cout << "Top 5 results: \n" << endl;
    while (!pq.empty() /*&& n != 6*/) {
        cout << "[" << n << "] " << pq.top().first << endl;
        pq.pop();
        //n++;
    }
}

void destructor(unordered_map<string, Trie>& data) {
    for (auto it : data) {
        deleteTrie(it.second.root);
    }
}