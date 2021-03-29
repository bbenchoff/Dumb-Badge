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
void CSIparamState(uint8_t character);
bool isValidCSIEscapeCode(uint8_t character);


///These are ESC mnemonic functions
void SC(void);
void RC(void);
void IND(void);
void NEL(void);
void RI(void);
void RIS(void);
void HTS(void);

//These are CSI mnemonic functions
void CUU(void);
void CUD(void);
void CUF(void);
void CUB(void);
void CNL(void);
void CPL(void);
void CHA(void);
void CUP(void);
void CHT(void);
void ED(void);
void EL(void);
void SGR(void);
void DCH(void);
void SEM(void);
void CTC(void);
void ECH(void);
void CBT(void);
void ICH(void);
void DSR(void);


int nextTab(int a);

#endif

