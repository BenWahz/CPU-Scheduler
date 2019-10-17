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

void enqueueProcesses(PQueueNode **eventQueue, Process *processes, int numProcesses) {
    Event *event;
    int startTimeArray[5] = {0, 3, 4, 6, 6};
    // create an event for each process and send that to
    for (int i = 0; i < numProcesses; ++i) {
        event = (Event *) malloc(sizeof(Event));
        eventQueue = (PQueueNode *) malloc(sizeof(PQueueNode));
        event->eventType = PROCESS_SUBMITTED;
        event->process = &processes[i];
        //(*eventQueue)->data = event;
        //(*eventQueue)->priority = startTimeArray[i];
        enqueue(eventQueue, startTimeArray[i], event);
    }
}

void runSimulation(int schedulerType, int quantum, PQueueNode *eventPQueue) {
    if (schedulerType == 0) {

    }
    else {

    }




    while (event != NULL) {
        if (event->eventType == PROCESS_SUBMITTED) {
            if (thingMachineIsBusy == 0) {

            }

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
    int numProcesses = 5;

    PQueueNode *eventQueue;
    PQueueNode *processQueue;
    //int i, startTime;
    int currentTime, thingMachineIsBusy;
    int totalWaitTime;
    int delta, waitTime;
    double d;
    eventQueue = NULL;
    Process *processArray = createProcess();
    enqueueProcesses(&eventQueue, processArray, numProcesses);
    runSimulation();
    // start times for processes


    // create PQueueNode for each process
   // for (int i = 0; i < 5; ++i) {
   //     processQueue =(PQueueNode *) malloc(sizeof(PQueueNode));
   //     processQueue->data = &processArray[i];
   //     processQueue->priority = startTimeArray[i];
   //     enqueueProcess(&eventQueue, &processQueue, numProcesses);
   // }
}