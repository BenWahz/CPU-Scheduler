// Jace Laquerre & Henry Rice
// CS 201
// Assignment 4 - DES: Simulation of CPU Scheduler
// pqueue.jhibble.h and runSimulation base code taken from
// class GitLab with instructor permission

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
        //*eventQueue = (PQueueNode *) malloc(sizeof(PQueueNode)); // possibily not a pointer in front here
        event->eventType = PROCESS_SUBMITTED;
        event->process = &processes[i];
        enqueue(eventQueue, startTimeArray[i], event);
    }
}

void runSimulation(int schedulerType, int quantum, PQueueNode *eventPQueue) {

    int i, startTime;
    int numProcesses = 5;
    Process *process;
    int currentTime = 0, processMachineIsBusy = 0;
    int totalWaitTime = 0;
    int delta, waitTime = 0;
    double d;
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

            //printf("t = %d: Process id=%d PROCESS_STARTS\n", currentTime, process->pid);
            waitTime = currentTime - process->waitTime;
            printf("t = %d: Process id=%d PROCESS_STARTS; wait time = %d \n", currentTime, process->pid, waitTime);
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
            printf("t = %d: Process id=%d PROCESS_ENDS, wait time = %d", currentTime, process->pid, waitTime);
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
            if (queueLength(processQueue) > 0) {
                //enqueue process to back of CPUqueue
                process = event->process;
                process->burstTime = ((process->burstTime) - quantum);
                enqueue(&processQueue, 0, process);
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

        event = dequeue(&eventPQueue);
    }

    printf("\n");
    printf("%d things; mean wait time = %.2f\n", numProcesses,
           (double) totalWaitTime / numProcesses);

}

int main() {
    int numProcesses = 5;
    int FCFS_TYPE = 1;
    int SJF_TYPE = 2;
    int RR_TYPE = 3;
    PQueueNode *eventQueue = NULL;
    eventQueue = NULL;

    Process *processArray = createProcess();
    enqueueProcesses(&eventQueue, processArray, numProcesses);
    // Rum FCFS simulation
    //runSimulation(FCFS_TYPE, 0, eventQueue);
    //run SJF simulation
    //runSimulation(SJF_TYPE,0, eventQueue);
    runSimulation(RR_TYPE,4, eventQueue);
}