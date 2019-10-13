//
// Created by jacel on 10/13/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "CPUscheduler.h"

Process *createProcess() {
    Process *process1, *process2, *process3, *process4, *process5;
    process1 = (Process *)malloc(sizeof(Process));
    process2 = (Process *)malloc(sizeof(Process));
    process3 = (Process *)malloc(sizeof(Process));
    process4 = (Process *)malloc(sizeof(Process));
    process5 = (Process *)malloc(sizeof(Process));
    process1->pid = 1;
    process1->burstTime = 6;
    process2->pid = 2;
    process2->burstTime = 7;
    process3->pid = 3;
    process3->burstTime = 2;
    process4->pid = 4;
    process4->burstTime = 5;
    process5->pid = 5;
    process5->burstTime = 2;
    Process array[4];
    array[0] = *process1;
    array[1] = *process2;
    array[2] = *process3;
    array[3] = *process4;
    array[4] = *process5;
    return array;

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
        else if (event->eventType == PROCESS_TIMESLICE_EXPIRES) {

        }
        else if (event->eventType == PROCESS_ENDS) {

        }
    }
}

int main() {
    return 0;
}