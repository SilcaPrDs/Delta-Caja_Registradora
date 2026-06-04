#include <iostream>

using namespace std;

int main(){

    string text;

    cout<<"ingrese un valor\n";

    try{

        cin >> text;

        int num = stoi(text);

        cout<<"el valor fue:\n" << num;

    }catch(...){

        cout<<"ha surgido un error\n";

    }

    return 0;

}