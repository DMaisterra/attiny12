
rm -f *.o *.elf *.out *.?hex *.hex *.S

avr-gcc -mmcu=attiny2313 -Os  ledblink.c -o ledblink.o &&\
avr-gcc -mmcu=attiny2313 -Os  ledblink.c -S -o ledblink.S &&\
avr-objcopy -j .text -j .data -O ihex  ledblink.o  ledblink.ihex &&\

avrdude -c usbasp -p t2313 -U flash:w:ledblink.ihex  &&\
rm -f *.o *.elf *.out *.?hex *.hex 
