// URL: https://www.hackerrank.com/contests/juniper-hackathon/challenges/friend-circles
/* Solution 1 with union find*/
class UnionFind {
  public:
    UnionFind(const int n):m_people_count(n),m_union_count(n),m_ids(n,0){
        for (int i=0;i<n;++i) m_ids[i] = i;
    }
    bool IsConnected(int i, int j) {
        return m_ids[i]==m_ids[j];
    }
    // If two nodes are in different disjoint-set, union their set together.
	// Here we go through all the nodes, if any node's id is the same as node2,
	// which means it is at the same disjoint-set with node2, we reset its id value
	// to be the same as node1.
    void Connect(int ppl1,int ppl2){
        int id1 = m_ids[ppl1], id2 = m_ids[ppl2];
        if (id1!=id2) {
            for (int i=0;i<m_people_count;++i) {
                if (m_ids[i]==m_ids[ppl2]) m_ids[i] = m_ids[ppl1];
            }
            -- m_union_count;
        }
    }
    int GetUnionCount() {
        return m_union_count;
    }
  private:
    int m_people_count;
    int m_union_count;
    vector<int> m_ids; 
};

int FriendCircles(vector<string> friends) {
    if (friends.empty()) return 0;
    const int n_size(friends.size());
    UnionFind union_finder(n_size);

    for (int i=0;i<n_size;++i) {
        for (int j=i;j<n_size;++j) {
            if (friends[i][j]=='Y' && !union_finder.IsConnected(i,j)) {
                union_finder.Connect(i,j);
            }
        }
    }
    return union_finder.GetUnionCount();
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

/* Solution 3 : DFS */
void dfs(vector<string> & friends, int row, int col) {
    const int n_size(friends.size());
    if (row<0||col<0||row>=n_size||col>=n_size || friends[row][col]=='N') 
        return;
    friends[row][col]=friends[col][row]='N';
    dfs(friends,row-1,col);
    dfs(friends,row+1,col);
    dfs(friends,row,col-1);
    dfs(friends,row,col+1);
}

int FriendCircles(vector<string> friends) {
    if (friends.empty()) return 0;
    const int n_size(friends.size());
    int reval(0);
    for (int i=0;i<n_size;++i) {
        for (int j=i;j<n_size;++j) {
            if (friends[i][j]=='Y') {
                dfs(friends,i,j);
                ++ reval;
            }
        }
    }
    return reval;
}
/* Main function*/
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
