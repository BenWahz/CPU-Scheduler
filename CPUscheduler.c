// Jace Laquerre & Henry Rice
// CS 201
// Assignment 4 - DES: Simulation of CPU Scheduler
// pqueue.jhibble.h and runSimulation base code taken from
// class GitLab with instructor permission

#include <stdio.h>
#include <stdlib.h>
#include "CPUscheduler.h"
#include "pqueue.jhibbele.h"

Process *createProcess() {
    Process *processArray = (Process *)malloc(sizeof(Process) * 5);
    for (int i = 0; i < 5; ++i) {
        memset(&processArray[i], 0, sizeof(Process));
    }
    int burstTimeQueue[5] = {6, 7, 2, 5, 2};
    for (int i = 0; i < 5; ++i) {
        processArray[i].pid = (i + 1);
        processArray[i].burstTime = burstTimeQueue[i];
    }
   // processArray[0].pid = 1;
   // processArray[0].burstTime = 6;
    //processArray[1].pid = 2;
    //processArray[1].burstTime = 7;
    //processArray[2].pid = 3;
    //processArray[2].burstTime = 2;
    //processArray[3].pid = 4;
    //processArray[3].burstTime = 5;
    //processArray[4].pid = 5;
    //processArray[4].burstTime = 2;

    return processArray;
}

void enqueueProcesses(PQueueNode **eventQueue, Process *processes, int numProcesses) {
    Event *event;
    int startTimeArray[5] = {0, 3, 4, 6, 6};
    // create an event for each process and send that to
    for (int i = 0; i < numProcesses; ++i) {
        event = (Event *) malloc(sizeof(Event));
        *eventQueue = (PQueueNode *) malloc(sizeof(PQueueNode)); // possibily not a pointer in front here
        event->eventType = PROCESS_SUBMITTED;
        event->process = &processes[i];
        //(*eventQueue)->data = event;
        //(*eventQueue)->priority = startTimeArray[i];
        enqueue(eventQueue, startTimeArray[i], event);
    }
}

void runSimulation(int schedulerType, int quantum, PQueueNode *eventPQueue) {
   // if (schedulerType == 0) {

  //  }
   // else {

   // }
    int i, startTime;
    int numProcesses = 5;
    Process *process;
    int currentTime, thingMachineIsBusy = 0;
    int totalWaitTime = 0;
    int delta, waitTime;
    double d;
    PQueueNode *processQueue = NULL;
    Event *event, *newEvent;
    currentTime = getMinPriority(eventPQueue);
    event = dequeue(&eventPQueue);
    while (event != NULL) {
        process = event->process;
        if (event->eventType == PROCESS_SUBMITTED) {
            process->waitTime = currentTime;
            if (thingMachineIsBusy == 0) {
                // create an event at currentTime to start this process
                newEvent = (Event *) malloc(sizeof(Event));
                newEvent->eventType = PROCESS_STARTS;
                newEvent->process = process;
                enqueue(&eventPQueue, currentTime, newEvent);
                thingMachineIsBusy = 1;
            } else {
                // can't start: put this process in the process queue
                printf("t = %d: %d wants to start but must go into the processQueue\n", currentTime, process->pid);
                enqueue(&eventPQueue, 0, process);
            }
        } else if (event->eventType == PROCESS_STARTS) {
//      printf("t = %d: %s starts\n", currentTime, process->name);
            waitTime = currentTime - process->waitTime;
         //   printf("t = %d: %d starts; wait time = %d\n",
       //            currentTime, process->pid, waitTime);
            totalWaitTime += waitTime;
            // create an event in the future for the termination of this process
            newEvent = (Event *) malloc(sizeof(Event));
            newEvent->eventType = PROCESS_ENDS;
            newEvent->process = process;
            enqueue(&eventPQueue, currentTime + process->lastTime, newEvent);
        } else if (event->eventType == PROCESS_ENDS) {
            process = event->process;
            printf("t = %d: %d ends\n", currentTime, process->pid);
            // see if there is a process in the thingQueue
            if (queueLength(processQueue) > 0) {
                process = dequeue(&processQueue);
      printf("t = %d: %d starts; wait time = %d\n",
             currentTime, process->pid, waitTime);
                // create an event in the future for the termination of this process
                newEvent = (Event *) malloc(sizeof(Event));
                newEvent->eventType = PROCESS_STARTS;
                newEvent->process = process;
                enqueue(&eventPQueue, currentTime, newEvent);
            } else {
                // current process finished, so process machine is not busy
                thingMachineIsBusy = 0;
            }
        }

        currentTime = getMinPriority(eventPQueue);
       // if (currentTime >= 0)
           // printf("currentTime = %d\n", currentTime);
      //  printQueue(eventPQueue, printEvent);
      //  printf("\n");

        event = dequeue(&eventPQueue);
    }

    printf("\n");
    printf("%d things; mean wait time = %.2f\n", numProcesses,
           (double) totalWaitTime / numProcesses);

}

int main() {

    int numProcesses = 5;
    int FCFS_TYPE = 0;
    int SJF_TYPE = 1;
    PQueueNode *eventQueue = NULL;
    //eventQueue = NULL;


    Process *processArray = createProcess();
    enqueueProcesses(&eventQueue, processArray, numProcesses);
    // Rum FCFS simulation
    runSimulation(FCFS_TYPE, 0, eventQueue);
    //run SJF simulation
    runSimulation(SJF_TYPE,0, eventQueue);


    // create PQueueNode for each process
   // for (int i = 0; i < 5; ++i) {
   //     processQueue =(PQueueNode *) malloc(sizeof(PQueueNode));
   //     processQueue->data = &processArray[i];
   //     processQueue->priority = startTimeArray[i];
   //     enqueueProcess(&eventQueue, &processQueue, numProcesses);
   // }
}