https://plus.google.com/u/0/+FrankBussProgrammer/posts/49GfxGzHqqi
D0 FD 20 00 21 F0 B2 D1
B3 A3 E1 A2 14 1F D1 B4
A3 F1 94 1C 19 D0 B2 40
09 A3 F1 F6 B3 40 09 D8
B4 A3 F1 94 1C 2A D1 B2
40 09 A3 F1 F5 B3 40 09


000 D0    LDM 0
001 FD    DCL
002 20 00 FIM P0,$00
004 21    SRC P0
005 F0    CLB
006 B2    XCH R2
007 D1    LDM 1
008 B3    XCH R3
009 A3    LD R3
00A E1    WMP
00B A2    LD R2
;;;; first out ;;;;
00C 14 1F JCN AZ,$1F
00E D1    LDM 1
00F B4    XCH R4
010 A3    LD R3
011 F1    CLC
012 94    SUB R4
013 1C 19 JCN AN,$19
015 D0    LDM 0
016 B2    XCH R2
017 40 09 JUN $009
019 A3    LD R3
01A F1    CLC
01B F6    RAR
01C B3    XCH R3
01D 40 09 JUN $009
01F D8    LDM 8
020 B4    XCH R4
021 A3    LD R3
022 F1    CLC
023 94    SUB R4
024 1C 2A JCN AN,$2A
026 D1    LDM 1
027 B2    XCH R2
028 40 09 JUN $009
02A A3    LD R3
02B F1    CLC
02C F5    RAL
02D B3    XCH R3
02E 40 09 JUN $009
