
# https://electronics.stackexchange.com/questions/2377/attiny13-avr-gcc-hello-world-uses-over-100-bytes
# www.tldp.org/HOWTO/Avr-Microcontrollers-in-Linux-Howto/x207.html

#avr-gcc -mmcu=atmega8 -Os ledblink.c -o ledblink.o -S
#avr-objcopy -j .text -j .data -O ihex  ledblink.o  ledblink.hex

rm -f *.o *.elf *.out *.?hex *.hex *.S

avr-gcc -mmcu=attiny2313 -Os  ledblink.c -o ledblink.o &&\
avr-gcc -mmcu=attiny2313 -Os  ledblink.c -S -o ledblink.S &&\
avr-objcopy -j .text -j .data -O ihex  ledblink.o  ledblink.ihex &&\

avrdude -c usbasp -p t2313 -U flash:w:ledblink.ihex  &&\
rm -f *.o *.elf *.out *.?hex *.hex 
