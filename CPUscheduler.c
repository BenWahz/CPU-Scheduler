//
// Created by jacel on 10/13/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "CPUscheduler.h"

Process *createProcess() {

}

void enqueueProcess(PQueueNode **eventPQueue, Process *processes, int numProcesses) {

}

void runSimulation(int schedulerType, int quantum, PQueueNode *eventPQueue) {
    Process *process;
    int numThings;
    Event *event, *newEvent;
    PQueueNode *eventQueue;
    PQueueNode *thingQueue;
    int i, startTime;
    int currentTime, thingMachineIsBusy;
    int totalWaitTime;
    int delta, waitTime;
    double d;


    event = (Event *) malloc(sizeof(Event));
    event->eventType = PROCESS_SUBMITTED;
    event->process = process;
    enqueueProcess(&eventQueue, startTime, event);

    while (event != NULL) {
        if (event->eventType == PROCESS_SUBMITTED) {

        }
        else if (event->eventType == PROCESS_STARTS) {

        }
        else if (event->eventType == PROCESS_ENDS) {

        }
    }
}

int main() {
    return 0;
}