/*
 * overflow.c
 *
 * Created: 3/8/2021 9:40:47 PM
 *  Author: bench
 */ 

#include <stdbool.h>
#include <stdio.h>

#include "overflow.h"

int MAXSIZE = 20;
char queueParser[20];
uint8_t queueParam[20];
int frontParser = -1;
int frontParam = -1;
int rearParam = -1;
int rearParser = -1;

bool isEmptyParser(void)
{
	if(frontParser == -1)
	{
		return true;
	}
	return false;
}
bool isFullParser(void)
{
	if(rearParser == MAXSIZE - 1)
	{
		return true;
	}
	return false;
}
char dequeueParser(void)
{
	char temp;
	
	temp = queueParser[frontParser];
	frontParser++;
	if(frontParser > rearParser)
	{
		frontParser = rearParser = -1;
	}
	return temp;
}
void enqueueParser(char data)
{
	if(frontParser == -1)
	{
		frontParser = 0;
	}
	rearParser++;
	queueParser[rearParser] = data;
}



bool isEmptyParam(void)
{
	if(frontParam == -1)
	{
		return true;
	}
	return false;
}
bool isFullParam(void)
{
	if(rearParam == MAXSIZE - 1)
	{
		return true;
	}
	return false;
}

uint8_t dequeueParam(void)
{
	uint8_t temp;
	
	temp = queueParam[frontParam];
	frontParam++;
	if(frontParam > rearParam)
	{
		frontParam = rearParam = -1;
	}

	return temp;
}
void enqueueParam(uint8_t data)
{

	if(frontParam == -1)
	{
		frontParam = 0;
	}
	rearParam++;
	queueParam[rearParam] = data;

}

void clearQueues(void)
{
	
}