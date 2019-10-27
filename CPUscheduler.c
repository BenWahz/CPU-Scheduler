// Jace Laquerre & Henry Rice
// CS 201
// Assignment 4 - DES: Simulation of CPU Scheduler
// pqueue.jhibble.h and runSimulation base code taken from
// class GitLab with instructor permission

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "CPUscheduler.h"
#include "pqueue.jhibbele.h"

Process *createProcess(void) {
    Process *processArray = (Process *)malloc(sizeof(Process) * 5);
    int burstTimeQueue[5] = {6, 7, 2, 5, 2};
    for (int i = 0; i < 5; ++i) {
        processArray[i].pid = (i + 1);
        processArray[i].burstTime = burstTimeQueue[i];
    }
    return processArray;
}

void enqueueProcesses(PQueueNode **eventQueue, Process *processes, int numProcesses) {
    Event *event;
    int startTimeArray[5] = {0, 3, 4, 6, 6};
    // create an event for each process and send that to
    for (int i = 0; i < numProcesses; ++i) {
        event = (Event *) malloc(sizeof(Event));
        event->eventType = PROCESS_SUBMITTED;
        event->process = &processes[i];
        enqueue(eventQueue, startTimeArray[i], event);
    }
}

void runSimulation(int schedulerType, int quantum, PQueueNode *eventPQueue) {

    int numProcesses = 5;
    Process *process;
    int currentTime = 0, processMachineIsBusy = 0;
    int totalWaitTime = 0;
    int waitTime = 0;
    PQueueNode *processQueue = NULL;
    Event *event, *newEvent;
    currentTime = getMinPriority(eventPQueue);
    event = dequeue(&eventPQueue);
    while (event != NULL) {
        process = event->process;
        if (event->eventType == PROCESS_SUBMITTED){
            process->waitTime = currentTime;
            if (processMachineIsBusy == 0) { //CPU queue is empty / not busy
                printf("\nt = 0, Process id=%d PROCESS_SUBMITTED. ", process->pid);
                // create an event at currentTime to start this process
                newEvent = (Event *) malloc(sizeof(Event));
                newEvent->eventType = PROCESS_STARTS;
                newEvent->process = process;
                enqueue(&eventPQueue, currentTime, newEvent);
                processMachineIsBusy = 1;
            }
            else {
                // FCFS
                if (schedulerType == 1 || schedulerType == 3) {
                    //can't start: put this process in the process queue
                    printf("t = %d: Process id=%d PROCESS_SUBMITTED but must go into the processQueue", currentTime, process->pid);
                    enqueue(&processQueue, 0, process);
                }
                // SJF
                else if (schedulerType == 2) {
                    printf("t = %d: Process id=%d PROCESS_SUBMITTED but must go into the processQueue", currentTime, process->pid);
                    enqueue(&processQueue, process->burstTime, process);
                }
            }
        }
        else if (event->eventType == PROCESS_STARTS) {

            printf("t = %d: Process id=%d PROCESS_STARTS\n", currentTime, process->pid);
            waitTime = currentTime - process->waitTime;
            //printf("t = %d: Process id=%d PROCESS_STARTS; wait time = %d \n", currentTime, process->pid, waitTime);
            totalWaitTime += waitTime;
            // create an event in the future for the termination of this process
            if(schedulerType == 3 && quantum < (process->burstTime)) {
                newEvent = (Event *) malloc(sizeof(Event));
                newEvent->eventType =PROCESS_TIMESLICE_EXPIRES;
                newEvent->process = process;
                enqueue(&eventPQueue, currentTime + quantum, newEvent);
            }
            else {
                newEvent = (Event *) malloc(sizeof(Event));
                newEvent->eventType = PROCESS_ENDS;
                newEvent->process = process;
                enqueue(&eventPQueue, currentTime + process->burstTime, newEvent);
            }

        }
        else if (event->eventType == PROCESS_ENDS) {
            process = event->process;
            printf("t = %d: Process id=%d PROCESS_ENDS, wait time = %d", currentTime, process->pid, currentTime - process->burstTime );
            // see if there is a process in the thingQueue
            if (queueLength(processQueue) > 0) {
                    process = dequeue(&processQueue);
                    // create an event in the future for the termination of this process
                    newEvent = (Event *) malloc(sizeof(Event));
                    newEvent->eventType = PROCESS_STARTS;
                    newEvent->process = process;
                    enqueue(&eventPQueue, currentTime, newEvent);
            }
            else {
                // current process finished, so process machine is not busy
                processMachineIsBusy = 0;
            }
        }
        else if (event -> eventType == PROCESS_TIMESLICE_EXPIRES) {
            printf("\nt = %d: Process id=%d PROCESS_TIME_SLICE_EXPIRES\n", currentTime, process->pid);

            //enqueue process to back of CPUqueue
            process = event->process;
            process->burstTime = ((process->burstTime) - quantum);
            enqueue(&processQueue, 0, process);
            if (queueLength(processQueue) > 0) {
                process = dequeue(&processQueue);
                // create an event in the future for the restart of this process
                newEvent = (Event *) malloc(sizeof(Event));
                newEvent->eventType = PROCESS_STARTS;
                newEvent->process = process;
                enqueue(&eventPQueue, currentTime, newEvent);
                //processMachineIsBusy = 0; /////////////////
            }
        }
        currentTime = getMinPriority(eventPQueue);
        printf("\n");
        //printQueue(eventPQueue, (void (*)(void *)) printEvent);
        event = dequeue(&eventPQueue);
    }

    printf("\n");
    printf("%d things; mean wait time = %.2f\n", numProcesses,
           (double) totalWaitTime / numProcesses);

}

Process *createRandomProcesses(int numProcesses, double meanBurstTime) {
    Process *processArray = (Process *)malloc(sizeof(Process) * numProcesses);
    for (int i = 0; i < numProcesses; ++i) {
        processArray[i].pid = (i + 1);
        processArray[i].waitTime = 0;
        processArray[i].lastTime = 0;
        processArray[i].burstTime = (int) genExpRand(meanBurstTime);
    }
    return processArray;
}

void enqueueRandomProcesses(int numProcesses, PQueueNode **eventQueue, Process *processes, double meanIAT) {
    int t = 0;
    for (int i = 0; i < numProcesses; ++i) {
        Event *event = (Event *) malloc(sizeof(Event));
        memset(event, 0, sizeof(Event));
        event->eventType = PROCESS_SUBMITTED;
        event->process = &processes[i];
        enqueue(eventQueue, t, event);
        t = t + (int) genExpRand(meanIAT);
    }
}

int genExpRand (double mean) {
    double r, t;
    //int *seed48(int);
    //seed48(1);
    int rtnval;
    r = drand48();
    t = -log(1 - r) * mean;
    rtnval = (int) floor(t);
    if (rtnval == 0) {
        rtnval = 1;
    }
    return(rtnval);
}


int main() {
    int numProcesses = 5;
    int FCFS_TYPE = 1;
    int SJF_TYPE = 2;
    int RR_TYPE = 3;
    PQueueNode *eventQueue = NULL;
    eventQueue = NULL;
    double meanBurstTime = 25.0;
    double meanIAT = 25.0;

    Process *processArray = createProcess();
    enqueueProcesses(&eventQueue, processArray, numProcesses);
    // Run FCFS simulation
    runSimulation(FCFS_TYPE, 0, eventQueue);
    eventQueue = NULL;
    enqueueProcesses(&eventQueue, processArray, numProcesses);
    // Run SJF simulation
    runSimulation(SJF_TYPE,0, eventQueue);
    eventQueue = NULL;
    enqueueProcesses(&eventQueue, processArray, numProcesses);
    // Run RR simulation
    runSimulation(RR_TYPE,4, eventQueue);
    eventQueue = NULL;
    // Run experiments
    Process *randomProcessArray = createRandomProcesses(numProcesses, meanBurstTime);
    enqueueRandomProcesses(numProcesses, &eventQueue, randomProcessArray, meanIAT);

    // Experiments
    //runSimulation(SJF_TYPE,0, eventQueue);

}


