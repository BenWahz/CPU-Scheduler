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
void enqueueProcesses(PQueueNode **eventPQueue, Process *processes, int numProcesses);
void runSimulation(int schedulerType, int quantum, PQueueNode *eventPQueue);

#endif //ASSINGMENT_3_CPUSCHEDULER_H
