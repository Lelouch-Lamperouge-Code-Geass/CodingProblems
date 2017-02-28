// https://segmentfault.com/a/1190000003819277#
/***
 ***/
class Solution {
public:
  void gameOfLife(vector<vector<int>>& board) {
    if (board.empty()) return;
    const std::size_t row_size(board.size()), col_size(board[0].size());
    for (std::size_t i = 0; i < row_size; ++i) {
      for (std::size_t j = 0; j < col_size; ++j) {
        int live(0);
        std::size_t min_row = (i > 0 ? i - 1 : 0);
        std::size_t min_col = (j > 0 ? j - 1 : 0);
        std::size_t max_row = (i + 1 < row_size ? i + 1 : i);
        std::size_t max_col = (j + 1 < col_size ? j + 1 : j);
        for (std::size_t p = min_row; p <= max_row; ++p) {
          for (std::size_t q = min_col; q <= max_col; ++q) {
            if (p == i && q == j) continue;
            live += board[p][q] & 1;
          }
        }

        if (live == 3 || (live == 2 && board[i][j] == 1) ) {
          board[i][j] |= 2;
        }

      }
    }

    for (std::size_t i = 0; i < row_size; ++i) {
      for (std::size_t j = 0; j < col_size; ++j) {
        board[i][j] >>= 1;
      }
    }
  }
};


// 如果循环矩阵如何解决？循环的意思是假设一个3x3的矩阵,则a[0][0]的左边是a[0][1]，其左上是a[2][2]
// 这样我们的坐标要多加一个数组长度，使用坐标时还要取模


class Solution {
public:
  void gameOfLife(vector<vector<int>>& board) {
    if (board.empty()) return;
    const std::size_t row_size(board.size()), col_size(board[0].size());
    for (std::size_t i = 0; i < row_size; ++i) {
      for (std::size_t j = 0; j < col_size; ++j) {
        int live(0);
        // 多加一个数组长度
        std::size_t min_row = row_size + i - 1;
        std::size_t min_col = col_size + j - 1;
        std::size_t max_row = row_size + i + 1;
        std::size_t max_col = col_size + j + 1;
        for (std::size_t p = min_row; p <= max_row; ++p) {
          for (std::size_t q = min_col; q <= max_col; ++q) {
            if (p == i && q == j) continue;
            // 使用的时候要取模
            live += board[p % row_size][q % col_size] & 1;
          }
        }

        if (live == 3 || (live == 2 && board[i][j] == 1) ) {
          board[i][j] |= 2;
        }

      }
    }

    for (std::size_t i = 0; i < row_size; ++i) {
      for (std::size_t j = 0; j < col_size; ++j) {
        board[i][j] >>= 1;
      }
    }
  }
};

/***
In principle, the Life field is infinite, but computers have finite memory. 
This leads to problems when the active area encroaches on the border of the array. 
Programmers have used several strategies to address these problems. 
The simplest strategy is simply to assume that every cell outside the array is dead. 
This is easy to program, but leads to inaccurate results when the active area crosses the boundary. 
A more sophisticated trick is to consider the left and right edges of the field to be stitched together, 
and the top and bottom edges also, yielding a toroidal array. 
The result is that active areas that move across a field edge reappear at the opposite edge. 
Inaccuracy can still result if the pattern grows too large, but at least there are no pathological edge effects. 
Techniques of dynamic storage allocation may also be used, creating ever-larger arrays to hold growing patterns.
Alternatively, the programmer may abandon the notion of representing the Life field with a 2-dimensional array, 
and use a different data structure, like a vector of coordinate pairs representing live cells. 
This approach allows the pattern to move about the field unhindered, 
as long as the population does not exceed the size of the live-coordinate array. 
The drawback is that counting live neighbours becomes a hash-table lookup or search operation, 
slowing down simulation speed. With more sophisticated data structures this problem can also be largely solved.
***/

typedef std::unordered_map<std::size_t, std::unordered_map<std::size_t,std::size_t> > LiveMapper;

class Solution {
public:
  LiveMapper GameOfLife(LiveMapper & live) {
    LiveMapper neighbors;
    for (auto outer_pair : live) {
      std::size_t row = outer_pair.first;
      for (auto inner_pair : live[row]) {
        std::size_t col = inner_pair.first;

        std::size_t start_row = row > 0 ? row - 1 : 0 ;
        std::size_t end_row =  row + 1;
        std::size_t start_col =  col > 0 ? col - 1 : 0 ;
        std::size_t end_col =  col + 1;

        // Increase count of all its neighbors
        for (std::size_t i = start_row; i <= end_row; ++i) {
          for (std::size_t j = start_col; j <= end_col; ++j) {
            if (i == row && j == col) {
              continue;
            } else {
              ++ neighbors[i][j];
            }
          }
        }
      }
    }

    LiveMapper new_live;
    for (auto outer_pair : neighbors) {
      std::size_t row = outer_pair.first;
      for (auto inner_pair : neighbors[row]) {
        std::size_t col = inner_pair.first;
        std::size_t count = inner_pair.second;
        if (count == 3 || (count == 2 && live.count(row)!=0 && live[row].count(col)!=0)) {
          ++ new_live[row][col];
        }
      }
    }
    return new_live;
  }

  void gameOfLife(vector<vector<int>>& board) {
    if (board.empty()) return;
    LiveMapper live;
    const std::size_t row_size(board.size()), col_size(board[0].size());
    for (std::size_t i = 0; i < row_size; ++i) {
      for (std::size_t j = 0; j < col_size; ++j) {
        if (board[i][j] == 1) {
          ++ live[i][j];
        }
      }
    }

    live = GameOfLife(live);

    for (std::size_t i = 0; i < row_size; ++i) {
      for (std::size_t j = 0; j < col_size; ++j) {
        if (live.count(i) && live[i].count(j)) {
          board[i][j] = 1;
        } else {
          board[i][j] = 0;
        }
      }
    }
  }
};
