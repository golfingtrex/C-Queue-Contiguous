#include "queue.h"
#include "menu.h"

int main(void) {
    system("clear");
    Queue qu;
    CreateQueue(&qu);

    while(TRUE)
        DoCommand(GetCommand(), &qu);

    return 0;
}
