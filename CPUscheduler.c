//
// Created by jacel on 10/13/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "CPUscheduler.h"

Process *createProcess() {

}

void enqueueProcess(PQueueNode **eventPQueue, Process *processes, int numProcesses) {
    PQueueNode *current;
    current = *eventPQueue;
    PQueueNode *new_node;

    new_node = (PQueueNode *)malloc(sizeof(PQueueNode));
    new_node->next=NULL;
    new_node->priority = processes->burstTime;
    new_node->data = processes;

    if(*eventPQueue != NULL) //if list is NOT empty
    {
        //PQueueNode *next_node = current->next;

        //if the current process is a higher priority than the Process we are enqueing
        if((*eventPQueue)->priority > processes->burstTime)
        {
            new_node->next = *eventPQueue;
            *eventPQueue = new_node;
        }
        while(current->next != NULL && current->next->priority <=  processes->burstTime)
        {
            current = current->next;
        }
        if (current->next == NULL && current->priority < processes->burstTime)
        {
            current->next = new_node;
            new_node->next = NULL;
        }
        else
        {
            new_node->next = current->next;
            current->next = new_node;
        }
    }
    else
    {
        //when this is the first node entered into the queue
        *eventPQueue = new_node;

    }
    
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