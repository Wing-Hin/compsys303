/*
 * Automatically generated Java code by
 * KIELER SCCharts - The Key to Efficient Modeling
 *
 * http://rtsys.informatik.uni-kiel.de/kieler
 */

public class TrafficLight_A {

  public double t1;
  public double t2;
  public double t3;
  public double t4;
  public double t5;
  public double t6;
  public int task;
  public boolean NSraised;
  public boolean EWraised;
  public int activeTask;
  public int LEDR;
  public int configChar;
  public boolean configValid;
  public boolean configReady;
  public boolean waitingConfig;
  public int configApplied;
  public int configRejected;
  public int configSequence;
  public int pending1;
  public int pending2;
  public int pending3;
  public int pending4;
  public int pending5;
  public int pending6;
  public int field;
  public int digits;
  public int number;
  public int staged1;
  public int staged2;
  public int staged3;
  public int staged4;
  public int staged5;
  public boolean badPacket;
  public int nsRequests;
  public int ewRequests;
  public int nsServed;
  public int ewServed;
  public double c;
  public int[] _taken_transitions;
  public double deltaT;
  public double sleepT;
  public int _reg_configApplied;
  public int _pre_configApplied;
  public boolean _reg_configReady;
  public boolean _pre_configReady;
  public int _reg_configSequence;
  public int _pre_configSequence;
  public int _reg_pending6;
  public int _pre_pending6;
  public int _reg_pending5;
  public int _pre_pending5;
  public int _reg_pending4;
  public int _pre_pending4;
  public int _reg_pending3;
  public int _pre_pending3;
  public int _reg_pending2;
  public int _pre_pending2;
  public int _reg_pending1;
  public int _pre_pending1;
  public int _reg_ewRequests;
  public int _pre_ewRequests;
  public int _reg_nsRequests;
  public int _pre_nsRequests;
  public boolean _Atrig;
  public double _TrafficLight_A_local_wNS;
  public double _TrafficLight_A_local_wEW;
  public boolean _g2;
  public boolean _g4;
  public boolean _g5;
  public boolean _g6;
  public boolean _g7;
  public boolean _g8;
  public boolean _g10;
  public boolean _g11;
  public boolean _g12;
  public boolean _g14;
  public boolean _g15;
  public boolean _g16;
  public boolean _g17;
  public boolean _g18;
  public boolean _g19;
  public boolean _g20;
  public boolean _g22;
  public boolean _g23;
  public boolean _g24;
  public boolean _g25;
  public boolean _g27;
  public boolean _g28;
  public boolean _g29;
  public boolean _g30;
  public boolean _g31;
  public boolean _g33;
  public boolean _g35;
  public boolean _g36;
  public boolean _g37;
  public boolean _g38;
  public boolean _g39;
  public boolean _g41;
  public boolean _g42;
  public boolean _g45;
  public boolean _g46;
  public boolean _g49;
  public boolean _g50;
  public boolean _g51;
  public boolean _g52;
  public boolean _g53;
  public boolean _g54;
  public boolean _g55;
  public boolean _g56;
  public boolean _g57;
  public boolean _g58;
  public boolean _g60;
  public boolean _g61;
  public boolean _g62;
  public boolean _g63;
  public boolean _g64;
  public boolean _g65;
  public boolean _g67;
  public boolean _g68;
  public boolean _g69;
  public boolean _g70;
  public boolean _g71;
  public boolean _g73;
  public boolean _g74;
  public boolean _g75;
  public boolean _g77;
  public boolean _g78;
  public boolean _g79;
  public boolean _g80;
  public boolean _g81;
  public boolean _g82;
  public boolean _g83;
  public boolean _g85;
  public boolean _g86;
  public boolean _g87;
  public boolean _g88;
  public boolean _g89;
  public boolean _g91;
  public boolean _g92;
  public boolean _g93;
  public boolean _g94;
  public boolean _g95;
  public boolean _g97;
  public boolean _g99;
  public boolean _g100;
  public boolean _g101;
  public boolean _g102;
  public boolean _g103;
  public boolean _g105;
  public boolean _g106;
  public boolean _g109;
  public boolean _g110;
  public boolean _g111;
  public boolean _g112;
  public boolean _g113;
  public boolean _g114;
  public boolean _g115;
  public boolean _g116;
  public boolean _g117;
  public boolean _g118;
  public boolean _g120;
  public boolean _g121;
  public boolean _g122;
  public boolean _g123;
  public boolean _g124;
  public boolean _g125;
  public boolean _g126;
  public boolean _g128;
  public boolean _g129;
  public boolean _g131;
  public boolean _g132;
  public boolean _g133;
  public boolean _g134;
  public boolean _g136;
  public boolean _g137;
  public boolean _g139;
  public boolean _g140;
  public boolean _g142;
  public boolean _g143;
  public boolean _g145;
  public boolean _g146;
  public boolean _g147;
  public boolean _g148;
  public boolean _g150;
  public boolean _g151;
  public boolean _g153;
  public boolean _g156;
  public boolean _g157;
  public boolean _g159;
  public boolean _g160;
  public boolean _g162;
  public boolean _g165;
  public boolean _g166;
  public boolean _g168;
  public boolean _g169;
  public boolean _g171;
  public boolean _g175;
  public boolean _g176;
  public boolean _g178;
  public boolean _g182;
  public boolean _g183;
  public boolean _g184;
  public boolean _g185;
  public boolean _g186;
  public boolean _g187;
  public boolean _g188;
  public boolean _g189;
  public boolean _g190;
  public boolean _g191;
  public boolean _g192;
  public boolean _g193;
  public boolean _g194;
  public boolean _g195;
  public boolean _g196;
  public boolean _g197;
  public boolean _g198;
  public boolean _g199;
  public boolean _g200;
  public boolean _g202;
  public boolean _g210;
  public boolean _g214;
  public boolean _g218;
  public boolean _g226;
  public boolean _g230;
  public boolean _g234;
  public boolean _g238;
  public boolean _g242;
  public boolean _g246;
  public boolean _GO;
  public boolean _cg3;
  public boolean _cg4;
  public boolean _cg5;
  public boolean _cg23;
  public boolean _cg6;
  public boolean _cg8;
  public boolean _cg11;
  public boolean _cg17;
  public boolean _cg31;
  public boolean _cg16;
  public boolean _cg15;
  public boolean _cg20;
  public boolean _cg24;
  public boolean _cg258;
  public boolean _cg27;
  public boolean _cg257;
  public boolean _cg29;
  public boolean _cg32;
  public boolean _cg33;
  public boolean _cg37;
  public boolean _cg36;
  public boolean _cg39;
  public boolean _cg42;
  public boolean _cg43;
  public boolean _cg45;
  public boolean _cg49;
  public boolean _cg52;
  public boolean _cg53;
  public boolean _cg151;
  public boolean _cg55;
  public boolean _cg57;
  public boolean _cg62;
  public boolean _cg63;
  public boolean _cg143;
  public boolean _cg64;
  public boolean _cg66;
  public boolean _cg67;
  public boolean _cg68;
  public boolean _cg86;
  public boolean _cg69;
  public boolean _cg71;
  public boolean _cg74;
  public boolean _cg80;
  public boolean _cg95;
  public boolean _cg79;
  public boolean _cg78;
  public boolean _cg83;
  public boolean _cg87;
  public boolean _cg89;
  public boolean _cg91;
  public boolean _cg93;
  public boolean _cg96;
  public boolean _cg97;
  public boolean _cg101;
  public boolean _cg100;
  public boolean _cg103;
  public boolean _cg106;
  public boolean _cg107;
  public boolean _cg109;
  public boolean _cg112;
  public boolean _cg113;
  public boolean _cg137;
  public boolean _cg115;
  public boolean _cg117;
  public boolean _cg122;
  public boolean _cg123;
  public boolean _cg129;
  public boolean _cg124;
  public boolean _cg132;
  public boolean _cg146;
  public boolean _cg156;
  public boolean _cg159;
  public boolean _cg165;
  public boolean _cg168;
  public boolean _cg174;
  public boolean _cg175;
  public boolean _cg179;
  public boolean _cg182;
  public boolean _cg184;
  public boolean _cg186;
  public boolean _cg188;
  public boolean _cg190;
  public boolean _cg192;
  public boolean _cg194;
  public boolean _cg196;
  public boolean _cg198;
  public boolean _g12_e1;
  public boolean _g38_e2;
  public boolean _g46_e3;
  public boolean _g50_e4;
  public boolean _g75_e1;
  public boolean _g102_e2;
  public boolean _g110_e3;
  public boolean _TERM;

  public TrafficLight_A() {
    _taken_transitions = new int[46];
  }
  public boolean _pg199;
  public boolean _pg79;
  public boolean _pg70;
  public boolean _pg71;
  public boolean _pg74;
  public boolean _pg89;
  public boolean _pg95;
  public boolean _pg83;
  public boolean _pg65;
  public boolean _pg117;
  public boolean _pg106;
  public boolean _pg103;
  public boolean _pg109;
  public boolean _pg2;
  public boolean _pg19;
  public boolean _pg39;
  public boolean _pg11;
  public boolean _pg17;
  public boolean _pg5;
  public boolean _pg33;
  public boolean _pg42;
  public boolean _pg126;
  public boolean _pg123;
  public boolean _pg58;
  public boolean _pg52;
  public boolean _pg55;
  public boolean _pg56;
  public boolean _pg148;
  public boolean _pg242;
  public boolean _pg234;
  public boolean _pg124;
  public boolean _pg118;
  public boolean _pg53;
  public boolean _pg151;
  public boolean _pg171;
  public boolean _pg169;
  public boolean _pg166;
  public boolean _pg189;
  public boolean _pg214;
  public boolean _pg176;
  public boolean _pg187;

  public void reset() {
    _GO = true;
    _TERM = false;
    t1 = 6.0;
    t2 = 2.0;
    t3 = 0.5;
    t4 = 6.0;
    t5 = 2.0;
    t6 = 0.5;
    activeTask = 1;
    LEDR = 33;
    configReady = true;
    waitingConfig = false;
    configApplied = 0;
    configRejected = 0;
    configSequence = 0;
    pending1 = 0;
    pending2 = 0;
    pending3 = 0;
    pending4 = 0;
    pending5 = 0;
    pending6 = 0;
    field = 0;
    digits = 0;
    number = 0;
    staged1 = 0;
    staged2 = 0;
    staged3 = 0;
    staged4 = 0;
    staged5 = 0;
    badPacket = false;
    nsRequests = 0;
    ewRequests = 0;
    nsServed = 0;
    ewServed = 0;
    c = 0.0;
    deltaT = 0.0;
    sleepT = 0.0;
    _reg_configApplied = 0;
    _reg_configReady = false;
    _reg_configSequence = 0;
    _reg_pending6 = 0;
    _reg_pending5 = 0;
    _reg_pending4 = 0;
    _reg_pending3 = 0;
    _reg_pending2 = 0;
    _reg_pending1 = 0;
    _reg_ewRequests = 0;
    _reg_nsRequests = 0;
    _taken_transitions[0] = 0;
    _taken_transitions[1] = 0;
    _taken_transitions[2] = 0;
    _taken_transitions[3] = 0;
    _taken_transitions[4] = 0;
    _taken_transitions[5] = 0;
    _taken_transitions[6] = 0;
    _taken_transitions[7] = 0;
    _taken_transitions[8] = 0;
    _taken_transitions[9] = 0;
    _taken_transitions[10] = 0;
    _taken_transitions[11] = 0;
    _taken_transitions[12] = 0;
    _taken_transitions[13] = 0;
    _taken_transitions[14] = 0;
    _taken_transitions[15] = 0;
    _taken_transitions[16] = 0;
    _taken_transitions[17] = 0;
    _taken_transitions[18] = 0;
    _taken_transitions[19] = 0;
    _taken_transitions[20] = 0;
    _taken_transitions[21] = 0;
    _taken_transitions[22] = 0;
    _taken_transitions[23] = 0;
    _taken_transitions[24] = 0;
    _taken_transitions[25] = 0;
    _taken_transitions[26] = 0;
    _taken_transitions[27] = 0;
    _taken_transitions[28] = 0;
    _taken_transitions[29] = 0;
    _taken_transitions[30] = 0;
    _taken_transitions[31] = 0;
    _taken_transitions[32] = 0;
    _taken_transitions[33] = 0;
    _taken_transitions[34] = 0;
    _taken_transitions[35] = 0;
    _taken_transitions[36] = 0;
    _taken_transitions[37] = 0;
    _taken_transitions[38] = 0;
    _taken_transitions[39] = 0;
    _taken_transitions[40] = 0;
    _taken_transitions[41] = 0;
    _taken_transitions[42] = 0;
    _taken_transitions[43] = 0;
    _taken_transitions[44] = 0;
    _taken_transitions[45] = 0;
    _pg199 = false;
    _pg79 = false;
    _pg70 = false;
    _pg71 = false;
    _pg74 = false;
    _pg89 = false;
    _pg95 = false;
    _pg83 = false;
    _pg65 = false;
    _pg117 = false;
    _pg106 = false;
    _pg103 = false;
    _pg109 = false;
    _pg2 = false;
    _pg19 = false;
    _pg39 = false;
    _pg11 = false;
    _pg17 = false;
    _pg5 = false;
    _pg33 = false;
    _pg42 = false;
    _pg126 = false;
    _pg123 = false;
    _pg58 = false;
    _pg52 = false;
    _pg55 = false;
    _pg56 = false;
    _pg148 = false;
    _pg242 = false;
    _pg234 = false;
    _pg124 = false;
    _pg118 = false;
    _pg53 = false;
    _pg151 = false;
    _pg171 = false;
    _pg169 = false;
    _pg166 = false;
    _pg189 = false;
    _pg214 = false;
    _pg176 = false;
    _pg187 = false;
  }

  public void logic() {
    _g210 = _pg199;
    if (_g210) {
      c += deltaT;
    }
    sleepT = 1000.0;
    _pre_configSequence = _reg_configSequence;
    _g91 = _pg79;
    _g73 = _pg70;
    _g85 = _pg71;
    _g77 = _pg74;
    _g75_e1 = !(_g91 || _g73 || _g85 || _g77);
    _pre_ewRequests = _reg_ewRequests;
    _g109 = _pg89;
    if (_g109) {
      _TrafficLight_A_local_wEW += deltaT;
    }
    _cg91 = activeTask >= 2 && _pre_ewRequests > ewServed;
    _g92 = _g91 && _cg91;
    if (_g92) {
      ewServed = _pre_ewRequests;
      _TrafficLight_A_local_wEW = 0.0;
      _taken_transitions[15] += 1;
      LEDR = 8 + 4 + 128;
    }
    _g77 = _g77 || _g85 || _g92;
    _cg78 = _TrafficLight_A_local_wEW < 4.0;
    _g85 = _g77 && _cg78;
    if (_g85) {
      sleepT = (sleepT < (4.0 - _TrafficLight_A_local_wEW)) ? sleepT : (4.0 - _TrafficLight_A_local_wEW);
    }
    _cg79 = _TrafficLight_A_local_wEW >= 4.0 || c >= t4;
    _g92 = _g77 && !_cg78;
    _cg83 = _TrafficLight_A_local_wEW >= 4.0 || c >= t4;
    _g78 = _g85 && _cg79 || _g92 && _cg83;
    _cg80 = _TrafficLight_A_local_wEW >= 4.0;
    _g81 = _g78 && _cg80;
    if (_g81) {
      ewServed = _pre_ewRequests;
      _taken_transitions[17] += 1;
    }
    _g91 = _g91 && !_cg91;
    _cg93 = !(activeTask >= 2 && _pre_ewRequests > ewServed);
    _g94 = _g91 && _cg93;
    if (_g94) {
      _taken_transitions[16] += 1;
    }
    _g81 = _g81 || _g94;
    if (_g81) {
      LEDR = 8 + 4;
    }
    _g94 = _g73 || _g81;
    _cg74 = c >= t4;
    _g73 = _g91 && !_cg93;
    _cg95 = c >= t4;
    _g82 = _g94 && _cg74 || _g78 && !_cg80 || _g73 && _cg95;
    _g93 = _pg95;
    _g80 = _pg83;
    _g102_e2 = !(_g93 || _g80);
    _g105 = _g80 || _g93;
    _cg100 = c < t4;
    _g99 = _g105 && _cg100;
    if (_g99) {
      sleepT = (sleepT < (t4 - c)) ? sleepT : (t4 - c);
    }
    _cg101 = c >= t4;
    _g100 = _g105 && !_cg100;
    _cg103 = c >= t4;
    _g102 = _g99 && _cg101 || _g100 && _cg103;
    _g110_e3 = !_g109;
    _cg109 = c >= t4;
    _g110 = _g109 && _cg109;
    _g102 = (_g75_e1 || _g82) && (_g102_e2 || _g102) && (_g110_e3 || _g110) && (_g82 || _g102 || _g110);
    if (_g102) {
      _taken_transitions[14] += 1;
      c = 0.0;
      LEDR = 16 + 4;
    }
    _g110 = _pg65;
    _g75 = _pg117;
    _g102_e2 = _g102 || _g110 || _g75;
    _cg112 = c < t5;
    _g110_e3 = _g102_e2 && _cg112;
    if (_g110_e3) {
      sleepT = (sleepT < (t5 - c)) ? sleepT : (t5 - c);
    }
    _cg113 = c >= t5;
    _g75_e1 = _g102_e2 && !_cg112;
    _cg137 = c >= t5;
    _g139 = _g110_e3 && _cg113 || _g75_e1 && _cg137;
    if (_g139) {
      _taken_transitions[18] += 1;
      c = 0.0;
      LEDR = 32 + 4;
      _taken_transitions[19] += 1;
    }
    _g136 = _pg106;
    if (_g136) {
      _taken_transitions[27] += 1;
    }
    _g111 = _g139 || _g136;
    _cg115 = task == 3 && activeTask != 3;
    _g112 = _g111 && _cg115;
    if (_g112) {
      activeTask = 3;
      waitingConfig = true;
      _taken_transitions[20] += 1;
    }
    _g120 = _g111 && !_cg115;
    _cg132 = task == 1 || task == 2;
    _g114 = _g120 && _cg132;
    if (_g114) {
      activeTask = task;
      waitingConfig = false;
      _taken_transitions[21] += 1;
    }
    _g115 = _g120 && !_cg132;
    if (_g115) {
      _taken_transitions[22] += 1;
    }
    _g132 = _g112 || _g114 || _g115;
    _cg117 = activeTask == 3 && _pre_configSequence != configApplied;
    _g134 = _g132 && !_cg117;
    if (_g134) {
      _taken_transitions[24] += 1;
    }
    _g116 = _pg103;
    _g133 = _pg109;
    _g131 = _g134 || _g116 || _g133;
    _cg122 = c < t6;
    _g128 = _g131 && _cg122;
    if (_g128) {
      sleepT = (sleepT < (t6 - c)) ? sleepT : (t6 - c);
    }
    _cg123 = !waitingConfig && c >= t6 || true;
    _g121 = _g131 && !_cg122;
    _cg129 = !waitingConfig && c >= t6 || true;
    _g122 = _g128 && _cg123 || _g121 && _cg129;
    _cg124 = !waitingConfig && c >= t6;
    _g125 = _g122 && _cg124;
    if (_g125) {
      _taken_transitions[25] += 1;
    }
    _g125 = _GO || _g125;
    if (_g125) {
      _TrafficLight_A_local_wNS = 0.0;
      c = 0.0;
      LEDR = 32 + 1;
      _Atrig = false;
    }
    _pre_nsRequests = _reg_nsRequests;
    _cg3 = activeTask >= 2 && _pre_nsRequests > nsServed;
    _g4 = _g125 && _cg3;
    if (_g4) {
      nsServed = _pre_nsRequests;
      _TrafficLight_A_local_wNS = 0.0;
      _taken_transitions[1] += 1;
      LEDR = 32 + 1 + 64;
    }
    _cg4 = _TrafficLight_A_local_wNS < 4.0;
    _g5 = _g4 && _cg4;
    if (_g5) {
      sleepT = (sleepT < (4.0 - _TrafficLight_A_local_wNS)) ? sleepT : (4.0 - _TrafficLight_A_local_wNS);
    }
    _cg5 = _TrafficLight_A_local_wNS >= 4.0 || _Atrig;
    _g4 = _g4 && !_cg4;
    _cg23 = _TrafficLight_A_local_wNS >= 4.0 || _Atrig;
    _g6 = _g5 && _cg5 || _g4 && _cg23;
    _cg6 = _TrafficLight_A_local_wNS >= 4.0;
    _g6 = _g6 && _cg6;
    if (_g6) {
      nsServed = _pre_nsRequests;
      _taken_transitions[3] += 1;
    }
    _g24 = _g125 && !_cg3;
    _cg24 = !(activeTask >= 2 && _pre_nsRequests > nsServed);
    _g25 = _g24 && _cg24;
    if (_g25) {
      _taken_transitions[2] += 1;
    }
    _g7 = _g6 || _g25;
    if (_g7) {
      LEDR = 32 + 1;
    }
    _cg8 = _Atrig;
    _g25 = _pg2;
    _cg49 = c >= t1;
    _g50 = _g25 && _cg49;
    if (_g50) {
      _Atrig = true;
    }
    _g10 = _pg19;
    _g45 = _pg39;
    if (_g45) {
      _TrafficLight_A_local_wNS += deltaT;
    }
    _g14 = _pg11;
    _g22 = _pg17;
    _g27 = _pg5;
    _cg27 = activeTask >= 2 && _pre_nsRequests > nsServed;
    _g28 = _g27 && _cg27;
    if (_g28) {
      nsServed = _pre_nsRequests;
      _TrafficLight_A_local_wNS = 0.0;
      _taken_transitions[1] += 1;
      LEDR = 32 + 1 + 64;
    }
    _g28 = _g14 || _g22 || _g28;
    _cg15 = _TrafficLight_A_local_wNS < 4.0;
    _g16 = _g28 && _cg15;
    if (_g16) {
      sleepT = (sleepT < (4.0 - _TrafficLight_A_local_wNS)) ? sleepT : (4.0 - _TrafficLight_A_local_wNS);
    }
    _cg16 = _TrafficLight_A_local_wNS >= 4.0 || _Atrig;
    _g15 = _g28 && !_cg15;
    _cg20 = _TrafficLight_A_local_wNS >= 4.0 || _Atrig;
    _g17 = _g16 && _cg16 || _g15 && _cg20;
    _cg17 = _TrafficLight_A_local_wNS >= 4.0;
    _g18 = _g17 && _cg17;
    if (_g18) {
      nsServed = _pre_nsRequests;
      _taken_transitions[3] += 1;
    }
    _g29 = _g27 && !_cg27;
    _cg29 = !(activeTask >= 2 && _pre_nsRequests > nsServed);
    _g30 = _g29 && _cg29;
    if (_g30) {
      _taken_transitions[2] += 1;
    }
    _g30 = _g18 || _g30;
    if (_g30) {
      LEDR = 32 + 1;
    }
    _g18 = _g10 || _g30;
    _cg11 = _Atrig;
    _g19 = _g7 && !_cg8 || _g18 && !_cg11;
    _g8 = _g29 && !_cg29;
    _cg31 = _Atrig;
    _g29 = _g18 && _cg11 || _g17 && !_cg17 || _g8 && _cg31;
    _g11 = _g5 && !_cg5 || _g16 && !_cg16;
    _g17 = _g15 && !_cg20 || _g4 && !_cg23;
    _g5 = _g24 && !_cg24 || _g8 && !_cg31;
    _cg32 = c < t1;
    _g16 = _g125 && _cg32;
    if (_g16) {
      sleepT = (sleepT < (t1 - c)) ? sleepT : (t1 - c);
    }
    _cg33 = _Atrig;
    _g23 = _pg33;
    _g20 = _pg42;
    _g24 = _g23 || _g20;
    _cg36 = c < t1;
    _g31 = _g24 && _cg36;
    if (_g31) {
      sleepT = (sleepT < (t1 - c)) ? sleepT : (t1 - c);
    }
    _cg37 = _Atrig;
    _g33 = _g16 && !_cg33 || _g31 && !_cg37;
    _g36 = _g24 && !_cg36;
    _cg39 = _Atrig;
    _g37 = _g31 && _cg37 || _g36 && _cg39;
    _g42 = _g125 && !_cg32;
    _cg42 = _Atrig;
    _g42 = _g36 && !_cg39 || _g42 && !_cg42;
    _cg43 = _Atrig;
    _cg45 = _Atrig;
    _g39 = _g125 && !_cg43 || _g45 && !_cg45;
    _g46 = _g45 && _cg45;
    _g2 = _g125 || _g25 && !_cg49;
    _g27 = !(_g27 || _g10 || _g22 || _g14);
    _g10 = !(_g20 || _g23);
    _g22 = !_g45;
    _g14 = !_g25;
    _g41 = (_g27 || _g29) && (_g10 || _g37) && (_g22 || _g46) && (_g14 || _g50) && (_g29 || _g37 || _g46 || _g50);
    if (_g41) {
      _taken_transitions[0] += 1;
      c = 0.0;
      LEDR = 32 + 2;
    }
    _g35 = _pg126;
    _g45 = _pg123;
    _g49 = _g41 || _g35 || _g45;
    _cg52 = c < t2;
    _g38 = _g49 && _cg52;
    if (_g38) {
      sleepT = (sleepT < (t2 - c)) ? sleepT : (t2 - c);
    }
    _cg53 = c >= t2;
    _g38_e2 = _g49 && !_cg52;
    _cg151 = c >= t2;
    _g12 = _g38 && _cg53 || _g38_e2 && _cg151;
    if (_g12) {
      _taken_transitions[4] += 1;
      c = 0.0;
      LEDR = 32 + 4;
      _taken_transitions[5] += 1;
    }
    _g46 = _pg58;
    if (_g46) {
      _taken_transitions[13] += 1;
    }
    _g46_e3 = _g12 || _g46;
    _cg55 = task == 3 && activeTask != 3;
    _g50_e4 = _g46_e3 && _cg55;
    if (_g50_e4) {
      activeTask = 3;
      waitingConfig = true;
      _taken_transitions[6] += 1;
    }
    _g50 = _g46_e3 && !_cg55;
    _cg146 = task == 1 || task == 2;
    _g12_e1 = _g50 && _cg146;
    if (_g12_e1) {
      activeTask = task;
      waitingConfig = false;
      _taken_transitions[7] += 1;
    }
    _g51 = _g50 && !_cg146;
    if (_g51) {
      _taken_transitions[8] += 1;
    }
    _g153 = _g50_e4 || _g12_e1 || _g51;
    _g150 = _pg52;
    _g52 = _GO || _g150;
    if (_g52) {
      _pre_pending1 = _reg_pending1;
    }
    _cg57 = activeTask == 3 && _pre_configSequence != configApplied;
    _g60 = _g153 && _cg57;
    if (_g60) {
      t1 = _pre_pending1;
    }
    _g54 = _pg55;
    _g55 = _GO || _g54;
    if (_g55) {
      _pre_pending2 = _reg_pending2;
    }
    if (_g60) {
      t2 = _pre_pending2;
    }
    _g146 = _pg56;
    _g56 = _GO || _g146;
    if (_g56) {
      _pre_pending3 = _reg_pending3;
    }
    if (_g60) {
      t3 = _pre_pending3;
    }
    _g147 = _pg148;
    _g148 = _GO || _g147;
    if (_g148) {
      _pre_pending4 = _reg_pending4;
    }
    if (_g60) {
      t4 = _pre_pending4;
    }
    _g246 = _pg242;
    _g242 = _GO || _g246;
    if (_g242) {
      _pre_pending5 = _reg_pending5;
    }
    if (_g60) {
      t5 = _pre_pending5;
    }
    _g238 = _pg234;
    _g234 = _GO || _g238;
    if (_g234) {
      _pre_pending6 = _reg_pending6;
    }
    if (_g60) {
      t6 = _pre_pending6;
      configApplied = _pre_configSequence;
      waitingConfig = false;
      c = 0.0;
      _taken_transitions[9] += 1;
    }
    _g230 = _g153 && !_cg57;
    if (_g230) {
      _taken_transitions[10] += 1;
    }
    _g226 = _pg124;
    _g57 = _pg118;
    _g145 = _g230 || _g226 || _g57;
    _cg62 = c < t3;
    _g142 = _g145 && _cg62;
    if (_g142) {
      sleepT = (sleepT < (t3 - c)) ? sleepT : (t3 - c);
    }
    _cg63 = !waitingConfig && c >= t3 || true;
    _g61 = _g145 && !_cg62;
    _cg143 = !waitingConfig && c >= t3 || true;
    _g62 = _g142 && _cg63 || _g61 && _cg143;
    _cg64 = !waitingConfig && c >= t3;
    _g140 = _g62 && !_cg64;
    if (_g140) {
      _taken_transitions[12] += 1;
    }
    _g58 = _g60 || _g140;
    _g140 = _g62 && _cg64;
    if (_g140) {
      _taken_transitions[11] += 1;
      _TrafficLight_A_local_wEW = 0.0;
      c = 0.0;
      LEDR = 8 + 4;
    }
    _cg66 = activeTask >= 2 && _pre_ewRequests > ewServed;
    _g64 = _g140 && _cg66;
    if (_g64) {
      ewServed = _pre_ewRequests;
      _TrafficLight_A_local_wEW = 0.0;
      _taken_transitions[15] += 1;
      LEDR = 8 + 4 + 128;
    }
    _cg67 = _TrafficLight_A_local_wEW < 4.0;
    _g68 = _g64 && _cg67;
    if (_g68) {
      sleepT = (sleepT < (4.0 - _TrafficLight_A_local_wEW)) ? sleepT : (4.0 - _TrafficLight_A_local_wEW);
    }
    _cg68 = _TrafficLight_A_local_wEW >= 4.0 || c >= t4;
    _g67 = _g64 && !_cg67;
    _cg86 = _TrafficLight_A_local_wEW >= 4.0 || c >= t4;
    _g69 = _g68 && _cg68 || _g67 && _cg86;
    _cg69 = _TrafficLight_A_local_wEW >= 4.0;
    _g69 = _g69 && _cg69;
    if (_g69) {
      ewServed = _pre_ewRequests;
      _taken_transitions[17] += 1;
    }
    _g87 = _g140 && !_cg66;
    _cg87 = !(activeTask >= 2 && _pre_ewRequests > ewServed);
    _g88 = _g87 && _cg87;
    if (_g88) {
      _taken_transitions[16] += 1;
    }
    _g88 = _g69 || _g88;
    if (_g88) {
      LEDR = 8 + 4;
    }
    _cg71 = c >= t4;
    _g70 = _g88 && !_cg71 || _g94 && !_cg74;
    _g74 = _g68 && !_cg68 || _g85 && !_cg79;
    _g71 = _g92 && !_cg83 || _g67 && !_cg86;
    _g68 = _g87 && !_cg87;
    _cg89 = c >= t4;
    _g79 = _g68 && !_cg89 || _g73 && !_cg95;
    _cg96 = c < t4;
    _g86 = _g140 && _cg96;
    if (_g86) {
      sleepT = (sleepT < (t4 - c)) ? sleepT : (t4 - c);
    }
    _cg97 = c >= t4;
    _g83 = _g86 && !_cg97 || _g99 && !_cg101;
    _g87 = _g140 && !_cg96;
    _cg106 = c >= t4;
    _g95 = _g100 && !_cg103 || _g87 && !_cg106;
    _cg107 = c >= t4;
    _g89 = _g140 && !_cg107 || _g109 && !_cg109;
    _g101 = _g132 && _cg117;
    if (_g101) {
      t1 = _pre_pending1;
      t2 = _pre_pending2;
      t3 = _pre_pending3;
      t4 = _pre_pending4;
      t5 = _pre_pending5;
      t6 = _pre_pending6;
      configApplied = _pre_configSequence;
      waitingConfig = false;
      c = 0.0;
      _taken_transitions[23] += 1;
    }
    _g97 = _g122 && !_cg124;
    if (_g97) {
      _taken_transitions[26] += 1;
    }
    _g106 = _g101 || _g97;
    _g103 = _g128 && !_cg123;
    _g109 = _g121 && !_cg129;
    _g65 = _g110_e3 && !_cg113;
    _g117 = _g75_e1 && !_cg137;
    _g124 = _g142 && !_cg63;
    _g118 = _g61 && !_cg143;
    _g126 = _g38 && !_cg53;
    _g123 = _g38_e2 && !_cg151;
    _g129 = _pg53;
    _cg159 = !NSraised;
    _g113 = _g129 && _cg159;
    if (_g113) {
      _taken_transitions[29] += 1;
    }
    _g137 = _pg151;
    _g63 = _GO || _g113 || _g137;
    _g143 = _g63 && NSraised;
    if (_g143) {
      nsRequests++;
      _taken_transitions[28] += 1;
    }
    _g53 = _g143 || _g129 && !_cg159;
    _g151 = _g63 && !NSraised;
    _g160 = _pg171;
    _cg168 = !EWraised;
    _g162 = _g160 && _cg168;
    if (_g162) {
      _taken_transitions[31] += 1;
    }
    _g157 = _pg169;
    _g159 = _GO || _g162 || _g157;
    _g156 = _g159 && EWraised;
    if (_g156) {
      ewRequests++;
      _taken_transitions[30] += 1;
    }
    _g171 = _g156 || _g160 && !_cg168;
    _g169 = _g159 && !EWraised;
    _g168 = _pg166;
    _g166 = _GO || _g168;
    if (_g166) {
      _pre_configReady = _reg_configReady;
    }
    _g165 = _pg189;
    if (_g165) {
      _taken_transitions[44] += 1;
    }
    _g218 = _pg214;
    _g214 = _GO || _g218;
    if (_g214) {
      _pre_configApplied = _reg_configApplied;
    }
    _g182 = _pg176;
    _cg182 = _pre_configApplied == configSequence;
    _g183 = _g182 && _cg182;
    if (_g183) {
      configReady = true;
      _taken_transitions[45] += 1;
    }
    _g202 = _pg187;
    _g178 = _GO || _g165 || _g183 || _g202;
    _cg174 = configValid && _pre_configReady;
    _g183 = _g178 && _cg174;
    if (_g183) {
      _taken_transitions[32] += 1;
    }
    _cg175 = configChar == 13;
    _g202 = _g183 && _cg175;
    if (_g202) {
      _taken_transitions[33] += 1;
    }
    _g175 = _g183 && !_cg175;
    _cg179 = configChar == 10 && !badPacket && field == 5 && digits > 0;
    _g184 = _g175 && !_cg179;
    _cg184 = configChar == 10;
    _g185 = _g184 && _cg184;
    if (_g185) {
      configRejected++;
      field = 0;
      digits = 0;
      number = 0;
      badPacket = false;
      _taken_transitions[35] += 1;
    }
    _g184 = _g184 && !_cg184;
    _cg186 = badPacket;
    _g187 = _g184 && _cg186;
    if (_g187) {
      _taken_transitions[36] += 1;
    }
    _g186 = _g184 && !_cg186;
    _cg188 = configChar >= 48 && configChar <= 57 && digits < 4;
    _g189 = _g186 && _cg188;
    if (_g189) {
      number *= 10;
      number += configChar - 48;
      digits++;
      _taken_transitions[37] += 1;
    }
    _g188 = _g186 && !_cg188;
    _cg190 = configChar == 44 && digits > 0 && field == 0;
    _g191 = _g188 && _cg190;
    if (_g191) {
      staged1 = number;
      field++;
      digits = 0;
      number = 0;
      _taken_transitions[38] += 1;
    }
    _g190 = _g188 && !_cg190;
    _cg192 = configChar == 44 && digits > 0 && field == 1;
    _g193 = _g190 && _cg192;
    if (_g193) {
      staged2 = number;
      field++;
      digits = 0;
      number = 0;
      _taken_transitions[39] += 1;
    }
    _g192 = _g190 && !_cg192;
    _cg194 = configChar == 44 && digits > 0 && field == 2;
    _g195 = _g192 && _cg194;
    if (_g195) {
      staged3 = number;
      field++;
      digits = 0;
      number = 0;
      _taken_transitions[40] += 1;
    }
    _g194 = _g192 && !_cg194;
    _cg196 = configChar == 44 && digits > 0 && field == 3;
    _g197 = _g194 && _cg196;
    if (_g197) {
      staged4 = number;
      field++;
      digits = 0;
      number = 0;
      _taken_transitions[41] += 1;
    }
    _g196 = _g194 && !_cg196;
    _cg198 = configChar == 44 && digits > 0 && field == 4;
    _g199 = _g196 && _cg198;
    if (_g199) {
      staged5 = number;
      field++;
      digits = 0;
      number = 0;
      _taken_transitions[42] += 1;
    }
    _g198 = _g196 && !_cg198;
    if (_g198) {
      badPacket = true;
      _taken_transitions[43] += 1;
    }
    _g189 = _g202 || _g185 || _g187 || _g189 || _g191 || _g193 || _g195 || _g197 || _g199 || _g198;
    _g200 = _g175 && _cg179;
    if (_g200) {
      pending1 = staged1;
      pending2 = staged2;
      pending3 = staged3;
      pending4 = staged4;
      pending5 = staged5;
      pending6 = number;
      configSequence++;
      configReady = false;
      field = 0;
      digits = 0;
      number = 0;
      badPacket = false;
      _taken_transitions[34] += 1;
    }
    _g176 = _g200 || _g182 && !_cg182;
    _g187 = _g178 && !_cg174;
    _g199 = _GO || _g210;
    if (_g214) {
      _reg_configApplied = configApplied;
    }
    if (_g166) {
      _reg_configReady = configReady;
    }
    _reg_configSequence = configSequence;
    if (_g234) {
      _reg_pending6 = pending6;
    }
    if (_g242) {
      _reg_pending5 = pending5;
    }
    if (_g148) {
      _reg_pending4 = pending4;
    }
    if (_g56) {
      _reg_pending3 = pending3;
    }
    if (_g55) {
      _reg_pending2 = pending2;
    }
    if (_g52) {
      _reg_pending1 = pending1;
    }
    _reg_ewRequests = ewRequests;
    _reg_nsRequests = nsRequests;
    _cg258 = !(activeTask >= 2 && _pre_nsRequests > nsServed);
    _cg257 = activeTask >= 2 && _pre_nsRequests > nsServed;
  }

  public void tick() {
    logic();

    _pg199 = _g199;
    _pg79 = _g79;
    _pg70 = _g70;
    _pg71 = _g71;
    _pg74 = _g74;
    _pg89 = _g89;
    _pg95 = _g95;
    _pg83 = _g83;
    _pg65 = _g65;
    _pg117 = _g117;
    _pg106 = _g106;
    _pg103 = _g103;
    _pg109 = _g109;
    _pg2 = _g2;
    _pg19 = _g19;
    _pg39 = _g39;
    _pg11 = _g11;
    _pg17 = _g17;
    _pg5 = _g5;
    _pg33 = _g33;
    _pg42 = _g42;
    _pg126 = _g126;
    _pg123 = _g123;
    _pg58 = _g58;
    _pg52 = _g52;
    _pg55 = _g55;
    _pg56 = _g56;
    _pg148 = _g148;
    _pg242 = _g242;
    _pg234 = _g234;
    _pg124 = _g124;
    _pg118 = _g118;
    _pg53 = _g53;
    _pg151 = _g151;
    _pg171 = _g171;
    _pg169 = _g169;
    _pg166 = _g166;
    _pg189 = _g189;
    _pg214 = _g214;
    _pg176 = _g176;
    _pg187 = _g187;
    _GO = false;
  }
}
