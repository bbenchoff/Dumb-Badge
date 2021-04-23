/*
 * settings.h
 *
 * Created: 6/29/2020 2:48:25 PM
 *  Author: bench
 */ 


#ifndef SETTINGS_H
#define SETTINGS_H




/*
struct Settings {
	
	bool localEcho;
	
};
*/


extern bool localEcho;
extern bool breakEnable;

//Line Feed / New Line is defined in VT100 Series Video Terminal
//Technical Manual Appendix A Page A-26
extern bool lineFeed;
extern int lineFeedNewLine;

extern bool autoWrap;	

bool capsLock;
bool scrollLock;
bool sPoNgEbObCaSe;

extern uint16_t defaultForegroundColor;
extern uint16_t defaultBackgroundColor;




#endif