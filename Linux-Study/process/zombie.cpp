#include <iostream>
#include <unistd.h>
#include <stdlib.h>
using namespace std;

int main()
{
    
    int pid = fork();
    if(pid == 0)
    {

        exit(0);

        cout << "child fork error" << endl;
    }
    else if(pid > 0)
    {

        cout << "father fork error" << endl;
    }

    sleep(10111);

    return 0;
}
