// https://segmentfault.com/a/1190000003819277

/*

In Conway's Game of Life, cells in a grid are used to simulate biological
cells. Each cell is considered to be either alive or dead. At each step of the
simulation each cell's current status and number of living neighbors is used to
determine the status of the cell during the following step of the
simulation.

In this one-dimensional version, there are N cells numbered 0
through N-1. The number of cells does not change at any point in the simulation.
Each cell i is adjacent to cells i-1 and i+1. Here, the indices are taken modulo
N meaning cells 0 and N-1 are also adjacent to eachother. At each step of the
simulation, cells with exactly one living neighbor change their status (alive
cells become dead, dead cells become alive).

For example, if we represent dead cells with a '0' and living cells with a '1', 
consider the state with 8 cells: 01100101 Cells 0 and 6 have two living neighbors. 
Cells 1, 2, 3, and 4 have one living neighbor. Cells 5 and 7 have no living neighbors. 
Thus, at the next step of the simulation, the state would be: 00011101
*/

#include <vector>
#include <cassert>
#include <iostream>
#include <sstream>

void OneDimensionGameOfLife(std::vector<int> & board) {
  const int board_size(board.size());
  for (int i=0;i<board_size;++i) {
    int left = (i==0? board_size-1 : i-1);
    int right = (i==board_size-1? 0 : i+1);
    if ( (board[left]&1) + (board[right]&1) == 1) board[i] += ((board[i]^1) << 1);
    else board[i] += (board[i]<<1);
  }

  for (int & cell : board) {
    cell >>= 1;
  }
}

void UnitTest_OneDimensionGameOfLife() {
  int arr[] = {0,1,1,0,0,1,0,1};
  std::vector<int> board(std::begin(arr),std::end(arr));
  OneDimensionGameOfLife(board);
  std::ostringstream oss;
  for (int num : board) {
    oss <<num;
  }
  assert(oss.str()=="00011101");
}

int main() {
  UnitTest_OneDimensionGameOfLife();
  return 0;
}
