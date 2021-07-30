#include "httplib.h"

using namespace httplib;
using namespace std;

bool reg[5];
int turn=1, people;

int main(){
    Server svr;

    cout << "Number of players?" << endl ;
    cin >> people ;

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
                res.set_content("yes", "text/plain");
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
           cout << tmp.content_type << endl;
           turn = (turn % people) + 1 ;
           res.set_content("number successfully arrived","text/plain");
       }else{
           res.set_content("Sth went wrong","text/plain");
       }
    });



    svr.listen("localhost", 8080);
}