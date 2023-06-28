#include "metaverse.h"
#include "display.h"
#include <fstream>
#include <ios>
#include <iostream>
#include <istream>
#include <vector>
/*
 * <count_neighbors>
 *
 * <Count the number of occupied neighbors for a given location.>
 *
 * input: <
 * 1) Size number: an int representing the number of rows and columns in the Metaverse.
 * 2)Metaverse reference: A "metaverse_t" reference to be resized according to the Size number.
 * >
 * output: <
 * 1) The function will resize the given metaverse_t parameter according to the specified size. The function always returns true.
 * >
 */
int count_neighbors(const metaverse_t &board, int row, int column) {
  int size = board.size();
  int neighbor_count = 0;
  for (int i = row - 1; i <= row + 1; i++) {
    for (int j = column - 1; j <= column + 1; j++) {
      if (i >= 0 && i < size && j >= 0 && j < size) {
        if (board[i][j]) {
          neighbor_count++;
        }
      }
    }
  }
  if (board[row][column]) {
    neighbor_count--;
  }
  return neighbor_count;
}
//
/*
 * <occupied_in_next_tick>
 *
 * <This function will return true if a given location in the Metaverse is occupied in the next generation.>
 *
 * input: <
 * 1) Boolean: A bool that indicates whether the location is occupied (or not) in the current generation.
 * 2) Occupied neighbor count: An integer holding the count of the number of occupied neighbors.
 * >
 * output: <The function will return true if the (un)occupied location with the specified number of occupied neighbors will be occupied in the next generation.>
 */
bool occupied_in_next_tick(bool currently_occupied, int neighbor_count) {
  if (currently_occupied) {
    if (neighbor_count == 2 || neighbor_count == 3) {
      return true;
    }
    else {
      return false;
    }
  }
  else {
    if (neighbor_count == 3) {
      return true;
    }
    else {
      return false;
    }
  }
}
//
/*
 * <tick>
 *
 * <Build a new Metaverse one tick in the future from a given Metaverse.>
 *
 * input: <
 * 1) Metaverse constant reference: A metaverse_t const reference.
 * >
 * output: <The function will return a new Metaverse (as a metaverse_t) that describes the next generation of the Metaverse described by the Metaverse reference parameter.>
 */
metaverse_t tick(const metaverse_t &board) {
  int size = board.size();
  metaverse_t new_board = board;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      int neighbor_count = count_neighbors(board, i, j);
      new_board[i][j] = occupied_in_next_tick(board[i][j], neighbor_count);
    }
  }
  return new_board;
}
//
/*
 * <resize_metaverse>
 *
 * <This function will resize a Metaverse according to a given size.>
 *
 * input: <
 * 1) Size number: an int representing the number of rows and columns in the Metaverse.
 * 2) Metaverse reference: A metaverse_t reference to be resized according to the Size number.
 * >
 * output: <The function will resize the given metaverse_t parameter according to the specified size. The function always returns true.>
 */
bool resize_metaverse(int rows, metaverse_t &board) {
  board.resize(rows);
  for (int i = 0; i < rows; i++) {
    board[i].resize(rows);
  }
  return true;
}
//
/*
 * <citizenship_row_to_metaverse_row>
 *
 * <This function will take a string of characters read from a row of the Universe File and update the initial citizenship of Metaverse accordingly.>
 *
 * input: <
 * 1) Row string: a const reference to a std::string which contains the citizenship row of the Metaverse at ...
 * 2) Row number: an int which specifies the row whose occupancy is defined by the Row string.
 * 3) Metaverse reference: A metaverse_t reference to be updated according to the preceding parameters.
 * >
 * output: <
 * The function will return true and update the given Metaverse according to the Row string as long as the initial occupancy length matches the Metaverse size.
 * It will return false, and not update the Metaverse, if the Row string does not have a valid length.
 * >
 */
/* For instance, if the user provided a Universe File with

8,3
00000000
00100000
00100000
00100000
00000000
00000000
00000000
00000000
00000000
then metaverse would display:

|------------------------|
|                        |
|       +                |
|       +                |
|       +                |
|                        |
|                        |
|                        |
|                        |
|------------------------|
|------------------------|
|                        |
|                        |
|    +  +  +             |
|                        |
|                        |
|                        |
|                        |
|                        |
|------------------------|
|------------------------|
|                        |
|       +                |
|       +                |
|       +                |
|                        |
|                        |
|                        |
|                        |
|------------------------|
*/
bool citizenship_row_to_metaverse_row(const std::string &input_row, int row,
                                      metaverse_t &board) {

  int size = board.size();
  if (input_row.length() != size) {
    return false;
  }
  for (int i = 0; i < size; i++) {
    if (input_row[i] == '1') {
      board[row][i] = true;
    }
    else if (input_row[i] == '0') {
      board[row][i] = false;
    }
    else {
      return false;
    }
  }
  return true;
}

//
/*
 * <read_metaverse_configuration_line_from_file>
 *
 * <This function will read and parse the configuration line from a Universe File. 
 * It will return true and update its out parameters if reading was successful 
 * (i.e., when a size and number of generations, separated by a comma, could be read).
 *  It will return false otherwise.>
 *
 * input: <
 * 1) Universe File reference: a reference to a std::ifstream for the Universe File. 
 * You can assume that the read head for the file will be positioned at the beginning of the metaverse configuration line.
 * 2) Size number reference: A reference to an int.
 * 3) Generation number reference: A reference to an int.
 * >
 * output: <
 * The function will return true or false depending upon whether a configuration could be read from the Universe File using the given reference.
 * If the read was successful, the Size reference will be updated with the size of the Metaverse and the Generation reference will be updated with the number of generations to model
 * (both as specified in the Universe File).
 * >
 */
bool read_metaverse_configuration_line_from_file(std::ifstream &metaverse_file,
                                                 int &size, int &generations) {
char comma;
if (metaverse_file >> size >> comma >> generations) {
  return true;
}
else {
  return false;
}
}
//
bool initialize_metaverse_from_file(std::ifstream &metaverse_file,
                                    metaverse_t &metaverse,
                                    int &generations) {
  int size{};
  int actual_row{};

  generations = 0;

  if (!read_metaverse_configuration_line_from_file(metaverse_file, size,
                                                   generations)) {
    return false;
  }

  if (!resize_metaverse(size, metaverse)) {
    return false;
  }

  metaverse_file >> std::ws;
  while (!metaverse_file.eof()) {
    std::string line{};
    if (!std::getline(metaverse_file, line)) {
      return false;
    }
    if (!citizenship_row_to_metaverse_row(line, actual_row, metaverse)) {
      return false;
    }
    actual_row++;
    metaverse_file >> std::ws;
  }
  return actual_row == size;
}
/*
 * <function name>
 *
 * <This function will model the evolution of a Metaverse for a given number of generations. At each tick, the function will display the state of the Metaverse.>
 *
 * input: <
 * Metaverse reference: A const reference to a metaverse_t specifying the citizenship of the Metaverse at Generation 0.
 * Generation number: The number of generations for which to model the Metaverse.
 * >
 * output: <This function will return no value. However, it will have the side effect of printing out the state of the Metaverse between generations.>
 */
void model_metaverse(const metaverse_t &starting_metaverse, int generations) {
metaverse_t new_board{0};
for (int gen{ 0 }; gen < generations; gen++) {
 if (gen == 0) {
  display_metaverse(std::cout, starting_metaverse);
   new_board = starting_metaverse;
 }
 else {
   new_board = tick(new_board);
    display_metaverse(std::cout, new_board);
 }
}
}