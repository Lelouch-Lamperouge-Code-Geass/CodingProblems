Given a ```M * N``` maze, which only contains 0 and 1. 

0 means you can pass the cell, 1 means you can't.

Write an algorithm to find the minimal steps from one position to another position.

If no path exists, return -1.


# Solution

```cpp
int getMinStep(const vector<vector<int>> &matrix, 
				 const pair<int, int> &start_pos,
				 const pair<int,int> &end_pos) {
        if (matrix.empty()) return 0;
        if (start_pos == end_pos) return 0;

        const int row_size = matrix.size(), col_size = matrix[0].size();
        vector<vector<bool>> visited(row_size, vector<bool>(col_size,false));

        queue<pair<int, int>> bfs_queue;

        visited[start_pos.first][start_pos.second] = true;
        bfs_queue.push(start_pos);

        int min_step(0);
        static vector<pair<int, int>> moves = {{1,0}, {-1, 0}, {0, 1}, {0,-1}};
        while (!bfs_queue.empty()) {
            const int cur_queue_size = bfs_queue.size();
            ++min_step;

            for (int i = 0; i < cur_queue_size; ++i) {
                pair<int, int> cur_pos = bfs_queue.front();
                bfs_queue.pop();

                for (const pair<int, int> &move : moves) {
                    int next_row = cur_pos.first + move.first;
                    int next_col = cur_pos.second + move.second;
                    if (next_row < 0 || next_row >= row_size
                        || next_col < 0 || next_col >= col_size) continue; // invalid range
                    if (matrix[next_row][next_col] == 1) continue; // can't pass
                    if (visited[next_row][next_col]) continue; // visited

                    if (next_row == end_pos.first && next_col == end_pos.second) {
                        return min_step;
                    }

                    visited[next_row][next_col] = true;
                    bfs_queue.push(make_pair(next_row, next_col));
                }
            }
        }
        return -1;
    }
    ```
