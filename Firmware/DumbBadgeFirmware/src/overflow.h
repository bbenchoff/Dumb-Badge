/*
 * overflow.h
 *
 * Created: 3/8/2021 9:40:47 PM
 *  Author: bench
 */ 


bool isEmptyParser(void);
bool isFullParser(void);

bool isEmptyParam(void);
bool isFullParam(void);

char dequeueParser(void);
void enqueueParser(char);

uint8_t dequeueParam(void);
void enqueueParam(uint8_t);

void clearQueues(void);

void queueTransmogrifier(void);
