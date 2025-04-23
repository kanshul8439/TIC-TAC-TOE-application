/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
using namespace std;
#include<string>
#include<deque>
#include<vector>
enum PieceType{
    X,
    O,
    Y,
    A,
    B,
    C,
};
const string PieceTypeStrings[]={
    "X",
    "O",
    "Y",
    "A",
    "B",
    "C"
};

class PlayingPiece{
  PieceType type;
  public:
  PlayingPiece(PieceType p){
      type=p;
  }
  PieceType getType(){
      return type;
  }
};

class Player{
  PlayingPiece* piece;  
  string name;
  public:
  Player(string n,PlayingPiece* p){
      piece=p;
      name=n;
  }
  string getName(){
      return name;
  }
  PlayingPiece* getPiece(){
      return piece;
  }
};

class Board{
    int size;
    vector<vector<PlayingPiece*>> board;
    public:
    Board(int n){
        size=n;
        board.resize(n,vector<PlayingPiece*> (n,nullptr));
    }
    int getSize(){
        return size;
    }
    vector<vector<PlayingPiece*>>& getBoard(){
        return board;
    }
};

class TicTacToeGame{
    deque<Player*> players;
    Board * playingBoard;
    public:
    TicTacToeGame(){
        initGame();
    }
    void initGame(){
        int n,m;
        cout<<"Enter the size of board" ;
        cin>>n;
        cout<<"Enter the no. of players";
        cin>>m;
        for(int i=0;i<m;i++)
        {
            players.push_back(new Player("Player "+ to_string(i+1), new PlayingPiece(static_cast<PieceType>(i))));    
        }
        
        playingBoard=new Board(n);
    }
    
    void printBoard( vector<vector<PlayingPiece*>> & board){
        
    cout<<endl;
    int n=board.size();
    for (int i = 0; i < n; ++i) {
        
        
        // Print row content
        for (int j = 0; j < n; ++j) {
            // cout << (board[i][j] ? board[i][j] : ' ');
            
             if(board[i][j]!=nullptr)
            {
                    cout<<PieceTypeStrings[board[i][j]->getType()]<<" ";
            }else
            cout<<"  ";
            
            if (j < n - 1) cout << " | ";
        }
        cout << endl;

        // Print separator
        if (i < n - 1) {
            for (int j = 0; j < n; ++j) {
                cout << "---";
                if (j < n - 1) cout << "+";
            }
            cout << endl;
        }
    }
        cout<<endl;
    }
    void startGame(){
        vector<vector<PlayingPiece*>> & board=playingBoard->getBoard();
        int n=board.size();
        while(1)
        {
        Player *currentplayer=players.front();
        players.pop_front();
        
        
         int x,y;
        while(1)
         {
             printBoard(board);
                 cout<<"Player : "<<currentplayer->getName()<<" Piece :- " <<PieceTypeStrings[currentplayer->getPiece()->getType()];
            cout<<" Enter your Turn coordinates ";
           
            cin>>x>>y;
            if(x<0||y<0||x>=n||y>=n||board[x][y]!=nullptr)
            {
            cout<<"Please Enter valid coordinates";
            }
            else
            {
               board[x][y]=currentplayer->getPiece();
                break;
            }
         }
         
         if(IsWinner(board[x][y])){
             cout<<"<<<<<<============GAME ENDED========>>>>>>";
              cout<<"Player : "<<currentplayer->getName()<<" Piece :- " <<PieceTypeStrings[currentplayer->getPiece()->getType()]<<"WON ";
             break;
         }
         if(IsBoardFUll(board))
         {
              cout<<"<<<<<<============GAME ENDED========>>>>>>";
              cout<<"!!!!!!!!!!!!    TIME WON        !!!!!!!";
             break;
         }
         
          players.push_back(currentplayer);  
        }
    }
    bool IsWinner(PlayingPiece * target){
        
        int n=playingBoard->getSize();
        vector<vector<PlayingPiece*>> &board=playingBoard->getBoard();
        
    for (int i = 0; i < n; ++i) {
        bool allMatch = true;
        for (int j = 0; j < n; ++j) {
            if (board[i][j] != target) {
                allMatch = false;
                break;
            }
        }
        if (allMatch) return true;
    }

    // Check columns
    for (int j = 0; j < n; ++j) {
        bool allMatch = true;
        for (int i = 0; i < n; ++i) {
            if (board[i][j] != target) {
                allMatch = false;
                break;
            }
        }
        if (allMatch) return true;
    }

    // Check main diagonal
    bool allMainDiag = true;
    for (int i = 0; i < n; ++i) {
        if (board[i][i] != target) {
            allMainDiag = false;
            break;
        }
    }
    if (allMainDiag) return true;

    // Check anti-diagonal
    bool allAntiDiag = true;
    for (int i = 0; i < n; ++i) {
        if (board[i][n - 1 - i] != target) {
            allAntiDiag = false;
            break;
        }
    }
    if (allAntiDiag) return true;

    return false;
        
    }

    bool IsBoardFUll(vector<vector<PlayingPiece*>> & board)
    {
        for(int i=0;i<board.size();i++)
        {
            for(int j=0;j<board[0].size();j++)
            {
                if(board[i][j]==nullptr)
                return false;
            }
        }
        return true;
    }
};
int main()
{
    
    TicTacToeGame *game=new TicTacToeGame();
    game->startGame();
    
    std::cout<<"Hello World";

    return 0;
}