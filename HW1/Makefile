############################################
# Won Yong Ha(woha)
# Partner: Brandon Burzon (brburzon)
# C335 HW1
# Makefile for test.o main.s ...
# Feb 9 2016 (Finished)

#Declare defult variables
ELF=$(notdir $(CURDIR)).elf
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
CFLAGS = -g -O1 -mcpu=cortex-m0 -mthumb 


#General All
all : test.o t1.o HW1.elf

#test.o
test.o : 
	$(CC) $(CFLAGS) -c test.c -c -o test.o


#t1.o
t1.o : 
	$(AS) -g -mcpu=cortex-m0 -mthumb t1.s -o t1.o 


#main.s
main.s : test.c
	arm-none-eabi-gcc -c -S -g -Wa,-a,-ad -O1 -mcpu=cortex-m0 -mthumb test.c -o main.s

#HW1.elf
HW1.elf : 
	$(CC) $(CFLAGS) --specs=rdimon.specs -lc -lrdimon t1.o test.o -o HW1.elf  

#test
test : HW1.elf
	qemu-system-arm  -cpu cortex-m3 -M versatilepb -nographic \
                   -monitor null -serial null \
                   -semihosting -kernel HW1.elf > output.txt

#clean 
clean : 
	rm HW1.elf
	rm t1.o
	rm test.o
