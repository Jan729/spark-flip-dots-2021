#include "shader.h"
void color_gradient()
{
  for (int y = 0; y < 32; y++)
  {
    for (int x = 0; x < 32; x++)
    {
      leds[y][x] = CHSV(((x + y) * 16 + millis()/shader_clk_div * 8) / 8 % 256, 255, 255);
    }
  }
  FastLED.show();
  delay(10);
}

void diag()
{
  for (int y = 0; y < 32; y++)
  {
    for (int x = 0; x < 32; x++)
    {
      leds[y][x] = x == (y+millis()/shader_clk_div)%32 ? CRGB::Red : CRGB::Black;
    }
  }
}


void run_shader(){
  switch(s_mode){
    case S_GRADIENT:
      color_gradient();
      break;
    case S_DIAG:
      diag();
      break;
    default:
       break;
  }
}