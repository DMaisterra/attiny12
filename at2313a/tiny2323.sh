#/bin/bash

PROGNAME=$1

rm -f *.o *.elf *.out *.ihex *.hex 

avr-gcc -c -mmcu=attiny2313 -o $PROGNAME.o $PROGNAME.c &&\
avr-ld -o $PROGNAME.elf $PROGNAME.o &&\
avr-objcopy --output-target=ihex $PROGNAME.elf $PROGNAME.ihex &&\
avrdude -c usbasp -p t2313 -U flash:w:$PROGNAME.ihex  -q  &&\
rm -f *.o *.elf *.out *.?hex *.hex
