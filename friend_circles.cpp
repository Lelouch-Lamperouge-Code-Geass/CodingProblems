// URL: https://www.hackerrank.com/contests/juniper-hackathon/challenges/friend-circles
/* Solution 1 with union find*/
class UnionFind {
public:
	UnionFind(int n) :m_num(n),m_ids(n,-1),m_count(n){
		for (int i=0;i<m_num;++i) {
			m_ids[i] = i;
		}
	}
	bool is_connected(int node1, int node2) {return m_ids[node1] == m_ids[node2];}
	int find(int node) {return m_ids[node];}
	int get_count() {return m_count;}
	// If two nodes are in different disjoint-set, union their set together.
	// Here we go through all the nodes, if any node's id is the same as node2,
	// which means it is at the same disjoint-set with node2, we reset its id value
	// to be the same as node1.
	void union_set(int node1,int node2) {
		const int id1 = m_ids[node1], id2 = m_ids[node2];
		if (id1 != id2) {
			for (int i=0;i<m_num;++i) {
				if (m_ids[i] == id2) m_ids[i] = id1;
			}
			-- m_count;
		}
	}
private:
	int m_num; // how many nodes in total
	int m_count; // how many disjoint-set 
	vector<int> m_ids; // ID of each node,ID is the representative of each disjoint-set
};
int friend_circle(vector<string>  friends){
	const int n(friends.size());
	UnionFind uf(n);
	for (int i=0;i<n;++i) {
		for (int j=0;j<n;++j) {
			if (friends[i][j]=='Y' && !uf.is_connected(i,j)) {
				uf.union_set(i,j);
			}
		}
	}
	return uf.get_count();
}

/* Solution 2 with BFS*/

int friend_circle(vector<string>  friends){
	const int n(friends.size());
	vector<bool> visited(n,false);
	queue<int> bfs_queue;
	bfs_queue.push(0);
	visited[0] = true;
	int reval(1);
	while( !bfs_queue.empty() ) {
		const int i = bfs_queue.front();
		for (int j=0;j<n;++j) {
			if (i!=j && friends[i][j]=='Y') {
				friends[i][j] = friends[j][i] = 'N';
				if(!visited[j]) { visited[j] = true; bfs_queue.push(j);}
			}
		}
		bfs_queue.pop();

		if(bfs_queue.empty()) {
			auto iter = std::find(visited.begin(),visited.end(),false);
			if (iter!=visited.end()) {
				int index = iter-visited.begin();
				bfs_queue.push(index);
				visited[index] = true;
				++ reval; // new connected components
			}
		}
	}
	return reval;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int num;
    cin >> num;
    vector<string>  friends;
    string input_line;
    for (int i=0;i<num && cin;++i) {
        cin >> input_line;
        friends.push_back(input_line);
    };
    cout << friend_circle(friends) << endl;
    return 0;
}
