 #include "DAVE.h"

void delay(uint32_t count) {
	for (int x = 0; x < count; x++) {
		asm("nop");
	}
}
    int main(void)
    {
    	DAVE_Init();

       while(1U)
       {
    	   DIGITAL_IO_SetOutputHigh(&LED);
    	   delay(1000000); //1000000 -> 1 sec
    	   DIGITAL_IO_SetOutputLow(&LED);
    	   delay(1000000);

       }

       return 1U;
   }



