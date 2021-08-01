#include "httplib.h"
#include "game.h"
#include <vector>

using namespace httplib;
using namespace std;








bool reg[5],answer,win=false;
int turn=1, people,winner=0,numwin=0;

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
                cout << endl <<  "Player 1 registered successfully" << endl;
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
                cout << endl << "Player 2 registered successfully" << endl;
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
                cout << endl <<  "Player 3 registered successfully" << endl;
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
                cout << endl << "Player 4 registered successfully" << endl;
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

                if (win && turn != winner){
                    res.set_content("Sorry! You Lost!" , "text/plain");
                    ++ numwin;
                    turn = (turn % people) + 1 ;
                    if (numwin == people){
                        svr.stop();
                    }
                }
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
        if (!win){
            if(req.has_file("play")){
                const auto& tmp = req.get_file_value("play");
        
            if (tmp.content_type!="w"){
                    answer=quoridor.Board_update(turn , tmp.content_type);
                    if (quoridor.win()){
                        winner=turn;
                        win=true;
                        ++ numwin;
                    }
            }else{
                    answer=quoridor.wallmaker(tmp.filename);
            }

            
            if(answer){
            
                    res.set_content("number successfully arrived","text/plain");
                    if (winner == turn){
                        res.set_content("You win", "text/plain");
                    }
            
            
            }else{
                    
                    res.set_content("Move is not acceptable","text/plain");
            
            }
        
        }else{
        
            res.set_content("Sth went wrong","text/plain");
        
        }
       }

       

        turn = (turn % people) + 1 ;
    });



    svr.listen("localhost", 8080);
}