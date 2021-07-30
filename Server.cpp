#include "httplib.h"
#include <vector>

using namespace httplib;
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

        if (Move=="u" && (player[gamer-1][0]!=0)){
            if(Board[player[gamer-1][0]-2][player[gamer-1][1]]=='o'){
                Board[player[gamer-1][0]-2][player[gamer-1][1]]=(char) (48 + gamer);
                Board[player[gamer-1][0]][player[gamer-1][1]]='o';
                player[gamer-1][0]-=2;
                return true;

            }else{
                return false;
            }
        }


        else if (Move=="d" && (player[gamer-1][0]!=20)){
            if(Board[player[gamer-1][0]+2][player[gamer-1][1]]=='o'){
                Board[player[gamer-1][0]+2][player[gamer-1][1]]=(char) (48 + gamer);
                Board[player[gamer-1][0]][player[gamer-1][1]]='o';
                player[gamer-1][0]+=2;
                return true;

            }else{
                return false;
            }

        }

        else if (Move=="r" && (player[gamer-1][1]!=20)){
            if(Board[player[gamer-1][0]][player[gamer-1][1]+2]=='o'){
                Board[player[gamer-1][0]][player[gamer-1][1]+2]=(char) (48 + gamer);
                Board[player[gamer-1][0]][player[gamer-1][1]]='o';
                player[gamer-1][1]+=2;
                return true;

            }else{
                return false;
            }

        }


        else if (Move=="l" && (player[gamer-1][1]!=0)){
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




private:
    char Board[21][21];
    int player[4][2],NP;







};






bool reg[5],answer;
int turn=1, people;

int main(){
    Server svr;

    cout << "Number of players?" << endl ;
    cin >> people ;
    Game quoridor(people);

    svr.Post("/register1", [&](const Request &req, Response &res){
        if(req.has_file("register1") && people>=1){
            if(reg[1]){
                res.set_content("Taken", "text/plain");
            }
            else{
                cout << "player 1 registered successfully" << endl;
                res.set_content("registered", "text.plain");
                reg[1] = true;
            }

        }else{
            res.set_content("Sth went wrong", "text/plain");
        }
    });




    svr.Post("/register2", [&](const Request &req, Response &res){
        if(req.has_file("register2") && people >=2){
            if(reg[2]){
                res.set_content("Taken", "text/plain");
            }
            else{
                cout << "player 2 registered successfully" << endl;
                res.set_content("registered", "text.plain");
                reg[2] = true;
            }

        }else{
            res.set_content("Sth went wrong", "text/plain");
        }
    });




    svr.Post("/register3", [&](const Request &req, Response &res){
        if(req.has_file("register3")&& people>=3){
            if(reg[3]){
                res.set_content("Taken", "text/plain");
            }
            else{
                cout << "player 3 registered successfully" << endl;
                res.set_content("registered", "text.plain");
                reg[3] = true;
            }

        }else{
            res.set_content("Sth went wrong", "text/plain");
        }
    });





    svr.Post("/register4", [&](const Request &req, Response &res){
        if(req.has_file("register4")&& people>=4){
            if(reg[4]){
                res.set_content("Taken", "text/plain");
            }
            else{
                cout << "player 4 registered successfully" << endl;
                res.set_content("registered", "text.plain");
                reg[4] = true;
            }

        }else{
            res.set_content("Sth went wrong", "text/plain");
        }
    });


    svr.Post("/turncheck", [&](const Request &req , Response &res){
        if(req.has_file("turncheck") && reg[people]){
            const auto& tmp = req.get_file_value("turncheck");
            if(turn == (int)tmp.content.size()){
                res.set_content(quoridor.string_maker(), "text/plain");
            }
            else{
                res.set_content("no", "text/plain");
            }
        }
        else{
            res.set_content("Sth went wrong", "text/plain");
        }
    });

    svr.Post("/play", [&](const Request &req, Response &res){
       if(req.has_file("play")){
           const auto& tmp = req.get_file_value("play");
           answer=quoridor.Board_update(turn , tmp.content_type);
           turn = (turn % people) + 1 ;
           
           if(answer){
           
                res.set_content("number successfully arrived","text/plain");
           
           
           }else{
                
                res.set_content("Move is not acceptable","text/plain");
           
           }
       
       }else{
       
           res.set_content("Sth went wrong","text/plain");
       
       }
    });



    svr.listen("localhost", 8080);
}