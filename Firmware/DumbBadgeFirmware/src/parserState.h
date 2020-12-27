/*
 * parserState.h
 *
 * Created: 12/16/2020 2:03:38 PM
 *  Author: bench
 */ 


#ifndef PARSERSTATE_H
#define PARSERSTATE_H

typedef enum
{
	stateGround,
	stateESC,
	stateESCinter,
	stateCSIentry,
	stateCSIparam,
	stateCSIinter,
	stateCSIignore,
	
} parserState;

extern parserState currentState;


#endif /* PARSERSTATE_H */