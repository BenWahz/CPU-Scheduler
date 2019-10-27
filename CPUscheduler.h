//
// Created by jacel on 10/13/2019.
//

#ifndef ASSINGMENT_3_CPUSCHEDULER_H
#define ASSINGMENT_3_CPUSCHEDULER_H

typedef struct PQueueStruct {
    int priority;
    void *data;
    struct PQueueStruct *next;
} PQueueNode;

typedef struct {
    int pid;
    int burstTime;
    int waitTime;
    int numPreemptiions;
    int lastTime;
} Process;

typedef enum EventTypeEnum {
    PROCESS_SUBMITTED,
    PROCESS_STARTS,
    PROCESS_ENDS,
    PROCESS_TIMESLICE_EXPIRES
} EventType;

typedef struct {
    EventType eventType ;
    Process *process ;
} Event;

Process *createProcess(void);
int genExpRand(double mean);
void enqueueProcesses(PQueueNode **eventPQueue, Process *processes, int numProcesses);
void runSimulation(int schedulerType, int quantum, PQueueNode *eventPQueue);
Process *createRandomProcesses(int numProcesses, double meanBurstTime);
void enqueueRandomProcesses(int numProcesses, PQueueNode **eventQueue, Process *processes, double meanIAT);
#endif //ASSINGMENT_3_CPUSCHEDULER_H
