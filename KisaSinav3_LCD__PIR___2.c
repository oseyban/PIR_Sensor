// Pin tanýmlarý
sbit HareketSensoru_Pin at GPIOA_ODR.B0;
sbit KirmiziLed_Pin at GPIOB_ODR.B0;
sbit YesilLed_Pin at GPIOB_ODR.B1;

// Hareket durumunu tutacak deðiþken
bit HareketVar = 0;

// LCD için gerekli tanýmlamalar
sbit LCD_RS at GPIOE_ODR.B8;
sbit LCD_EN at GPIOE_ODR.B10;
sbit LCD_D4 at GPIOE_ODR.B12;
sbit LCD_D5 at GPIOE_ODR.B13;
sbit LCD_D6 at GPIOE_ODR.B14;
sbit LCD_D7 at GPIOE_ODR.B15;
sbit LCD_BL at GPIOE_ODR.B9;

// LCD'ye string yazdýrmak için kullanýlacak fonksiyon
void LCD_Write_String(char *s) {
  while(*s) {
    LCD_Chr_Cp(*s);
    s++;
  }
}

void main() {
  // Pin konfigürasyonlarý
  GPIO_Config(&GPIOA_BASE,
              _GPIO_PINMASK_0,
              _GPIO_CFG_MODE_INPUT | _GPIO_CFG_PULL_NO);

  GPIO_Config(&GPIOB_BASE,
              _GPIO_PINMASK_0 | _GPIO_PINMASK_1,
              _GPIO_CFG_MODE_OUTPUT | _GPIO_CFG_PULL_NO | _GPIO_CFG_SPEED_HIGH);

  // LCD konfigürasyonlarý
  LCD_Config(&GPIOE_ODR,
             8, 10,
             12, 13, 14, 15,
             20, 4, 0, 0);

  // LCD baþlatýlýyor
  LCD_Cmd(_LCD_CLEAR);
  LCD_Cmd(_LCD_CURSOR_OFF);
  LCD_Cmd(_LCD_SECOND_ROW);

  // Baþlangýçta hareket algýlanmadýðýndan Yeþil Led yanacak
  YesilLed_Pin = 1;

  while(1) {
    // Hareket algýlandýysa
    if(HareketSensoru_Pin == 1 && !HareketVar) {
      HareketVar = 1;

      // Kýrmýzý Led yanacak
      KirmiziLed_Pin = 1;
      // Yeþil Led sönecek
      YesilLed_Pin = 0;

      // LCD'ye hareket algýlandý yazdýrýlýyor
      LCD_Cmd(_LCD_CLEAR);
      LCD_Out(1, 1, "Hareket Durumu");
      LCD_Out(2, 1, "Algilandi");
    }
    // Hareket algýlanmadýysa
    else if(HareketSensoru_Pin == 0 && HareketVar) {
      HareketVar = 0;

      // Yeþil Led yanacak
      YesilLed_Pin = 1;
      // Kýrmýzý Led sönecek
      KirmiziLed_Pin = 0;

      // LCD'ye hareket algýlanmadý yazdýrýlýyor
      LCD_Cmd(_LCD_CLEAR);
      LCD_Out(1, 1, "Hareket Durumu");
      LCD_Out(2, 1, "Algýlanmadý");
 }
}
