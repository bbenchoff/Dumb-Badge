/*
 * parser.h
 *
 * Created: 11/19/2020 4:47:23 PM
 *  Author: bench
 */ 
#ifndef PARSER_H
#define PARSER_H

#define gnd_state 0;

void parseChar(uint8_t character);

void groundState(uint8_t character);
void escState(uint8_t character);

int nextTab(int a);

#endif

