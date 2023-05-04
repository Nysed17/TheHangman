#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "class.hpp"

// global
int lan;
int isTrue = 0;

game::game(){
   system("clear");
   std::cout<<"The Hangman"<<"\n\n";
}

void game::choose(){
   std::cout<<"Choose language:\n1] for english\n2] for italian\n\n";
   std::cin>>lan;
   if (lan == 1){
      system("clear");
      std::cout<<"The Hangman"<<"\n\n";
      std::ifstream inFile("ENwords.txt");
      if (inFile.is_open()){
         std::string wordlist[102];
         for(int i = 0; i < 102 ; ++i){
            inFile>>wordlist[i];
         }
         srand(time(0));
         secretword = wordlist[rand()%102];
         tempsecretword = secretword;
         for (int i = 0 ; i < secretword.size() ; i++){
            tempsecretword[i] = '_';
         }
         //cout<< secretword << endl;
         inFile.close(); 
      }
   } else if (lan == 2){
      system("clear");
      std::cout<<"The Hangman"<<"\n\n";
      std::ifstream inFile("ITwords.txt");
      if (inFile.is_open()){
         std::string wordlist[102];
         for(int i = 0; i < 102 ; ++i){
            inFile>>wordlist[i];
         }
         srand(time(0));
         secretword = wordlist[rand()%102];
         tempsecretword = secretword;
         for (int i = 0 ; i < secretword.size() ; i++){
            tempsecretword[i] = '_';
         }
         //cout<< secretword << endl;
         inFile.close(); 
      }
   }
}

void game::change(){
   std::cout<<"\n\n-> ";
   std::cin>>c;
   wc = c;
}

void game::check(){
   game();
   int count = 0;
   for (int i = 0 ; i < secretword.size() ; i++){
      if (secretword.at(i) != c){
         count++;
      } else {
         tempsecretword.at(i) = c;
         count = 0;
      }
   }
   if (count == secretword.size()){
      isTrue++;
      count = 0;
   }
}

game g;

void hangman(int& gameover){
   //char wrongchar[isTrue] = g.wc;
   char hang[7][10] = { {' ',' ',' ',' ','_','_','_','_',' ',' '},
      {' ',' ',' ','|',' ',' ',' ',' ','|',' '},
      {' ',' ',' ','|',' ',' ',' ',' ',' ',' '},
      {' ',' ',' ','|',' ',' ',' ',' ',' ',' '},
      {' ',' ',' ','|',' ',' ',' ',' ',' ',' '},
      {' ',' ',' ','|',' ',' ',' ',' ',' ',' '},
      {' ','_','_','|','_','_',' ',' ',' ',' '} };

   switch (isTrue){
      case 1:
         hang[2][8] = 'O';
         break;
      case 2:
         hang[2][8] = 'O';
         hang[3][8] = '|';
         hang[4][8] = 39;
         break;
      case 3:
         hang[2][8] = 'O';
         hang[3][8] = '|';
         hang[4][8] = 39;
         hang[3][7] = '/';
         break;
      case 4:
         hang[2][8] = 'O';
         hang[3][8] = '|';
         hang[4][8] = 39;
         hang[3][7] = '/';
         hang[3][9] = 92;
         break;
      case 5:
         hang[2][8] = 'O';
         hang[3][8] = '|';
         hang[4][8] = 39;
         hang[3][7] = '/';
         hang[3][9] = 92;
         hang[4][7] = '/';
         break;
      case 6:
         hang[2][8] = 'O';
         hang[3][8] = '|';
         hang[4][8] = 39;
         hang[3][7] = '/';
         hang[3][9] = 92;
         hang[4][7] = '/';
         hang[4][9] = 92;
         gameover = 1;
         g.tempsecretword = g.secretword;
         break;
   }
   for (int i = 0 ; i < 7 ; i++){
      for (int j = 0 ; j < 10 ; j++){
         std::cout<<hang[i][j];
      }
      std::cout<<'\n';
   }
   std::cout<<"\n "<<g.tempsecretword;
}

void checkwin(int& gm){
   int count = 0;
   for (int i = 0 ; i < g.secretword.size() ; i++){
      if (g.secretword.at(i) == g.tempsecretword.at(i) && gm != 1){
         count++;
      }
   }
   if (count == g.secretword.size()){
      gm = 2;
      count = 0;
   }
}

void checkforgmorwin(int& gm){
   checkwin(gm);
   if (gm == 1){
      sleep(1);
      system("clear");
      sleep(1);
      std::cout<<" <- the word was this...\n\n    OPS!\n  Gameover\n\n";
      exit(0);
   }
   if (gm == 2){
      sleep(1);
      system("clear");
      sleep(1);
      std::cout<<" <- the word was this!\n\n    You win!\n\n\n";
      exit(0);
   }
}

int main(){

   g.choose();
   int gameover = 0;
   while (!gameover){
      hangman(gameover);
      checkforgmorwin(gameover);
      g.change();
      g.check();
   }

   return 0;
}
