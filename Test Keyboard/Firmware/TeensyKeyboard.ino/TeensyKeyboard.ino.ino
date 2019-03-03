#include <Keypad.h>

const byte ROWS = 5; //eight rows
const byte COLS = 16; //sixteen columns

//Don't fucking ask me what this macro is doing here
//I'm just copying and pasting LiKe A sOfTwArE eNgInEeR

#ifdef M
#undef M
#endif

#define M(n) ((n) & KEYCODE_MASK)

char keys[ROWS][COLS] = {
  {M(KEY_ESC),M(KEY_1),M(KEY_2),M(KEY_3),M(KEY_4),M(KEY_5),M(KEY_6),M(KEY_7),M(KEY_8),0,0,0,M(KEY_LEFT),M(KEY_DOWN),M(KEY_UP),M(KEY_RIGHT)},
  {M(MODIFIERKEY_GUI),M(KEY_TAB),M(KEY_Q),M(KEY_W),M(KEY_E),M(KEY_R),M(KEY_T),M(KEY_Y),M(KEY_U),M(KEY_9),M(KEY_0),M(KEY_MINUS),M(KEY_EQUAL),M(KEY_TILDE),M(KEY_BACKSPACE),M(KEY_PAUSE)},
  {0,M(KEY_CAPS_LOCK),M(MODIFIERKEY_CTRL),M(KEY_A),M(KEY_S),M(KEY_D),M(KEY_F),M(KEY_G),M(KEY_H),M(KEY_I),M(KEY_O),M(KEY_P),M(KEY_LEFT_BRACE),M(KEY_RIGHT_BRACE),M(KEY_ENTER),M(KEY_DELETE)},
  {0,M(KEY_SCROLL_LOCK),0,M(MODIFIERKEY_SHIFT),M(KEY_Z),M(KEY_X),M(KEY_C),M(KEY_V),M(KEY_B),M(KEY_J),M(KEY_K),M(KEY_L),M(KEY_SEMICOLON),M(KEY_QUOTE),M(MODIFIERKEY_RIGHT_SHIFT),M(KEY_BACKSLASH)},
  {M(MODIFIERKEY_RIGHT_ALT),M(MODIFIERKEY_RIGHT_GUI),0,M(MODIFIERKEY_GUI),M(MODIFIERKEY_ALT),M(KEY_SPACE),0,0,0,M(KEY_N),M(KEY_M),M(KEY_COMMA),M(KEY_PERIOD),M(KEY_SLASH),0,M(KEY_PRINTSCREEN)} 
};
byte rowPins[ROWS] = {19,20,21,22,23}; 
byte colPins[COLS] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; 

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

unsigned long loopCount;
unsigned long startTime;
String msg;
int x = 0;

void setup() {
    Serial.begin(9600);
    loopCount = 0;
    startTime = millis();
    msg = "";
}


void loop() {
    loopCount++;
    //char key = kpd.getKey();
    if ( (millis()-startTime)>5000 ) {
        Serial.print("Average loops per second = ");
        Serial.println(loopCount/5);
        startTime = millis();
        loopCount = 0;
    }
    
    
    // Fills kpd.key[ ] array with up-to 10 active keys.
    // Returns true if there are ANY active keys.
    if (kpd.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
            {
                switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:
                    msg = " PRESSED.";

                    
                    
                    Serial.print("Key ");
                Serial.print(kpd.key[i].kchar);
                Serial.println(msg);
                // release all the keys at the same instant
                 Keyboard.set_key1(kpd.key[i].kchar);
                Keyboard.send_now();
               
                //Keyboard.set_key1(0);
                //Keyboard.send_now();
                if (kpd.key[i].kchar == char(KEY_LEFT_SHIFT)) {
                  Serial.print("Shift ");
                  Keyboard.set_modifier(MODIFIERKEY_SHIFT);
                  Keyboard.send_now();
                  x=1;
             
        }
        
                break;
                 
                    case HOLD:
                    msg = " HOLD.";
                    //Keyboard.set_modifier(MODIFIERKEY_SHIFT);
                    //Keyboard.send_now();
                    
                    Keyboard.set_key1(kpd.key[i].kchar);
                Keyboard.send_now();
                    
                break;
                    case RELEASED:
                    msg = " RELEASED.";
                    Serial.println(msg);
                    Keyboard.set_key1(0);
                Keyboard.send_now();
                if (kpd.key[i].kchar == char(KEY_LEFT_SHIFT)) {
                  Serial.print("Shift Released ");
                  Keyboard.set_modifier(0);
                  Keyboard.send_now();
                  x=0;
                }
               
                break;
                    case IDLE:
                    msg = " IDLE.";
                    
                }
                
            }
        }
    }
} 
