#include "types.h"
#include "stat.h"
#include "user.h"

#define MAX_TICKET_ENTRIES 7
#define MIN_TICKETS 10
#define SLEEP_PERIOD 3

void
printusage()
{
    printf(1, "usage: schedtest loops tickets1 [ tickets2 ... ticketsN ]\n");
    printf(1, "loops must be greater than 0\n");
    printf(1, "tickets must be greater than or equal to %d\n", MIN_TICKETS);
    printf(1, "up to %d tickets can be provided\n", MAX_TICKET_ENTRIES);
}

int
main(int argc, char *argv[])
{
    // check for argument count
    if (argc < 3 || argc > (2 + MAX_TICKET_ENTRIES)) {
        printusage();
        exit();
    } 

    int loops = atoi(argv[1]);
    int i;
    int ticketentries = argc - 2;
    int ticketlist[ticketentries];

    //load arguments
    for (i = 0; i < ticketentries; i++) {
        ticketlist[i] = atoi(argv[i + 2]);
        if (ticketlist[i] < MIN_TICKETS) {
            printusage();
            exit();
        }
    }

    int pids[ticketentries];
    for (i = 0; i < ticketentries; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            settickets(ticketlist[i]);
            while(1);
        }
    }
    for (i = 0; i < loops; i++) {
        sleep(SLEEP_PERIOD);
        ps();
    }
    for (i = 0; i < ticketentries; i++) {
        kill(pids[i]);
    }

    exit();
}


