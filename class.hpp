#include <iostream>
#include <string>

class game{
   public:
      char wc;
      std::string tempsecretword;
      std::string secretword;

      game();
      void choose();
      void change();
      void check();
   private:
      char c;
};

