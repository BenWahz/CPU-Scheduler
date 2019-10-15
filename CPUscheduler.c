//
// Created by jacel on 10/13/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "CPUscheduler.h"
#include "pqueue.jhibbele.h"

Process *createProcess() {
    Process *processArray = (Process *)malloc(sizeof(Process) * 5);
    for (int i = 0; i < 5; ++i) {
        memset(&processArray[i], 0, sizeof(Process));
    }

    processArray[0].pid = 1;
    processArray[0].burstTime = 6;
    processArray[1].pid = 2;
    processArray[1].burstTime = 7;
    processArray[2].pid = 3;
    processArray[2].burstTime = 2;
    processArray[3].pid = 4;
    processArray[3].burstTime = 5;
    processArray[4].pid = 5;
    processArray[4].burstTime = 2;
    return processArray;
}

void enqueueProcess(PQueueNode **eventPQueue, Process *processes, int numProcesses) {

    enqueue(PQueueNode **pqueue, int priority, void *data)


}

void runSimulation(int schedulerType, int quantum, PQueueNode *eventPQueue) {
    if (schedulerType == 0) {

    }
    else {

    }




    while (event != NULL) {
        if (event->eventType == PROCESS_SUBMITTED) {

        }
        else if (event->eventType == PROCESS_STARTS) {

        }
        else if (event->eventType == PROCESS_TIMESLICE_EXPIRES) {

        }
        else if (event->eventType == PROCESS_ENDS) {

        }
    }
}

int main() {
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
    Process *processArray = createProcess();

    // create an event for process
    for (int i = 0; i < 5; ++i) {
        event = (Event *) malloc(sizeof(Event));
        event->eventType = PROCESS_SUBMITTED;
        event->process = &processArray[i];
        enqueue(&eventQueue, startTime, event);
    }

}