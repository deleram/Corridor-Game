#include <vector>
using namespace std;


class Game{
    
public:
    
    Game(int number_of_players){
        
        for (int i=0 ; i<21;++i){
            for(int j=0;j<21 ; j++){
                if (j%2==1 || i%2==1){
                    Board[i][j]= ' ' ;
                }else{
                    Board[i][j]= 'o';
                }
            }
        }
        NP = number_of_players;
        vector <int> A = {0, 20};
        vector <int> B = {0, 20};
        for(int i = 0; i < NP; i++){
            player[i][0] = A[i / 2];
            player[i][1] = B[i % 2];
            Board[player[i][0]][player[i][1]] = (char)(49+ i);
        }
    }


    string string_maker (){
        string ans= "";
        for(int i=0 ; i<21 ; ++i){
            for (int j=0 ; j<21 ; j++){
                ans.push_back(Board[i][j]);
            }
            ans+= '\n';
        }
        return ans;
    }

    bool Board_update(int gamer , string Move){

        if (Move=="u" && (player[gamer-1][0]!=0) && (Board[player[gamer-1][0]-1][player[gamer-1][1]]==' ')){
            if(Board[player[gamer-1][0]-2][player[gamer-1][1]]=='o'){
                Board[player[gamer-1][0]-2][player[gamer-1][1]]=(char) (48 + gamer);
                Board[player[gamer-1][0]][player[gamer-1][1]]='o';
                player[gamer-1][0]-=2;
                return true;

            }else{
                return false;
            }
        }


        else if (Move=="d" && (player[gamer-1][0]!=20) && (Board[player[gamer-1][0]+1][player[gamer-1][1]]==' ')){
            if(Board[player[gamer-1][0]+2][player[gamer-1][1]]=='o'){
                Board[player[gamer-1][0]+2][player[gamer-1][1]]=(char) (48 + gamer);
                Board[player[gamer-1][0]][player[gamer-1][1]]='o';
                player[gamer-1][0]+=2;
                return true;

            }else{
                return false;
            }

        }

        else if (Move=="r" && (player[gamer-1][1]!=20) && (Board[player[gamer-1][0]][player[gamer-1][1]+1]==' ')){
            if(Board[player[gamer-1][0]][player[gamer-1][1]+2]=='o'){
                Board[player[gamer-1][0]][player[gamer-1][1]+2]=(char) (48 + gamer);
                Board[player[gamer-1][0]][player[gamer-1][1]]='o';
                player[gamer-1][1]+=2;
                return true;

            }else{
                return false;
            }

        }


        else if (Move=="l" && (player[gamer-1][1]!=0) && (Board[player[gamer-1][0]][player[gamer-1][1]-1]==' ')){
            if(Board[player[gamer-1][0]][player[gamer-1][1]-2]=='o'){
                Board[player[gamer-1][0]][player[gamer-1][1]-2]=(char) (48 + gamer);
                Board[player[gamer-1][0]][player[gamer-1][1]]='o';
                player[gamer-1][1]-=2;
                return true;

            }else{
                return false;
            }
        }else{
            return false;
        }

    }



    bool wallmaker(string square){
        int i=0,j=0;
        char direction;
        if (square[1]!=','){
            i= stoi(square.substr(0,2));
            if (square[4]!=','){
                j=stoi(square.substr(3,2));
            }else{
                j=stoi(square.substr(3,1));
            }
        }else{
            i=stoi(square.substr(0,1));
            if (square[3]==','){
                j=stoi(square.substr(2,1));
            }else{
                j=stoi(square.substr(2,2));
            }

        }
        direction=square.back();

        if ((i==1 && direction == 'u') || (j==11 && direction == 'r') || (i>11 || j >11 || i<1 || j<1) || ((direction != 'u') && (direction != 'r')) ){
            return false;
        }


        else if (direction == 'r'){
            for (int a=0 ; a<5 ; ++a){
                if(!( (a<2 && i<2) || (a>2) && i>10)){
                    if (Board[2*(i-2)+a][(2*j)-1]!= ' '){
                        return false;
                    }
                }
            }
            for (int b=0 ; b<5 ; ++b){
                if (!( (b<2 && i<2) || (b>2) && i>10)){
                    Board[2*(i-2)+b][(2*j)-1]='|';
                }
            }
            return true;
        }


        else if (direction == 'u'){
            for (int a=0 ; a<5 ; ++a){
                if(!( (a<2 && j<2) || (a>2) && j>10)){
                    if (Board[2*i-3][2*(j-2)+a]!= ' '){
                        return false;
                    }
                }
            }
            for (int b=0 ; b<5 ; ++b){
                if (!( (b<2 && j<2) || (b>2 && j>10))){
                    Board[2*i-3][2*(j-2)+b]='-';
                }
            }
            return true;
        }else {
            return false;
        }





    }




    bool win(){
        if (Board[10][10]!='o'){
            return true;
        }else{
            return false;
        }
    }




private:
    char Board[21][21];
    int player[4][2],NP;







};
