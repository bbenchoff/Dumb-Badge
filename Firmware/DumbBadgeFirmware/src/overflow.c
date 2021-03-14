/*
 * overflow.c
 *
 * Created: 3/8/2021 9:40:47 PM
 *  Author: bench
 */ 

#include <stdbool.h>
#include <stdio.h>

#include "overflow.h"

/*
	These are two naively-implemented queues, using arrays. One queue is
	implemented as a char array, the other is implemented as a uint8_t.
	
	The different types are important for reasons.
	
	When in a CSI state, the parser throws intermediate characters into
	queueParser. When an ending character is found in the incoming stream,
	(i.e. {ABCDEFGHIJKmPQWXZ}), everything is reassembled into queueParam.
		
		see queueTransmogrifier for this.
	
	queueTransmogrifier takes the intermediate characters and transforms them
	into parameters for the escape code. The contents of queueParam will be
	an array of ints, where the 0th position is the first parameter, the 1st
	position is the second, and so forth.
	
	These parameters are then acted upon by various escape code functions.
*/

int MAXSIZE = 50;		//50 should be enough for everything ¯\_(ツ)_/¯

char queueParser[50];
uint8_t queueParam[50];

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

	for(int i = 0 ; i < (MAXSIZE - 1) ; i++)
	{
		queueParam[i] = 0;
		queueParser[i] = 0;
	}
	
	frontParser = -1;
	frontParam = -1;
	rearParam = -1;
	rearParser = -1;
}

void queueTransmogrifier(void)
{
	/*
	This function converts queueParser into queueParam.
	
	The contents of queueParser are only chars 0-9 and ';'.
	This is converted to ints.
	Therefore if contents of queueParser are:
	[2],[4],[;],[8],[0]
	the contents of queueParser are:
	[24],[80]
	
	It's like reimplementing atoi() but it's not an interview question.
	*/
	
	int param = 0;
	char currentByte;
	
	while(!isEmptyParser())
	{
		
		currentByte = dequeueParser();		//deque from parser

		if(currentByte != 0x3B)
		{
			param = (10 * param) + (int)(currentByte-48);
		}
		else
		{
			enqueueParam(param);
			param = 0;	
		}
	}
	enqueueParam(param);
}
