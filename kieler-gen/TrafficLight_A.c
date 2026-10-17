/*
 * Automatically generated C code by
 * KIELER SCCharts - The Key to Efficient Modeling
 *
 * http://rtsys.informatik.uni-kiel.de/kieler
 */

#include "TrafficLight_A.h"

void logic(TickData* d) {
  d->_g210 = d->_pg199;
  if (d->_g210) {
    d->c += d->deltaT;
  }
  d->sleepT = 1000.0;
  d->_pre_configSequence = d->_reg_configSequence;
  d->_g91 = d->_pg79;
  d->_g73 = d->_pg70;
  d->_g85 = d->_pg71;
  d->_g77 = d->_pg74;
  d->_g75_e1 = !(d->_g91 || d->_g73 || d->_g85 || d->_g77);
  d->_pre_ewRequests = d->_reg_ewRequests;
  d->_g109 = d->_pg89;
  if (d->_g109) {
    d->_TrafficLight_A_local_wEW += d->deltaT;
  }
  d->_cg91 = d->activeTask >= 2 && d->_pre_ewRequests > d->ewServed;
  d->_g92 = d->_g91 && d->_cg91;
  if (d->_g92) {
    d->ewServed = d->_pre_ewRequests;
    d->_TrafficLight_A_local_wEW = 0.0;
    d->_taken_transitions[15] += 1;
    d->LEDR = 8 + 4 + 128;
  }
  d->_g77 = d->_g77 || d->_g85 || d->_g92;
  d->_cg78 = d->_TrafficLight_A_local_wEW < 4.0;
  d->_g85 = d->_g77 && d->_cg78;
  if (d->_g85) {
    d->sleepT = (d->sleepT < (4.0 - d->_TrafficLight_A_local_wEW)) ? d->sleepT : (4.0 - d->_TrafficLight_A_local_wEW);
  }
  d->_cg79 = d->_TrafficLight_A_local_wEW >= 4.0 || d->c >= d->t4;
  d->_g92 = d->_g77 && !d->_cg78;
  d->_cg83 = d->_TrafficLight_A_local_wEW >= 4.0 || d->c >= d->t4;
  d->_g78 = (d->_g85 && d->_cg79) || (d->_g92 && d->_cg83);
  d->_cg80 = d->_TrafficLight_A_local_wEW >= 4.0;
  d->_g81 = d->_g78 && d->_cg80;
  if (d->_g81) {
    d->ewServed = d->_pre_ewRequests;
    d->_taken_transitions[17] += 1;
  }
  d->_g91 = d->_g91 && !d->_cg91;
  d->_cg93 = !(d->activeTask >= 2 && d->_pre_ewRequests > d->ewServed);
  d->_g94 = d->_g91 && d->_cg93;
  if (d->_g94) {
    d->_taken_transitions[16] += 1;
  }
  d->_g81 = d->_g81 || d->_g94;
  if (d->_g81) {
    d->LEDR = 8 + 4;
  }
  d->_g94 = d->_g73 || d->_g81;
  d->_cg74 = d->c >= d->t4;
  d->_g73 = d->_g91 && !d->_cg93;
  d->_cg95 = d->c >= d->t4;
  d->_g82 = (d->_g94 && d->_cg74) || (d->_g78 && !d->_cg80) || (d->_g73 && d->_cg95);
  d->_g93 = d->_pg95;
  d->_g80 = d->_pg83;
  d->_g102_e2 = !(d->_g93 || d->_g80);
  d->_g105 = d->_g80 || d->_g93;
  d->_cg100 = d->c < d->t4;
  d->_g99 = d->_g105 && d->_cg100;
  if (d->_g99) {
    d->sleepT = (d->sleepT < (d->t4 - d->c)) ? d->sleepT : (d->t4 - d->c);
  }
  d->_cg101 = d->c >= d->t4;
  d->_g100 = d->_g105 && !d->_cg100;
  d->_cg103 = d->c >= d->t4;
  d->_g102 = (d->_g99 && d->_cg101) || (d->_g100 && d->_cg103);
  d->_g110_e3 = !d->_g109;
  d->_cg109 = d->c >= d->t4;
  d->_g110 = d->_g109 && d->_cg109;
  d->_g102 = (d->_g75_e1 || d->_g82) && (d->_g102_e2 || d->_g102) && (d->_g110_e3 || d->_g110) && (d->_g82 || d->_g102 || d->_g110);
  if (d->_g102) {
    d->_taken_transitions[14] += 1;
    d->c = 0.0;
    d->LEDR = 16 + 4;
  }
  d->_g110 = d->_pg65;
  d->_g75 = d->_pg117;
  d->_g102_e2 = d->_g102 || d->_g110 || d->_g75;
  d->_cg112 = d->c < d->t5;
  d->_g110_e3 = d->_g102_e2 && d->_cg112;
  if (d->_g110_e3) {
    d->sleepT = (d->sleepT < (d->t5 - d->c)) ? d->sleepT : (d->t5 - d->c);
  }
  d->_cg113 = d->c >= d->t5;
  d->_g75_e1 = d->_g102_e2 && !d->_cg112;
  d->_cg137 = d->c >= d->t5;
  d->_g139 = (d->_g110_e3 && d->_cg113) || (d->_g75_e1 && d->_cg137);
  if (d->_g139) {
    d->_taken_transitions[18] += 1;
    d->c = 0.0;
    d->LEDR = 32 + 4;
    d->_taken_transitions[19] += 1;
  }
  d->_g136 = d->_pg106;
  if (d->_g136) {
    d->_taken_transitions[27] += 1;
  }
  d->_g111 = d->_g139 || d->_g136;
  d->_cg115 = d->task == 3 && d->activeTask != 3;
  d->_g112 = d->_g111 && d->_cg115;
  if (d->_g112) {
    d->activeTask = 3;
    d->waitingConfig = 1;
    d->_taken_transitions[20] += 1;
  }
  d->_g120 = d->_g111 && !d->_cg115;
  d->_cg132 = d->task == 1 || d->task == 2;
  d->_g114 = d->_g120 && d->_cg132;
  if (d->_g114) {
    d->activeTask = d->task;
    d->waitingConfig = 0;
    d->_taken_transitions[21] += 1;
  }
  d->_g115 = d->_g120 && !d->_cg132;
  if (d->_g115) {
    d->_taken_transitions[22] += 1;
  }
  d->_g132 = d->_g112 || d->_g114 || d->_g115;
  d->_cg117 = d->activeTask == 3 && d->_pre_configSequence != d->configApplied;
  d->_g134 = d->_g132 && !d->_cg117;
  if (d->_g134) {
    d->_taken_transitions[24] += 1;
  }
  d->_g116 = d->_pg103;
  d->_g133 = d->_pg109;
  d->_g131 = d->_g134 || d->_g116 || d->_g133;
  d->_cg122 = d->c < d->t6;
  d->_g128 = d->_g131 && d->_cg122;
  if (d->_g128) {
    d->sleepT = (d->sleepT < (d->t6 - d->c)) ? d->sleepT : (d->t6 - d->c);
  }
  d->_cg123 = (!d->waitingConfig && d->c >= d->t6) || 1;
  d->_g121 = d->_g131 && !d->_cg122;
  d->_cg129 = (!d->waitingConfig && d->c >= d->t6) || 1;
  d->_g122 = (d->_g128 && d->_cg123) || (d->_g121 && d->_cg129);
  d->_cg124 = !d->waitingConfig && d->c >= d->t6;
  d->_g125 = d->_g122 && d->_cg124;
  if (d->_g125) {
    d->_taken_transitions[25] += 1;
  }
  d->_g125 = d->_GO || d->_g125;
  if (d->_g125) {
    d->_TrafficLight_A_local_wNS = 0.0;
    d->c = 0.0;
    d->LEDR = 32 + 1;
    d->_Atrig = 0;
  }
  d->_pre_nsRequests = d->_reg_nsRequests;
  d->_cg3 = d->activeTask >= 2 && d->_pre_nsRequests > d->nsServed;
  d->_g4 = d->_g125 && d->_cg3;
  if (d->_g4) {
    d->nsServed = d->_pre_nsRequests;
    d->_TrafficLight_A_local_wNS = 0.0;
    d->_taken_transitions[1] += 1;
    d->LEDR = 32 + 1 + 64;
  }
  d->_cg4 = d->_TrafficLight_A_local_wNS < 4.0;
  d->_g5 = d->_g4 && d->_cg4;
  if (d->_g5) {
    d->sleepT = (d->sleepT < (4.0 - d->_TrafficLight_A_local_wNS)) ? d->sleepT : (4.0 - d->_TrafficLight_A_local_wNS);
  }
  d->_cg5 = d->_TrafficLight_A_local_wNS >= 4.0 || d->_Atrig;
  d->_g4 = d->_g4 && !d->_cg4;
  d->_cg23 = d->_TrafficLight_A_local_wNS >= 4.0 || d->_Atrig;
  d->_g6 = (d->_g5 && d->_cg5) || (d->_g4 && d->_cg23);
  d->_cg6 = d->_TrafficLight_A_local_wNS >= 4.0;
  d->_g6 = d->_g6 && d->_cg6;
  if (d->_g6) {
    d->nsServed = d->_pre_nsRequests;
    d->_taken_transitions[3] += 1;
  }
  d->_g24 = d->_g125 && !d->_cg3;
  d->_cg24 = !(d->activeTask >= 2 && d->_pre_nsRequests > d->nsServed);
  d->_g25 = d->_g24 && d->_cg24;
  if (d->_g25) {
    d->_taken_transitions[2] += 1;
  }
  d->_g7 = d->_g6 || d->_g25;
  if (d->_g7) {
    d->LEDR = 32 + 1;
  }
  d->_cg8 = d->_Atrig;
  d->_g25 = d->_pg2;
  d->_cg49 = d->c >= d->t1;
  d->_g50 = d->_g25 && d->_cg49;
  if (d->_g50) {
    d->_Atrig = 1;
  }
  d->_g10 = d->_pg19;
  d->_g45 = d->_pg39;
  if (d->_g45) {
    d->_TrafficLight_A_local_wNS += d->deltaT;
  }
  d->_g14 = d->_pg11;
  d->_g22 = d->_pg17;
  d->_g27 = d->_pg5;
  d->_cg27 = d->activeTask >= 2 && d->_pre_nsRequests > d->nsServed;
  d->_g28 = d->_g27 && d->_cg27;
  if (d->_g28) {
    d->nsServed = d->_pre_nsRequests;
    d->_TrafficLight_A_local_wNS = 0.0;
    d->_taken_transitions[1] += 1;
    d->LEDR = 32 + 1 + 64;
  }
  d->_g28 = d->_g14 || d->_g22 || d->_g28;
  d->_cg15 = d->_TrafficLight_A_local_wNS < 4.0;
  d->_g16 = d->_g28 && d->_cg15;
  if (d->_g16) {
    d->sleepT = (d->sleepT < (4.0 - d->_TrafficLight_A_local_wNS)) ? d->sleepT : (4.0 - d->_TrafficLight_A_local_wNS);
  }
  d->_cg16 = d->_TrafficLight_A_local_wNS >= 4.0 || d->_Atrig;
  d->_g15 = d->_g28 && !d->_cg15;
  d->_cg20 = d->_TrafficLight_A_local_wNS >= 4.0 || d->_Atrig;
  d->_g17 = (d->_g16 && d->_cg16) || (d->_g15 && d->_cg20);
  d->_cg17 = d->_TrafficLight_A_local_wNS >= 4.0;
  d->_g18 = d->_g17 && d->_cg17;
  if (d->_g18) {
    d->nsServed = d->_pre_nsRequests;
    d->_taken_transitions[3] += 1;
  }
  d->_g29 = d->_g27 && !d->_cg27;
  d->_cg29 = !(d->activeTask >= 2 && d->_pre_nsRequests > d->nsServed);
  d->_g30 = d->_g29 && d->_cg29;
  if (d->_g30) {
    d->_taken_transitions[2] += 1;
  }
  d->_g30 = d->_g18 || d->_g30;
  if (d->_g30) {
    d->LEDR = 32 + 1;
  }
  d->_g18 = d->_g10 || d->_g30;
  d->_cg11 = d->_Atrig;
  d->_g19 = (d->_g7 && !d->_cg8) || (d->_g18 && !d->_cg11);
  d->_g8 = d->_g29 && !d->_cg29;
  d->_cg31 = d->_Atrig;
  d->_g29 = (d->_g18 && d->_cg11) || (d->_g17 && !d->_cg17) || (d->_g8 && d->_cg31);
  d->_g11 = (d->_g5 && !d->_cg5) || (d->_g16 && !d->_cg16);
  d->_g17 = (d->_g15 && !d->_cg20) || (d->_g4 && !d->_cg23);
  d->_g5 = (d->_g24 && !d->_cg24) || (d->_g8 && !d->_cg31);
  d->_cg32 = d->c < d->t1;
  d->_g16 = d->_g125 && d->_cg32;
  if (d->_g16) {
    d->sleepT = (d->sleepT < (d->t1 - d->c)) ? d->sleepT : (d->t1 - d->c);
  }
  d->_cg33 = d->_Atrig;
  d->_g23 = d->_pg33;
  d->_g20 = d->_pg42;
  d->_g24 = d->_g23 || d->_g20;
  d->_cg36 = d->c < d->t1;
  d->_g31 = d->_g24 && d->_cg36;
  if (d->_g31) {
    d->sleepT = (d->sleepT < (d->t1 - d->c)) ? d->sleepT : (d->t1 - d->c);
  }
  d->_cg37 = d->_Atrig;
  d->_g33 = (d->_g16 && !d->_cg33) || (d->_g31 && !d->_cg37);
  d->_g36 = d->_g24 && !d->_cg36;
  d->_cg39 = d->_Atrig;
  d->_g37 = (d->_g31 && d->_cg37) || (d->_g36 && d->_cg39);
  d->_g42 = d->_g125 && !d->_cg32;
  d->_cg42 = d->_Atrig;
  d->_g42 = (d->_g36 && !d->_cg39) || (d->_g42 && !d->_cg42);
  d->_cg43 = d->_Atrig;
  d->_cg45 = d->_Atrig;
  d->_g39 = (d->_g125 && !d->_cg43) || (d->_g45 && !d->_cg45);
  d->_g46 = d->_g45 && d->_cg45;
  d->_g2 = d->_g125 || (d->_g25 && !d->_cg49);
  d->_g27 = !(d->_g27 || d->_g10 || d->_g22 || d->_g14);
  d->_g10 = !(d->_g20 || d->_g23);
  d->_g22 = !d->_g45;
  d->_g14 = !d->_g25;
  d->_g41 = (d->_g27 || d->_g29) && (d->_g10 || d->_g37) && (d->_g22 || d->_g46) && (d->_g14 || d->_g50) && (d->_g29 || d->_g37 || d->_g46 || d->_g50);
  if (d->_g41) {
    d->_taken_transitions[0] += 1;
    d->c = 0.0;
    d->LEDR = 32 + 2;
  }
  d->_g35 = d->_pg126;
  d->_g45 = d->_pg123;
  d->_g49 = d->_g41 || d->_g35 || d->_g45;
  d->_cg52 = d->c < d->t2;
  d->_g38 = d->_g49 && d->_cg52;
  if (d->_g38) {
    d->sleepT = (d->sleepT < (d->t2 - d->c)) ? d->sleepT : (d->t2 - d->c);
  }
  d->_cg53 = d->c >= d->t2;
  d->_g38_e2 = d->_g49 && !d->_cg52;
  d->_cg151 = d->c >= d->t2;
  d->_g12 = (d->_g38 && d->_cg53) || (d->_g38_e2 && d->_cg151);
  if (d->_g12) {
    d->_taken_transitions[4] += 1;
    d->c = 0.0;
    d->LEDR = 32 + 4;
    d->_taken_transitions[5] += 1;
  }
  d->_g46 = d->_pg58;
  if (d->_g46) {
    d->_taken_transitions[13] += 1;
  }
  d->_g46_e3 = d->_g12 || d->_g46;
  d->_cg55 = d->task == 3 && d->activeTask != 3;
  d->_g50_e4 = d->_g46_e3 && d->_cg55;
  if (d->_g50_e4) {
    d->activeTask = 3;
    d->waitingConfig = 1;
    d->_taken_transitions[6] += 1;
  }
  d->_g50 = d->_g46_e3 && !d->_cg55;
  d->_cg146 = d->task == 1 || d->task == 2;
  d->_g12_e1 = d->_g50 && d->_cg146;
  if (d->_g12_e1) {
    d->activeTask = d->task;
    d->waitingConfig = 0;
    d->_taken_transitions[7] += 1;
  }
  d->_g51 = d->_g50 && !d->_cg146;
  if (d->_g51) {
    d->_taken_transitions[8] += 1;
  }
  d->_g153 = d->_g50_e4 || d->_g12_e1 || d->_g51;
  d->_g150 = d->_pg52;
  d->_g52 = d->_GO || d->_g150;
  if (d->_g52) {
    d->_pre_pending1 = d->_reg_pending1;
  }
  d->_cg57 = d->activeTask == 3 && d->_pre_configSequence != d->configApplied;
  d->_g60 = d->_g153 && d->_cg57;
  if (d->_g60) {
    d->t1 = d->_pre_pending1;
  }
  d->_g54 = d->_pg55;
  d->_g55 = d->_GO || d->_g54;
  if (d->_g55) {
    d->_pre_pending2 = d->_reg_pending2;
  }
  if (d->_g60) {
    d->t2 = d->_pre_pending2;
  }
  d->_g146 = d->_pg56;
  d->_g56 = d->_GO || d->_g146;
  if (d->_g56) {
    d->_pre_pending3 = d->_reg_pending3;
  }
  if (d->_g60) {
    d->t3 = d->_pre_pending3;
  }
  d->_g147 = d->_pg148;
  d->_g148 = d->_GO || d->_g147;
  if (d->_g148) {
    d->_pre_pending4 = d->_reg_pending4;
  }
  if (d->_g60) {
    d->t4 = d->_pre_pending4;
  }
  d->_g246 = d->_pg242;
  d->_g242 = d->_GO || d->_g246;
  if (d->_g242) {
    d->_pre_pending5 = d->_reg_pending5;
  }
  if (d->_g60) {
    d->t5 = d->_pre_pending5;
  }
  d->_g238 = d->_pg234;
  d->_g234 = d->_GO || d->_g238;
  if (d->_g234) {
    d->_pre_pending6 = d->_reg_pending6;
  }
  if (d->_g60) {
    d->t6 = d->_pre_pending6;
    d->configApplied = d->_pre_configSequence;
    d->waitingConfig = 0;
    d->c = 0.0;
    d->_taken_transitions[9] += 1;
  }
  d->_g230 = d->_g153 && !d->_cg57;
  if (d->_g230) {
    d->_taken_transitions[10] += 1;
  }
  d->_g226 = d->_pg124;
  d->_g57 = d->_pg118;
  d->_g145 = d->_g230 || d->_g226 || d->_g57;
  d->_cg62 = d->c < d->t3;
  d->_g142 = d->_g145 && d->_cg62;
  if (d->_g142) {
    d->sleepT = (d->sleepT < (d->t3 - d->c)) ? d->sleepT : (d->t3 - d->c);
  }
  d->_cg63 = (!d->waitingConfig && d->c >= d->t3) || 1;
  d->_g61 = d->_g145 && !d->_cg62;
  d->_cg143 = (!d->waitingConfig && d->c >= d->t3) || 1;
  d->_g62 = (d->_g142 && d->_cg63) || (d->_g61 && d->_cg143);
  d->_cg64 = !d->waitingConfig && d->c >= d->t3;
  d->_g140 = d->_g62 && !d->_cg64;
  if (d->_g140) {
    d->_taken_transitions[12] += 1;
  }
  d->_g58 = d->_g60 || d->_g140;
  d->_g140 = d->_g62 && d->_cg64;
  if (d->_g140) {
    d->_taken_transitions[11] += 1;
    d->_TrafficLight_A_local_wEW = 0.0;
    d->c = 0.0;
    d->LEDR = 8 + 4;
  }
  d->_cg66 = d->activeTask >= 2 && d->_pre_ewRequests > d->ewServed;
  d->_g64 = d->_g140 && d->_cg66;
  if (d->_g64) {
    d->ewServed = d->_pre_ewRequests;
    d->_TrafficLight_A_local_wEW = 0.0;
    d->_taken_transitions[15] += 1;
    d->LEDR = 8 + 4 + 128;
  }
  d->_cg67 = d->_TrafficLight_A_local_wEW < 4.0;
  d->_g68 = d->_g64 && d->_cg67;
  if (d->_g68) {
    d->sleepT = (d->sleepT < (4.0 - d->_TrafficLight_A_local_wEW)) ? d->sleepT : (4.0 - d->_TrafficLight_A_local_wEW);
  }
  d->_cg68 = d->_TrafficLight_A_local_wEW >= 4.0 || d->c >= d->t4;
  d->_g67 = d->_g64 && !d->_cg67;
  d->_cg86 = d->_TrafficLight_A_local_wEW >= 4.0 || d->c >= d->t4;
  d->_g69 = (d->_g68 && d->_cg68) || (d->_g67 && d->_cg86);
  d->_cg69 = d->_TrafficLight_A_local_wEW >= 4.0;
  d->_g69 = d->_g69 && d->_cg69;
  if (d->_g69) {
    d->ewServed = d->_pre_ewRequests;
    d->_taken_transitions[17] += 1;
  }
  d->_g87 = d->_g140 && !d->_cg66;
  d->_cg87 = !(d->activeTask >= 2 && d->_pre_ewRequests > d->ewServed);
  d->_g88 = d->_g87 && d->_cg87;
  if (d->_g88) {
    d->_taken_transitions[16] += 1;
  }
  d->_g88 = d->_g69 || d->_g88;
  if (d->_g88) {
    d->LEDR = 8 + 4;
  }
  d->_cg71 = d->c >= d->t4;
  d->_g70 = (d->_g88 && !d->_cg71) || (d->_g94 && !d->_cg74);
  d->_g74 = (d->_g68 && !d->_cg68) || (d->_g85 && !d->_cg79);
  d->_g71 = (d->_g92 && !d->_cg83) || (d->_g67 && !d->_cg86);
  d->_g68 = d->_g87 && !d->_cg87;
  d->_cg89 = d->c >= d->t4;
  d->_g79 = (d->_g68 && !d->_cg89) || (d->_g73 && !d->_cg95);
  d->_cg96 = d->c < d->t4;
  d->_g86 = d->_g140 && d->_cg96;
  if (d->_g86) {
    d->sleepT = (d->sleepT < (d->t4 - d->c)) ? d->sleepT : (d->t4 - d->c);
  }
  d->_cg97 = d->c >= d->t4;
  d->_g83 = (d->_g86 && !d->_cg97) || (d->_g99 && !d->_cg101);
  d->_g87 = d->_g140 && !d->_cg96;
  d->_cg106 = d->c >= d->t4;
  d->_g95 = (d->_g100 && !d->_cg103) || (d->_g87 && !d->_cg106);
  d->_cg107 = d->c >= d->t4;
  d->_g89 = (d->_g140 && !d->_cg107) || (d->_g109 && !d->_cg109);
  d->_g101 = d->_g132 && d->_cg117;
  if (d->_g101) {
    d->t1 = d->_pre_pending1;
    d->t2 = d->_pre_pending2;
    d->t3 = d->_pre_pending3;
    d->t4 = d->_pre_pending4;
    d->t5 = d->_pre_pending5;
    d->t6 = d->_pre_pending6;
    d->configApplied = d->_pre_configSequence;
    d->waitingConfig = 0;
    d->c = 0.0;
    d->_taken_transitions[23] += 1;
  }
  d->_g97 = d->_g122 && !d->_cg124;
  if (d->_g97) {
    d->_taken_transitions[26] += 1;
  }
  d->_g106 = d->_g101 || d->_g97;
  d->_g103 = d->_g128 && !d->_cg123;
  d->_g109 = d->_g121 && !d->_cg129;
  d->_g65 = d->_g110_e3 && !d->_cg113;
  d->_g117 = d->_g75_e1 && !d->_cg137;
  d->_g124 = d->_g142 && !d->_cg63;
  d->_g118 = d->_g61 && !d->_cg143;
  d->_g126 = d->_g38 && !d->_cg53;
  d->_g123 = d->_g38_e2 && !d->_cg151;
  d->_g129 = d->_pg53;
  d->_cg159 = !d->NSraised;
  d->_g113 = d->_g129 && d->_cg159;
  if (d->_g113) {
    d->_taken_transitions[29] += 1;
  }
  d->_g137 = d->_pg151;
  d->_g63 = d->_GO || d->_g113 || d->_g137;
  d->_g143 = d->_g63 && d->NSraised;
  if (d->_g143) {
    d->nsRequests++;
    d->_taken_transitions[28] += 1;
  }
  d->_g53 = d->_g143 || (d->_g129 && !d->_cg159);
  d->_g151 = d->_g63 && !d->NSraised;
  d->_g160 = d->_pg171;
  d->_cg168 = !d->EWraised;
  d->_g162 = d->_g160 && d->_cg168;
  if (d->_g162) {
    d->_taken_transitions[31] += 1;
  }
  d->_g157 = d->_pg169;
  d->_g159 = d->_GO || d->_g162 || d->_g157;
  d->_g156 = d->_g159 && d->EWraised;
  if (d->_g156) {
    d->ewRequests++;
    d->_taken_transitions[30] += 1;
  }
  d->_g171 = d->_g156 || (d->_g160 && !d->_cg168);
  d->_g169 = d->_g159 && !d->EWraised;
  d->_g168 = d->_pg166;
  d->_g166 = d->_GO || d->_g168;
  if (d->_g166) {
    d->_pre_configReady = d->_reg_configReady;
  }
  d->_g165 = d->_pg189;
  if (d->_g165) {
    d->_taken_transitions[44] += 1;
  }
  d->_g218 = d->_pg214;
  d->_g214 = d->_GO || d->_g218;
  if (d->_g214) {
    d->_pre_configApplied = d->_reg_configApplied;
  }
  d->_g182 = d->_pg176;
  d->_cg182 = d->_pre_configApplied == d->configSequence;
  d->_g183 = d->_g182 && d->_cg182;
  if (d->_g183) {
    d->configReady = 1;
    d->_taken_transitions[45] += 1;
  }
  d->_g202 = d->_pg187;
  d->_g178 = d->_GO || d->_g165 || d->_g183 || d->_g202;
  d->_cg174 = d->configValid && d->_pre_configReady;
  d->_g183 = d->_g178 && d->_cg174;
  if (d->_g183) {
    d->_taken_transitions[32] += 1;
  }
  d->_cg175 = d->configChar == 13;
  d->_g202 = d->_g183 && d->_cg175;
  if (d->_g202) {
    d->_taken_transitions[33] += 1;
  }
  d->_g175 = d->_g183 && !d->_cg175;
  d->_cg179 = d->configChar == 10 && !d->badPacket && d->field == 5 && d->digits > 0;
  d->_g184 = d->_g175 && !d->_cg179;
  d->_cg184 = d->configChar == 10;
  d->_g185 = d->_g184 && d->_cg184;
  if (d->_g185) {
    d->configRejected++;
    d->field = 0;
    d->digits = 0;
    d->number = 0;
    d->badPacket = 0;
    d->_taken_transitions[35] += 1;
  }
  d->_g184 = d->_g184 && !d->_cg184;
  d->_cg186 = d->badPacket;
  d->_g187 = d->_g184 && d->_cg186;
  if (d->_g187) {
    d->_taken_transitions[36] += 1;
  }
  d->_g186 = d->_g184 && !d->_cg186;
  d->_cg188 = d->configChar >= 48 && d->configChar <= 57 && d->digits < 4;
  d->_g189 = d->_g186 && d->_cg188;
  if (d->_g189) {
    d->number *= 10;
    d->number += d->configChar - 48;
    d->digits++;
    d->_taken_transitions[37] += 1;
  }
  d->_g188 = d->_g186 && !d->_cg188;
  d->_cg190 = d->configChar == 44 && d->digits > 0 && d->field == 0;
  d->_g191 = d->_g188 && d->_cg190;
  if (d->_g191) {
    d->staged1 = d->number;
    d->field++;
    d->digits = 0;
    d->number = 0;
    d->_taken_transitions[38] += 1;
  }
  d->_g190 = d->_g188 && !d->_cg190;
  d->_cg192 = d->configChar == 44 && d->digits > 0 && d->field == 1;
  d->_g193 = d->_g190 && d->_cg192;
  if (d->_g193) {
    d->staged2 = d->number;
    d->field++;
    d->digits = 0;
    d->number = 0;
    d->_taken_transitions[39] += 1;
  }
  d->_g192 = d->_g190 && !d->_cg192;
  d->_cg194 = d->configChar == 44 && d->digits > 0 && d->field == 2;
  d->_g195 = d->_g192 && d->_cg194;
  if (d->_g195) {
    d->staged3 = d->number;
    d->field++;
    d->digits = 0;
    d->number = 0;
    d->_taken_transitions[40] += 1;
  }
  d->_g194 = d->_g192 && !d->_cg194;
  d->_cg196 = d->configChar == 44 && d->digits > 0 && d->field == 3;
  d->_g197 = d->_g194 && d->_cg196;
  if (d->_g197) {
    d->staged4 = d->number;
    d->field++;
    d->digits = 0;
    d->number = 0;
    d->_taken_transitions[41] += 1;
  }
  d->_g196 = d->_g194 && !d->_cg196;
  d->_cg198 = d->configChar == 44 && d->digits > 0 && d->field == 4;
  d->_g199 = d->_g196 && d->_cg198;
  if (d->_g199) {
    d->staged5 = d->number;
    d->field++;
    d->digits = 0;
    d->number = 0;
    d->_taken_transitions[42] += 1;
  }
  d->_g198 = d->_g196 && !d->_cg198;
  if (d->_g198) {
    d->badPacket = 1;
    d->_taken_transitions[43] += 1;
  }
  d->_g189 = d->_g202 || d->_g185 || d->_g187 || d->_g189 || d->_g191 || d->_g193 || d->_g195 || d->_g197 || d->_g199 || d->_g198;
  d->_g200 = d->_g175 && d->_cg179;
  if (d->_g200) {
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
    d->_taken_transitions[34] += 1;
  }
  d->_g176 = d->_g200 || (d->_g182 && !d->_cg182);
  d->_g187 = d->_g178 && !d->_cg174;
  d->_g199 = d->_GO || d->_g210;
  if (d->_g214) {
    d->_reg_configApplied = d->configApplied;
  }
  if (d->_g166) {
    d->_reg_configReady = d->configReady;
  }
  d->_reg_configSequence = d->configSequence;
  if (d->_g234) {
    d->_reg_pending6 = d->pending6;
  }
  if (d->_g242) {
    d->_reg_pending5 = d->pending5;
  }
  if (d->_g148) {
    d->_reg_pending4 = d->pending4;
  }
  if (d->_g56) {
    d->_reg_pending3 = d->pending3;
  }
  if (d->_g55) {
    d->_reg_pending2 = d->pending2;
  }
  if (d->_g52) {
    d->_reg_pending1 = d->pending1;
  }
  d->_reg_ewRequests = d->ewRequests;
  d->_reg_nsRequests = d->nsRequests;
  d->_cg258 = !(d->activeTask >= 2 && d->_pre_nsRequests > d->nsServed);
  d->_cg257 = d->activeTask >= 2 && d->_pre_nsRequests > d->nsServed;
}

void reset(TickData* d) {
  d->_GO = 1;
  d->_TERM = 0;
  d->t1 = 6.0;
  d->t2 = 2.0;
  d->t3 = 0.5;
  d->t4 = 6.0;
  d->t5 = 2.0;
  d->t6 = 0.5;
  d->activeTask = 1;
  d->LEDR = 33;
  d->configReady = 1;
  d->waitingConfig = 0;
  d->configApplied = 0;
  d->configRejected = 0;
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
  d->c = 0.0;
  d->deltaT = 0.0;
  d->sleepT = 0.0;
  d->_reg_configApplied = 0;
  d->_reg_configReady = 0;
  d->_reg_configSequence = 0;
  d->_reg_pending6 = 0;
  d->_reg_pending5 = 0;
  d->_reg_pending4 = 0;
  d->_reg_pending3 = 0;
  d->_reg_pending2 = 0;
  d->_reg_pending1 = 0;
  d->_reg_ewRequests = 0;
  d->_reg_nsRequests = 0;
  d->_taken_transitions[0] = 0;
  d->_taken_transitions[1] = 0;
  d->_taken_transitions[2] = 0;
  d->_taken_transitions[3] = 0;
  d->_taken_transitions[4] = 0;
  d->_taken_transitions[5] = 0;
  d->_taken_transitions[6] = 0;
  d->_taken_transitions[7] = 0;
  d->_taken_transitions[8] = 0;
  d->_taken_transitions[9] = 0;
  d->_taken_transitions[10] = 0;
  d->_taken_transitions[11] = 0;
  d->_taken_transitions[12] = 0;
  d->_taken_transitions[13] = 0;
  d->_taken_transitions[14] = 0;
  d->_taken_transitions[15] = 0;
  d->_taken_transitions[16] = 0;
  d->_taken_transitions[17] = 0;
  d->_taken_transitions[18] = 0;
  d->_taken_transitions[19] = 0;
  d->_taken_transitions[20] = 0;
  d->_taken_transitions[21] = 0;
  d->_taken_transitions[22] = 0;
  d->_taken_transitions[23] = 0;
  d->_taken_transitions[24] = 0;
  d->_taken_transitions[25] = 0;
  d->_taken_transitions[26] = 0;
  d->_taken_transitions[27] = 0;
  d->_taken_transitions[28] = 0;
  d->_taken_transitions[29] = 0;
  d->_taken_transitions[30] = 0;
  d->_taken_transitions[31] = 0;
  d->_taken_transitions[32] = 0;
  d->_taken_transitions[33] = 0;
  d->_taken_transitions[34] = 0;
  d->_taken_transitions[35] = 0;
  d->_taken_transitions[36] = 0;
  d->_taken_transitions[37] = 0;
  d->_taken_transitions[38] = 0;
  d->_taken_transitions[39] = 0;
  d->_taken_transitions[40] = 0;
  d->_taken_transitions[41] = 0;
  d->_taken_transitions[42] = 0;
  d->_taken_transitions[43] = 0;
  d->_taken_transitions[44] = 0;
  d->_taken_transitions[45] = 0;
  d->_pg199 = 0;
  d->_pg79 = 0;
  d->_pg70 = 0;
  d->_pg71 = 0;
  d->_pg74 = 0;
  d->_pg89 = 0;
  d->_pg95 = 0;
  d->_pg83 = 0;
  d->_pg65 = 0;
  d->_pg117 = 0;
  d->_pg106 = 0;
  d->_pg103 = 0;
  d->_pg109 = 0;
  d->_pg2 = 0;
  d->_pg19 = 0;
  d->_pg39 = 0;
  d->_pg11 = 0;
  d->_pg17 = 0;
  d->_pg5 = 0;
  d->_pg33 = 0;
  d->_pg42 = 0;
  d->_pg126 = 0;
  d->_pg123 = 0;
  d->_pg58 = 0;
  d->_pg52 = 0;
  d->_pg55 = 0;
  d->_pg56 = 0;
  d->_pg148 = 0;
  d->_pg242 = 0;
  d->_pg234 = 0;
  d->_pg124 = 0;
  d->_pg118 = 0;
  d->_pg53 = 0;
  d->_pg151 = 0;
  d->_pg171 = 0;
  d->_pg169 = 0;
  d->_pg166 = 0;
  d->_pg189 = 0;
  d->_pg214 = 0;
  d->_pg176 = 0;
  d->_pg187 = 0;
}

void tick(TickData* d) {
  logic(d);

  d->_pg199 = d->_g199;
  d->_pg79 = d->_g79;
  d->_pg70 = d->_g70;
  d->_pg71 = d->_g71;
  d->_pg74 = d->_g74;
  d->_pg89 = d->_g89;
  d->_pg95 = d->_g95;
  d->_pg83 = d->_g83;
  d->_pg65 = d->_g65;
  d->_pg117 = d->_g117;
  d->_pg106 = d->_g106;
  d->_pg103 = d->_g103;
  d->_pg109 = d->_g109;
  d->_pg2 = d->_g2;
  d->_pg19 = d->_g19;
  d->_pg39 = d->_g39;
  d->_pg11 = d->_g11;
  d->_pg17 = d->_g17;
  d->_pg5 = d->_g5;
  d->_pg33 = d->_g33;
  d->_pg42 = d->_g42;
  d->_pg126 = d->_g126;
  d->_pg123 = d->_g123;
  d->_pg58 = d->_g58;
  d->_pg52 = d->_g52;
  d->_pg55 = d->_g55;
  d->_pg56 = d->_g56;
  d->_pg148 = d->_g148;
  d->_pg242 = d->_g242;
  d->_pg234 = d->_g234;
  d->_pg124 = d->_g124;
  d->_pg118 = d->_g118;
  d->_pg53 = d->_g53;
  d->_pg151 = d->_g151;
  d->_pg171 = d->_g171;
  d->_pg169 = d->_g169;
  d->_pg166 = d->_g166;
  d->_pg189 = d->_g189;
  d->_pg214 = d->_g214;
  d->_pg176 = d->_g176;
  d->_pg187 = d->_g187;
  d->_GO = 0;
}
