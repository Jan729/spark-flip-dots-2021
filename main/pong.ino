#include "names.h"

void UpdatePaddle1() {
  lastActive=millis();
  int dtV = digitalRead(ENCODER_DT_C);
  int deltaV = dtV == HIGH ? 1 : -1;
  lpaddle += deltaV;
  lpaddle = max(0, min(lpaddle, NUM_STRIPS - 1));
}

void UpdatePaddle2() {
  lastActive=millis();
  int dtH = digitalRead(ENCODER_DT_H);
  int deltaH = dtH == HIGH ? 1 : -1;
  rpaddle += deltaH;
  rpaddle = max(0, min(rpaddle, NUM_STRIPS - 1));
}

void pong() {
  attachInterrupt(digitalPinToInterrupt(ENCODER_CLK_C), UpdatePaddle1, FALLING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_CLK_H), UpdatePaddle2, FALLING);
  int ball_y = random(10, 22); //Ball y position
  int ball_x = random(10, 22); //Ball x position
  int ball_vy = 2 * random(0, 2) - 1; //Ball vertical speed
  int ball_vx = 2 * random(0, 2) - 1; //Ball horizontal speed
  uint32_t ball_colour = 0xff0000;
  uint32_t lpaddle_fill = 0xff00;
  uint32_t rpaddle_fill = 0xff;
  lpaddle = 0; //Vertical position of left paddle wrt to bottom pixel
  rpaddle = 0; //Vertical position of right paddle wrt to bottom pixel
  int ball_speed = 250; //ball delay between frames
  int paddle_speed = 50; //paddle delay between frames
  int play = 1;
  while (play) {
    if (shouldClearDisplay) {
      return;
    }
    if (ball_x == 0 || ball_x == NUM_LEDS_PER_STRIP - 1) {
      play = 0;
      break;
    } else if (ball_x == 1) {
      if ((ball_y >= lpaddle && ball_y < lpaddle + 5) || (ball_vy == -1 && ball_y == lpaddle + 5) || (ball_vy == 1 && ball_y == lpaddle - 1)) {
        ball_vx *= -1;
        if (ball_y == lpaddle + 5 || ball_y == lpaddle - 1) {
          ball_vy *= -1;
        }
      }
    } else if (ball_x == NUM_LEDS_PER_STRIP - 2) {
      if ((ball_y >= rpaddle && ball_y < rpaddle + 5) || (ball_vy == -1 && ball_y == rpaddle + 5) || (ball_vy == 1 && ball_y == rpaddle - 1)) {
        ball_vx *= -1;
        if (ball_y == rpaddle + 5 || ball_y == rpaddle - 1) {
          ball_vy *= -1;
        }
      }
    }
    if (ball_y == 0 || ball_y == NUM_STRIPS - 1) {
      ball_vy *= -1;
    }
    ball_y += ball_vy;
    ball_x += ball_vx;

    clearDisplay();
    changePixel(ball_colour, ball_y, ball_x);
    draw_paddle(lpaddle, 0, lpaddle_fill);
    draw_paddle(rpaddle, 31, rpaddle_fill);
    delay(ball_speed);
  }
  clearDisplay();
  detachInterrupt(digitalPinToInterrupt(ENCODER_CLK_H));
  detachInterrupt(digitalPinToInterrupt(ENCODER_CLK_C));

}
void draw_paddle(int ypos, int xpos, uint32_t fill) {
  int drawpos = (ypos > (NUM_STRIPS - 5)) ? (NUM_STRIPS - 5) : (ypos);
  for (int i = drawpos; i < drawpos + 5; i++) {
    leds[i][xpos] = CRGB(fill);
  }
  FastLED.show();
}