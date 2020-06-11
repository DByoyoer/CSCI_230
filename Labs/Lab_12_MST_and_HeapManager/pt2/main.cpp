#include "Memory.h"
#include <random>

using namespace std;

int main()
{
    Memory test(4048);

    while(test.getBytesAvaliable() > (4048 / 2))
    {
        int range = 80 - 20 + 1;
        int num = rand() % range + 20;

        test.allocate(num);
    }

    while(test.getBytesAvaliable() > 20)
    {
        int allocate = rand() % 3;
        cout << allocate << endl;
        if(allocate > 0)
        {
            int range = 80 - 20 + 1;
            int num = rand() % range + 20;

            test.allocate(num);
        }
        else
        {
            test.deallocate(rand() % test.getBlocks());
        }
        
    }
    test.debug();
    cout << "Blocks: " << test.getBlocks() << endl;
    cout << "MemoryLeft: " << test.getBytesAvaliable() << endl;
    system("pause");
    return 0;
}