#include "httplib.h"

using namespace httplib;
using namespace std;

bool reg[5];

int main(){
    Server svr;

    svr.Post("/register1", [&](const Request &req, Response &res){
        cout << "YOHO " << endl;
        if(req.has_file("register1")){
            if(reg[1]){
                res.set_content("Taken", "text/plain");
            }
            else{
                cout << "player 1 registered successfully" << endl;
                res.set_content("registered", "text.plain");
                reg[1] = true;
            }

        }else{
            cout << "Sth went wrong" << endl;
            res.set_content("Sth went wrong", "text/plain");
        }
    });




    svr.Post("/register2", [&](const Request &req, Response &res){
        if(req.has_file("register2")){
            if(reg[2]){
                res.set_content("Taken", "text/plain");
            }
            else{
                cout << "player 2 registered successfully" << endl;
                res.set_content("registered", "text.plain");
                reg[2] = true;
            }

        }else{
            cout << "Sth went wrong" << endl;
            res.set_content("Sth went wrong", "text/plain");
        }
    });




    svr.Post("/register3", [&](const Request &req, Response &res){
        if(req.has_file("register3")){
            if(reg[3]){
                res.set_content("Taken", "text/plain");
            }
            else{
                cout << "player 3 registered successfully" << endl;
                res.set_content("registered", "text.plain");
                reg[3] = true;
            }

        }else{
            cout << "Sth went wrong" << endl;
            res.set_content("Sth went wrong", "text/plain");
        }
    });





    svr.Post("/register4", [&](const Request &req, Response &res){
        if(req.has_file("register4")){
            if(reg[4]){
                res.set_content("Taken", "text/plain");
            }
            else{
                cout << "player 4 registered successfully" << endl;
                res.set_content("registered", "text.plain");
                reg[4] = true;
            }

        }else{
            cout << "Sth went wrong" << endl;
            res.set_content("Sth went wrong", "text/plain");
        }
    });



    svr.listen("localhost", 8080);
}