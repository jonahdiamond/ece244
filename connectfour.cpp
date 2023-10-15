#include <iostream>
#include <string>
using namespace std;

#include "GameState.h"
#include "globals.h"

// Function prototypes

// The main function
int main() {
  /**********************************************************************************/
  /* Create three initialized game state objects in an array */
  /**********************************************************************************/
  const int numOfRounds = 3;
  GameState game_state[numOfRounds];

  // Read one integer from the user that represents the column
  // the player would like to place their piece (R or Y) in
  // You can assume there will be no formatting errors in the input

  int col;
  int round = 0;
  int rWins = 0, yWins = 0;
  cout<< "Game " << round + 1 << endl;

  while (!game_state[round].get_gameOver()) {
    
    cout << "Enter column to place piece: ";
    cin >> col;
 
    if( cin.eof() ) {
      cerr << endl << "Game ended by user." << endl ;
      exit( 0 ) ;
    }
    if( cin.fail() ) {
      cin.clear() ;
      cin.ignore( 1000, '\n' ) ;
      col = -1 ; // giving col invalid value so it will be handled as invalid input below
    }
  
    // Check validity of input and if not valid, handle accordingly
    /// move validity here and assign state.moveValid 
    if ((col == -1) //invalid col input
      ||(col < 0) //column too small
      ||(col >= boardSize) //column too big
      ||(game_state[round].get_gameBoard(boardSize - 1, col) != Empty)){ //filled place
      
        //game_state[numOfRounds].set_moveValid(true);
        cout<<"Invalid column!"<<endl;
        // if invalid column, continue
        continue;
      } else{

    // The coordinates are valid; set the selectedRow and selectedColumn
    // members of the game state to the read values
    // Note that the corresponding mutators of GameState must be first
    // implemented before this works
    game_state[round].set_selectedColumn(col); //set column
    cout << "column chosen: " << col << endl;
    for (int r = 0; r < boardSize; r++){ //set row as first empty row from bottom
      if (game_state[round].get_gameBoard(r, col) == Empty){
        game_state[round].set_selectedRow(r);
        break;
      }
    }


    // Call playMove
    playMove(game_state[round]);

    // Print the GameState object, as prescribed in the handout
    for (int i = boardSize - 1; i >= 0; i--){
      for (int j = 0; j < boardSize; j++){
        //cout << game_state[round].get_gameBoard(i,j);
        switch (game_state[round].get_gameBoard(i,j)){
          case Empty:
            cout<<"_";
            break;
          case Y:
            cout<<"Y";
            break;
          case R:
            cout<<"R";
            break;
          default:
            cout<<"^";
            break;
        }
      }
      cout<<endl;
    }
    }

    // Check if a player won this round and if so handle accordingly
    if (game_state[round].get_gameOver()){
      switch (game_state[round].get_winner()){
        case R:
          cout<<"R won this round!"<<endl;
          rWins++;
          break;
        case Y:
          cout<<"Y won this round!"<<endl;
          yWins++;
          break;
      }
      round++;
      if (round < 2){
          cout<< "Game " << round + 1 << endl;
      }
    }

    // Check if a player won this match and if so handle accordingly
    if (yWins > 1){
      cout<<"Y won the match!"<<endl;
      break; //end the game
    }
    if (rWins > 1){
      cout<<"R won the match!"<<endl;
      break; //end the game
    }
  }
}
  
