/*
 * Automatically generated C code by
 * KIELER SCCharts - The Key to Efficient Modeling
 *
 * http://rtsys.informatik.uni-kiel.de/kieler
 */

#include <stdio.h>

#include "TrafficLight_B.h"

void logic(TickData* d) {
  d->_pre_pending2 = d->_reg_pending2;
  d->_pre_pending1 = d->_reg_pending1;
  d->_pre_configSequence = d->_reg_configSequence;
  d->_g63 = d->_pg47;
  d->_g50 = d->_pg40;
  d->_g54 = d->_pg41;
  d->_g52_e1 = !(d->_g63 || d->_g50 || d->_g54);
  d->_g69 = d->_pg48;
  d->_g70 = d->_g69 && d->timerTick;
  if (d->_g70) {
    d->c++;
  }
  d->_pre_ewRequests = d->_reg_ewRequests;
  d->_g55 = d->_g54 && d->timerTick;
  if (d->_g55) {
    d->_TrafficLight_B_local_wEW++;
  }
  d->_cg63 = d->activeTask >= 2 && d->_pre_ewRequests > d->ewServed;
  d->_g64 = d->_g63 && d->_cg63;
  if (d->_g64) {
    d->ewServed = d->_pre_ewRequests;
    d->_TrafficLight_B_local_wEW = 0;
    d->LEDR = 8 + 4 + 128;
  }
  d->_g55 = d->_g55 || (d->_g54 && !d->timerTick) || d->_g64;
  d->_cg56 = d->_TrafficLight_B_local_wEW * 10 >= 4000 || d->c * 10 >= d->t4;
  d->_g64 = d->_g55 && d->_cg56;
  d->_cg57 = d->_TrafficLight_B_local_wEW * 10 >= 4000;
  d->_g54 = d->_g64 && d->_cg57;
  if (d->_g54) {
    d->ewServed = d->_pre_ewRequests;
  }
  d->_g63 = d->_g63 && !d->_cg63;
  d->_cg65 = !(d->activeTask >= 2 && d->_pre_ewRequests > d->ewServed);
  d->_g58 = d->_g54 || (d->_g63 && d->_cg65);
  if (d->_g58) {
    d->LEDR = 8 + 4;
  }
  d->_g59 = d->_g50 || d->_g58;
  d->_cg51 = d->c * 10 >= d->t4;
  d->_g50 = d->_g63 && !d->_cg65;
  d->_cg66 = d->c * 10 >= d->t4;
  d->_g65 = (d->_g59 && d->_cg51) || (d->_g64 && !d->_cg57) || (d->_g50 && d->_cg66);
  d->_g57 = !d->_g69;
  d->_g70 = d->_g70 || (d->_g69 && !d->timerTick);
  d->_cg71 = d->c * 10 >= d->t4;
  d->_g69 = d->_g70 && d->_cg71;
  d->_g52_e1 = (d->_g52_e1 || d->_g65) && (d->_g57 || d->_g69) && (d->_g65 || d->_g69);
  if (d->_g52_e1) {
    d->c = 0;
    d->LEDR = 16 + 4;
  }
  d->_g52 = d->_pg45;
  d->_g72_e2 = d->_g52 && d->timerTick;
  if (d->_g72_e2) {
    d->c++;
  }
  d->_g72 = d->_g52_e1 || d->_g72_e2 || (d->_g52 && !d->timerTick);
  d->_cg74 = d->c * 10 >= d->t5;
  d->_g88 = d->_g72 && d->_cg74;
  if (d->_g88) {
    d->c = 0;
    d->LEDR = 32 + 4;
  }
  d->_g73 = d->_pg51;
  d->_g87 = d->_g73 && d->timerTick;
  if (d->_g87) {
    d->c++;
  }
  d->_g82 = d->_g88 || d->_g87 || (d->_g73 && !d->timerTick);
  d->_cg76 = d->task == 3 && d->activeTask != 3;
  d->_g75 = d->_g82 && d->_cg76;
  if (d->_g75) {
    d->activeTask = 3;
    d->waitingConfig = 1;
  }
  d->_g83 = d->_g82 && !d->_cg76;
  d->_cg84 = d->task == 1 || d->task == 2 || d->task == 4;
  d->_g76 = d->_g83 && d->_cg84;
  if (d->_g76) {
    d->activeTask = d->task;
    d->waitingConfig = 0;
  }
  d->_g84 = d->_g75 || d->_g76 || (d->_g83 && !d->_cg84);
  d->_cg78 = d->activeTask >= 3 && d->_pre_configSequence != d->configApplied;
  d->_g77 = d->_g84 && d->_cg78;
  if (d->_g77) {
    d->t1 = d->_pre_pending1;
    d->t2 = d->_pre_pending2;
  }
  d->_g85 = d->_pg185;
  d->_g185 = d->_GO || d->_g85;
  if (d->_g185) {
    d->_pre_pending3 = d->_reg_pending3;
  }
  if (d->_g77) {
    d->t3 = d->_pre_pending3;
  }
  d->_pre_pending4 = d->_reg_pending4;
  if (d->_g77) {
    d->t4 = d->_pre_pending4;
  }
  d->_pre_pending5 = d->_reg_pending5;
  if (d->_g77) {
    d->t5 = d->_pre_pending5;
  }
  d->_pre_pending6 = d->_reg_pending6;
  if (d->_g77) {
    d->t6 = d->_pre_pending6;
    d->configApplied = d->_pre_configSequence;
    d->waitingConfig = 0;
    d->c = 0;
  }
  d->_g78 = d->_g77 || (d->_g84 && !d->_cg78);
  d->_cg80 = !d->waitingConfig && d->c * 10 >= d->t6;
  d->_g79 = d->_GO || (d->_g78 && d->_cg80);
  if (d->_g79) {
    d->_TrafficLight_B_local_wNS = 0;
    d->c = 0;
    d->LEDR = 32 + 1;
    d->_Atrig = 0;
  }
  d->_pre_nsRequests = d->_reg_nsRequests;
  d->_cg3 = d->activeTask >= 2 && d->_pre_nsRequests > d->nsServed;
  d->_g4 = d->_g79 && d->_cg3;
  if (d->_g4) {
    d->nsServed = d->_pre_nsRequests;
    d->_TrafficLight_B_local_wNS = 0;
    d->LEDR = 32 + 1 + 64;
  }
  d->_cg4 = d->_TrafficLight_B_local_wNS * 10 >= 4000 || d->_Atrig;
  d->_g5 = d->_g4 && d->_cg4;
  d->_cg5 = d->_TrafficLight_B_local_wNS * 10 >= 4000;
  d->_g5 = d->_g5 && d->_cg5;
  if (d->_g5) {
    d->nsServed = d->_pre_nsRequests;
  }
  d->_g19 = d->_g79 && !d->_cg3;
  d->_cg19 = !(d->activeTask >= 2 && d->_pre_nsRequests > d->nsServed);
  d->_g6 = d->_g5 || (d->_g19 && d->_cg19);
  if (d->_g6) {
    d->LEDR = 32 + 1;
  }
  d->_cg7 = d->_Atrig;
  d->_g27 = d->_pg19;
  d->_g28 = d->_g27 && d->timerTick;
  if (d->_g28) {
    d->c++;
  }
  d->_g33 = d->_pg28;
  d->_cg33 = d->c * 10 >= d->t1;
  d->_g34 = d->_g33 && d->_cg33;
  if (d->_g34) {
    d->_Atrig = 1;
  }
  d->_g9 = d->_pg7;
  d->_g13 = d->_pg10;
  d->_g14 = d->_g13 && d->timerTick;
  if (d->_g14) {
    d->_TrafficLight_B_local_wNS++;
  }
  d->_g21 = d->_pg15;
  d->_cg21 = d->activeTask >= 2 && d->_pre_nsRequests > d->nsServed;
  d->_g22 = d->_g21 && d->_cg21;
  if (d->_g22) {
    d->nsServed = d->_pre_nsRequests;
    d->_TrafficLight_B_local_wNS = 0;
    d->LEDR = 32 + 1 + 64;
  }
  d->_g22 = d->_g14 || (d->_g13 && !d->timerTick) || d->_g22;
  d->_cg15 = d->_TrafficLight_B_local_wNS * 10 >= 4000 || d->_Atrig;
  d->_g14 = d->_g22 && d->_cg15;
  d->_cg16 = d->_TrafficLight_B_local_wNS * 10 >= 4000;
  d->_g17 = d->_g14 && d->_cg16;
  if (d->_g17) {
    d->nsServed = d->_pre_nsRequests;
  }
  d->_g23 = d->_g21 && !d->_cg21;
  d->_cg23 = !(d->activeTask >= 2 && d->_pre_nsRequests > d->nsServed);
  d->_g17 = d->_g17 || (d->_g23 && d->_cg23);
  if (d->_g17) {
    d->LEDR = 32 + 1;
  }
  d->_g18 = d->_g9 || d->_g17;
  d->_cg10 = d->_Atrig;
  d->_g7 = (d->_g6 && !d->_cg7) || (d->_g18 && !d->_cg10);
  d->_g23 = d->_g23 && !d->_cg23;
  d->_cg24 = d->_Atrig;
  d->_g16 = (d->_g18 && d->_cg10) || (d->_g14 && !d->_cg16) || (d->_g23 && d->_cg24);
  d->_g10 = (d->_g4 && !d->_cg4) || (d->_g22 && !d->_cg15);
  d->_g15 = (d->_g19 && !d->_cg19) || (d->_g23 && !d->_cg24);
  d->_cg25 = d->_Atrig;
  d->_g4 = d->_g28 || (d->_g27 && !d->timerTick);
  d->_cg29 = d->_Atrig;
  d->_g19 = (d->_g79 && !d->_cg25) || (d->_g4 && !d->_cg29);
  d->_g24 = d->_g4 && d->_cg29;
  d->_g28 = d->_g79 || (d->_g33 && !d->_cg33);
  d->_g29 = !(d->_g21 || d->_g9 || d->_g13);
  d->_g2 = !d->_g27;
  d->_g9 = !d->_g33;
  d->_g13 = (d->_g29 || d->_g16) && (d->_g2 || d->_g24) && (d->_g9 || d->_g34) && (d->_g16 || d->_g24 || d->_g34);
  if (d->_g13) {
    d->c = 0;
    d->LEDR = 32 + 2;
  }
  d->_g21 = d->_pg60;
  d->_g27 = d->_g21 && d->timerTick;
  if (d->_g27) {
    d->c++;
  }
  d->_g33 = d->_g13 || d->_g27 || (d->_g21 && !d->timerTick);
  d->_cg36 = d->c * 10 >= d->t2;
  d->_g30 = d->_g33 && d->_cg36;
  if (d->_g30) {
    d->c = 0;
    d->LEDR = 32 + 4;
  }
  d->_g11 = d->_pg56;
  d->_g34 = d->_g11 && d->timerTick;
  if (d->_g34) {
    d->c++;
  }
  d->_g34_e3 = d->_g30 || d->_g34 || (d->_g11 && !d->timerTick);
  d->_cg38 = d->task == 3 && d->activeTask != 3;
  d->_g30_e2 = d->_g34_e3 && d->_cg38;
  if (d->_g30_e2) {
    d->activeTask = 3;
    d->waitingConfig = 1;
  }
  d->_g11_e1 = d->_g34_e3 && !d->_cg38;
  d->_cg92 = d->task == 1 || d->task == 2 || d->task == 4;
  d->_g95 = d->_g11_e1 && d->_cg92;
  if (d->_g95) {
    d->activeTask = d->task;
    d->waitingConfig = 0;
  }
  d->_g96 = d->_g30_e2 || d->_g95 || (d->_g11_e1 && !d->_cg92);
  d->_cg40 = d->activeTask >= 3 && d->_pre_configSequence != d->configApplied;
  d->_g35 = d->_g96 && d->_cg40;
  if (d->_g35) {
    d->t1 = d->_pre_pending1;
    d->t2 = d->_pre_pending2;
    d->t3 = d->_pre_pending3;
    d->t4 = d->_pre_pending4;
    d->t5 = d->_pre_pending5;
    d->t6 = d->_pre_pending6;
    d->configApplied = d->_pre_configSequence;
    d->waitingConfig = 0;
    d->c = 0;
  }
  d->_g91 = d->_g35 || (d->_g96 && !d->_cg40);
  d->_cg42 = !d->waitingConfig && d->c * 10 >= d->t3;
  d->_g37 = d->_g91 && d->_cg42;
  if (d->_g37) {
    d->_TrafficLight_B_local_wEW = 0;
    d->c = 0;
    d->LEDR = 8 + 4;
  }
  d->_cg44 = d->activeTask >= 2 && d->_pre_ewRequests > d->ewServed;
  d->_g90 = d->_g37 && d->_cg44;
  if (d->_g90) {
    d->ewServed = d->_pre_ewRequests;
    d->_TrafficLight_B_local_wEW = 0;
    d->LEDR = 8 + 4 + 128;
  }
  d->_cg45 = d->_TrafficLight_B_local_wEW * 10 >= 4000 || d->c * 10 >= d->t4;
  d->_g38 = d->_g90 && d->_cg45;
  d->_cg46 = d->_TrafficLight_B_local_wEW * 10 >= 4000;
  d->_g92 = d->_g38 && d->_cg46;
  if (d->_g92) {
    d->ewServed = d->_pre_ewRequests;
  }
  d->_g93 = d->_g37 && !d->_cg44;
  d->_cg60 = !(d->activeTask >= 2 && d->_pre_ewRequests > d->ewServed);
  d->_g39 = d->_g92 || (d->_g93 && d->_cg60);
  if (d->_g39) {
    d->LEDR = 8 + 4;
  }
  d->_cg48 = d->c * 10 >= d->t4;
  d->_g40 = (d->_g39 && !d->_cg48) || (d->_g59 && !d->_cg51);
  d->_g41 = (d->_g90 && !d->_cg45) || (d->_g55 && !d->_cg56);
  d->_g46 = d->_g93 && !d->_cg60;
  d->_cg61 = d->c * 10 >= d->t4;
  d->_g47 = (d->_g46 && !d->_cg61) || (d->_g50 && !d->_cg66);
  d->_cg67 = d->c * 10 >= d->t4;
  d->_g48 = (d->_g37 && !d->_cg67) || (d->_g70 && !d->_cg71);
  d->_g51 = d->_g78 && !d->_cg80;
  d->_g45 = d->_g72 && !d->_cg74;
  d->_g56 = d->_g91 && !d->_cg42;
  d->_g60 = d->_g33 && !d->_cg36;
  d->_g66 = d->_pg80;
  d->_cg102 = !d->NSraised;
  d->_g61 = d->_pg74;
  d->_g71 = d->_GO || (d->_g66 && d->_cg102) || d->_g61;
  d->_g43 = d->_g71 && d->NSraised;
  if (d->_g43) {
    d->nsRequests++;
  }
  d->_g80 = d->_g43 || (d->_g66 && !d->_cg102);
  d->_g74 = d->_g71 && !d->NSraised;
  d->_g42 = d->_pg100;
  d->_cg110 = !d->EWraised;
  d->_g36 = d->_pg99;
  d->_g104 = d->_GO || (d->_g42 && d->_cg110) || d->_g36;
  d->_g102 = d->_g104 && d->EWraised;
  if (d->_g102) {
    d->ewRequests++;
  }
  d->_g100 = d->_g102 || (d->_g42 && !d->_cg110);
  d->_g99 = d->_g104 && !d->EWraised;
  d->_g112 = d->_pg134;
  d->_g110 = d->_pg108;
  d->_g108 = d->_GO || d->_g110;
  if (d->_g108) {
    d->_pre_configApplied = d->_reg_configApplied;
  }
  d->_g107 = d->_pg138;
  d->_cg122 = d->_pre_configApplied == d->configSequence;
  d->_g165 = d->_g107 && d->_cg122;
  if (d->_g165) {
    d->configReady = 1;
  }
  d->_g141 = d->_pg116;
  d->_g123 = d->_GO || d->_g112 || d->_g165 || d->_g141;
  d->_cg115 = d->configValid && d->configReady;
  d->_g141 = d->_g123 && d->_cg115;
  d->_cg116 = d->configChar == 13;
  d->_g118 = d->_g141 && !d->_cg116;
  d->_cg119 = d->configChar == 10 && !d->badPacket && d->field == 5 && d->digits > 0 && d->number > 0;
  d->_g124 = d->_g118 && !d->_cg119;
  d->_cg124 = d->configChar == 10;
  d->_g125 = d->_g124 && d->_cg124;
  if (d->_g125) {
    d->configRejected++;
    d->field = 0;
    d->digits = 0;
    d->number = 0;
    d->badPacket = 0;
  }
  d->_g124 = d->_g124 && !d->_cg124;
  d->_cg126 = d->badPacket;
  d->_g127 = d->_g124 && !d->_cg126;
  d->_cg127 = d->configChar >= 48 && d->configChar <= 57 && d->digits < 4;
  d->_g128 = d->_g127 && d->_cg127;
  if (d->_g128) {
    d->number *= 10;
    d->number += d->configChar - 48;
    d->digits++;
  }
  d->_g127 = d->_g127 && !d->_cg127;
  d->_cg129 = d->configChar == 44 && d->digits > 0 && d->number > 0 && d->field == 0;
  d->_g130 = d->_g127 && d->_cg129;
  if (d->_g130) {
    d->staged1 = d->number;
    d->field++;
    d->digits = 0;
    d->number = 0;
  }
  d->_g129 = d->_g127 && !d->_cg129;
  d->_cg131 = d->configChar == 44 && d->digits > 0 && d->number > 0 && d->field == 1;
  d->_g132 = d->_g129 && d->_cg131;
  if (d->_g132) {
    d->staged2 = d->number;
    d->field++;
    d->digits = 0;
    d->number = 0;
  }
  d->_g131 = d->_g129 && !d->_cg131;
  d->_cg133 = d->configChar == 44 && d->digits > 0 && d->number > 0 && d->field == 2;
  d->_g134 = d->_g131 && d->_cg133;
  if (d->_g134) {
    d->staged3 = d->number;
    d->field++;
    d->digits = 0;
    d->number = 0;
  }
  d->_g133 = d->_g131 && !d->_cg133;
  d->_cg135 = d->configChar == 44 && d->digits > 0 && d->number > 0 && d->field == 3;
  d->_g136 = d->_g133 && d->_cg135;
  if (d->_g136) {
    d->staged4 = d->number;
    d->field++;
    d->digits = 0;
    d->number = 0;
  }
  d->_g135 = d->_g133 && !d->_cg135;
  d->_cg137 = d->configChar == 44 && d->digits > 0 && d->number > 0 && d->field == 4;
  d->_g138 = d->_g135 && d->_cg137;
  if (d->_g138) {
    d->staged5 = d->number;
    d->field++;
    d->digits = 0;
    d->number = 0;
  }
  d->_g137 = d->_g135 && !d->_cg137;
  if (d->_g137) {
    d->badPacket = 1;
  }
  d->_g134 = (d->_g141 && d->_cg116) || d->_g125 || (d->_g124 && d->_cg126) || d->_g128 || d->_g130 || d->_g132 || d->_g134 || d->_g136 || d->_g138 || d->_g137;
  d->_g132 = d->_g118 && d->_cg119;
  if (d->_g132) {
    d->pending1 = d->staged1;
    d->pending2 = d->staged2;
    d->pending3 = d->staged3;
    d->pending4 = d->staged4;
    d->pending5 = d->staged5;
    d->pending6 = d->number;
    d->configSequence++;
    d->configReady = 0;
    d->field = 0;
    d->digits = 0;
    d->number = 0;
    d->badPacket = 0;
  }
  d->_g138 = d->_g132 || (d->_g107 && !d->_cg122);
  d->_g116 = d->_g123 && !d->_cg115;
  d->_g139 = d->_pg145;
  d->_cg150 = d->timerTick && d->cameraArmed;
  d->_g128 = d->_g139 && d->_cg150;
  if (d->_g128) {
    d->camCount++;
  }
  d->_g136 = d->_GO || d->_g128 || (d->_g139 && !d->_cg150);
  if (d->_g136) {
    d->cameraActivated = 0;
    d->snapshotTaken = 0;
    d->vehicleLeft = 0;
  }
  d->_g125 = d->_pg126;
  d->_g126 = d->_GO || d->_g125;
  if (d->_g126) {
    d->_pre_vehicleButton = d->_reg_vehicleButton;
    d->_reg_vehicleButton = d->vehicleButton;
  }
  d->_cg144 = d->vehicleButton && !d->_pre_vehicleButton && d->vehiclePresent;
  d->_g130 = d->_g136 && d->_cg144;
  if (d->_g130) {
    d->vehiclePresent = 0;
    d->photographed = 0;
  }
  d->_cg145 = d->activeTask == 4;
  d->_g119 = d->_g130 && d->_cg145;
  if (d->_g119) {
    d->vehicleLeft = 1;
    printf("%s", "Vehicle left\n");
  }
  d->_g120 = d->_g136 && !d->_cg144;
  d->_cg156 = d->vehicleButton && !d->_pre_vehicleButton && !d->vehiclePresent;
  d->_g122 = d->_g120 && d->_cg156;
  if (d->_g122) {
    d->vehiclePresent = 1;
    d->photographed = 0;
  }
  d->_g115 = d->_g119 || (d->_g130 && !d->_cg145) || d->_g122 || (d->_g120 && !d->_cg156);
  d->_cg147 = d->activeTask != 4 || !d->vehiclePresent;
  d->_g150 = d->_g115 && d->_cg147;
  if (d->_g150) {
    d->cameraArmed = 0;
  }
  d->_g151 = d->_g115 && !d->_cg147;
  d->_cg152 = d->cameraArmed && d->camCount * 10 >= 1000;
  d->_g161 = d->_g151 && d->_cg152;
  if (d->_g161) {
    d->cameraArmed = 0;
    d->photographed = 1;
    d->snapshotTaken = 1;
    d->snapshots++;
    printf("%s", "Snapshot taken\n");
  }
  d->_g144 = d->_g151 && !d->_cg152;
  d->_cg154 = !d->cameraArmed && !d->photographed && (d->LEDR == 34 || d->LEDR == 20);
  d->_g156 = d->_g144 && d->_cg154;
  if (d->_g156) {
    d->camCount = 0;
    d->cameraArmed = 1;
    d->cameraActivated = 1;
    printf("%s", "Camera activated\n");
  }
  d->_g145 = d->_g150 || d->_g161 || d->_g156 || (d->_g144 && !d->_cg154);
  if (d->_g108) {
    d->_reg_configApplied = d->configApplied;
  }
  d->_reg_configSequence = d->configSequence;
  d->_reg_pending6 = d->pending6;
  d->_reg_pending5 = d->pending5;
  d->_reg_pending4 = d->pending4;
  if (d->_g185) {
    d->_reg_pending3 = d->pending3;
  }
  d->_reg_pending2 = d->pending2;
  d->_reg_pending1 = d->pending1;
  d->_reg_ewRequests = d->ewRequests;
  d->_reg_nsRequests = d->nsRequests;
  d->_cg205 = !(d->activeTask >= 2 && d->_pre_nsRequests > d->nsServed);
  d->_cg204 = d->activeTask >= 2 && d->_pre_nsRequests > d->nsServed;
}

void reset(TickData* d) {
  d->_GO = 1;
  d->_TERM = 0;
  d->t1 = 6000;
  d->t2 = 2000;
  d->t3 = 500;
  d->t4 = 6000;
  d->t5 = 2000;
  d->t6 = 500;
  d->activeTask = 1;
  d->LEDR = 33;
  d->configReady = 1;
  d->waitingConfig = 0;
  d->configApplied = 0;
  d->configRejected = 0;
  d->vehiclePresent = 0;
  d->cameraArmed = 0;
  d->cameraActivated = 0;
  d->snapshotTaken = 0;
  d->vehicleLeft = 0;
  d->snapshots = 0;
  d->photographed = 0;
  d->camCount = 0;
  d->configSequence = 0;
  d->pending1 = 0;
  d->pending2 = 0;
  d->pending3 = 0;
  d->pending4 = 0;
  d->pending5 = 0;
  d->pending6 = 0;
  d->field = 0;
  d->digits = 0;
  d->number = 0;
  d->staged1 = 0;
  d->staged2 = 0;
  d->staged3 = 0;
  d->staged4 = 0;
  d->staged5 = 0;
  d->badPacket = 0;
  d->nsRequests = 0;
  d->ewRequests = 0;
  d->nsServed = 0;
  d->ewServed = 0;
  d->c = 0;
  d->_reg_vehicleButton = 0;
  d->_reg_configApplied = 0;
  d->_reg_configSequence = 0;
  d->_reg_pending6 = 0;
  d->_reg_pending5 = 0;
  d->_reg_pending4 = 0;
  d->_reg_pending3 = 0;
  d->_reg_pending2 = 0;
  d->_reg_pending1 = 0;
  d->_reg_ewRequests = 0;
  d->_reg_nsRequests = 0;
  d->_pg47 = 0;
  d->_pg40 = 0;
  d->_pg41 = 0;
  d->_pg48 = 0;
  d->_pg45 = 0;
  d->_pg51 = 0;
  d->_pg185 = 0;
  d->_pg19 = 0;
  d->_pg28 = 0;
  d->_pg7 = 0;
  d->_pg10 = 0;
  d->_pg15 = 0;
  d->_pg60 = 0;
  d->_pg56 = 0;
  d->_pg80 = 0;
  d->_pg74 = 0;
  d->_pg100 = 0;
  d->_pg99 = 0;
  d->_pg134 = 0;
  d->_pg108 = 0;
  d->_pg138 = 0;
  d->_pg116 = 0;
  d->_pg145 = 0;
  d->_pg126 = 0;
}

void tick(TickData* d) {
  logic(d);

  d->_pg47 = d->_g47;
  d->_pg40 = d->_g40;
  d->_pg41 = d->_g41;
  d->_pg48 = d->_g48;
  d->_pg45 = d->_g45;
  d->_pg51 = d->_g51;
  d->_pg185 = d->_g185;
  d->_pg19 = d->_g19;
  d->_pg28 = d->_g28;
  d->_pg7 = d->_g7;
  d->_pg10 = d->_g10;
  d->_pg15 = d->_g15;
  d->_pg60 = d->_g60;
  d->_pg56 = d->_g56;
  d->_pg80 = d->_g80;
  d->_pg74 = d->_g74;
  d->_pg100 = d->_g100;
  d->_pg99 = d->_g99;
  d->_pg134 = d->_g134;
  d->_pg108 = d->_g108;
  d->_pg138 = d->_g138;
  d->_pg116 = d->_g116;
  d->_pg145 = d->_g145;
  d->_pg126 = d->_g126;
  d->_GO = 0;
}
