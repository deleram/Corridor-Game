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

    cout << "registered as number " << num << endl;

    while(true){
        items[0].name = "turncheck";
        items[0].content = "";
        for(int i = 0; i < num; i++) items[0].content += "I";
        bool turnflag = false;
        while(!turnflag){
            if(auto res = cli.Post("/turncheck", items)){
                if((res -> body) == "yes"){
                    turnflag = true;
                }
            }
        }
        items[0].name = "play";
        cout << "Enter the desired number" << endl;
        cin >> items[0].content_type;
        auto res = cli.Post("/play", items);
    }

    return 0;
}