/*
 * parser.h
 *
 * Created: 11/19/2020 4:47:23 PM
 *  Author: bench
 */ 
#ifndef PARSER_H
#define PARSER_H

uint8_t stateEnterBuffer;

void parserInit(void);

void parseChar(uint8_t character);

void groundState(uint8_t character);
void escState(uint8_t character);
void escIntState(uint8_t character);
void CSIentryState(uint8_t character);
void CSIignoreState(uint8_t character);

int nextTab(int a);

#endif

