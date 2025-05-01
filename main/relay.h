#pragma once

#define RELAY_CH_A 0
#define RELAY_CH_B 1

void relay_setup();
void relay_enable(int channel);
void relay_disable(int channel);

