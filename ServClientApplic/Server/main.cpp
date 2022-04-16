
#include "Server.h"




int main() {
   // Creating a localhost server
    Server mainServ(boost :: asio :: ip :: address ::from_string(LOCAL_HOST),PORT);
   //  Starting the server
    mainServ.Start();
   // Starting the thread that will monitor server info
    boost :: thread MonitorThread(boost :: bind(&Server :: Monitor,&mainServ));
    MonitorThread.join();
}