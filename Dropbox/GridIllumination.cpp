/***
Grid Illumination: Given an NxN grid with an array of lamp coordinates. Each lamp provides illumination to every square on their x axis, every square on their y axis, and every square that lies in their diagonal (think of a Queen in chess). Given an array of query coordinates, determine whether that point is illuminated or not. The catch is when checking a query all lamps adjacent to, or on, that query get turned off. The ranges for the variables/arrays were about: 10^3 < N < 10^9, 10^3 < lamps < 10^9, 10^3 < queries < 10^9
***/

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cassert>
#include <iostream>

void AddLamp(std::unordered_map<std::size_t, std::size_t> & row_lamp_count,
             std::unordered_map<std::size_t, std::size_t> & col_lamp_count,
             std::unordered_map<std::size_t, std::size_t> & first_diagonal_lamp_count,
             std::unordered_map<std::size_t, std::size_t> & second_diagonal_lamp_count,
             std::size_t row,
             std::size_t column,
             std::size_t n_size) {
  ++ row_lamp_count[row];
  ++ col_lamp_count[column];
  ++ first_diagonal_lamp_count[n_size + row - column];
  ++ second_diagonal_lamp_count[row + column];
}

void ToggleLamp(std::unordered_map<std::size_t, std::size_t> & row_lamp_count,
                std::unordered_map<std::size_t, std::size_t> & col_lamp_count,
                std::unordered_map<std::size_t, std::size_t> & first_diagonal_lamp_count,
                std::unordered_map<std::size_t, std::size_t> & second_diagonal_lamp_count,
                std::size_t row,
                std::size_t column,
                std::size_t n_size,
                bool toggle) {
// Toggle == True, means turn on lamp; False, means turn off lamp
  if (toggle) {
    ++ row_lamp_count[row];
    ++ col_lamp_count[column];
    ++ first_diagonal_lamp_count[ n_size + row - column];
    ++ second_diagonal_lamp_count[row + column];
  } else {
    if (row_lamp_count[row] > 0) -- row_lamp_count[row];
    if (col_lamp_count[column] > 0) -- col_lamp_count[column];
    if (first_diagonal_lamp_count[ n_size + row - column] > 0) -- first_diagonal_lamp_count[ n_size + row - column];
    if (second_diagonal_lamp_count[row + column]) -- second_diagonal_lamp_count[row + column];
  }
}

bool IsIlluminated(std::unordered_map<std::size_t, std::size_t> & row_lamp_count,
                   std::unordered_map<std::size_t, std::size_t> & col_lamp_count,
                   std::unordered_map<std::size_t, std::size_t> & first_diagonal_lamp_count,
                   std::unordered_map<std::size_t, std::size_t> & second_diagonal_lamp_count,
                   std::size_t row,
                   std::size_t column,
                   std::size_t n_size) {
  
  return row_lamp_count[row] > 0
    || col_lamp_count[column] > 0
    || first_diagonal_lamp_count[ n_size + row - column] > 0
    || second_diagonal_lamp_count[row + column] > 0;
}

std::string GetLampPositionHash(std::size_t row, std::size_t col) {
  return std::to_string(row) + std::to_string(col);
}

void ToggleBlock(const std::unordered_set< std::string > & lamp_hashset,
                 std::unordered_map<std::size_t, std::size_t> & row_lamp_count,
                 std::unordered_map<std::size_t, std::size_t> & col_lamp_count,
                 std::unordered_map<std::size_t, std::size_t> & first_diagonal_lamp_count,
                 std::unordered_map<std::size_t, std::size_t> & second_diagonal_lamp_count,
                 std::size_t row,
                 std::size_t column,
                 std::size_t n_size,
                 bool toggle) {
  std::size_t min_row = row > 0 ? row - 1 : 0;
  std::size_t min_column = column > 0 ? column - 1 : column;
  std::size_t max_row = row + 1 < n_size ? row + 1 : row;
  std::size_t max_column = column + 1 < n_size ? column + 1 : column;
  
  for (std::size_t i = min_row; i <= max_row; ++i) {
    for (std::size_t j = min_column; j <= max_column; ++j) {
      if (lamp_hashset.count(GetLampPositionHash(i,j)) > 0) {
        ToggleLamp(row_lamp_count, col_lamp_count, first_diagonal_lamp_count, second_diagonal_lamp_count,
                   i, j, n_size, toggle);
      }
    }
  }
}

std::vector<bool> GetIluminated(const std::size_t n_size,
                               const std::vector< std::pair<std::size_t, std::size_t> > & lamps,
                               const std::vector< std::pair<std::size_t, std::size_t> > & query_positions) {
  std::vector<bool> reval;
  std::unordered_map<std::size_t, std::size_t> row_lamp_count,
    col_lamp_count, first_diagonal_lamp_count, second_diagonal_lamp_count;
  std::unordered_set< std::string > lamp_hashset;
  for (const std::pair<std::size_t, std::size_t> & lamp : lamps) {
    AddLamp(row_lamp_count, col_lamp_count, first_diagonal_lamp_count, second_diagonal_lamp_count,
            lamp.first, lamp.second, n_size);
    lamp_hashset.insert( GetLampPositionHash(lamp.first, lamp.second) );
  }

  for (const std::pair<std::size_t, std::size_t> & query_position : query_positions) {
    ToggleBlock(lamp_hashset, row_lamp_count, col_lamp_count, first_diagonal_lamp_count, second_diagonal_lamp_count,
               query_position.first, query_position.second, n_size, false);
    
    reval.push_back(IsIlluminated(row_lamp_count,
                                  col_lamp_count,
                                  first_diagonal_lamp_count,
                                  second_diagonal_lamp_count,
                                  query_position.first, query_position.second, n_size));
    
    ToggleBlock(lamp_hashset, row_lamp_count, col_lamp_count, first_diagonal_lamp_count, second_diagonal_lamp_count,
                  query_position.first, query_position.second, n_size, true);
  }
  
  return reval;
}


void UnitTest() {
  std::size_t n_size = 3;
  std::vector< std::pair<std::size_t,std::size_t> > lamps = {{2,0}};
  std::vector< std::pair<std::size_t,std::size_t> > query_positions = {{0,0},{1,0},{2,0}};
  std::vector<bool> reval = GetIluminated(n_size, lamps, query_positions);
  for (bool item : reval) {
    std::cout << (item ? "TRUE" : "FALSE") << std::endl;
  }
}

int main() {
  UnitTest();
  return 0;
}
