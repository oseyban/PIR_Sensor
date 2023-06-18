
sbit LCD_RS at GPIOE_ODR.B8
sbit LCD_EN at GPIOE_ODR.B10
sbit LCD_D4 at GPIOE_ODR.B4;
sbit LCD_D5 at GPIOE_ODR.B5;
sbit LCD_D6 at GPIOE_ODR.B6;
sbit LCD_D7 at GPIOE_ODR.B7

void main() {         
GPIO_Digital_Input(&GPIOA_IDR, _GPIO_PINMASK_0)
GPIO_Digital_OUTPUT(&GPIOA_IDR, _GPIO_PINMASK_1|_GPIO_PINMASK_2)

ADC_Init();
Lcd_Init();
Lcd_Cmd(_CURSOR_OFF);
Lcd_Cmd(_LCD_CLEAR);
Lcd_Out(1,1,"Hareket Durumu" );

SYSCFG_EXTICR1=0;
EXTI_PR=1;
EXTI_FTSR=0;
EXTI_RTSR=1;
EXTI_EMR=0;
EXTI_IMR=1;
NVIC_IntEnable(IVT_INT_EXTI0);


while(1){
if( GPIOA_IDR.A0==1)
{
GPIOA_ODR.A1=1;
GPIOA_ODR.A2=0;
 Lcd_Out(2,1,"Hareket Algýlandý" );
}
else
{
GPIOA_ODR.A2=1;
GPIOA_ODR.A1=0;
 Lcd_Out(2,1,"Hareket Algýlanmadý" );
}

IntToStr(i,txt);
Lcd_Out(1,1,"ses degeri");
Lcd_Out(2,1,"%");
Lcd_Out_Cp(txt);


}

}

















