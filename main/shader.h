#ifndef SHADER_H
#define SHADER_H

enum shader_mode{
  S_GRADIENT, S_DIAG
};
uint8_t shader_clk_div = 10;
shader_mode s_mode = S_GRADIENT;

void run_shader();

#endif 