#/bin/bash

PROGNAME=$1

rm -f *.o *.elf *.out *.ihex *.hex 

avr-gcc -c -mmcu=attiny12 -o $PROGNAME.o $PROGNAME.S &&\
avr-ld -o $PROGNAME.elf $PROGNAME.o &&\
avr-objcopy --output-target=ihex $PROGNAME.elf $PROGNAME.ihex &&\
avrdude -c usbasp -p t12 -U flash:w:$PROGNAME.ihex  -q  &&\
rm -f *.o *.elf *.out *.?hex *.hex
