#include "httplib.h"

using namespace std;
using namespace httplib;

bool flag;
int num;

int main(){
    Client cli("localhost", 8080);

    MultipartFormDataItems items{
        {"register1", "", "", ""},
        {"register2", "", "", ""},
        {"register3", "", "", ""},
        {"register4", "", "", ""},

    };

    if(!flag){
        if(auto res = cli.Post("/register1", items)){
            if((res -> body) == "registered"){
                flag = true;
                num = 1;
            }
        }
    }

    if(!flag){
        if(auto res = cli.Post("/register2", items)){
            if((res -> body) == "registered"){
                flag = true;
                num = 2;
            }
        }
    }

    if(!flag){
        if(auto res = cli.Post("/register3", items)){
            if((res -> body) == "registered"){
                flag = true;
                num = 3;
            }
        }
    }

    if(!flag){
        if(auto res = cli.Post("/register4", items)){
            if((res -> body) == "registered"){
                flag = true;
                num = 4;
            }
        }
    }

    if (num == 0){
        cout << "Sorry it's full :( "<< endl ;
        return 0;

    }


    cout << "registered as number " << num << endl;

    while(true){
        items[0].name = "turncheck";
        items[0].content = "";
        for(int i = 0; i < num; i++) items[0].content += "I";
        bool turnflag = false;
        string Board;
        while(!turnflag){
            if(auto res = cli.Post("/turncheck", items)){
                if((res -> body) != "no" && (res -> body) != "Sth went wrong"){
                    Board=res -> body;

                    turnflag = true;
                }
            }
        }
        items[0].name = "play";
        cout << Board;
        cout << "Enter your desired move (u/d/r/l) or 'w' for walls" << endl;
        cin >> items[0].content_type;
        if (items[0].content_type == "w"){
            cout << "Enter i,j as in matrix and up or right for example :3,3,u" << endl ;
            cin >> items[0].filename ;

        }
        if (auto res = cli.Post("/play", items)){
            if (res->body=="Move is not acceptable")
            {
                cout << res->body<<endl;
            }
            
        }
    }

    return 0;
}

