#include <iostream>

using namespace std;

struct Block
{
    int size;
    int allocatedSize;
    bool isAvaliable;
    Block* next;
};

class Memory
{
private:
    int bytesAvaliable;
    Block* head;
    int blocks;
public:
    Memory(int size)
    {
        bytesAvaliable = size;  
        blocks = 0;
        head = NULL;    
    }
    
    void allocate(int size)
    {
        if(size > bytesAvaliable)
        {
            return;
        }

        if(head == NULL)
        {

            Block* temp = new Block();
            bytesAvaliable -= size;
            temp->size = size;
            temp->allocatedSize = size;
            temp->isAvaliable = false;
            temp->next = NULL;
            head = temp;
            blocks++;
            return;
        }
        else
        {
            Block* temp = new Block();
            temp = head;
            Block* best = NULL;
            //best = head;
            int closestSize = 9999;
            while(temp->next != NULL)
            {
               /*  if(temp->isAvaliable && temp->allocatedSize >= size)
                {
                    
                    blocks++;
                    temp->size = size;
                    temp->isAvaliable = false;
                    return;
                } */
                
               /*  if(temp->isAvaliable)
                {
                    if(temp->allocatedSize >= size)
                    {
                       
                        if(temp->allocatedSize < closestSize)
                        {
                            best = temp;
                            closestSize = temp->allocatedSize;
                        }
                    }
                } */
                temp = temp->next;
                
            }

            if(best != NULL)
            {
         
                blocks++;
                best->size = size;
                best->isAvaliable = false;
                return;
            }

            Block* end = new Block();
            end->next = NULL;
            end->size = size;
            end->allocatedSize = size;
            bytesAvaliable -= size;
            end->isAvaliable = false;
            temp->next = end;
            blocks++;
        }
    }

    void deallocate(int blockNumber)
    {
        Block* temp = head;
        for(int b = 0; b < blocks; b++)
        {
            if(b == blockNumber)
            {
                
                temp->isAvaliable = true;
                temp->size = 0;
                return;
            }
        }
    }

    int getBytesAvaliable()
    {
        return bytesAvaliable;
    }
    
    int getBlocks()
    {
        return blocks;
    }

    void debug()
    {
        Block* temp = new Block();
        temp = head;
         while(temp->next != NULL)
            {
                //if(temp->isAvaliable)
                 std::cout << temp->allocatedSize << " " << temp->size;
                 if(temp->size < temp->allocatedSize)
                    std::cout << " different";
                    
                std::cout << std::endl;
                temp = temp->next;
            }
    }
    
};