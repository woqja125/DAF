#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <tuple>
#include <cstring>
#include <cassert>

using namespace std;

const int N = 3112, M = 400;
vector<int> de[N], e[M], r;
int dc[N], c[M], w[M], v[M];

void read_data_graph(ifstream &fin){
	char dumc;
	int dumi;
	fin >> dumc >> dumi >> dumi;
	
	while(true){
		char typ;
		fin >> typ;
		if(fin.eof()) break;
		
		if(typ == 'v'){
			int x, y;
			fin >> x >> y;
			dc[x] = y;
		}
		else {
			int x, y;
			fin >> x >> y >> dumi;
			de[x].push_back(y);
			de[y].push_back(x);
		}
	}
}

void init(){
	for(int i = 0; i < M; i++) e[i].clear();
	r.clear();
	fill(v, v + M, 0);
	fill(w, w + M, 0);
}

void read_query_graph(ifstream &fin){
	char dumc;
	int dumi;
	fin >> dumc >> dumi >> dumi >> dumi;

	for(int i = 0; i < M; i++){
		int cur_deg;
		fin >> dumi >> c[i] >> cur_deg;
		while(cur_deg--){
			int x;
			fin >> x;
			e[i].push_back(x);
		}
	}
}

void calc_weight(){
	for(int i = 0; i < M; i++) w[i] = e[i].size();
}

void greedy_bfs(){
	int st = 0;
	for(int i = 1; i < M; i++) if(w[st] < w[i]) st = i;

	priority_queue<pair<int, int>> pq;
	v[st] = 1;
	pq.emplace(w[st], st);

	while(!pq.empty()){
		int cur;
		tie(ignore, cur) = pq.top();
		pq.pop();
		r.push_back(cur);

		for(int nxt : e[cur]){
			if(v[nxt]) continue;
			v[nxt] = 1;
			pq.emplace(w[nxt], nxt);
		}
	}
}

void print(){
	for(int i = 0; i < M; i++) cout << r[i] << " \n"[i == M-1];
}

void build_query_graph(ifstream &fin){
	init();
	read_query_graph(fin);

	calc_weight();
	greedy_bfs();
	
	print();
}
int main(int argc, char *argv[]){
	if(argc != 4) {
    cout << "Usage: ./program dataFile queryFile numQuery" << endl;
    return -1;
  }

	ifstream data_in(argv[1]);
	ifstream qry_in(argv[2]);
	int qry_n = atoi(argv[3]);

	read_data_graph(data_in);
	for(int i = 0; i < qry_n; i++) build_query_graph(qry_in);

	data_in.close();
	qry_in.close();

	return 0;
}