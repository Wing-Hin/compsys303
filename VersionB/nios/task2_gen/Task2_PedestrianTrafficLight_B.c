/*
 * Automatically generated C code by
 * KIELER SCCharts - The Key to Efficient Modeling
 *
 * http://rtsys.informatik.uni-kiel.de/kieler
 */

#include "Task2_PedestrianTrafficLight_B.h"

void logic(TickData* d) {
  d->_g71 = d->_pg65_e2;
  d->_g74_e1 = !d->_g71;
  d->_g72 = d->_g71 && d->timerTick;
  if (d->_g72) {
    d->c++;
  }
  d->_g77 = d->_pg45_e1;
  d->_cg77 = d->c * 10 >= 500;
  d->_g78 = d->_g77 && d->_cg77;
  if (d->_g78) {
    d->_Atrig = 1;
  }
  d->_g71 = d->_g72 || (d->_g71 && !d->timerTick);
  d->_cg73 = d->_Atrig;
  d->_g72 = d->_g71 && d->_cg73;
  d->_g78_e2 = !d->_g77;
  d->_g74 = (d->_g74_e1 || d->_g72) && (d->_g78_e2 || d->_g78) && (d->_g72 || d->_g78);
  d->_g74_e1 = d->_GO || d->_g74;
  if (d->_g74_e1) {
    d->_Task2_PedestrianTrafficLight_B_local_wNS = 0;
    d->c = 0;
    d->LEDR = 32 + 1;
  }
  d->_g78 = d->_pg78_e2;
  d->_g78_e2 = d->_GO || d->_g78;
  if (d->_g78_e2) {
    d->_pre_nsRequests = d->_reg_nsRequests;
  }
  d->_cg3 = d->_pre_nsRequests > d->nsServed;
  d->_g79 = d->_g74_e1 && d->_cg3;
  if (d->_g79) {
    d->nsServed = d->_pre_nsRequests;
    d->_Task2_PedestrianTrafficLight_B_local_wNS = 0;
    d->LEDR = 32 + 1 + 64;
  }
  d->_cg4 = d->_Task2_PedestrianTrafficLight_B_local_wNS * 10 >= 4000 || d->c * 10 >= 6000;
  d->_g112 = d->_g79 && d->_cg4;
  d->_cg5 = d->_Task2_PedestrianTrafficLight_B_local_wNS * 10 >= 4000;
  d->_g5 = d->_g112 && d->_cg5;
  if (d->_g5) {
    d->nsServed = d->_pre_nsRequests;
  }
  d->_g19 = d->_g74_e1 && !d->_cg3;
  d->_cg19 = !(d->_pre_nsRequests > d->nsServed);
  d->_g6 = d->_g5 || (d->_g19 && d->_cg19);
  if (d->_g6) {
    d->LEDR = 32 + 1;
  }
  d->_cg7 = d->c * 10 >= 6000;
  d->_g28 = d->_pg20;
  d->_g29 = d->_g28 && d->timerTick;
  if (d->_g29) {
    d->c++;
  }
  d->_g9 = d->_pg7;
  d->_g13 = d->_pg10;
  d->_g14 = d->_g13 && d->timerTick;
  if (d->_g14) {
    d->_Task2_PedestrianTrafficLight_B_local_wNS++;
  }
  d->_g22 = d->_pg4;
  d->_cg22 = d->_pre_nsRequests > d->nsServed;
  d->_g23 = d->_g22 && d->_cg22;
  if (d->_g23) {
    d->nsServed = d->_pre_nsRequests;
    d->_Task2_PedestrianTrafficLight_B_local_wNS = 0;
    d->LEDR = 32 + 1 + 64;
  }
  d->_g23 = d->_g14 || (d->_g13 && !d->timerTick) || d->_g23;
  d->_cg15 = d->_Task2_PedestrianTrafficLight_B_local_wNS * 10 >= 4000 || d->c * 10 >= 6000;
  d->_g14 = d->_g23 && d->_cg15;
  d->_cg16 = d->_Task2_PedestrianTrafficLight_B_local_wNS * 10 >= 4000;
  d->_g17 = d->_g14 && d->_cg16;
  if (d->_g17) {
    d->nsServed = d->_pre_nsRequests;
  }
  d->_g24 = d->_g22 && !d->_cg22;
  d->_cg24 = !(d->_pre_nsRequests > d->nsServed);
  d->_g17 = d->_g17 || (d->_g24 && d->_cg24);
  if (d->_g17) {
    d->LEDR = 32 + 1;
  }
  d->_g18 = d->_g9 || d->_g17;
  d->_cg10 = d->c * 10 >= 6000;
  d->_g7 = (d->_g6 && !d->_cg7) || (d->_g18 && !d->_cg10);
  d->_g24 = d->_g24 && !d->_cg24;
  d->_cg25 = d->c * 10 >= 6000;
  d->_g16 = (d->_g18 && d->_cg10) || (d->_g14 && !d->_cg16) || (d->_g24 && d->_cg25);
  d->_g10 = (d->_g79 && !d->_cg4) || (d->_g23 && !d->_cg15);
  d->_g15 = d->_g19 && !d->_cg19;
  d->_cg20 = d->c * 10 >= 6000;
  d->_g4 = (d->_g15 && !d->_cg20) || (d->_g24 && !d->_cg25);
  d->_cg26 = d->c * 10 >= 6000;
  d->_g19 = d->_g29 || (d->_g28 && !d->timerTick);
  d->_cg30 = d->c * 10 >= 6000;
  d->_g20 = (d->_g74_e1 && !d->_cg26) || (d->_g19 && !d->_cg30);
  d->_g25 = d->_g19 && d->_cg30;
  d->_g29 = !(d->_g22 || d->_g9 || d->_g13);
  d->_g2 = !d->_g28;
  d->_g30 = (d->_g29 || d->_g16) && (d->_g2 || d->_g25) && (d->_g16 || d->_g25);
  if (d->_g30) {
    d->c = 0;
    d->LEDR = 32 + 2;
  }
  d->_g22 = d->_pg66;
  d->_g9 = d->_g22 && d->timerTick;
  if (d->_g9) {
    d->c++;
  }
  d->_g13 = d->_g30 || d->_g9 || (d->_g22 && !d->timerTick);
  d->_cg33 = d->c * 10 >= 2000;
  d->_g28 = d->_g13 && d->_cg33;
  if (d->_g28) {
    d->c = 0;
    d->LEDR = 32 + 4;
  }
  d->_g31 = d->_pg45;
  d->_g11 = d->_g31 && d->timerTick;
  if (d->_g11) {
    d->c++;
  }
  d->_g11_e1 = d->_g28 || d->_g11 || (d->_g31 && !d->timerTick);
  d->_cg35 = d->c * 10 >= 500;
  d->_g31_e2 = d->_g11_e1 && d->_cg35;
  if (d->_g31_e2) {
    d->_Task2_PedestrianTrafficLight_B_local_wEW = 0;
    d->c = 0;
    d->LEDR = 8 + 4;
  }
  d->_g88 = d->_pg32;
  d->_g32 = d->_GO || d->_g88;
  if (d->_g32) {
    d->_pre_ewRequests = d->_reg_ewRequests;
  }
  d->_cg37 = d->_pre_ewRequests > d->ewServed;
  d->_g87 = d->_g31_e2 && d->_cg37;
  if (d->_g87) {
    d->ewServed = d->_pre_ewRequests;
    d->_Task2_PedestrianTrafficLight_B_local_wEW = 0;
    d->LEDR = 8 + 4 + 128;
  }
  d->_cg38 = d->_Task2_PedestrianTrafficLight_B_local_wEW * 10 >= 4000 || d->c * 10 >= 6000;
  d->_g84 = d->_g87 && d->_cg38;
  d->_cg39 = d->_Task2_PedestrianTrafficLight_B_local_wEW * 10 >= 4000;
  d->_g34 = d->_g84 && d->_cg39;
  if (d->_g34) {
    d->ewServed = d->_pre_ewRequests;
  }
  d->_g85 = d->_g31_e2 && !d->_cg37;
  d->_cg53 = !(d->_pre_ewRequests > d->ewServed);
  d->_g108 = d->_g34 || (d->_g85 && d->_cg53);
  if (d->_g108) {
    d->LEDR = 8 + 4;
  }
  d->_cg41 = d->c * 10 >= 6000;
  d->_g39 = d->_pg59;
  d->_g40 = d->_g39 && d->timerTick;
  if (d->_g40) {
    d->c++;
  }
  d->_g43 = d->_pg41;
  d->_g47 = d->_pg50;
  d->_g48 = d->_g47 && d->timerTick;
  if (d->_g48) {
    d->_Task2_PedestrianTrafficLight_B_local_wEW++;
  }
  d->_g56 = d->_pg38;
  d->_cg56 = d->_pre_ewRequests > d->ewServed;
  d->_g57 = d->_g56 && d->_cg56;
  if (d->_g57) {
    d->ewServed = d->_pre_ewRequests;
    d->_Task2_PedestrianTrafficLight_B_local_wEW = 0;
    d->LEDR = 8 + 4 + 128;
  }
  d->_g48 = d->_g48 || (d->_g47 && !d->timerTick) || d->_g57;
  d->_cg49 = d->_Task2_PedestrianTrafficLight_B_local_wEW * 10 >= 4000 || d->c * 10 >= 6000;
  d->_g57 = d->_g48 && d->_cg49;
  d->_cg50 = d->_Task2_PedestrianTrafficLight_B_local_wEW * 10 >= 4000;
  d->_g51 = d->_g57 && d->_cg50;
  if (d->_g51) {
    d->ewServed = d->_pre_ewRequests;
  }
  d->_g58 = d->_g56 && !d->_cg56;
  d->_cg58 = !(d->_pre_ewRequests > d->ewServed);
  d->_g51 = d->_g51 || (d->_g58 && d->_cg58);
  if (d->_g51) {
    d->LEDR = 8 + 4;
  }
  d->_g52 = d->_g43 || d->_g51;
  d->_cg44 = d->c * 10 >= 6000;
  d->_g41 = (d->_g108 && !d->_cg41) || (d->_g52 && !d->_cg44);
  d->_g58 = d->_g58 && !d->_cg58;
  d->_cg59 = d->c * 10 >= 6000;
  d->_g44 = (d->_g52 && d->_cg44) || (d->_g57 && !d->_cg50) || (d->_g58 && d->_cg59);
  d->_g50 = (d->_g87 && !d->_cg38) || (d->_g48 && !d->_cg49);
  d->_g49 = d->_g85 && !d->_cg53;
  d->_cg54 = d->c * 10 >= 6000;
  d->_g38 = (d->_g49 && !d->_cg54) || (d->_g58 && !d->_cg59);
  d->_cg60 = d->c * 10 >= 6000;
  d->_g53 = d->_g40 || (d->_g39 && !d->timerTick);
  d->_cg64 = d->c * 10 >= 6000;
  d->_g59 = (d->_g31_e2 && !d->_cg60) || (d->_g53 && !d->_cg64);
  d->_g54 = d->_g53 && d->_cg64;
  d->_g63 = !(d->_g56 || d->_g43 || d->_g47);
  d->_g36 = !d->_g39;
  d->_g64 = (d->_g63 || d->_g44) && (d->_g36 || d->_g54) && (d->_g44 || d->_g54);
  if (d->_g64) {
    d->c = 0;
    d->LEDR = 16 + 4;
  }
  d->_g56 = d->_pg65;
  d->_g47 = d->_g56 && d->timerTick;
  if (d->_g47) {
    d->c++;
  }
  d->_g43 = d->_g64 || d->_g47 || (d->_g56 && !d->timerTick);
  d->_cg67 = d->c * 10 >= 2000;
  d->_g62 = d->_g43 && d->_cg67;
  if (d->_g62) {
    d->c = 0;
    d->LEDR = 32 + 4;
    d->_Atrig = 0;
  }
  d->_cg69 = d->_Atrig;
  d->_g65_e2 = (d->_g62 && !d->_cg69) || (d->_g71 && !d->_cg73);
  d->_g45_e1 = d->_g62 || (d->_g77 && !d->_cg77);
  d->_g65 = d->_g43 && !d->_cg67;
  d->_g45 = d->_g11_e1 && !d->_cg35;
  d->_g66 = d->_g13 && !d->_cg33;
  d->_g81 = d->_pg68;
  d->_cg94 = !d->NSraised;
  d->_g82 = d->_pg67;
  d->_g73 = d->_GO || (d->_g81 && d->_cg94) || d->_g82;
  d->_g77 = d->_g73 && d->NSraised;
  if (d->_g77) {
    d->nsRequests++;
  }
  d->_g68 = d->_g77 || (d->_g81 && !d->_cg94);
  d->_g67 = d->_g73 && !d->NSraised;
  d->_g35 = d->_pg94;
  d->_cg102 = !d->EWraised;
  d->_g33 = d->_pg91;
  d->_g96 = d->_GO || (d->_g35 && d->_cg102) || d->_g33;
  d->_g92 = d->_g96 && d->EWraised;
  if (d->_g92) {
    d->ewRequests++;
  }
  d->_g94 = d->_g92 || (d->_g35 && !d->_cg102);
  d->_g91 = d->_g96 && !d->EWraised;
  if (d->_g32) {
    d->_reg_ewRequests = d->ewRequests;
  }
  if (d->_g78_e2) {
    d->_reg_nsRequests = d->nsRequests;
  }
}

void reset(TickData* d) {
  d->_GO = 1;
  d->_TERM = 0;
  d->LEDR = 33;
  d->nsRequests = 0;
  d->ewRequests = 0;
  d->nsServed = 0;
  d->ewServed = 0;
  d->c = 0;
  d->_reg_ewRequests = 0;
  d->_reg_nsRequests = 0;
  d->_pg65_e2 = 0;
  d->_pg45_e1 = 0;
  d->_pg78_e2 = 0;
  d->_pg20 = 0;
  d->_pg7 = 0;
  d->_pg10 = 0;
  d->_pg4 = 0;
  d->_pg66 = 0;
  d->_pg45 = 0;
  d->_pg32 = 0;
  d->_pg59 = 0;
  d->_pg41 = 0;
  d->_pg50 = 0;
  d->_pg38 = 0;
  d->_pg65 = 0;
  d->_pg68 = 0;
  d->_pg67 = 0;
  d->_pg94 = 0;
  d->_pg91 = 0;
}

void tick(TickData* d) {
  logic(d);

  d->_pg65_e2 = d->_g65_e2;
  d->_pg45_e1 = d->_g45_e1;
  d->_pg78_e2 = d->_g78_e2;
  d->_pg20 = d->_g20;
  d->_pg7 = d->_g7;
  d->_pg10 = d->_g10;
  d->_pg4 = d->_g4;
  d->_pg66 = d->_g66;
  d->_pg45 = d->_g45;
  d->_pg32 = d->_g32;
  d->_pg59 = d->_g59;
  d->_pg41 = d->_g41;
  d->_pg50 = d->_g50;
  d->_pg38 = d->_g38;
  d->_pg65 = d->_g65;
  d->_pg68 = d->_g68;
  d->_pg67 = d->_g67;
  d->_pg94 = d->_g94;
  d->_pg91 = d->_g91;
  d->_GO = 0;
}
