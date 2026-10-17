<#macro simulation_imports position>
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import org.json.*;
</#macro>

<#macro simulation_in position>
receiveVariables();
</#macro>

<#macro simulation_out position>
sendVariables();
</#macro>

<#macro simulation_body position>
    public static BufferedReader stdInReader = new BufferedReader(new InputStreamReader(System.in));
            
    private static void receiveVariables() {
        try {
            String line = stdInReader.readLine();
            JSONObject json = new JSONObject(line);
            
            // Receive EWraised
            if (json.has("EWraised")) {
                ${tickdata_name}.EWraised = json.getBoolean("EWraised");
            }
            // Receive NSraised
            if (json.has("NSraised")) {
                ${tickdata_name}.NSraised = json.getBoolean("NSraised");
            }
            // Receive configChar
            if (json.has("configChar")) {
                ${tickdata_name}.configChar = json.getInt("configChar");
            }
            // Receive configValid
            if (json.has("configValid")) {
                ${tickdata_name}.configValid = json.getBoolean("configValid");
            }
            // Receive deltaT
            if (json.has("deltaT")) {
                ${tickdata_name}.deltaT = json.getDouble("deltaT");
            }
            // Receive task
            if (json.has("task")) {
                ${tickdata_name}.task = json.getInt("task");
            }
            // Receive LEDR
            if (json.has("LEDR")) {
                ${tickdata_name}.LEDR = json.getInt("LEDR");
            }
            // Receive activeTask
            if (json.has("activeTask")) {
                ${tickdata_name}.activeTask = json.getInt("activeTask");
            }
            // Receive configApplied
            if (json.has("configApplied")) {
                ${tickdata_name}.configApplied = json.getInt("configApplied");
            }
            // Receive configReady
            if (json.has("configReady")) {
                ${tickdata_name}.configReady = json.getBoolean("configReady");
            }
            // Receive configRejected
            if (json.has("configRejected")) {
                ${tickdata_name}.configRejected = json.getInt("configRejected");
            }
            // Receive sleepT
            if (json.has("sleepT")) {
                ${tickdata_name}.sleepT = json.getDouble("sleepT");
            }
            // Receive t1
            if (json.has("t1")) {
                ${tickdata_name}.t1 = json.getDouble("t1");
            }
            // Receive t2
            if (json.has("t2")) {
                ${tickdata_name}.t2 = json.getDouble("t2");
            }
            // Receive t3
            if (json.has("t3")) {
                ${tickdata_name}.t3 = json.getDouble("t3");
            }
            // Receive t4
            if (json.has("t4")) {
                ${tickdata_name}.t4 = json.getDouble("t4");
            }
            // Receive t5
            if (json.has("t5")) {
                ${tickdata_name}.t5 = json.getDouble("t5");
            }
            // Receive t6
            if (json.has("t6")) {
                ${tickdata_name}.t6 = json.getDouble("t6");
            }
            // Receive waitingConfig
            if (json.has("waitingConfig")) {
                ${tickdata_name}.waitingConfig = json.getBoolean("waitingConfig");
            }
            // Receive #ticktime
            if (json.has("#ticktime")) {
                _ticktime = json.getInt("#ticktime");
            }
            // Receive _Atrig
            if (json.has("_Atrig")) {
                ${tickdata_name}._Atrig = json.getBoolean("_Atrig");
            }
            // Receive _GO
            if (json.has("_GO")) {
                ${tickdata_name}._GO = json.getBoolean("_GO");
            }
            // Receive _TERM
            if (json.has("_TERM")) {
                ${tickdata_name}._TERM = json.getBoolean("_TERM");
            }
            // Receive _TrafficLight_A_local_wEW
            if (json.has("_TrafficLight_A_local_wEW")) {
                ${tickdata_name}._TrafficLight_A_local_wEW = json.getDouble("_TrafficLight_A_local_wEW");
            }
            // Receive _TrafficLight_A_local_wNS
            if (json.has("_TrafficLight_A_local_wNS")) {
                ${tickdata_name}._TrafficLight_A_local_wNS = json.getDouble("_TrafficLight_A_local_wNS");
            }
            // Receive _cg100
            if (json.has("_cg100")) {
                ${tickdata_name}._cg100 = json.getBoolean("_cg100");
            }
            // Receive _cg101
            if (json.has("_cg101")) {
                ${tickdata_name}._cg101 = json.getBoolean("_cg101");
            }
            // Receive _cg103
            if (json.has("_cg103")) {
                ${tickdata_name}._cg103 = json.getBoolean("_cg103");
            }
            // Receive _cg106
            if (json.has("_cg106")) {
                ${tickdata_name}._cg106 = json.getBoolean("_cg106");
            }
            // Receive _cg107
            if (json.has("_cg107")) {
                ${tickdata_name}._cg107 = json.getBoolean("_cg107");
            }
            // Receive _cg109
            if (json.has("_cg109")) {
                ${tickdata_name}._cg109 = json.getBoolean("_cg109");
            }
            // Receive _cg11
            if (json.has("_cg11")) {
                ${tickdata_name}._cg11 = json.getBoolean("_cg11");
            }
            // Receive _cg112
            if (json.has("_cg112")) {
                ${tickdata_name}._cg112 = json.getBoolean("_cg112");
            }
            // Receive _cg113
            if (json.has("_cg113")) {
                ${tickdata_name}._cg113 = json.getBoolean("_cg113");
            }
            // Receive _cg115
            if (json.has("_cg115")) {
                ${tickdata_name}._cg115 = json.getBoolean("_cg115");
            }
            // Receive _cg117
            if (json.has("_cg117")) {
                ${tickdata_name}._cg117 = json.getBoolean("_cg117");
            }
            // Receive _cg122
            if (json.has("_cg122")) {
                ${tickdata_name}._cg122 = json.getBoolean("_cg122");
            }
            // Receive _cg123
            if (json.has("_cg123")) {
                ${tickdata_name}._cg123 = json.getBoolean("_cg123");
            }
            // Receive _cg124
            if (json.has("_cg124")) {
                ${tickdata_name}._cg124 = json.getBoolean("_cg124");
            }
            // Receive _cg129
            if (json.has("_cg129")) {
                ${tickdata_name}._cg129 = json.getBoolean("_cg129");
            }
            // Receive _cg132
            if (json.has("_cg132")) {
                ${tickdata_name}._cg132 = json.getBoolean("_cg132");
            }
            // Receive _cg137
            if (json.has("_cg137")) {
                ${tickdata_name}._cg137 = json.getBoolean("_cg137");
            }
            // Receive _cg143
            if (json.has("_cg143")) {
                ${tickdata_name}._cg143 = json.getBoolean("_cg143");
            }
            // Receive _cg146
            if (json.has("_cg146")) {
                ${tickdata_name}._cg146 = json.getBoolean("_cg146");
            }
            // Receive _cg15
            if (json.has("_cg15")) {
                ${tickdata_name}._cg15 = json.getBoolean("_cg15");
            }
            // Receive _cg151
            if (json.has("_cg151")) {
                ${tickdata_name}._cg151 = json.getBoolean("_cg151");
            }
            // Receive _cg156
            if (json.has("_cg156")) {
                ${tickdata_name}._cg156 = json.getBoolean("_cg156");
            }
            // Receive _cg159
            if (json.has("_cg159")) {
                ${tickdata_name}._cg159 = json.getBoolean("_cg159");
            }
            // Receive _cg16
            if (json.has("_cg16")) {
                ${tickdata_name}._cg16 = json.getBoolean("_cg16");
            }
            // Receive _cg165
            if (json.has("_cg165")) {
                ${tickdata_name}._cg165 = json.getBoolean("_cg165");
            }
            // Receive _cg168
            if (json.has("_cg168")) {
                ${tickdata_name}._cg168 = json.getBoolean("_cg168");
            }
            // Receive _cg17
            if (json.has("_cg17")) {
                ${tickdata_name}._cg17 = json.getBoolean("_cg17");
            }
            // Receive _cg174
            if (json.has("_cg174")) {
                ${tickdata_name}._cg174 = json.getBoolean("_cg174");
            }
            // Receive _cg175
            if (json.has("_cg175")) {
                ${tickdata_name}._cg175 = json.getBoolean("_cg175");
            }
            // Receive _cg179
            if (json.has("_cg179")) {
                ${tickdata_name}._cg179 = json.getBoolean("_cg179");
            }
            // Receive _cg182
            if (json.has("_cg182")) {
                ${tickdata_name}._cg182 = json.getBoolean("_cg182");
            }
            // Receive _cg184
            if (json.has("_cg184")) {
                ${tickdata_name}._cg184 = json.getBoolean("_cg184");
            }
            // Receive _cg186
            if (json.has("_cg186")) {
                ${tickdata_name}._cg186 = json.getBoolean("_cg186");
            }
            // Receive _cg188
            if (json.has("_cg188")) {
                ${tickdata_name}._cg188 = json.getBoolean("_cg188");
            }
            // Receive _cg190
            if (json.has("_cg190")) {
                ${tickdata_name}._cg190 = json.getBoolean("_cg190");
            }
            // Receive _cg192
            if (json.has("_cg192")) {
                ${tickdata_name}._cg192 = json.getBoolean("_cg192");
            }
            // Receive _cg194
            if (json.has("_cg194")) {
                ${tickdata_name}._cg194 = json.getBoolean("_cg194");
            }
            // Receive _cg196
            if (json.has("_cg196")) {
                ${tickdata_name}._cg196 = json.getBoolean("_cg196");
            }
            // Receive _cg198
            if (json.has("_cg198")) {
                ${tickdata_name}._cg198 = json.getBoolean("_cg198");
            }
            // Receive _cg20
            if (json.has("_cg20")) {
                ${tickdata_name}._cg20 = json.getBoolean("_cg20");
            }
            // Receive _cg23
            if (json.has("_cg23")) {
                ${tickdata_name}._cg23 = json.getBoolean("_cg23");
            }
            // Receive _cg24
            if (json.has("_cg24")) {
                ${tickdata_name}._cg24 = json.getBoolean("_cg24");
            }
            // Receive _cg257
            if (json.has("_cg257")) {
                ${tickdata_name}._cg257 = json.getBoolean("_cg257");
            }
            // Receive _cg258
            if (json.has("_cg258")) {
                ${tickdata_name}._cg258 = json.getBoolean("_cg258");
            }
            // Receive _cg27
            if (json.has("_cg27")) {
                ${tickdata_name}._cg27 = json.getBoolean("_cg27");
            }
            // Receive _cg29
            if (json.has("_cg29")) {
                ${tickdata_name}._cg29 = json.getBoolean("_cg29");
            }
            // Receive _cg3
            if (json.has("_cg3")) {
                ${tickdata_name}._cg3 = json.getBoolean("_cg3");
            }
            // Receive _cg31
            if (json.has("_cg31")) {
                ${tickdata_name}._cg31 = json.getBoolean("_cg31");
            }
            // Receive _cg32
            if (json.has("_cg32")) {
                ${tickdata_name}._cg32 = json.getBoolean("_cg32");
            }
            // Receive _cg33
            if (json.has("_cg33")) {
                ${tickdata_name}._cg33 = json.getBoolean("_cg33");
            }
            // Receive _cg36
            if (json.has("_cg36")) {
                ${tickdata_name}._cg36 = json.getBoolean("_cg36");
            }
            // Receive _cg37
            if (json.has("_cg37")) {
                ${tickdata_name}._cg37 = json.getBoolean("_cg37");
            }
            // Receive _cg39
            if (json.has("_cg39")) {
                ${tickdata_name}._cg39 = json.getBoolean("_cg39");
            }
            // Receive _cg4
            if (json.has("_cg4")) {
                ${tickdata_name}._cg4 = json.getBoolean("_cg4");
            }
            // Receive _cg42
            if (json.has("_cg42")) {
                ${tickdata_name}._cg42 = json.getBoolean("_cg42");
            }
            // Receive _cg43
            if (json.has("_cg43")) {
                ${tickdata_name}._cg43 = json.getBoolean("_cg43");
            }
            // Receive _cg45
            if (json.has("_cg45")) {
                ${tickdata_name}._cg45 = json.getBoolean("_cg45");
            }
            // Receive _cg49
            if (json.has("_cg49")) {
                ${tickdata_name}._cg49 = json.getBoolean("_cg49");
            }
            // Receive _cg5
            if (json.has("_cg5")) {
                ${tickdata_name}._cg5 = json.getBoolean("_cg5");
            }
            // Receive _cg52
            if (json.has("_cg52")) {
                ${tickdata_name}._cg52 = json.getBoolean("_cg52");
            }
            // Receive _cg53
            if (json.has("_cg53")) {
                ${tickdata_name}._cg53 = json.getBoolean("_cg53");
            }
            // Receive _cg55
            if (json.has("_cg55")) {
                ${tickdata_name}._cg55 = json.getBoolean("_cg55");
            }
            // Receive _cg57
            if (json.has("_cg57")) {
                ${tickdata_name}._cg57 = json.getBoolean("_cg57");
            }
            // Receive _cg6
            if (json.has("_cg6")) {
                ${tickdata_name}._cg6 = json.getBoolean("_cg6");
            }
            // Receive _cg62
            if (json.has("_cg62")) {
                ${tickdata_name}._cg62 = json.getBoolean("_cg62");
            }
            // Receive _cg63
            if (json.has("_cg63")) {
                ${tickdata_name}._cg63 = json.getBoolean("_cg63");
            }
            // Receive _cg64
            if (json.has("_cg64")) {
                ${tickdata_name}._cg64 = json.getBoolean("_cg64");
            }
            // Receive _cg66
            if (json.has("_cg66")) {
                ${tickdata_name}._cg66 = json.getBoolean("_cg66");
            }
            // Receive _cg67
            if (json.has("_cg67")) {
                ${tickdata_name}._cg67 = json.getBoolean("_cg67");
            }
            // Receive _cg68
            if (json.has("_cg68")) {
                ${tickdata_name}._cg68 = json.getBoolean("_cg68");
            }
            // Receive _cg69
            if (json.has("_cg69")) {
                ${tickdata_name}._cg69 = json.getBoolean("_cg69");
            }
            // Receive _cg71
            if (json.has("_cg71")) {
                ${tickdata_name}._cg71 = json.getBoolean("_cg71");
            }
            // Receive _cg74
            if (json.has("_cg74")) {
                ${tickdata_name}._cg74 = json.getBoolean("_cg74");
            }
            // Receive _cg78
            if (json.has("_cg78")) {
                ${tickdata_name}._cg78 = json.getBoolean("_cg78");
            }
            // Receive _cg79
            if (json.has("_cg79")) {
                ${tickdata_name}._cg79 = json.getBoolean("_cg79");
            }
            // Receive _cg8
            if (json.has("_cg8")) {
                ${tickdata_name}._cg8 = json.getBoolean("_cg8");
            }
            // Receive _cg80
            if (json.has("_cg80")) {
                ${tickdata_name}._cg80 = json.getBoolean("_cg80");
            }
            // Receive _cg83
            if (json.has("_cg83")) {
                ${tickdata_name}._cg83 = json.getBoolean("_cg83");
            }
            // Receive _cg86
            if (json.has("_cg86")) {
                ${tickdata_name}._cg86 = json.getBoolean("_cg86");
            }
            // Receive _cg87
            if (json.has("_cg87")) {
                ${tickdata_name}._cg87 = json.getBoolean("_cg87");
            }
            // Receive _cg89
            if (json.has("_cg89")) {
                ${tickdata_name}._cg89 = json.getBoolean("_cg89");
            }
            // Receive _cg91
            if (json.has("_cg91")) {
                ${tickdata_name}._cg91 = json.getBoolean("_cg91");
            }
            // Receive _cg93
            if (json.has("_cg93")) {
                ${tickdata_name}._cg93 = json.getBoolean("_cg93");
            }
            // Receive _cg95
            if (json.has("_cg95")) {
                ${tickdata_name}._cg95 = json.getBoolean("_cg95");
            }
            // Receive _cg96
            if (json.has("_cg96")) {
                ${tickdata_name}._cg96 = json.getBoolean("_cg96");
            }
            // Receive _cg97
            if (json.has("_cg97")) {
                ${tickdata_name}._cg97 = json.getBoolean("_cg97");
            }
            // Receive _g10
            if (json.has("_g10")) {
                ${tickdata_name}._g10 = json.getBoolean("_g10");
            }
            // Receive _g100
            if (json.has("_g100")) {
                ${tickdata_name}._g100 = json.getBoolean("_g100");
            }
            // Receive _g101
            if (json.has("_g101")) {
                ${tickdata_name}._g101 = json.getBoolean("_g101");
            }
            // Receive _g102
            if (json.has("_g102")) {
                ${tickdata_name}._g102 = json.getBoolean("_g102");
            }
            // Receive _g102_e2
            if (json.has("_g102_e2")) {
                ${tickdata_name}._g102_e2 = json.getBoolean("_g102_e2");
            }
            // Receive _g103
            if (json.has("_g103")) {
                ${tickdata_name}._g103 = json.getBoolean("_g103");
            }
            // Receive _g105
            if (json.has("_g105")) {
                ${tickdata_name}._g105 = json.getBoolean("_g105");
            }
            // Receive _g106
            if (json.has("_g106")) {
                ${tickdata_name}._g106 = json.getBoolean("_g106");
            }
            // Receive _g109
            if (json.has("_g109")) {
                ${tickdata_name}._g109 = json.getBoolean("_g109");
            }
            // Receive _g11
            if (json.has("_g11")) {
                ${tickdata_name}._g11 = json.getBoolean("_g11");
            }
            // Receive _g110
            if (json.has("_g110")) {
                ${tickdata_name}._g110 = json.getBoolean("_g110");
            }
            // Receive _g110_e3
            if (json.has("_g110_e3")) {
                ${tickdata_name}._g110_e3 = json.getBoolean("_g110_e3");
            }
            // Receive _g111
            if (json.has("_g111")) {
                ${tickdata_name}._g111 = json.getBoolean("_g111");
            }
            // Receive _g112
            if (json.has("_g112")) {
                ${tickdata_name}._g112 = json.getBoolean("_g112");
            }
            // Receive _g113
            if (json.has("_g113")) {
                ${tickdata_name}._g113 = json.getBoolean("_g113");
            }
            // Receive _g114
            if (json.has("_g114")) {
                ${tickdata_name}._g114 = json.getBoolean("_g114");
            }
            // Receive _g115
            if (json.has("_g115")) {
                ${tickdata_name}._g115 = json.getBoolean("_g115");
            }
            // Receive _g116
            if (json.has("_g116")) {
                ${tickdata_name}._g116 = json.getBoolean("_g116");
            }
            // Receive _g117
            if (json.has("_g117")) {
                ${tickdata_name}._g117 = json.getBoolean("_g117");
            }
            // Receive _g118
            if (json.has("_g118")) {
                ${tickdata_name}._g118 = json.getBoolean("_g118");
            }
            // Receive _g12
            if (json.has("_g12")) {
                ${tickdata_name}._g12 = json.getBoolean("_g12");
            }
            // Receive _g120
            if (json.has("_g120")) {
                ${tickdata_name}._g120 = json.getBoolean("_g120");
            }
            // Receive _g121
            if (json.has("_g121")) {
                ${tickdata_name}._g121 = json.getBoolean("_g121");
            }
            // Receive _g122
            if (json.has("_g122")) {
                ${tickdata_name}._g122 = json.getBoolean("_g122");
            }
            // Receive _g123
            if (json.has("_g123")) {
                ${tickdata_name}._g123 = json.getBoolean("_g123");
            }
            // Receive _g124
            if (json.has("_g124")) {
                ${tickdata_name}._g124 = json.getBoolean("_g124");
            }
            // Receive _g125
            if (json.has("_g125")) {
                ${tickdata_name}._g125 = json.getBoolean("_g125");
            }
            // Receive _g126
            if (json.has("_g126")) {
                ${tickdata_name}._g126 = json.getBoolean("_g126");
            }
            // Receive _g128
            if (json.has("_g128")) {
                ${tickdata_name}._g128 = json.getBoolean("_g128");
            }
            // Receive _g129
            if (json.has("_g129")) {
                ${tickdata_name}._g129 = json.getBoolean("_g129");
            }
            // Receive _g12_e1
            if (json.has("_g12_e1")) {
                ${tickdata_name}._g12_e1 = json.getBoolean("_g12_e1");
            }
            // Receive _g131
            if (json.has("_g131")) {
                ${tickdata_name}._g131 = json.getBoolean("_g131");
            }
            // Receive _g132
            if (json.has("_g132")) {
                ${tickdata_name}._g132 = json.getBoolean("_g132");
            }
            // Receive _g133
            if (json.has("_g133")) {
                ${tickdata_name}._g133 = json.getBoolean("_g133");
            }
            // Receive _g134
            if (json.has("_g134")) {
                ${tickdata_name}._g134 = json.getBoolean("_g134");
            }
            // Receive _g136
            if (json.has("_g136")) {
                ${tickdata_name}._g136 = json.getBoolean("_g136");
            }
            // Receive _g137
            if (json.has("_g137")) {
                ${tickdata_name}._g137 = json.getBoolean("_g137");
            }
            // Receive _g139
            if (json.has("_g139")) {
                ${tickdata_name}._g139 = json.getBoolean("_g139");
            }
            // Receive _g14
            if (json.has("_g14")) {
                ${tickdata_name}._g14 = json.getBoolean("_g14");
            }
            // Receive _g140
            if (json.has("_g140")) {
                ${tickdata_name}._g140 = json.getBoolean("_g140");
            }
            // Receive _g142
            if (json.has("_g142")) {
                ${tickdata_name}._g142 = json.getBoolean("_g142");
            }
            // Receive _g143
            if (json.has("_g143")) {
                ${tickdata_name}._g143 = json.getBoolean("_g143");
            }
            // Receive _g145
            if (json.has("_g145")) {
                ${tickdata_name}._g145 = json.getBoolean("_g145");
            }
            // Receive _g146
            if (json.has("_g146")) {
                ${tickdata_name}._g146 = json.getBoolean("_g146");
            }
            // Receive _g147
            if (json.has("_g147")) {
                ${tickdata_name}._g147 = json.getBoolean("_g147");
            }
            // Receive _g148
            if (json.has("_g148")) {
                ${tickdata_name}._g148 = json.getBoolean("_g148");
            }
            // Receive _g15
            if (json.has("_g15")) {
                ${tickdata_name}._g15 = json.getBoolean("_g15");
            }
            // Receive _g150
            if (json.has("_g150")) {
                ${tickdata_name}._g150 = json.getBoolean("_g150");
            }
            // Receive _g151
            if (json.has("_g151")) {
                ${tickdata_name}._g151 = json.getBoolean("_g151");
            }
            // Receive _g153
            if (json.has("_g153")) {
                ${tickdata_name}._g153 = json.getBoolean("_g153");
            }
            // Receive _g156
            if (json.has("_g156")) {
                ${tickdata_name}._g156 = json.getBoolean("_g156");
            }
            // Receive _g157
            if (json.has("_g157")) {
                ${tickdata_name}._g157 = json.getBoolean("_g157");
            }
            // Receive _g159
            if (json.has("_g159")) {
                ${tickdata_name}._g159 = json.getBoolean("_g159");
            }
            // Receive _g16
            if (json.has("_g16")) {
                ${tickdata_name}._g16 = json.getBoolean("_g16");
            }
            // Receive _g160
            if (json.has("_g160")) {
                ${tickdata_name}._g160 = json.getBoolean("_g160");
            }
            // Receive _g162
            if (json.has("_g162")) {
                ${tickdata_name}._g162 = json.getBoolean("_g162");
            }
            // Receive _g165
            if (json.has("_g165")) {
                ${tickdata_name}._g165 = json.getBoolean("_g165");
            }
            // Receive _g166
            if (json.has("_g166")) {
                ${tickdata_name}._g166 = json.getBoolean("_g166");
            }
            // Receive _g168
            if (json.has("_g168")) {
                ${tickdata_name}._g168 = json.getBoolean("_g168");
            }
            // Receive _g169
            if (json.has("_g169")) {
                ${tickdata_name}._g169 = json.getBoolean("_g169");
            }
            // Receive _g17
            if (json.has("_g17")) {
                ${tickdata_name}._g17 = json.getBoolean("_g17");
            }
            // Receive _g171
            if (json.has("_g171")) {
                ${tickdata_name}._g171 = json.getBoolean("_g171");
            }
            // Receive _g175
            if (json.has("_g175")) {
                ${tickdata_name}._g175 = json.getBoolean("_g175");
            }
            // Receive _g176
            if (json.has("_g176")) {
                ${tickdata_name}._g176 = json.getBoolean("_g176");
            }
            // Receive _g178
            if (json.has("_g178")) {
                ${tickdata_name}._g178 = json.getBoolean("_g178");
            }
            // Receive _g18
            if (json.has("_g18")) {
                ${tickdata_name}._g18 = json.getBoolean("_g18");
            }
            // Receive _g182
            if (json.has("_g182")) {
                ${tickdata_name}._g182 = json.getBoolean("_g182");
            }
            // Receive _g183
            if (json.has("_g183")) {
                ${tickdata_name}._g183 = json.getBoolean("_g183");
            }
            // Receive _g184
            if (json.has("_g184")) {
                ${tickdata_name}._g184 = json.getBoolean("_g184");
            }
            // Receive _g185
            if (json.has("_g185")) {
                ${tickdata_name}._g185 = json.getBoolean("_g185");
            }
            // Receive _g186
            if (json.has("_g186")) {
                ${tickdata_name}._g186 = json.getBoolean("_g186");
            }
            // Receive _g187
            if (json.has("_g187")) {
                ${tickdata_name}._g187 = json.getBoolean("_g187");
            }
            // Receive _g188
            if (json.has("_g188")) {
                ${tickdata_name}._g188 = json.getBoolean("_g188");
            }
            // Receive _g189
            if (json.has("_g189")) {
                ${tickdata_name}._g189 = json.getBoolean("_g189");
            }
            // Receive _g19
            if (json.has("_g19")) {
                ${tickdata_name}._g19 = json.getBoolean("_g19");
            }
            // Receive _g190
            if (json.has("_g190")) {
                ${tickdata_name}._g190 = json.getBoolean("_g190");
            }
            // Receive _g191
            if (json.has("_g191")) {
                ${tickdata_name}._g191 = json.getBoolean("_g191");
            }
            // Receive _g192
            if (json.has("_g192")) {
                ${tickdata_name}._g192 = json.getBoolean("_g192");
            }
            // Receive _g193
            if (json.has("_g193")) {
                ${tickdata_name}._g193 = json.getBoolean("_g193");
            }
            // Receive _g194
            if (json.has("_g194")) {
                ${tickdata_name}._g194 = json.getBoolean("_g194");
            }
            // Receive _g195
            if (json.has("_g195")) {
                ${tickdata_name}._g195 = json.getBoolean("_g195");
            }
            // Receive _g196
            if (json.has("_g196")) {
                ${tickdata_name}._g196 = json.getBoolean("_g196");
            }
            // Receive _g197
            if (json.has("_g197")) {
                ${tickdata_name}._g197 = json.getBoolean("_g197");
            }
            // Receive _g198
            if (json.has("_g198")) {
                ${tickdata_name}._g198 = json.getBoolean("_g198");
            }
            // Receive _g199
            if (json.has("_g199")) {
                ${tickdata_name}._g199 = json.getBoolean("_g199");
            }
            // Receive _g2
            if (json.has("_g2")) {
                ${tickdata_name}._g2 = json.getBoolean("_g2");
            }
            // Receive _g20
            if (json.has("_g20")) {
                ${tickdata_name}._g20 = json.getBoolean("_g20");
            }
            // Receive _g200
            if (json.has("_g200")) {
                ${tickdata_name}._g200 = json.getBoolean("_g200");
            }
            // Receive _g202
            if (json.has("_g202")) {
                ${tickdata_name}._g202 = json.getBoolean("_g202");
            }
            // Receive _g210
            if (json.has("_g210")) {
                ${tickdata_name}._g210 = json.getBoolean("_g210");
            }
            // Receive _g214
            if (json.has("_g214")) {
                ${tickdata_name}._g214 = json.getBoolean("_g214");
            }
            // Receive _g218
            if (json.has("_g218")) {
                ${tickdata_name}._g218 = json.getBoolean("_g218");
            }
            // Receive _g22
            if (json.has("_g22")) {
                ${tickdata_name}._g22 = json.getBoolean("_g22");
            }
            // Receive _g226
            if (json.has("_g226")) {
                ${tickdata_name}._g226 = json.getBoolean("_g226");
            }
            // Receive _g23
            if (json.has("_g23")) {
                ${tickdata_name}._g23 = json.getBoolean("_g23");
            }
            // Receive _g230
            if (json.has("_g230")) {
                ${tickdata_name}._g230 = json.getBoolean("_g230");
            }
            // Receive _g234
            if (json.has("_g234")) {
                ${tickdata_name}._g234 = json.getBoolean("_g234");
            }
            // Receive _g238
            if (json.has("_g238")) {
                ${tickdata_name}._g238 = json.getBoolean("_g238");
            }
            // Receive _g24
            if (json.has("_g24")) {
                ${tickdata_name}._g24 = json.getBoolean("_g24");
            }
            // Receive _g242
            if (json.has("_g242")) {
                ${tickdata_name}._g242 = json.getBoolean("_g242");
            }
            // Receive _g246
            if (json.has("_g246")) {
                ${tickdata_name}._g246 = json.getBoolean("_g246");
            }
            // Receive _g25
            if (json.has("_g25")) {
                ${tickdata_name}._g25 = json.getBoolean("_g25");
            }
            // Receive _g27
            if (json.has("_g27")) {
                ${tickdata_name}._g27 = json.getBoolean("_g27");
            }
            // Receive _g28
            if (json.has("_g28")) {
                ${tickdata_name}._g28 = json.getBoolean("_g28");
            }
            // Receive _g29
            if (json.has("_g29")) {
                ${tickdata_name}._g29 = json.getBoolean("_g29");
            }
            // Receive _g30
            if (json.has("_g30")) {
                ${tickdata_name}._g30 = json.getBoolean("_g30");
            }
            // Receive _g31
            if (json.has("_g31")) {
                ${tickdata_name}._g31 = json.getBoolean("_g31");
            }
            // Receive _g33
            if (json.has("_g33")) {
                ${tickdata_name}._g33 = json.getBoolean("_g33");
            }
            // Receive _g35
            if (json.has("_g35")) {
                ${tickdata_name}._g35 = json.getBoolean("_g35");
            }
            // Receive _g36
            if (json.has("_g36")) {
                ${tickdata_name}._g36 = json.getBoolean("_g36");
            }
            // Receive _g37
            if (json.has("_g37")) {
                ${tickdata_name}._g37 = json.getBoolean("_g37");
            }
            // Receive _g38
            if (json.has("_g38")) {
                ${tickdata_name}._g38 = json.getBoolean("_g38");
            }
            // Receive _g38_e2
            if (json.has("_g38_e2")) {
                ${tickdata_name}._g38_e2 = json.getBoolean("_g38_e2");
            }
            // Receive _g39
            if (json.has("_g39")) {
                ${tickdata_name}._g39 = json.getBoolean("_g39");
            }
            // Receive _g4
            if (json.has("_g4")) {
                ${tickdata_name}._g4 = json.getBoolean("_g4");
            }
            // Receive _g41
            if (json.has("_g41")) {
                ${tickdata_name}._g41 = json.getBoolean("_g41");
            }
            // Receive _g42
            if (json.has("_g42")) {
                ${tickdata_name}._g42 = json.getBoolean("_g42");
            }
            // Receive _g45
            if (json.has("_g45")) {
                ${tickdata_name}._g45 = json.getBoolean("_g45");
            }
            // Receive _g46
            if (json.has("_g46")) {
                ${tickdata_name}._g46 = json.getBoolean("_g46");
            }
            // Receive _g46_e3
            if (json.has("_g46_e3")) {
                ${tickdata_name}._g46_e3 = json.getBoolean("_g46_e3");
            }
            // Receive _g49
            if (json.has("_g49")) {
                ${tickdata_name}._g49 = json.getBoolean("_g49");
            }
            // Receive _g5
            if (json.has("_g5")) {
                ${tickdata_name}._g5 = json.getBoolean("_g5");
            }
            // Receive _g50
            if (json.has("_g50")) {
                ${tickdata_name}._g50 = json.getBoolean("_g50");
            }
            // Receive _g50_e4
            if (json.has("_g50_e4")) {
                ${tickdata_name}._g50_e4 = json.getBoolean("_g50_e4");
            }
            // Receive _g51
            if (json.has("_g51")) {
                ${tickdata_name}._g51 = json.getBoolean("_g51");
            }
            // Receive _g52
            if (json.has("_g52")) {
                ${tickdata_name}._g52 = json.getBoolean("_g52");
            }
            // Receive _g53
            if (json.has("_g53")) {
                ${tickdata_name}._g53 = json.getBoolean("_g53");
            }
            // Receive _g54
            if (json.has("_g54")) {
                ${tickdata_name}._g54 = json.getBoolean("_g54");
            }
            // Receive _g55
            if (json.has("_g55")) {
                ${tickdata_name}._g55 = json.getBoolean("_g55");
            }
            // Receive _g56
            if (json.has("_g56")) {
                ${tickdata_name}._g56 = json.getBoolean("_g56");
            }
            // Receive _g57
            if (json.has("_g57")) {
                ${tickdata_name}._g57 = json.getBoolean("_g57");
            }
            // Receive _g58
            if (json.has("_g58")) {
                ${tickdata_name}._g58 = json.getBoolean("_g58");
            }
            // Receive _g6
            if (json.has("_g6")) {
                ${tickdata_name}._g6 = json.getBoolean("_g6");
            }
            // Receive _g60
            if (json.has("_g60")) {
                ${tickdata_name}._g60 = json.getBoolean("_g60");
            }
            // Receive _g61
            if (json.has("_g61")) {
                ${tickdata_name}._g61 = json.getBoolean("_g61");
            }
            // Receive _g62
            if (json.has("_g62")) {
                ${tickdata_name}._g62 = json.getBoolean("_g62");
            }
            // Receive _g63
            if (json.has("_g63")) {
                ${tickdata_name}._g63 = json.getBoolean("_g63");
            }
            // Receive _g64
            if (json.has("_g64")) {
                ${tickdata_name}._g64 = json.getBoolean("_g64");
            }
            // Receive _g65
            if (json.has("_g65")) {
                ${tickdata_name}._g65 = json.getBoolean("_g65");
            }
            // Receive _g67
            if (json.has("_g67")) {
                ${tickdata_name}._g67 = json.getBoolean("_g67");
            }
            // Receive _g68
            if (json.has("_g68")) {
                ${tickdata_name}._g68 = json.getBoolean("_g68");
            }
            // Receive _g69
            if (json.has("_g69")) {
                ${tickdata_name}._g69 = json.getBoolean("_g69");
            }
            // Receive _g7
            if (json.has("_g7")) {
                ${tickdata_name}._g7 = json.getBoolean("_g7");
            }
            // Receive _g70
            if (json.has("_g70")) {
                ${tickdata_name}._g70 = json.getBoolean("_g70");
            }
            // Receive _g71
            if (json.has("_g71")) {
                ${tickdata_name}._g71 = json.getBoolean("_g71");
            }
            // Receive _g73
            if (json.has("_g73")) {
                ${tickdata_name}._g73 = json.getBoolean("_g73");
            }
            // Receive _g74
            if (json.has("_g74")) {
                ${tickdata_name}._g74 = json.getBoolean("_g74");
            }
            // Receive _g75
            if (json.has("_g75")) {
                ${tickdata_name}._g75 = json.getBoolean("_g75");
            }
            // Receive _g75_e1
            if (json.has("_g75_e1")) {
                ${tickdata_name}._g75_e1 = json.getBoolean("_g75_e1");
            }
            // Receive _g77
            if (json.has("_g77")) {
                ${tickdata_name}._g77 = json.getBoolean("_g77");
            }
            // Receive _g78
            if (json.has("_g78")) {
                ${tickdata_name}._g78 = json.getBoolean("_g78");
            }
            // Receive _g79
            if (json.has("_g79")) {
                ${tickdata_name}._g79 = json.getBoolean("_g79");
            }
            // Receive _g8
            if (json.has("_g8")) {
                ${tickdata_name}._g8 = json.getBoolean("_g8");
            }
            // Receive _g80
            if (json.has("_g80")) {
                ${tickdata_name}._g80 = json.getBoolean("_g80");
            }
            // Receive _g81
            if (json.has("_g81")) {
                ${tickdata_name}._g81 = json.getBoolean("_g81");
            }
            // Receive _g82
            if (json.has("_g82")) {
                ${tickdata_name}._g82 = json.getBoolean("_g82");
            }
            // Receive _g83
            if (json.has("_g83")) {
                ${tickdata_name}._g83 = json.getBoolean("_g83");
            }
            // Receive _g85
            if (json.has("_g85")) {
                ${tickdata_name}._g85 = json.getBoolean("_g85");
            }
            // Receive _g86
            if (json.has("_g86")) {
                ${tickdata_name}._g86 = json.getBoolean("_g86");
            }
            // Receive _g87
            if (json.has("_g87")) {
                ${tickdata_name}._g87 = json.getBoolean("_g87");
            }
            // Receive _g88
            if (json.has("_g88")) {
                ${tickdata_name}._g88 = json.getBoolean("_g88");
            }
            // Receive _g89
            if (json.has("_g89")) {
                ${tickdata_name}._g89 = json.getBoolean("_g89");
            }
            // Receive _g91
            if (json.has("_g91")) {
                ${tickdata_name}._g91 = json.getBoolean("_g91");
            }
            // Receive _g92
            if (json.has("_g92")) {
                ${tickdata_name}._g92 = json.getBoolean("_g92");
            }
            // Receive _g93
            if (json.has("_g93")) {
                ${tickdata_name}._g93 = json.getBoolean("_g93");
            }
            // Receive _g94
            if (json.has("_g94")) {
                ${tickdata_name}._g94 = json.getBoolean("_g94");
            }
            // Receive _g95
            if (json.has("_g95")) {
                ${tickdata_name}._g95 = json.getBoolean("_g95");
            }
            // Receive _g97
            if (json.has("_g97")) {
                ${tickdata_name}._g97 = json.getBoolean("_g97");
            }
            // Receive _g99
            if (json.has("_g99")) {
                ${tickdata_name}._g99 = json.getBoolean("_g99");
            }
            // Receive _pg103
            if (json.has("_pg103")) {
                ${tickdata_name}._pg103 = json.getBoolean("_pg103");
            }
            // Receive _pg106
            if (json.has("_pg106")) {
                ${tickdata_name}._pg106 = json.getBoolean("_pg106");
            }
            // Receive _pg109
            if (json.has("_pg109")) {
                ${tickdata_name}._pg109 = json.getBoolean("_pg109");
            }
            // Receive _pg11
            if (json.has("_pg11")) {
                ${tickdata_name}._pg11 = json.getBoolean("_pg11");
            }
            // Receive _pg117
            if (json.has("_pg117")) {
                ${tickdata_name}._pg117 = json.getBoolean("_pg117");
            }
            // Receive _pg118
            if (json.has("_pg118")) {
                ${tickdata_name}._pg118 = json.getBoolean("_pg118");
            }
            // Receive _pg123
            if (json.has("_pg123")) {
                ${tickdata_name}._pg123 = json.getBoolean("_pg123");
            }
            // Receive _pg124
            if (json.has("_pg124")) {
                ${tickdata_name}._pg124 = json.getBoolean("_pg124");
            }
            // Receive _pg126
            if (json.has("_pg126")) {
                ${tickdata_name}._pg126 = json.getBoolean("_pg126");
            }
            // Receive _pg148
            if (json.has("_pg148")) {
                ${tickdata_name}._pg148 = json.getBoolean("_pg148");
            }
            // Receive _pg151
            if (json.has("_pg151")) {
                ${tickdata_name}._pg151 = json.getBoolean("_pg151");
            }
            // Receive _pg166
            if (json.has("_pg166")) {
                ${tickdata_name}._pg166 = json.getBoolean("_pg166");
            }
            // Receive _pg169
            if (json.has("_pg169")) {
                ${tickdata_name}._pg169 = json.getBoolean("_pg169");
            }
            // Receive _pg17
            if (json.has("_pg17")) {
                ${tickdata_name}._pg17 = json.getBoolean("_pg17");
            }
            // Receive _pg171
            if (json.has("_pg171")) {
                ${tickdata_name}._pg171 = json.getBoolean("_pg171");
            }
            // Receive _pg176
            if (json.has("_pg176")) {
                ${tickdata_name}._pg176 = json.getBoolean("_pg176");
            }
            // Receive _pg187
            if (json.has("_pg187")) {
                ${tickdata_name}._pg187 = json.getBoolean("_pg187");
            }
            // Receive _pg189
            if (json.has("_pg189")) {
                ${tickdata_name}._pg189 = json.getBoolean("_pg189");
            }
            // Receive _pg19
            if (json.has("_pg19")) {
                ${tickdata_name}._pg19 = json.getBoolean("_pg19");
            }
            // Receive _pg199
            if (json.has("_pg199")) {
                ${tickdata_name}._pg199 = json.getBoolean("_pg199");
            }
            // Receive _pg2
            if (json.has("_pg2")) {
                ${tickdata_name}._pg2 = json.getBoolean("_pg2");
            }
            // Receive _pg214
            if (json.has("_pg214")) {
                ${tickdata_name}._pg214 = json.getBoolean("_pg214");
            }
            // Receive _pg234
            if (json.has("_pg234")) {
                ${tickdata_name}._pg234 = json.getBoolean("_pg234");
            }
            // Receive _pg242
            if (json.has("_pg242")) {
                ${tickdata_name}._pg242 = json.getBoolean("_pg242");
            }
            // Receive _pg33
            if (json.has("_pg33")) {
                ${tickdata_name}._pg33 = json.getBoolean("_pg33");
            }
            // Receive _pg39
            if (json.has("_pg39")) {
                ${tickdata_name}._pg39 = json.getBoolean("_pg39");
            }
            // Receive _pg42
            if (json.has("_pg42")) {
                ${tickdata_name}._pg42 = json.getBoolean("_pg42");
            }
            // Receive _pg5
            if (json.has("_pg5")) {
                ${tickdata_name}._pg5 = json.getBoolean("_pg5");
            }
            // Receive _pg52
            if (json.has("_pg52")) {
                ${tickdata_name}._pg52 = json.getBoolean("_pg52");
            }
            // Receive _pg53
            if (json.has("_pg53")) {
                ${tickdata_name}._pg53 = json.getBoolean("_pg53");
            }
            // Receive _pg55
            if (json.has("_pg55")) {
                ${tickdata_name}._pg55 = json.getBoolean("_pg55");
            }
            // Receive _pg56
            if (json.has("_pg56")) {
                ${tickdata_name}._pg56 = json.getBoolean("_pg56");
            }
            // Receive _pg58
            if (json.has("_pg58")) {
                ${tickdata_name}._pg58 = json.getBoolean("_pg58");
            }
            // Receive _pg65
            if (json.has("_pg65")) {
                ${tickdata_name}._pg65 = json.getBoolean("_pg65");
            }
            // Receive _pg70
            if (json.has("_pg70")) {
                ${tickdata_name}._pg70 = json.getBoolean("_pg70");
            }
            // Receive _pg71
            if (json.has("_pg71")) {
                ${tickdata_name}._pg71 = json.getBoolean("_pg71");
            }
            // Receive _pg74
            if (json.has("_pg74")) {
                ${tickdata_name}._pg74 = json.getBoolean("_pg74");
            }
            // Receive _pg79
            if (json.has("_pg79")) {
                ${tickdata_name}._pg79 = json.getBoolean("_pg79");
            }
            // Receive _pg83
            if (json.has("_pg83")) {
                ${tickdata_name}._pg83 = json.getBoolean("_pg83");
            }
            // Receive _pg89
            if (json.has("_pg89")) {
                ${tickdata_name}._pg89 = json.getBoolean("_pg89");
            }
            // Receive _pg95
            if (json.has("_pg95")) {
                ${tickdata_name}._pg95 = json.getBoolean("_pg95");
            }
            // Receive _pre_configApplied
            if (json.has("_pre_configApplied")) {
                ${tickdata_name}._pre_configApplied = json.getInt("_pre_configApplied");
            }
            // Receive _pre_configReady
            if (json.has("_pre_configReady")) {
                ${tickdata_name}._pre_configReady = json.getBoolean("_pre_configReady");
            }
            // Receive _pre_configSequence
            if (json.has("_pre_configSequence")) {
                ${tickdata_name}._pre_configSequence = json.getInt("_pre_configSequence");
            }
            // Receive _pre_ewRequests
            if (json.has("_pre_ewRequests")) {
                ${tickdata_name}._pre_ewRequests = json.getInt("_pre_ewRequests");
            }
            // Receive _pre_nsRequests
            if (json.has("_pre_nsRequests")) {
                ${tickdata_name}._pre_nsRequests = json.getInt("_pre_nsRequests");
            }
            // Receive _pre_pending1
            if (json.has("_pre_pending1")) {
                ${tickdata_name}._pre_pending1 = json.getInt("_pre_pending1");
            }
            // Receive _pre_pending2
            if (json.has("_pre_pending2")) {
                ${tickdata_name}._pre_pending2 = json.getInt("_pre_pending2");
            }
            // Receive _pre_pending3
            if (json.has("_pre_pending3")) {
                ${tickdata_name}._pre_pending3 = json.getInt("_pre_pending3");
            }
            // Receive _pre_pending4
            if (json.has("_pre_pending4")) {
                ${tickdata_name}._pre_pending4 = json.getInt("_pre_pending4");
            }
            // Receive _pre_pending5
            if (json.has("_pre_pending5")) {
                ${tickdata_name}._pre_pending5 = json.getInt("_pre_pending5");
            }
            // Receive _pre_pending6
            if (json.has("_pre_pending6")) {
                ${tickdata_name}._pre_pending6 = json.getInt("_pre_pending6");
            }
            // Receive _reg_configApplied
            if (json.has("_reg_configApplied")) {
                ${tickdata_name}._reg_configApplied = json.getInt("_reg_configApplied");
            }
            // Receive _reg_configReady
            if (json.has("_reg_configReady")) {
                ${tickdata_name}._reg_configReady = json.getBoolean("_reg_configReady");
            }
            // Receive _reg_configSequence
            if (json.has("_reg_configSequence")) {
                ${tickdata_name}._reg_configSequence = json.getInt("_reg_configSequence");
            }
            // Receive _reg_ewRequests
            if (json.has("_reg_ewRequests")) {
                ${tickdata_name}._reg_ewRequests = json.getInt("_reg_ewRequests");
            }
            // Receive _reg_nsRequests
            if (json.has("_reg_nsRequests")) {
                ${tickdata_name}._reg_nsRequests = json.getInt("_reg_nsRequests");
            }
            // Receive _reg_pending1
            if (json.has("_reg_pending1")) {
                ${tickdata_name}._reg_pending1 = json.getInt("_reg_pending1");
            }
            // Receive _reg_pending2
            if (json.has("_reg_pending2")) {
                ${tickdata_name}._reg_pending2 = json.getInt("_reg_pending2");
            }
            // Receive _reg_pending3
            if (json.has("_reg_pending3")) {
                ${tickdata_name}._reg_pending3 = json.getInt("_reg_pending3");
            }
            // Receive _reg_pending4
            if (json.has("_reg_pending4")) {
                ${tickdata_name}._reg_pending4 = json.getInt("_reg_pending4");
            }
            // Receive _reg_pending5
            if (json.has("_reg_pending5")) {
                ${tickdata_name}._reg_pending5 = json.getInt("_reg_pending5");
            }
            // Receive _reg_pending6
            if (json.has("_reg_pending6")) {
                ${tickdata_name}._reg_pending6 = json.getInt("_reg_pending6");
            }
            // Receive _taken_transitions
            if (json.has("_taken_transitions")) {
                JSONArray _array = json.getJSONArray("_taken_transitions");
                for (int i = 0; i < _array.length(); i++) {
                    ${tickdata_name}._taken_transitions[i] = _array.getInt(i);
                }
            }
            // Receive badPacket
            if (json.has("badPacket")) {
                ${tickdata_name}.badPacket = json.getBoolean("badPacket");
            }
            // Receive c
            if (json.has("c")) {
                ${tickdata_name}.c = json.getDouble("c");
            }
            // Receive configSequence
            if (json.has("configSequence")) {
                ${tickdata_name}.configSequence = json.getInt("configSequence");
            }
            // Receive digits
            if (json.has("digits")) {
                ${tickdata_name}.digits = json.getInt("digits");
            }
            // Receive ewRequests
            if (json.has("ewRequests")) {
                ${tickdata_name}.ewRequests = json.getInt("ewRequests");
            }
            // Receive ewServed
            if (json.has("ewServed")) {
                ${tickdata_name}.ewServed = json.getInt("ewServed");
            }
            // Receive field
            if (json.has("field")) {
                ${tickdata_name}.field = json.getInt("field");
            }
            // Receive nsRequests
            if (json.has("nsRequests")) {
                ${tickdata_name}.nsRequests = json.getInt("nsRequests");
            }
            // Receive nsServed
            if (json.has("nsServed")) {
                ${tickdata_name}.nsServed = json.getInt("nsServed");
            }
            // Receive number
            if (json.has("number")) {
                ${tickdata_name}.number = json.getInt("number");
            }
            // Receive pending1
            if (json.has("pending1")) {
                ${tickdata_name}.pending1 = json.getInt("pending1");
            }
            // Receive pending2
            if (json.has("pending2")) {
                ${tickdata_name}.pending2 = json.getInt("pending2");
            }
            // Receive pending3
            if (json.has("pending3")) {
                ${tickdata_name}.pending3 = json.getInt("pending3");
            }
            // Receive pending4
            if (json.has("pending4")) {
                ${tickdata_name}.pending4 = json.getInt("pending4");
            }
            // Receive pending5
            if (json.has("pending5")) {
                ${tickdata_name}.pending5 = json.getInt("pending5");
            }
            // Receive pending6
            if (json.has("pending6")) {
                ${tickdata_name}.pending6 = json.getInt("pending6");
            }
            // Receive staged1
            if (json.has("staged1")) {
                ${tickdata_name}.staged1 = json.getInt("staged1");
            }
            // Receive staged2
            if (json.has("staged2")) {
                ${tickdata_name}.staged2 = json.getInt("staged2");
            }
            // Receive staged3
            if (json.has("staged3")) {
                ${tickdata_name}.staged3 = json.getInt("staged3");
            }
            // Receive staged4
            if (json.has("staged4")) {
                ${tickdata_name}.staged4 = json.getInt("staged4");
            }
            // Receive staged5
            if (json.has("staged5")) {
                ${tickdata_name}.staged5 = json.getInt("staged5");
            }
        } catch (IOException e) {
            e.printStackTrace();
        } catch (JSONException e) {
           // Ignore other input
        }
    }
    
    private static void sendVariables() {
        JSONObject json = new JSONObject();
        
        // Send EWraised
        json.put("EWraised", JSONObject.wrap(${tickdata_name}.EWraised));
        // Send NSraised
        json.put("NSraised", JSONObject.wrap(${tickdata_name}.NSraised));
        // Send configChar
        json.put("configChar", JSONObject.wrap(${tickdata_name}.configChar));
        // Send configValid
        json.put("configValid", JSONObject.wrap(${tickdata_name}.configValid));
        // Send deltaT
        json.put("deltaT", JSONObject.wrap(${tickdata_name}.deltaT));
        // Send task
        json.put("task", JSONObject.wrap(${tickdata_name}.task));
        // Send LEDR
        json.put("LEDR", JSONObject.wrap(${tickdata_name}.LEDR));
        // Send activeTask
        json.put("activeTask", JSONObject.wrap(${tickdata_name}.activeTask));
        // Send configApplied
        json.put("configApplied", JSONObject.wrap(${tickdata_name}.configApplied));
        // Send configReady
        json.put("configReady", JSONObject.wrap(${tickdata_name}.configReady));
        // Send configRejected
        json.put("configRejected", JSONObject.wrap(${tickdata_name}.configRejected));
        // Send sleepT
        json.put("sleepT", JSONObject.wrap(${tickdata_name}.sleepT));
        // Send t1
        json.put("t1", JSONObject.wrap(${tickdata_name}.t1));
        // Send t2
        json.put("t2", JSONObject.wrap(${tickdata_name}.t2));
        // Send t3
        json.put("t3", JSONObject.wrap(${tickdata_name}.t3));
        // Send t4
        json.put("t4", JSONObject.wrap(${tickdata_name}.t4));
        // Send t5
        json.put("t5", JSONObject.wrap(${tickdata_name}.t5));
        // Send t6
        json.put("t6", JSONObject.wrap(${tickdata_name}.t6));
        // Send waitingConfig
        json.put("waitingConfig", JSONObject.wrap(${tickdata_name}.waitingConfig));
        // Send #ticktime
        json.put("#ticktime", _ticktime);
        // Send _Atrig
        json.put("_Atrig", JSONObject.wrap(${tickdata_name}._Atrig));
        // Send _GO
        json.put("_GO", JSONObject.wrap(${tickdata_name}._GO));
        // Send _TERM
        json.put("_TERM", JSONObject.wrap(${tickdata_name}._TERM));
        // Send _TrafficLight_A_local_wEW
        json.put("_TrafficLight_A_local_wEW", JSONObject.wrap(${tickdata_name}._TrafficLight_A_local_wEW));
        // Send _TrafficLight_A_local_wNS
        json.put("_TrafficLight_A_local_wNS", JSONObject.wrap(${tickdata_name}._TrafficLight_A_local_wNS));
        // Send _cg100
        json.put("_cg100", JSONObject.wrap(${tickdata_name}._cg100));
        // Send _cg101
        json.put("_cg101", JSONObject.wrap(${tickdata_name}._cg101));
        // Send _cg103
        json.put("_cg103", JSONObject.wrap(${tickdata_name}._cg103));
        // Send _cg106
        json.put("_cg106", JSONObject.wrap(${tickdata_name}._cg106));
        // Send _cg107
        json.put("_cg107", JSONObject.wrap(${tickdata_name}._cg107));
        // Send _cg109
        json.put("_cg109", JSONObject.wrap(${tickdata_name}._cg109));
        // Send _cg11
        json.put("_cg11", JSONObject.wrap(${tickdata_name}._cg11));
        // Send _cg112
        json.put("_cg112", JSONObject.wrap(${tickdata_name}._cg112));
        // Send _cg113
        json.put("_cg113", JSONObject.wrap(${tickdata_name}._cg113));
        // Send _cg115
        json.put("_cg115", JSONObject.wrap(${tickdata_name}._cg115));
        // Send _cg117
        json.put("_cg117", JSONObject.wrap(${tickdata_name}._cg117));
        // Send _cg122
        json.put("_cg122", JSONObject.wrap(${tickdata_name}._cg122));
        // Send _cg123
        json.put("_cg123", JSONObject.wrap(${tickdata_name}._cg123));
        // Send _cg124
        json.put("_cg124", JSONObject.wrap(${tickdata_name}._cg124));
        // Send _cg129
        json.put("_cg129", JSONObject.wrap(${tickdata_name}._cg129));
        // Send _cg132
        json.put("_cg132", JSONObject.wrap(${tickdata_name}._cg132));
        // Send _cg137
        json.put("_cg137", JSONObject.wrap(${tickdata_name}._cg137));
        // Send _cg143
        json.put("_cg143", JSONObject.wrap(${tickdata_name}._cg143));
        // Send _cg146
        json.put("_cg146", JSONObject.wrap(${tickdata_name}._cg146));
        // Send _cg15
        json.put("_cg15", JSONObject.wrap(${tickdata_name}._cg15));
        // Send _cg151
        json.put("_cg151", JSONObject.wrap(${tickdata_name}._cg151));
        // Send _cg156
        json.put("_cg156", JSONObject.wrap(${tickdata_name}._cg156));
        // Send _cg159
        json.put("_cg159", JSONObject.wrap(${tickdata_name}._cg159));
        // Send _cg16
        json.put("_cg16", JSONObject.wrap(${tickdata_name}._cg16));
        // Send _cg165
        json.put("_cg165", JSONObject.wrap(${tickdata_name}._cg165));
        // Send _cg168
        json.put("_cg168", JSONObject.wrap(${tickdata_name}._cg168));
        // Send _cg17
        json.put("_cg17", JSONObject.wrap(${tickdata_name}._cg17));
        // Send _cg174
        json.put("_cg174", JSONObject.wrap(${tickdata_name}._cg174));
        // Send _cg175
        json.put("_cg175", JSONObject.wrap(${tickdata_name}._cg175));
        // Send _cg179
        json.put("_cg179", JSONObject.wrap(${tickdata_name}._cg179));
        // Send _cg182
        json.put("_cg182", JSONObject.wrap(${tickdata_name}._cg182));
        // Send _cg184
        json.put("_cg184", JSONObject.wrap(${tickdata_name}._cg184));
        // Send _cg186
        json.put("_cg186", JSONObject.wrap(${tickdata_name}._cg186));
        // Send _cg188
        json.put("_cg188", JSONObject.wrap(${tickdata_name}._cg188));
        // Send _cg190
        json.put("_cg190", JSONObject.wrap(${tickdata_name}._cg190));
        // Send _cg192
        json.put("_cg192", JSONObject.wrap(${tickdata_name}._cg192));
        // Send _cg194
        json.put("_cg194", JSONObject.wrap(${tickdata_name}._cg194));
        // Send _cg196
        json.put("_cg196", JSONObject.wrap(${tickdata_name}._cg196));
        // Send _cg198
        json.put("_cg198", JSONObject.wrap(${tickdata_name}._cg198));
        // Send _cg20
        json.put("_cg20", JSONObject.wrap(${tickdata_name}._cg20));
        // Send _cg23
        json.put("_cg23", JSONObject.wrap(${tickdata_name}._cg23));
        // Send _cg24
        json.put("_cg24", JSONObject.wrap(${tickdata_name}._cg24));
        // Send _cg257
        json.put("_cg257", JSONObject.wrap(${tickdata_name}._cg257));
        // Send _cg258
        json.put("_cg258", JSONObject.wrap(${tickdata_name}._cg258));
        // Send _cg27
        json.put("_cg27", JSONObject.wrap(${tickdata_name}._cg27));
        // Send _cg29
        json.put("_cg29", JSONObject.wrap(${tickdata_name}._cg29));
        // Send _cg3
        json.put("_cg3", JSONObject.wrap(${tickdata_name}._cg3));
        // Send _cg31
        json.put("_cg31", JSONObject.wrap(${tickdata_name}._cg31));
        // Send _cg32
        json.put("_cg32", JSONObject.wrap(${tickdata_name}._cg32));
        // Send _cg33
        json.put("_cg33", JSONObject.wrap(${tickdata_name}._cg33));
        // Send _cg36
        json.put("_cg36", JSONObject.wrap(${tickdata_name}._cg36));
        // Send _cg37
        json.put("_cg37", JSONObject.wrap(${tickdata_name}._cg37));
        // Send _cg39
        json.put("_cg39", JSONObject.wrap(${tickdata_name}._cg39));
        // Send _cg4
        json.put("_cg4", JSONObject.wrap(${tickdata_name}._cg4));
        // Send _cg42
        json.put("_cg42", JSONObject.wrap(${tickdata_name}._cg42));
        // Send _cg43
        json.put("_cg43", JSONObject.wrap(${tickdata_name}._cg43));
        // Send _cg45
        json.put("_cg45", JSONObject.wrap(${tickdata_name}._cg45));
        // Send _cg49
        json.put("_cg49", JSONObject.wrap(${tickdata_name}._cg49));
        // Send _cg5
        json.put("_cg5", JSONObject.wrap(${tickdata_name}._cg5));
        // Send _cg52
        json.put("_cg52", JSONObject.wrap(${tickdata_name}._cg52));
        // Send _cg53
        json.put("_cg53", JSONObject.wrap(${tickdata_name}._cg53));
        // Send _cg55
        json.put("_cg55", JSONObject.wrap(${tickdata_name}._cg55));
        // Send _cg57
        json.put("_cg57", JSONObject.wrap(${tickdata_name}._cg57));
        // Send _cg6
        json.put("_cg6", JSONObject.wrap(${tickdata_name}._cg6));
        // Send _cg62
        json.put("_cg62", JSONObject.wrap(${tickdata_name}._cg62));
        // Send _cg63
        json.put("_cg63", JSONObject.wrap(${tickdata_name}._cg63));
        // Send _cg64
        json.put("_cg64", JSONObject.wrap(${tickdata_name}._cg64));
        // Send _cg66
        json.put("_cg66", JSONObject.wrap(${tickdata_name}._cg66));
        // Send _cg67
        json.put("_cg67", JSONObject.wrap(${tickdata_name}._cg67));
        // Send _cg68
        json.put("_cg68", JSONObject.wrap(${tickdata_name}._cg68));
        // Send _cg69
        json.put("_cg69", JSONObject.wrap(${tickdata_name}._cg69));
        // Send _cg71
        json.put("_cg71", JSONObject.wrap(${tickdata_name}._cg71));
        // Send _cg74
        json.put("_cg74", JSONObject.wrap(${tickdata_name}._cg74));
        // Send _cg78
        json.put("_cg78", JSONObject.wrap(${tickdata_name}._cg78));
        // Send _cg79
        json.put("_cg79", JSONObject.wrap(${tickdata_name}._cg79));
        // Send _cg8
        json.put("_cg8", JSONObject.wrap(${tickdata_name}._cg8));
        // Send _cg80
        json.put("_cg80", JSONObject.wrap(${tickdata_name}._cg80));
        // Send _cg83
        json.put("_cg83", JSONObject.wrap(${tickdata_name}._cg83));
        // Send _cg86
        json.put("_cg86", JSONObject.wrap(${tickdata_name}._cg86));
        // Send _cg87
        json.put("_cg87", JSONObject.wrap(${tickdata_name}._cg87));
        // Send _cg89
        json.put("_cg89", JSONObject.wrap(${tickdata_name}._cg89));
        // Send _cg91
        json.put("_cg91", JSONObject.wrap(${tickdata_name}._cg91));
        // Send _cg93
        json.put("_cg93", JSONObject.wrap(${tickdata_name}._cg93));
        // Send _cg95
        json.put("_cg95", JSONObject.wrap(${tickdata_name}._cg95));
        // Send _cg96
        json.put("_cg96", JSONObject.wrap(${tickdata_name}._cg96));
        // Send _cg97
        json.put("_cg97", JSONObject.wrap(${tickdata_name}._cg97));
        // Send _g10
        json.put("_g10", JSONObject.wrap(${tickdata_name}._g10));
        // Send _g100
        json.put("_g100", JSONObject.wrap(${tickdata_name}._g100));
        // Send _g101
        json.put("_g101", JSONObject.wrap(${tickdata_name}._g101));
        // Send _g102
        json.put("_g102", JSONObject.wrap(${tickdata_name}._g102));
        // Send _g102_e2
        json.put("_g102_e2", JSONObject.wrap(${tickdata_name}._g102_e2));
        // Send _g103
        json.put("_g103", JSONObject.wrap(${tickdata_name}._g103));
        // Send _g105
        json.put("_g105", JSONObject.wrap(${tickdata_name}._g105));
        // Send _g106
        json.put("_g106", JSONObject.wrap(${tickdata_name}._g106));
        // Send _g109
        json.put("_g109", JSONObject.wrap(${tickdata_name}._g109));
        // Send _g11
        json.put("_g11", JSONObject.wrap(${tickdata_name}._g11));
        // Send _g110
        json.put("_g110", JSONObject.wrap(${tickdata_name}._g110));
        // Send _g110_e3
        json.put("_g110_e3", JSONObject.wrap(${tickdata_name}._g110_e3));
        // Send _g111
        json.put("_g111", JSONObject.wrap(${tickdata_name}._g111));
        // Send _g112
        json.put("_g112", JSONObject.wrap(${tickdata_name}._g112));
        // Send _g113
        json.put("_g113", JSONObject.wrap(${tickdata_name}._g113));
        // Send _g114
        json.put("_g114", JSONObject.wrap(${tickdata_name}._g114));
        // Send _g115
        json.put("_g115", JSONObject.wrap(${tickdata_name}._g115));
        // Send _g116
        json.put("_g116", JSONObject.wrap(${tickdata_name}._g116));
        // Send _g117
        json.put("_g117", JSONObject.wrap(${tickdata_name}._g117));
        // Send _g118
        json.put("_g118", JSONObject.wrap(${tickdata_name}._g118));
        // Send _g12
        json.put("_g12", JSONObject.wrap(${tickdata_name}._g12));
        // Send _g120
        json.put("_g120", JSONObject.wrap(${tickdata_name}._g120));
        // Send _g121
        json.put("_g121", JSONObject.wrap(${tickdata_name}._g121));
        // Send _g122
        json.put("_g122", JSONObject.wrap(${tickdata_name}._g122));
        // Send _g123
        json.put("_g123", JSONObject.wrap(${tickdata_name}._g123));
        // Send _g124
        json.put("_g124", JSONObject.wrap(${tickdata_name}._g124));
        // Send _g125
        json.put("_g125", JSONObject.wrap(${tickdata_name}._g125));
        // Send _g126
        json.put("_g126", JSONObject.wrap(${tickdata_name}._g126));
        // Send _g128
        json.put("_g128", JSONObject.wrap(${tickdata_name}._g128));
        // Send _g129
        json.put("_g129", JSONObject.wrap(${tickdata_name}._g129));
        // Send _g12_e1
        json.put("_g12_e1", JSONObject.wrap(${tickdata_name}._g12_e1));
        // Send _g131
        json.put("_g131", JSONObject.wrap(${tickdata_name}._g131));
        // Send _g132
        json.put("_g132", JSONObject.wrap(${tickdata_name}._g132));
        // Send _g133
        json.put("_g133", JSONObject.wrap(${tickdata_name}._g133));
        // Send _g134
        json.put("_g134", JSONObject.wrap(${tickdata_name}._g134));
        // Send _g136
        json.put("_g136", JSONObject.wrap(${tickdata_name}._g136));
        // Send _g137
        json.put("_g137", JSONObject.wrap(${tickdata_name}._g137));
        // Send _g139
        json.put("_g139", JSONObject.wrap(${tickdata_name}._g139));
        // Send _g14
        json.put("_g14", JSONObject.wrap(${tickdata_name}._g14));
        // Send _g140
        json.put("_g140", JSONObject.wrap(${tickdata_name}._g140));
        // Send _g142
        json.put("_g142", JSONObject.wrap(${tickdata_name}._g142));
        // Send _g143
        json.put("_g143", JSONObject.wrap(${tickdata_name}._g143));
        // Send _g145
        json.put("_g145", JSONObject.wrap(${tickdata_name}._g145));
        // Send _g146
        json.put("_g146", JSONObject.wrap(${tickdata_name}._g146));
        // Send _g147
        json.put("_g147", JSONObject.wrap(${tickdata_name}._g147));
        // Send _g148
        json.put("_g148", JSONObject.wrap(${tickdata_name}._g148));
        // Send _g15
        json.put("_g15", JSONObject.wrap(${tickdata_name}._g15));
        // Send _g150
        json.put("_g150", JSONObject.wrap(${tickdata_name}._g150));
        // Send _g151
        json.put("_g151", JSONObject.wrap(${tickdata_name}._g151));
        // Send _g153
        json.put("_g153", JSONObject.wrap(${tickdata_name}._g153));
        // Send _g156
        json.put("_g156", JSONObject.wrap(${tickdata_name}._g156));
        // Send _g157
        json.put("_g157", JSONObject.wrap(${tickdata_name}._g157));
        // Send _g159
        json.put("_g159", JSONObject.wrap(${tickdata_name}._g159));
        // Send _g16
        json.put("_g16", JSONObject.wrap(${tickdata_name}._g16));
        // Send _g160
        json.put("_g160", JSONObject.wrap(${tickdata_name}._g160));
        // Send _g162
        json.put("_g162", JSONObject.wrap(${tickdata_name}._g162));
        // Send _g165
        json.put("_g165", JSONObject.wrap(${tickdata_name}._g165));
        // Send _g166
        json.put("_g166", JSONObject.wrap(${tickdata_name}._g166));
        // Send _g168
        json.put("_g168", JSONObject.wrap(${tickdata_name}._g168));
        // Send _g169
        json.put("_g169", JSONObject.wrap(${tickdata_name}._g169));
        // Send _g17
        json.put("_g17", JSONObject.wrap(${tickdata_name}._g17));
        // Send _g171
        json.put("_g171", JSONObject.wrap(${tickdata_name}._g171));
        // Send _g175
        json.put("_g175", JSONObject.wrap(${tickdata_name}._g175));
        // Send _g176
        json.put("_g176", JSONObject.wrap(${tickdata_name}._g176));
        // Send _g178
        json.put("_g178", JSONObject.wrap(${tickdata_name}._g178));
        // Send _g18
        json.put("_g18", JSONObject.wrap(${tickdata_name}._g18));
        // Send _g182
        json.put("_g182", JSONObject.wrap(${tickdata_name}._g182));
        // Send _g183
        json.put("_g183", JSONObject.wrap(${tickdata_name}._g183));
        // Send _g184
        json.put("_g184", JSONObject.wrap(${tickdata_name}._g184));
        // Send _g185
        json.put("_g185", JSONObject.wrap(${tickdata_name}._g185));
        // Send _g186
        json.put("_g186", JSONObject.wrap(${tickdata_name}._g186));
        // Send _g187
        json.put("_g187", JSONObject.wrap(${tickdata_name}._g187));
        // Send _g188
        json.put("_g188", JSONObject.wrap(${tickdata_name}._g188));
        // Send _g189
        json.put("_g189", JSONObject.wrap(${tickdata_name}._g189));
        // Send _g19
        json.put("_g19", JSONObject.wrap(${tickdata_name}._g19));
        // Send _g190
        json.put("_g190", JSONObject.wrap(${tickdata_name}._g190));
        // Send _g191
        json.put("_g191", JSONObject.wrap(${tickdata_name}._g191));
        // Send _g192
        json.put("_g192", JSONObject.wrap(${tickdata_name}._g192));
        // Send _g193
        json.put("_g193", JSONObject.wrap(${tickdata_name}._g193));
        // Send _g194
        json.put("_g194", JSONObject.wrap(${tickdata_name}._g194));
        // Send _g195
        json.put("_g195", JSONObject.wrap(${tickdata_name}._g195));
        // Send _g196
        json.put("_g196", JSONObject.wrap(${tickdata_name}._g196));
        // Send _g197
        json.put("_g197", JSONObject.wrap(${tickdata_name}._g197));
        // Send _g198
        json.put("_g198", JSONObject.wrap(${tickdata_name}._g198));
        // Send _g199
        json.put("_g199", JSONObject.wrap(${tickdata_name}._g199));
        // Send _g2
        json.put("_g2", JSONObject.wrap(${tickdata_name}._g2));
        // Send _g20
        json.put("_g20", JSONObject.wrap(${tickdata_name}._g20));
        // Send _g200
        json.put("_g200", JSONObject.wrap(${tickdata_name}._g200));
        // Send _g202
        json.put("_g202", JSONObject.wrap(${tickdata_name}._g202));
        // Send _g210
        json.put("_g210", JSONObject.wrap(${tickdata_name}._g210));
        // Send _g214
        json.put("_g214", JSONObject.wrap(${tickdata_name}._g214));
        // Send _g218
        json.put("_g218", JSONObject.wrap(${tickdata_name}._g218));
        // Send _g22
        json.put("_g22", JSONObject.wrap(${tickdata_name}._g22));
        // Send _g226
        json.put("_g226", JSONObject.wrap(${tickdata_name}._g226));
        // Send _g23
        json.put("_g23", JSONObject.wrap(${tickdata_name}._g23));
        // Send _g230
        json.put("_g230", JSONObject.wrap(${tickdata_name}._g230));
        // Send _g234
        json.put("_g234", JSONObject.wrap(${tickdata_name}._g234));
        // Send _g238
        json.put("_g238", JSONObject.wrap(${tickdata_name}._g238));
        // Send _g24
        json.put("_g24", JSONObject.wrap(${tickdata_name}._g24));
        // Send _g242
        json.put("_g242", JSONObject.wrap(${tickdata_name}._g242));
        // Send _g246
        json.put("_g246", JSONObject.wrap(${tickdata_name}._g246));
        // Send _g25
        json.put("_g25", JSONObject.wrap(${tickdata_name}._g25));
        // Send _g27
        json.put("_g27", JSONObject.wrap(${tickdata_name}._g27));
        // Send _g28
        json.put("_g28", JSONObject.wrap(${tickdata_name}._g28));
        // Send _g29
        json.put("_g29", JSONObject.wrap(${tickdata_name}._g29));
        // Send _g30
        json.put("_g30", JSONObject.wrap(${tickdata_name}._g30));
        // Send _g31
        json.put("_g31", JSONObject.wrap(${tickdata_name}._g31));
        // Send _g33
        json.put("_g33", JSONObject.wrap(${tickdata_name}._g33));
        // Send _g35
        json.put("_g35", JSONObject.wrap(${tickdata_name}._g35));
        // Send _g36
        json.put("_g36", JSONObject.wrap(${tickdata_name}._g36));
        // Send _g37
        json.put("_g37", JSONObject.wrap(${tickdata_name}._g37));
        // Send _g38
        json.put("_g38", JSONObject.wrap(${tickdata_name}._g38));
        // Send _g38_e2
        json.put("_g38_e2", JSONObject.wrap(${tickdata_name}._g38_e2));
        // Send _g39
        json.put("_g39", JSONObject.wrap(${tickdata_name}._g39));
        // Send _g4
        json.put("_g4", JSONObject.wrap(${tickdata_name}._g4));
        // Send _g41
        json.put("_g41", JSONObject.wrap(${tickdata_name}._g41));
        // Send _g42
        json.put("_g42", JSONObject.wrap(${tickdata_name}._g42));
        // Send _g45
        json.put("_g45", JSONObject.wrap(${tickdata_name}._g45));
        // Send _g46
        json.put("_g46", JSONObject.wrap(${tickdata_name}._g46));
        // Send _g46_e3
        json.put("_g46_e3", JSONObject.wrap(${tickdata_name}._g46_e3));
        // Send _g49
        json.put("_g49", JSONObject.wrap(${tickdata_name}._g49));
        // Send _g5
        json.put("_g5", JSONObject.wrap(${tickdata_name}._g5));
        // Send _g50
        json.put("_g50", JSONObject.wrap(${tickdata_name}._g50));
        // Send _g50_e4
        json.put("_g50_e4", JSONObject.wrap(${tickdata_name}._g50_e4));
        // Send _g51
        json.put("_g51", JSONObject.wrap(${tickdata_name}._g51));
        // Send _g52
        json.put("_g52", JSONObject.wrap(${tickdata_name}._g52));
        // Send _g53
        json.put("_g53", JSONObject.wrap(${tickdata_name}._g53));
        // Send _g54
        json.put("_g54", JSONObject.wrap(${tickdata_name}._g54));
        // Send _g55
        json.put("_g55", JSONObject.wrap(${tickdata_name}._g55));
        // Send _g56
        json.put("_g56", JSONObject.wrap(${tickdata_name}._g56));
        // Send _g57
        json.put("_g57", JSONObject.wrap(${tickdata_name}._g57));
        // Send _g58
        json.put("_g58", JSONObject.wrap(${tickdata_name}._g58));
        // Send _g6
        json.put("_g6", JSONObject.wrap(${tickdata_name}._g6));
        // Send _g60
        json.put("_g60", JSONObject.wrap(${tickdata_name}._g60));
        // Send _g61
        json.put("_g61", JSONObject.wrap(${tickdata_name}._g61));
        // Send _g62
        json.put("_g62", JSONObject.wrap(${tickdata_name}._g62));
        // Send _g63
        json.put("_g63", JSONObject.wrap(${tickdata_name}._g63));
        // Send _g64
        json.put("_g64", JSONObject.wrap(${tickdata_name}._g64));
        // Send _g65
        json.put("_g65", JSONObject.wrap(${tickdata_name}._g65));
        // Send _g67
        json.put("_g67", JSONObject.wrap(${tickdata_name}._g67));
        // Send _g68
        json.put("_g68", JSONObject.wrap(${tickdata_name}._g68));
        // Send _g69
        json.put("_g69", JSONObject.wrap(${tickdata_name}._g69));
        // Send _g7
        json.put("_g7", JSONObject.wrap(${tickdata_name}._g7));
        // Send _g70
        json.put("_g70", JSONObject.wrap(${tickdata_name}._g70));
        // Send _g71
        json.put("_g71", JSONObject.wrap(${tickdata_name}._g71));
        // Send _g73
        json.put("_g73", JSONObject.wrap(${tickdata_name}._g73));
        // Send _g74
        json.put("_g74", JSONObject.wrap(${tickdata_name}._g74));
        // Send _g75
        json.put("_g75", JSONObject.wrap(${tickdata_name}._g75));
        // Send _g75_e1
        json.put("_g75_e1", JSONObject.wrap(${tickdata_name}._g75_e1));
        // Send _g77
        json.put("_g77", JSONObject.wrap(${tickdata_name}._g77));
        // Send _g78
        json.put("_g78", JSONObject.wrap(${tickdata_name}._g78));
        // Send _g79
        json.put("_g79", JSONObject.wrap(${tickdata_name}._g79));
        // Send _g8
        json.put("_g8", JSONObject.wrap(${tickdata_name}._g8));
        // Send _g80
        json.put("_g80", JSONObject.wrap(${tickdata_name}._g80));
        // Send _g81
        json.put("_g81", JSONObject.wrap(${tickdata_name}._g81));
        // Send _g82
        json.put("_g82", JSONObject.wrap(${tickdata_name}._g82));
        // Send _g83
        json.put("_g83", JSONObject.wrap(${tickdata_name}._g83));
        // Send _g85
        json.put("_g85", JSONObject.wrap(${tickdata_name}._g85));
        // Send _g86
        json.put("_g86", JSONObject.wrap(${tickdata_name}._g86));
        // Send _g87
        json.put("_g87", JSONObject.wrap(${tickdata_name}._g87));
        // Send _g88
        json.put("_g88", JSONObject.wrap(${tickdata_name}._g88));
        // Send _g89
        json.put("_g89", JSONObject.wrap(${tickdata_name}._g89));
        // Send _g91
        json.put("_g91", JSONObject.wrap(${tickdata_name}._g91));
        // Send _g92
        json.put("_g92", JSONObject.wrap(${tickdata_name}._g92));
        // Send _g93
        json.put("_g93", JSONObject.wrap(${tickdata_name}._g93));
        // Send _g94
        json.put("_g94", JSONObject.wrap(${tickdata_name}._g94));
        // Send _g95
        json.put("_g95", JSONObject.wrap(${tickdata_name}._g95));
        // Send _g97
        json.put("_g97", JSONObject.wrap(${tickdata_name}._g97));
        // Send _g99
        json.put("_g99", JSONObject.wrap(${tickdata_name}._g99));
        // Send _pg103
        json.put("_pg103", JSONObject.wrap(${tickdata_name}._pg103));
        // Send _pg106
        json.put("_pg106", JSONObject.wrap(${tickdata_name}._pg106));
        // Send _pg109
        json.put("_pg109", JSONObject.wrap(${tickdata_name}._pg109));
        // Send _pg11
        json.put("_pg11", JSONObject.wrap(${tickdata_name}._pg11));
        // Send _pg117
        json.put("_pg117", JSONObject.wrap(${tickdata_name}._pg117));
        // Send _pg118
        json.put("_pg118", JSONObject.wrap(${tickdata_name}._pg118));
        // Send _pg123
        json.put("_pg123", JSONObject.wrap(${tickdata_name}._pg123));
        // Send _pg124
        json.put("_pg124", JSONObject.wrap(${tickdata_name}._pg124));
        // Send _pg126
        json.put("_pg126", JSONObject.wrap(${tickdata_name}._pg126));
        // Send _pg148
        json.put("_pg148", JSONObject.wrap(${tickdata_name}._pg148));
        // Send _pg151
        json.put("_pg151", JSONObject.wrap(${tickdata_name}._pg151));
        // Send _pg166
        json.put("_pg166", JSONObject.wrap(${tickdata_name}._pg166));
        // Send _pg169
        json.put("_pg169", JSONObject.wrap(${tickdata_name}._pg169));
        // Send _pg17
        json.put("_pg17", JSONObject.wrap(${tickdata_name}._pg17));
        // Send _pg171
        json.put("_pg171", JSONObject.wrap(${tickdata_name}._pg171));
        // Send _pg176
        json.put("_pg176", JSONObject.wrap(${tickdata_name}._pg176));
        // Send _pg187
        json.put("_pg187", JSONObject.wrap(${tickdata_name}._pg187));
        // Send _pg189
        json.put("_pg189", JSONObject.wrap(${tickdata_name}._pg189));
        // Send _pg19
        json.put("_pg19", JSONObject.wrap(${tickdata_name}._pg19));
        // Send _pg199
        json.put("_pg199", JSONObject.wrap(${tickdata_name}._pg199));
        // Send _pg2
        json.put("_pg2", JSONObject.wrap(${tickdata_name}._pg2));
        // Send _pg214
        json.put("_pg214", JSONObject.wrap(${tickdata_name}._pg214));
        // Send _pg234
        json.put("_pg234", JSONObject.wrap(${tickdata_name}._pg234));
        // Send _pg242
        json.put("_pg242", JSONObject.wrap(${tickdata_name}._pg242));
        // Send _pg33
        json.put("_pg33", JSONObject.wrap(${tickdata_name}._pg33));
        // Send _pg39
        json.put("_pg39", JSONObject.wrap(${tickdata_name}._pg39));
        // Send _pg42
        json.put("_pg42", JSONObject.wrap(${tickdata_name}._pg42));
        // Send _pg5
        json.put("_pg5", JSONObject.wrap(${tickdata_name}._pg5));
        // Send _pg52
        json.put("_pg52", JSONObject.wrap(${tickdata_name}._pg52));
        // Send _pg53
        json.put("_pg53", JSONObject.wrap(${tickdata_name}._pg53));
        // Send _pg55
        json.put("_pg55", JSONObject.wrap(${tickdata_name}._pg55));
        // Send _pg56
        json.put("_pg56", JSONObject.wrap(${tickdata_name}._pg56));
        // Send _pg58
        json.put("_pg58", JSONObject.wrap(${tickdata_name}._pg58));
        // Send _pg65
        json.put("_pg65", JSONObject.wrap(${tickdata_name}._pg65));
        // Send _pg70
        json.put("_pg70", JSONObject.wrap(${tickdata_name}._pg70));
        // Send _pg71
        json.put("_pg71", JSONObject.wrap(${tickdata_name}._pg71));
        // Send _pg74
        json.put("_pg74", JSONObject.wrap(${tickdata_name}._pg74));
        // Send _pg79
        json.put("_pg79", JSONObject.wrap(${tickdata_name}._pg79));
        // Send _pg83
        json.put("_pg83", JSONObject.wrap(${tickdata_name}._pg83));
        // Send _pg89
        json.put("_pg89", JSONObject.wrap(${tickdata_name}._pg89));
        // Send _pg95
        json.put("_pg95", JSONObject.wrap(${tickdata_name}._pg95));
        // Send _pre_configApplied
        json.put("_pre_configApplied", JSONObject.wrap(${tickdata_name}._pre_configApplied));
        // Send _pre_configReady
        json.put("_pre_configReady", JSONObject.wrap(${tickdata_name}._pre_configReady));
        // Send _pre_configSequence
        json.put("_pre_configSequence", JSONObject.wrap(${tickdata_name}._pre_configSequence));
        // Send _pre_ewRequests
        json.put("_pre_ewRequests", JSONObject.wrap(${tickdata_name}._pre_ewRequests));
        // Send _pre_nsRequests
        json.put("_pre_nsRequests", JSONObject.wrap(${tickdata_name}._pre_nsRequests));
        // Send _pre_pending1
        json.put("_pre_pending1", JSONObject.wrap(${tickdata_name}._pre_pending1));
        // Send _pre_pending2
        json.put("_pre_pending2", JSONObject.wrap(${tickdata_name}._pre_pending2));
        // Send _pre_pending3
        json.put("_pre_pending3", JSONObject.wrap(${tickdata_name}._pre_pending3));
        // Send _pre_pending4
        json.put("_pre_pending4", JSONObject.wrap(${tickdata_name}._pre_pending4));
        // Send _pre_pending5
        json.put("_pre_pending5", JSONObject.wrap(${tickdata_name}._pre_pending5));
        // Send _pre_pending6
        json.put("_pre_pending6", JSONObject.wrap(${tickdata_name}._pre_pending6));
        // Send _reg_configApplied
        json.put("_reg_configApplied", JSONObject.wrap(${tickdata_name}._reg_configApplied));
        // Send _reg_configReady
        json.put("_reg_configReady", JSONObject.wrap(${tickdata_name}._reg_configReady));
        // Send _reg_configSequence
        json.put("_reg_configSequence", JSONObject.wrap(${tickdata_name}._reg_configSequence));
        // Send _reg_ewRequests
        json.put("_reg_ewRequests", JSONObject.wrap(${tickdata_name}._reg_ewRequests));
        // Send _reg_nsRequests
        json.put("_reg_nsRequests", JSONObject.wrap(${tickdata_name}._reg_nsRequests));
        // Send _reg_pending1
        json.put("_reg_pending1", JSONObject.wrap(${tickdata_name}._reg_pending1));
        // Send _reg_pending2
        json.put("_reg_pending2", JSONObject.wrap(${tickdata_name}._reg_pending2));
        // Send _reg_pending3
        json.put("_reg_pending3", JSONObject.wrap(${tickdata_name}._reg_pending3));
        // Send _reg_pending4
        json.put("_reg_pending4", JSONObject.wrap(${tickdata_name}._reg_pending4));
        // Send _reg_pending5
        json.put("_reg_pending5", JSONObject.wrap(${tickdata_name}._reg_pending5));
        // Send _reg_pending6
        json.put("_reg_pending6", JSONObject.wrap(${tickdata_name}._reg_pending6));
        // Send _taken_transitions
        json.put("_taken_transitions", JSONObject.wrap(${tickdata_name}._taken_transitions));
        // Send badPacket
        json.put("badPacket", JSONObject.wrap(${tickdata_name}.badPacket));
        // Send c
        json.put("c", JSONObject.wrap(${tickdata_name}.c));
        // Send configSequence
        json.put("configSequence", JSONObject.wrap(${tickdata_name}.configSequence));
        // Send digits
        json.put("digits", JSONObject.wrap(${tickdata_name}.digits));
        // Send ewRequests
        json.put("ewRequests", JSONObject.wrap(${tickdata_name}.ewRequests));
        // Send ewServed
        json.put("ewServed", JSONObject.wrap(${tickdata_name}.ewServed));
        // Send field
        json.put("field", JSONObject.wrap(${tickdata_name}.field));
        // Send nsRequests
        json.put("nsRequests", JSONObject.wrap(${tickdata_name}.nsRequests));
        // Send nsServed
        json.put("nsServed", JSONObject.wrap(${tickdata_name}.nsServed));
        // Send number
        json.put("number", JSONObject.wrap(${tickdata_name}.number));
        // Send pending1
        json.put("pending1", JSONObject.wrap(${tickdata_name}.pending1));
        // Send pending2
        json.put("pending2", JSONObject.wrap(${tickdata_name}.pending2));
        // Send pending3
        json.put("pending3", JSONObject.wrap(${tickdata_name}.pending3));
        // Send pending4
        json.put("pending4", JSONObject.wrap(${tickdata_name}.pending4));
        // Send pending5
        json.put("pending5", JSONObject.wrap(${tickdata_name}.pending5));
        // Send pending6
        json.put("pending6", JSONObject.wrap(${tickdata_name}.pending6));
        // Send staged1
        json.put("staged1", JSONObject.wrap(${tickdata_name}.staged1));
        // Send staged2
        json.put("staged2", JSONObject.wrap(${tickdata_name}.staged2));
        // Send staged3
        json.put("staged3", JSONObject.wrap(${tickdata_name}.staged3));
        // Send staged4
        json.put("staged4", JSONObject.wrap(${tickdata_name}.staged4));
        // Send staged5
        json.put("staged5", JSONObject.wrap(${tickdata_name}.staged5));
        
        System.out.println(json.toString());
    }
</#macro>
