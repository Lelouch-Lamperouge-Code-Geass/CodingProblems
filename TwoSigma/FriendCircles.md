There are N students in a class. Some of them are friends, while some are not. Their friendship is transitive in nature. For example, if A is a direct friend of B, and B is a direct friend of C, then A is an indirect friend of C. And we defined a friend circle is a group of students who are direct or indirect friends.

Given a N*N matrix M representing the friend relationship between students in the class. If M[i][j] = 1, then the ith and jth students are direct friends with each other, otherwise not. And you have to output the total number of friend circles among all the students.

##### Example 1:

```
Input: 
[[1,1,0],
 [1,1,0],
 [0,0,1]]
Output: 2
Explanation:The 0th and 1st students are direct friends, so they are in a friend circle. 
The 2nd student himself is in a friend circle. So return 2.
```

##### Example 2:

```
Input: 
[[1,1,0],
 [1,1,1],
 [0,1,1]]
Output: 1
Explanation:The 0th and 1st students are direct friends, the 1st and 2nd students are direct friends, 
so the 0th and 2nd students are indirect friends. All of them are in the same friend circle, so return 1.
```

##### Note:

* N is in range [1,200].  
* M[i][i] = 1 for all students.  
* If M[i][j] = 1, then M[j][i] = 1.  

# Solution

### BFS

```cpp
class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        if (M.empty()) return 0;
        const std::size_t n(M.size());
        int reval(0);
        for (std::size_t i = 0; i < n; ++i) {
            if (M[i][i] == 1) { // Not visited
                bfs(M, i);
                ++ reval;
            }
        }
        return reval;
    }
private:
    void bfs(vector<vector<int>>& M, int start) {
        const std::size_t n(M.size());
        queue<int> bfs_queue;
        bfs_queue.push(start);
        while (!bfs_queue.empty()) {
            int curr = bfs_queue.front();
            bfs_queue.pop();
            M[curr][curr] = 0;
            for (int i = 0; i < n; ++i) {
                if (i!= curr && M[curr][i] == 1) {
                    bfs_queue.push(i);
                    M[curr][i] = 0;
                }
            }
        }
    }
};
```

### DFS

```cpp
class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        if (M.empty()) return 0;
        const std::size_t n(M.size());
        int reval(0);
        for (std::size_t i = 0; i < n; ++i) {
            if (M[i][i] == 1) { // Not visited
                dfs(M,i);
                ++ reval;
            }
        }
        return reval;
    }
private:
    void dfs(vector<vector<int>>& M, int i) {
        const std::size_t n(M.size());
        M[i][i] = 0;
        for (std::size_t j = 0; j < n; ++j) {
            if (M[i][j] == 1) {
                M[i][j] = 0;
                M[j][i] = 0;
                dfs(M, j);
            }
        }
    }
};
```

We can use a visited vector to improve the performance.

```cpp
class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        if (M.empty()) return 0;
        const std::size_t n(M.size());
        int reval(0);
        vector<bool> visited(n, false);
        for (std::size_t i = 0; i < n; ++i) {
            if (M[i][i] == 1) {
                dfs(M,visited, i);
                ++ reval;
            }
        }
        return reval;
    }
private:
    void dfs(vector<vector<int>>& M, vector<bool> &visited, int i) {
        if (visited[i]) return;
        const std::size_t n(M.size());
        visited[i] = true;
        M[i][i] = 0;
        for (std::size_t j = 0; j < n; ++j) {
            if (M[i][j] == 1) {
                M[i][j] = 0;
                M[j][i] = 0;
                dfs(M, visited, j);
            }
        }
    }
};
```

### Union-Find

```cpp
class Solution {

private:
    class UnionFind {
      public:
        UnionFind(std::size_t n) : m_count(n), m_parent(n, 0), m_rank(n, 0) {
            for (std::size_t i = 0; i < n; ++i) {
                m_parent[i] = i;
            }
        }
        
        std::size_t Find(std::size_t i) {
            while (m_parent[i] != i) {
                i = m_parent[i] = m_parent[m_parent[i]]; // Path compression by halving
            }
            return i;
        }
        
        std::size_t Count() {
            return m_count;
        }
        
        void Union(std::size_t i, std::size_t j) {
            std::size_t i_root = Find(i), j_root = Find(j);
            if (i_root != j_root) {
                if (m_rank[i_root] > m_rank[j_root]) {
                    m_parent[j_root] = i_root;
                } else {
                    m_parent[i_root] = j_root;
                    if (m_rank[i_root] == m_rank[j_root]) {
                        ++ m_rank[j_root];
                    }
                }
                -- m_count;
            }
        }
      private:
        vector<std::size_t> m_parent;
        vector<std::size_t> m_rank;
        std::size_t m_count;
    };
    
public:
    int findCircleNum(vector<vector<int>>& M) {
        if (M.empty()) return 0;
        const std::size_t n(M.size());
        UnionFind uf(n);
        for (int i = 0; i + 1 < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (M[i][j] == 1) uf.Union(i, j);
            }
        }
        return uf.Count();
    }
};
```
