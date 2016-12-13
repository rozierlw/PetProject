#include <iostream>
#include <math.h>
#include <fstream>

int parser(){
    int cards = 0;
    int a,b;
    std::string raw;
    std::cout << "What are your cards?(J=11, Q=12, K=13, A=14)(no space between): ";
    std::cin >> raw;
    for(int i = 0; i<raw.length(); i++){
        if(tolower(raw[i]) == 'a'){
            cards+= pow(10,(i+(cards/10)))*(14);
        }else if(tolower(raw[i]) == 'k') {
            cards += pow(10, (i+(cards/10))) * (13);
        }else if(tolower(raw[i]) == 'q') {
            cards += pow(10, (i+(cards/10))) * (12);
        }else if(tolower(raw[i]) == 'j') {
            cards += pow(10, (i+(cards/10))) * (11);
        }
        else{
            cards += pow(10,(i+(cards/10))) * raw[i]-'a';
        }
    }

    if(cards>1000) {
        a = cards / 100;
        b = cards % 100;
    }else{
        a = cards/10;
        b = cards%10;
    }
    if(b>a) {
        int temp = a;
        a = b;
        b = temp;
    }
    if(a<10) {
        return 10 * a + b;
    }else{
        return 100*a+b;
    }
}
void chartMaker(int hands[13][13]){
    int num;
    int ct = 0;
    std::ifstream file;
    file.open("HandsFile.txt");
    if (!file)
    {
        throw std::invalid_argument("File could not be opened");
    }
    while (file >> num)
    {
        hands[12-ct/13][12-ct%13] = num;
        ct++;
    }
}
void advice(int a){
    if(a==0){
        std::cout << "Re-Raise. You're in a strong position here, "
                "so go for it. This is your chance to take control.";
    }else if(a==1){
        std::cout << "Raise. You've got good cards in a good position. "
                "see if you can make them count with a solid and confident raise.";
    }else if(a==2){
        std::cout << "Play these cards, but watch out - your opponents' "
                "may be stronger. If people are raising in front of you, you may have to fold.";
    }else if(a==3){
        std::cout << "If you have the opportunity to see the flop"
                " for free, check, if not fold your hand.";
    }
}
void preFlop(int cards, bool suit, std::string pos){
    int a,b;
    if(cards>1000) {
        a = cards / 100;
        b = cards % 100;
    }else{
        a = cards/10;
        b = cards%10;
    }
    if(pos == "l"){
        if(b>11 && a>11) {
            advice(0);
        }else if(b>9){
            if(a==11 || a==10){
                advice(0);
            }else{
                advice(2);
            }
        }else if(b==9 && (a== 13 || a==12)){
            advice(2);
        }else if(a==b){
            advice(2);
        }else{
            if(suit) {
                if (cards == 149 || cards == 142 || cards == 109) {
                    advice(2);
                }
                else{
                    advice(3);
                }
            }else{
                advice(3);
            }
        }
    }else if(pos == "m"){
        if(a>10 && a==b){
            advice(1);
        }else if(a==14 && b>11){
            advice(1);
        }else if(a==b) {
            if (cards > 13) {
                advice(2);
            } else {
                advice(3);
            }
        }else if(cards==1411|| cards== 1312){
            advice(2);
        } else {
            if(suit){
                if(cards == 1410 || cards== 1311 || cards== 1211 || cards== 1110 || cards== 109){
                    advice(2);
                }else{
                    advice(3);
                }
            }
            else{
                advice(3);
            }
        }
    }else{
        if(b>12){
            advice(1);
        }else if(cards==1412 || cards == 1212){
            advice(1);
        }else if(a>9 && a==b){
            advice(2);
        }else{
            advice(3);
        }
    }
}
/*
void chartTester(){
    int hands [13][13];
    chartMaker(hands);
    for(int i=0; i<13; i++){
        for(int j = 0; j<13; j++){
            std::cout << hands[i][j];
        }
        std::cout <<"\n";
    }
}
*/
int main() {
   /* bool again = true;
    std::string next;
    std::string pos;
    std::string suit;
    while(again) {
        std::cout << "What position are you in?(late(l), middle(m), early(e)): ";
        std::cin >> pos;

        int cards = parser();

        std::cout << "Are they suited? (y or n): ";
        std::cin >> suit;
        std::cout << "\n";

        preFlop(cards,suit=="y", pos);
        std::cout << "\n";
        std::cout << "Next hand? (y or n): ";
        std::cin >> next;
        if(next!="y"){again = false;}
        std::cout << "\n";
    }*/
    return 0;
}
