/*
 * Timer.c
 *
 * Created: 9/4/2021 6:11:00 AM
 *  Author: Eslam Emara
 */ 

#include "Timer.h"

void __vector_10(void) __attribute__((signal,used));			//TIMER0 COMPARE MATCH ISR
void (*TIMER0_CM_ISR)(void);

void __vector_4(void) __attribute__((signal,used));				//TIMER2 COMPARE MATCH ISR
void (*TIMER2_CM_ISR)(void);

void __vector_7(void) __attribute__((signal,used));				//TIMER1 COMPARE MATCH A ISR
void (*TIMER1_CMA_ISR)(void);


#if (TIMER0_CTRL == ENABLED) || (TIMER1_CTRL == ENABLED)
	EN_PRESCALAR0_t PRESCALARS_0[5] = {PRESCALAR0_1,PRESCALAR0_8,PRESCALAR0_64,PRESCALAR0_256,PRESCALAR0_1024};		//array of all available prescalars of timer 0/1
#endif		

#if TIMER0_CTRL == ENABLED
	static void adjustPrescalarT0(EN_PRESCALAR0_t prescalar){					/*ADJUSTIN PRESCALAR BITS FOR TIMER0 */
		if(prescalar == PRESCALAR0_1){
			SETBIT(TCCR0,0);
			CLRBIT(TCCR0,1);
			CLRBIT(TCCR0,2);
		}
		else if(prescalar == PRESCALAR0_8){
			CLRBIT(TCCR0,0);
			SETBIT(TCCR0,1);
			CLRBIT(TCCR0,2);
		}
		else if(prescalar == PRESCALAR0_64){
			SETBIT(TCCR0,0);
			SETBIT(TCCR0,1);
			CLRBIT(TCCR0,2);
		}
		else if(prescalar == PRESCALAR0_256){
			CLRBIT(TCCR0,0);
			CLRBIT(TCCR0,1);
			SETBIT(TCCR0,2);
		}
		else if(prescalar == PRESCALAR0_1024){
		
			SETBIT(TCCR0,0);
			CLRBIT(TCCR0,1);
			SETBIT(TCCR0,2);
		}

	}
#endif

#if TIMER1_CTRL == ENABLED
static void adjustPrescalarT1(EN_PRESCALAR0_t prescalar){						/*ADJUSTIN PRESCALAR BITS FOR TIMER1 */
	if(prescalar == PRESCALAR0_1){
		SETBIT(TCCR1B,0);
		CLRBIT(TCCR1B,1);
		CLRBIT(TCCR1B,2);
	}
	else if(prescalar == PRESCALAR0_8){
		CLRBIT(TCCR1B,0);
		SETBIT(TCCR1B,1);
		CLRBIT(TCCR1B,2);
	}
	else if(prescalar == PRESCALAR0_64){
		SETBIT(TCCR1B,0);
		SETBIT(TCCR1B,1);
		CLRBIT(TCCR1B,2);
	}
	else if(prescalar == PRESCALAR0_256){
		CLRBIT(TCCR1B,0);
		CLRBIT(TCCR1B,1);
		SETBIT(TCCR1B,2);
	}
	else if(prescalar == PRESCALAR0_1024){
		
		SETBIT(TCCR1B,0);
		CLRBIT(TCCR1B,1);
		SETBIT(TCCR1B,2);
	}

}
#endif

#if TIMER2_CTRL == ENABLED
	EN_PRESCALAR2_t PRESCALARS_2[7] = {PRESCALAR2_1,PRESCALAR2_8,PRESCALAR2_32,PRESCALAR2_64,PRESCALAR2_128,PRESCALAR2_256,PRESCALAR2_1024}; //PRESCALARS OF TIMER2
	static void adjustPrescalarT2(EN_PRESCALAR2_t prescalar){				/*ADJUSTIN PRESCALAR BITS FOR TIMER2 */
		if(prescalar == PRESCALAR2_1){
			SETBIT(TCCR2,0);
			CLRBIT(TCCR2,1);
			CLRBIT(TCCR2,2);
		}
		else if(prescalar == PRESCALAR2_8){
			CLRBIT(TCCR2,0);
			SETBIT(TCCR2,1);
			CLRBIT(TCCR2,2);
		}
	
		else if(prescalar == PRESCALAR2_32){
			SETBIT(TCCR2,0);
			SETBIT(TCCR2,1);
			CLRBIT(TCCR2,2);
		}
		else if(prescalar == PRESCALAR2_64){
			CLRBIT(TCCR2,0);
			CLRBIT(TCCR2,1);
			SETBIT(TCCR2,2);
		}
		else if(prescalar == PRESCALAR2_128){
			SETBIT(TCCR2,0);
			CLRBIT(TCCR2,1);
			SETBIT(TCCR2,2);
		}
		else if(prescalar == PRESCALAR2_256){
			CLRBIT(TCCR2,0);
			SETBIT(TCCR2,1);
			SETBIT(TCCR2,2);
		}
		else if(prescalar == PRESCALAR2_1024){
		
			SETBIT(TCCR2,0);
			SETBIT(TCCR2,1);
			SETBIT(TCCR2,2);
		}

	}
#endif


/*
 *Initialization function for timers
 *PS============ MAKE SURE YOU ENABLE THE DESIRED TIMER IN THE CONFIG FILE ===============
 *INPUTS ST_TIMER_config_t (see Timers.h for definition)
 *void return
 */
void Timer_init(ST_TIMER_config_t config)
{
	if (config.mode == NORMAL_MODE)
		REG(config.timer) = 0x00;				//Normal Mode
		
	else if (config.mode == FAST_PWM){
		if (config.timer == TIMER0)
			SETBIT(PORTB_DIR,3);
		if (config.timer == TIMER2)
			SETBIT(PORTD_DIR,7);
		REG(config.timer) =0b01101001;			// FAST PWM with no prescalar and non inverting mode
	}											// for inverting mode 0b01111001
	
	else if (config.mode == CTC_MODE){
		if(config.timer == TIMER1){	
			TCCR1A = 0x00;
			SETBIT(TCCR1B,3);					//CTC MODE BITS
			CLRBIT(TCCR1B,4);
		}
		else{
			REG(config.timer) = 0b00001000;
		}
	}
}

/*
 *Function to delay for a period of time.
 *Conditions on desired delay ::: 255 < FREQ * desired < 216120 FOR timer 0 and timer 2
 *65536 < FREQ * desired < 67,108,864 for timer1 otherwise try to divide the delay on more than one time
 *==================================Config.mode must be NORMAL_MODE =====================================
 *INPUTS: desired delay in SECONDS , ST_TIMER_config_t timer config
 *Return 0 if the desired delay doesn't match the frequency
 *Return 1 in successful delay
 */

uint8_t Timer_Delay(float desired,ST_TIMER_config_t config)
{
	#if TIMER0_CTRL == ENABLED 
		if (config.timer == TIMER0){
			uint8_t i = 0;
			uint8_t found = 0;
			EN_PRESCALAR0_t prescalar = PRESCALAR0_1;	
		
			for(i=0;i<5;i++) {
				if((config.freq/PRESCALARS_0[i] < (255.0/desired)) && ((config.freq/PRESCALARS_0[i]) > 0)){					/*Find a suitable Prescalar through (FREQ/PRESCALAR) < (255/DESIRED DELAY)*/
					prescalar = PRESCALARS_0[i];
					found = 1;																							/* A suitable prescalar is found*/
					break;
				}
			}
		
			if (found==0){
				return 0;																/*No suitable prescalar is found ,Frequency mismatch the desired delay TRY TIMER 1*/
			}
			else{
				adjustPrescalarT0(prescalar);
				TCNT0 =(int) (255 - ((float)((config.freq*desired)/prescalar)));
				
				while(GETBIT(TIFR,0)==0);										/* Wait for overflow flag to rise*/
				SETBIT(TIFR,0);  												/* Clear the flag */
			
				return 1;
			}

		}
	#endif
	
	#if TIMER2_CTRL == ENABLED
		if (config.timer == TIMER2){
			
			uint8_t i = 0;
			uint8_t found = 0;
			EN_PRESCALAR2_t prescalar = PRESCALAR2_1;	
			for(i=0;i<7;i++){
				if((config.freq/PRESCALARS_2[i] < (255.0/desired)) && ((config.freq/PRESCALARS_2[i]) > 0)){
					prescalar = PRESCALARS_2[i];
					found = 1;
					break;
				}
			}
		
			if (found==0){												/*Frequency doesn't match desired delay try timer1*/
				return 0;
			}
			else{
				adjustPrescalarT2(prescalar);
				TCNT2 =(int) (255 - ((float)((config.freq*desired)/prescalar)));
				while(GETBIT(TIFR,6)==0);								 /* Wait for the overflow flag to rise */
				SETBIT(TIFR,6);  											/* Clear OF flag */
			
				return 1;
			}
		}
	#endif
	
	#if TIMER1_CTRL == ENABLED
	if (config.timer == TIMER1)
	{
		uint8_t i = 0;
		uint8_t found = 0;
		EN_PRESCALAR0_t prescalar = PRESCALAR0_1;
		
		for(i=0;i<5;i++){
			if(((uint16_t)(config.freq/PRESCALARS_0[i]) < (65536.0/desired)) && ((config.freq/PRESCALARS_0[i]) > 0.0)){				/*Find a suitable prescalar*/
				prescalar = PRESCALARS_0[i];
				found = 1;
				break;
			}
		}
		
		if (found==0){
			return 0;												/*Frequency doesn't match desired delay try dividing it*/
		}
		else{
			adjustPrescalarT1(prescalar);							/*Adjust PreScalars registers*/
			
			TCNT1H =((uint16_t) (65536 - ((float)((config.freq*desired)/prescalar)))) >> 8;			/*Put high 8 bits in high reg*/
			TCNT1L =((uint16_t) (65536 - ((float)((config.freq*desired)/prescalar)))) && 0x00FF;	/*put least 8 bits in low reg*/
			
			while(GETBIT(TIFR,2)==0);													/* Wait for overflow to rise */
			SETBIT(TIFR,2);  															/* Clear the flag */
			return 1;
		}

	}
	#endif
return 0;
}

/*
 *Function to generate PWM with 8bit resolution
 *INPUTS: uint8_t holds the duty cycle percentage, ST_TIMER_config_t timer config
 *CONDITIONs on input:  ============================== dutyCycle percentage must be between 0 and 100 ======================================
 *======================= PS:WORKS ON TIMER 0 AND TIMER 2 ONLY==============================
 *return 0 in input error type and 1 in success.
 */
uint8_t Timer_generate_8bitRes_PWM(uint8_t dutyCycle,ST_TIMER_config_t config)
{
	if (dutyCycle >=0 && dutyCycle <=100)								/*Check for valid input*/
	{
		#if TIMER0_CTRL == ENABLED
			
			if (config.timer == TIMER0){
				OCR0 = ((float)dutyCycle /0.01) * 255;						/*Generate pwm with duty cycle percentage of 255*/
			}
		#endif
			
		#if TIMER2_CTRL == ENABLED
			if (config.timer == TIMER2){
				OCR2 = ((float)dutyCycle /0.01) * 255;
			}
		#endif
		
		return 1;
	}
	else
		return 0;											/*DATA input error*/
}

/*
	*Function to do an event every period of time
	*INPUTS: desired delay in SECONDS , ST_TIMER_config_t timer config , Function takes void and return void
	*Conditions on desired delay ::: 255 < FREQ * desired < 216120 FOR timer 0 and timer 2
	*65536 < FREQ * desired < 67,108,864 for timer1 otherwise try to divide the delay on more than one time
	*==================================Config.mode must be CTC_MODE =====================================
	*Return 0 if the desired delay doesn't match the frequency
	*Return 1 in successful delay
 */

uint8_t Timer_Schedule_Fun(float delay,ST_TIMER_config_t config,void (*function)(void))
{
	if (config.mode == CTC_MODE)
	{
		SETBIT(STATUS_REG,7);								/*ENABLE_GLOBAL_INTERUPT*/	
		#if TIMER0_CTRL == ENABLED
			SETBIT(TIMSK,1);								/*ENABLE COMPARE ON MATCH TIMER0 INTERUPT*/
			if (config.timer == TIMER0){
				TIMER0_CM_ISR = function;						/*ASSIGN FUNCTION ISR*/
				uint8_t i = 0;
				uint8_t found = 0;
				EN_PRESCALAR0_t prescalar = PRESCALAR0_1;
			
				for(i=0;i<5;i++)
				{
					if((((config.freq*delay)/PRESCALARS_0[i]) < 255.0) && (((config.freq*delay)/PRESCALARS_0[i]) > 0.0))			/*Find a suitable Prescalar through (FREQ*DELAY)/PRESCALAR < 255*/
					{
						prescalar = PRESCALARS_0[i];
						found = 1;															/*A suitable prescalar is found*/
						break;
					}
				}
			
				if (found==0){
					return 0;																/*No suitable prescalar is found Frequency mismatch the desired delay*/
				}
				else{
					adjustPrescalarT0(prescalar);
					OCR0 =(int)((config.freq*delay)/prescalar);
					return 1;
				}
			}
			#endif
	
		#if TIMER2_CTRL == ENABLED
			SETBIT(TIMSK,7);									/*ENABLE COMPARE ON MATCH TIMER2 INTERUPT*/
			if (config.timer == TIMER2){
				TIMER2_CM_ISR = function;
				uint8_t i = 0;
				uint8_t found = 0;
				EN_PRESCALAR2_t prescalar = PRESCALAR2_1;
		
				for(i=0;i<7;i++){
					if((((config.freq*delay)/PRESCALARS_2[i]) < 255.0) && (((config.freq*delay)/PRESCALARS_2[i]) > 0.0)){	
						prescalar = PRESCALARS_2[i];
						found = 1;
						break;
					}
				}
			
				if (found==0){												/*Frequency doesn't match desired delay try 16-bit timer*/
					return 0;
				}
				else{
					adjustPrescalarT2(prescalar);
					OCR2 =(int)((config.freq*delay)/prescalar);
					return 1;
				}
			}
		#endif
	
		#if TIMER1_CTRL == ENABLED
			SETBIT(TIMSK,4);									/*ENABLE COMPARE ON MATCH TIMER1 INTERUPT*/
		
			if (config.timer == TIMER1)
			{

				TIMER1_CMA_ISR = function;
				uint8_t i = 0;
				uint8_t found = 0;
				EN_PRESCALAR0_t prescalar = PRESCALAR0_1;
				for(i=0;i<5;i++){
					if((uint16_t)(((config.freq*delay)/PRESCALARS_0[i]) < 65536.0) && (((config.freq*delay)/PRESCALARS_0[i]) > 0.0)){		/*Find a suitable Prescalar through (FREQ*DELAY)/PRESCALAR < 65536*/
						prescalar = PRESCALARS_0[i];
						found = 1;
						break;
					}
				}
	
				if (found==0){
					return 0;												/*Frequency doesn't match desired delay try dividing it*/
				}
				else{
					adjustPrescalarT1(prescalar);							/*Adjust PreScalars registers*/
		
					OCR1AH =((uint16_t) (((float)((config.freq*delay)/prescalar)))) >> 8;			/*Put high 8 bits in high reg*/
					OCR1AL =((uint16_t) (((float)((config.freq*delay)/prescalar)))) && 0x00FF;		/*put least 8 bits in low reg*/
		
					return 1;
				}
			}
		#endif
	}
return 0;
}
/*
	*Function to stop any desired timer
	*INPUTS: EN_TIMER_t (see Timer.h for definition)
	*Void return
 */
void Timer_Stop(EN_TIMER_t timer){
	if (timer == TIMER1){
		TCCR1B =0x00;
	}
	else{
		REG(timer) = 0x00;
	}
}


/* ISR DEFINITIONS */

void __vector_10(){
	TIMER0_CM_ISR();
}

void __vector_7(){
	TIMER1_CMA_ISR();
}

void __vector_4(){
	TIMER2_CM_ISR();
}
