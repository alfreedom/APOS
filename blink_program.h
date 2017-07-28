
const char blink_program[] = "/******************************************************\
\n * main.c\
\n *\
\n * Program Name:  Blink\
\n *         Date:  DATE\
\n *       Author:  YOUR_NAME\
\n *      License:  YOUR_LICENSE\
\n *\
\n * Description:\
\n *  Blink 8 leds connected on the PORTB of the AVR.\
\n * \
\n *****************************************************/\
\n#include <avr/io.h> \
\n#include <util/delay.h> \
\n\
\nvoid AVRInit()\
\n{\
\n  DDRB = 0xFF;  // PORTB as Output\
\n}\
\n\
\nint main()\
\n{\
\n  // Initialize the AVR modules\
\n  AVRInit();\
\n\
\n  // Infinite loop\
\n  while(1)\
\n  {\
\n    PORTB = 0xFF;   // PORTB High\
\n    _delay_ms(1000);  // Wait 1s\
\n    PORTB = 0x00;   // PORTB Low\
\n    _delay_ms(1000);  // Wait 1s\
\n  }\
\n\
\n  return 0;\
\n}\
\n";
