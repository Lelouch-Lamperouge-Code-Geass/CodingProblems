/**
Given a phone keypad and Knight(Chess), find out if you can form a phone number using 
all the possible moves of the Knight, if you can then return all the possible phone numbers as a list of string.
e.g. The Knight moves in an L shape in any direction. We can say that it either moves 
two squares sideways and then one square up or down e.t.c
Find out all the possible numbers, digits in the number can repeat.  
 **/
#include <vector>
#include <cassert>
#include <iostream>
#include <string>

std::vector< std::vector<char> > keypad = {{'1','2','3'},
                                          {'4','5','6'},
                                          {'7','8','9'},
                                          {'*','0','#'}};
typedef std::pair<int,int> Move;

// Knight can only move in an L shape
std::vector<Move> moves = {{-2,-1},{-2,1},{2,-1},{2,1},{-1,-2},{-1,2},{1,-2},{+1,+2}};
  
void MoveOnKeypad(std::vector<std::string> & result, std::string & temp, int row, int col, int count){
  if (row < 0 || row > 3 || col < 0 || col > 2) return;
  if (keypad[row][col] == '*' || keypad[row][col] == '#') return;
  
  temp.push_back(keypad[row][col]);

  if (count == 1) {
    result.push_back(temp);
  } else{
    for (std::size_t i = 0; i < 8; ++i) {
      int move_row = row + moves[i].first;
      int move_col = col + moves[i].second;
      
      MoveOnKeypad(result, temp, move_row, move_col, count - 1);
    }
  }
  
  temp.pop_back(); // revert back
  
}

std::vector<std::string> KnightMoveOnKeyPad(int n) {
  
  std::vector<std::string> reval;
  std::string temp("");
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 3; ++j) {
      MoveOnKeypad(reval, temp, i, j, n);
    }
  }
  
  return reval;
}


void UnitTest() {
  std::vector<std::string> reval = KnightMoveOnKeyPad(3);
  for (std::string & str : reval) {
    std::cout << str << std::endl;
  }
}

int main() {
  UnitTest();
  return 0;
}


