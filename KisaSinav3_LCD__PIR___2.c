// Pin tan�mlar�
sbit HareketSensoru_Pin at GPIOA_ODR.B0;
sbit KirmiziLed_Pin at GPIOB_ODR.B0;
sbit YesilLed_Pin at GPIOB_ODR.B1;

// Hareket durumunu tutacak de�i�ken
bit HareketVar = 0;

// LCD i�in gerekli tan�mlamalar
sbit LCD_RS at GPIOE_ODR.B8;
sbit LCD_EN at GPIOE_ODR.B10;
sbit LCD_D4 at GPIOE_ODR.B12;
sbit LCD_D5 at GPIOE_ODR.B13;
sbit LCD_D6 at GPIOE_ODR.B14;
sbit LCD_D7 at GPIOE_ODR.B15;
sbit LCD_BL at GPIOE_ODR.B9;

// LCD'ye string yazd�rmak i�in kullan�lacak fonksiyon
void LCD_Write_String(char *s) {
  while(*s) {
    LCD_Chr_Cp(*s);
    s++;
  }
}

void main() {
  // Pin konfig�rasyonlar�
  GPIO_Config(&GPIOA_BASE,
              _GPIO_PINMASK_0,
              _GPIO_CFG_MODE_INPUT | _GPIO_CFG_PULL_NO);

  GPIO_Config(&GPIOB_BASE,
              _GPIO_PINMASK_0 | _GPIO_PINMASK_1,
              _GPIO_CFG_MODE_OUTPUT | _GPIO_CFG_PULL_NO | _GPIO_CFG_SPEED_HIGH);

  // LCD konfig�rasyonlar�
  LCD_Config(&GPIOE_ODR,
             8, 10,
             12, 13, 14, 15,
             20, 4, 0, 0);

  // LCD ba�lat�l�yor
  LCD_Cmd(_LCD_CLEAR);
  LCD_Cmd(_LCD_CURSOR_OFF);
  LCD_Cmd(_LCD_SECOND_ROW);

  // Ba�lang��ta hareket alg�lanmad���ndan Ye�il Led yanacak
  YesilLed_Pin = 1;

  while(1) {
    // Hareket alg�land�ysa
    if(HareketSensoru_Pin == 1 && !HareketVar) {
      HareketVar = 1;

      // K�rm�z� Led yanacak
      KirmiziLed_Pin = 1;
      // Ye�il Led s�necek
      YesilLed_Pin = 0;

      // LCD'ye hareket alg�land� yazd�r�l�yor
      LCD_Cmd(_LCD_CLEAR);
      LCD_Out(1, 1, "Hareket Durumu");
      LCD_Out(2, 1, "Algilandi");
    }
    // Hareket alg�lanmad�ysa
    else if(HareketSensoru_Pin == 0 && HareketVar) {
      HareketVar = 0;

      // Ye�il Led yanacak
      YesilLed_Pin = 1;
      // K�rm�z� Led s�necek
      KirmiziLed_Pin = 0;

      // LCD'ye hareket alg�lanmad� yazd�r�l�yor
      LCD_Cmd(_LCD_CLEAR);
      LCD_Out(1, 1, "Hareket Durumu");
      LCD_Out(2, 1, "Alg�lanmad�");
 }
}
