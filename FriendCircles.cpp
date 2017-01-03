// URL: https://www.hackerrank.com/contests/juniper-hackathon/challenges/friend-circles
/* Solution 1 with union find*/
// http://www.1point3acres.com/bbs/thread-135529-1-1.html
class UnionFind {
public:
  UnionFind(const int num)
    :m_union_count(num),m_ids(num,0){
    for (int i=0;i<num;++i) {
      m_ids[i] = i;
    }
  }
  // Determine which subset a particular element is in
  int Find(int i) {
    return m_ids[i];
  }
  bool IsConnected(int i, int j){
    return Find(i) == Find(j);
  }
  // Join two subsets into a single subset.
  void Union(int i, int j){
    int i_id = Find(i), j_id = Find(j);
    if (i_id!=j_id) {
      for (int k=0;k<m_ids.size();++k) {
        if (m_ids[k]==j_id) m_ids[k] = i_id;
      }
      -- m_union_count;
    }
  }
  int GetUnionCount() { return m_union_count;}
private:
  std::vector<int> m_ids;
  int m_union_count;
};

int FriendCirclesCount(std::vector<std::string> & friends) {
  if (friends.empty()) return 0;
  int friends_size(friends.size());
  UnionFind union_find(friends_size);
  for (int i=0;i<friends_size;++i) {
    for (int j=0;j<friends_size;++j) {
      if (friends[i][j]=='Y' && !union_find.IsConnected(i,j)){
        union_find.Union(i,j);
      }
    }
  }
  return union_find.GetUnionCount();
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
