#ifndef __CA51F2_XDATA_H__
#define __CA51F2_XDATA_H__

#ifdef _MAIN_C_
	#define XRAM_U8										volatile unsigned char xdata
	#define XRAM_U16									volatile unsigned int xdata
	#define XRAM_AT_(x)									_at_ x		
#else
	#define XRAM_U8										extern volatile unsigned char xdata
	#define XRAM_U16									extern volatile unsigned int xdata
	#define XRAM_AT_(x)
#endif

XRAM_U8 P00F        XRAM_AT_(0x8000);
XRAM_U8 P01F        XRAM_AT_(0x8001);
XRAM_U8 P02F        XRAM_AT_(0x8002);
XRAM_U8 P03F        XRAM_AT_(0x8003);
XRAM_U8 P04F        XRAM_AT_(0x8004);
XRAM_U8 P05F        XRAM_AT_(0x8005);
XRAM_U8 P06F        XRAM_AT_(0x8006);
XRAM_U8 P07F        XRAM_AT_(0x8007);

XRAM_U8 P10F        XRAM_AT_(0x8008);
XRAM_U8 P11F        XRAM_AT_(0x8009);
XRAM_U8 P12F        XRAM_AT_(0x800a);
XRAM_U8 P13F        XRAM_AT_(0x800b);
XRAM_U8 P14F        XRAM_AT_(0x800c);
XRAM_U8 P15F        XRAM_AT_(0x800d);
XRAM_U8 P16F        XRAM_AT_(0x800e);
XRAM_U8 P17F        XRAM_AT_(0x800f);

XRAM_U8 P20F        XRAM_AT_(0x8010);
XRAM_U8 P21F        XRAM_AT_(0x8011);
XRAM_U8 P22F        XRAM_AT_(0x8012);
XRAM_U8 P23F        XRAM_AT_(0x8013);
XRAM_U8 P24F        XRAM_AT_(0x8014);
XRAM_U8 P25F        XRAM_AT_(0x8015);
XRAM_U8 P26F        XRAM_AT_(0x8016);
XRAM_U8 P27F        XRAM_AT_(0x8017);

XRAM_U8 P30F        XRAM_AT_(0x8018);
XRAM_U8 P31F        XRAM_AT_(0x8019);
XRAM_U8 P32F        XRAM_AT_(0x801a);
XRAM_U8 P33F        XRAM_AT_(0x801b);
XRAM_U8 P34F        XRAM_AT_(0x801c);
XRAM_U8 P35F        XRAM_AT_(0x801d);
XRAM_U8 P36F        XRAM_AT_(0x801e);
XRAM_U8 P37F        XRAM_AT_(0x801f);

XRAM_U8 P40F        XRAM_AT_(0x8020);
XRAM_U8 P41F        XRAM_AT_(0x8021);
XRAM_U8 P42F        XRAM_AT_(0x8022);
XRAM_U8 P43F        XRAM_AT_(0x8023);
XRAM_U8 P44F        XRAM_AT_(0x8024);
XRAM_U8 P45F        XRAM_AT_(0x8025);
XRAM_U8 P46F        XRAM_AT_(0x8026);
XRAM_U8 P47F        XRAM_AT_(0x8027);

XRAM_U8 P50F        XRAM_AT_(0x8028);
XRAM_U8 P51F        XRAM_AT_(0x8029);
XRAM_U8 P52F        XRAM_AT_(0x802a);
XRAM_U8 P53F        XRAM_AT_(0x802b);
XRAM_U8 P54F        XRAM_AT_(0x802c);
XRAM_U8 P55F        XRAM_AT_(0x802d);
XRAM_U8 P56F        XRAM_AT_(0x802e);
XRAM_U8 P57F        XRAM_AT_(0x802f);

XRAM_U8 P60F        XRAM_AT_(0x8030);
XRAM_U8 P61F        XRAM_AT_(0x8031);
XRAM_U8 P62F        XRAM_AT_(0x8032);
XRAM_U8 P63F        XRAM_AT_(0x8033);
XRAM_U8 P64F        XRAM_AT_(0x8034);
XRAM_U8 P65F        XRAM_AT_(0x8035);
XRAM_U8 P66F        XRAM_AT_(0x8036);
XRAM_U8 P67F        XRAM_AT_(0x8037);

XRAM_U8 P70F        XRAM_AT_(0x8038);
XRAM_U8 P71F        XRAM_AT_(0x8039);
XRAM_U8 P72F        XRAM_AT_(0x803a);
XRAM_U8 P73F        XRAM_AT_(0x803b);
XRAM_U8 P74F        XRAM_AT_(0x803c);
XRAM_U8 P75F        XRAM_AT_(0x803d);


XRAM_U8 OPACON      XRAM_AT_(0x8040);
XRAM_U8 OPBCON      XRAM_AT_(0x8041);
XRAM_U8 OSTRIM      XRAM_AT_(0x8042);


XRAM_U8 CP0CON      XRAM_AT_(0x8048);
XRAM_U8 CP1CON      XRAM_AT_(0x8049);
XRAM_U8 CP2CON      XRAM_AT_(0x804a);
XRAM_U8 CP3CON      XRAM_AT_(0x804b);
XRAM_U8 CPCKS       XRAM_AT_(0x804c);
XRAM_U8 CPSTA       XRAM_AT_(0x804d);
XRAM_U8 CPVTC       XRAM_AT_(0x804e);

XRAM_U8 FT0SL       XRAM_AT_(0x8050);
XRAM_U8 FT0SH       XRAM_AT_(0x8051);
XRAM_U8 FT1SL       XRAM_AT_(0x8052);
XRAM_U8 FT1SH       XRAM_AT_(0x8053);
XRAM_U8 FT2SL       XRAM_AT_(0x8054);
XRAM_U8 FT2SH       XRAM_AT_(0x8055);
XRAM_U8 FT3SL       XRAM_AT_(0x8056);
XRAM_U8 FT3SH       XRAM_AT_(0x8057);

XRAM_U8 CTMCON      XRAM_AT_(0x8058);
XRAM_U8 CTMVTHL     XRAM_AT_(0x8059);
XRAM_U8 CTMVTHH     XRAM_AT_(0x805a);
XRAM_U8 CTMCNTL     XRAM_AT_(0x805b);
XRAM_U8 CTMCNTH     XRAM_AT_(0x805c);

XRAM_U8 MOTCON      XRAM_AT_(0x8060);
XRAM_U8 MOTCFG      XRAM_AT_(0x8061);
XRAM_U8 MTGCON      XRAM_AT_(0x8062);
XRAM_U8 MHLCON      XRAM_AT_(0x8063);
XRAM_U8 MFPCON      XRAM_AT_(0x8064);
XRAM_U8 MOTCMD      XRAM_AT_(0x8065);
XRAM_U8 MTGDL       XRAM_AT_(0x8066);
XRAM_U8 MOTIF       XRAM_AT_(0x8067);

XRAM_U8 HDCT0       XRAM_AT_(0x8068);
XRAM_U8 HDCT1       XRAM_AT_(0x8069);
XRAM_U8 HDCT2       XRAM_AT_(0x806a);
XRAM_U8 HDCT3       XRAM_AT_(0x806b);
XRAM_U8 HDCT4       XRAM_AT_(0x806c);
XRAM_U8 HDCT5       XRAM_AT_(0x806d);
XRAM_U8 HDCT6       XRAM_AT_(0x806e);
XRAM_U8 HDCT7       XRAM_AT_(0x806f);

XRAM_U8 HDCT8       XRAM_AT_(0x8070);
XRAM_U8 HDCT9       XRAM_AT_(0x8071);
XRAM_U8 HDCT10      XRAM_AT_(0x8072);
XRAM_U8 HDCT11      XRAM_AT_(0x8073);
XRAM_U8 MOTPLC      XRAM_AT_(0x8074);

XRAM_U8 SMCON       XRAM_AT_(0x8078);
XRAM_U8 SMSTA       XRAM_AT_(0x8079);
XRAM_U8 SMDIV       XRAM_AT_(0x807a);
XRAM_U8 SMDATL      XRAM_AT_(0x807b);
XRAM_U8 SMDATH      XRAM_AT_(0x807c);
XRAM_U8 SMVTHL      XRAM_AT_(0x807d);
XRAM_U8 SMVTHH      XRAM_AT_(0x807e);

XRAM_U8 CKCON       XRAM_AT_(0x8080);
XRAM_U8 CKSEL       XRAM_AT_(0x8081);
XRAM_U8 CKDIV       XRAM_AT_(0x8082);
XRAM_U8 IHCFGL      XRAM_AT_(0x8083);
XRAM_U8 IHCFGH      XRAM_AT_(0x8084);
XRAM_U8 ILCFGL      XRAM_AT_(0x8085);
XRAM_U8 ILCFGH      XRAM_AT_(0x8086);
XRAM_U8 TFCFG       XRAM_AT_(0x8087);

XRAM_U8 ADCALL      XRAM_AT_(0x8088);
XRAM_U8 ADCALH      XRAM_AT_(0x8089);
XRAM_U8 ACPDLL      XRAM_AT_(0x808a);
XRAM_U8 ACPDLH      XRAM_AT_(0x808b);
XRAM_U8 ACPDHL      XRAM_AT_(0x808c);
XRAM_U8 ACPDHH      XRAM_AT_(0x808d);

XRAM_U8 TKMAXF      XRAM_AT_(0x8090);
XRAM_U8 TKMINF      XRAM_AT_(0x8091);
XRAM_U8 ATKNL       XRAM_AT_(0x8092);
XRAM_U8 ATKNH       XRAM_AT_(0x8093);

XRAM_U8 SPMAX       XRAM_AT_(0x8100);
XRAM_U8 I2CIOS      XRAM_AT_(0x8101);
XRAM_U8 TKPWC       XRAM_AT_(0x8103);

XRAM_U8 TLEN        XRAM_AT_(0x8106);
XRAM_U8 TLDAT       XRAM_AT_(0x8107);

XRAM_U8 TLCON       XRAM_AT_(0x8108);
XRAM_U8 TLFLG       XRAM_AT_(0x8109);
XRAM_U8 TLCKS       XRAM_AT_(0x810a);
XRAM_U8 TLCNTKL     XRAM_AT_(0x810b);
XRAM_U8 TLCNTKH     XRAM_AT_(0x810c);
XRAM_U8 TLCNTLL     XRAM_AT_(0x810d);
XRAM_U8 TLCNTLH     XRAM_AT_(0x810e);
XRAM_U8 TLCNTD      XRAM_AT_(0x810f);		  

XRAM_U8 TLCOMS      XRAM_AT_(0x8110);
XRAM_U8 LXCAD       XRAM_AT_(0x8117);
XRAM_U8 FTCTL       XRAM_AT_(0x811e);
XRAM_U8 TPCTL       XRAM_AT_(0x811f);

XRAM_U8 P00C        XRAM_AT_(0x8120);
XRAM_U8 P01C        XRAM_AT_(0x8121);
XRAM_U8 P02C        XRAM_AT_(0x8122);
XRAM_U8 P03C        XRAM_AT_(0x8123);
XRAM_U8 P04C        XRAM_AT_(0x8124);
XRAM_U8 P05C        XRAM_AT_(0x8125);
XRAM_U8 P06C        XRAM_AT_(0x8126);
XRAM_U8 P07C        XRAM_AT_(0x8127);

XRAM_U8 P10C        XRAM_AT_(0x8128);
XRAM_U8 P11C        XRAM_AT_(0x8129);
XRAM_U8 P12C        XRAM_AT_(0x812a);
XRAM_U8 P13C        XRAM_AT_(0x812b);
XRAM_U8 P14C        XRAM_AT_(0x812c);
XRAM_U8 P15C        XRAM_AT_(0x812d);
XRAM_U8 P16C        XRAM_AT_(0x812e);
XRAM_U8 P17C        XRAM_AT_(0x812f);

XRAM_U8 P20C        XRAM_AT_(0x8130);
XRAM_U8 P21C        XRAM_AT_(0x8131);
XRAM_U8 P22C        XRAM_AT_(0x8132);
XRAM_U8 P23C        XRAM_AT_(0x8133);
XRAM_U8 P24C        XRAM_AT_(0x8134);
XRAM_U8 P25C        XRAM_AT_(0x8135);
XRAM_U8 P26C        XRAM_AT_(0x8136);
XRAM_U8 P27C        XRAM_AT_(0x8137);

XRAM_U8 P30C        XRAM_AT_(0x8138);
XRAM_U8 P31C        XRAM_AT_(0x8139);
XRAM_U8 P32C        XRAM_AT_(0x813a);
XRAM_U8 P33C        XRAM_AT_(0x813b);
XRAM_U8 P34C        XRAM_AT_(0x813c);
XRAM_U8 P35C        XRAM_AT_(0x813d);
XRAM_U8 P36C        XRAM_AT_(0x813e);
XRAM_U8 P37C        XRAM_AT_(0x813f);

XRAM_U8 P40C        XRAM_AT_(0x8140);
XRAM_U8 P41C        XRAM_AT_(0x8141);
XRAM_U8 P42C        XRAM_AT_(0x8142);
XRAM_U8 P43C        XRAM_AT_(0x8143);
XRAM_U8 P44C        XRAM_AT_(0x8144);
XRAM_U8 P45C        XRAM_AT_(0x8145);
XRAM_U8 P46C        XRAM_AT_(0x8146);
XRAM_U8 P47C        XRAM_AT_(0x8147);

XRAM_U8 P50C        XRAM_AT_(0x8148);
XRAM_U8 P51C        XRAM_AT_(0x8149);
XRAM_U8 P52C        XRAM_AT_(0x814a);
XRAM_U8 P53C        XRAM_AT_(0x814b);
XRAM_U8 P54C        XRAM_AT_(0x814c);
XRAM_U8 P55C        XRAM_AT_(0x814d);
XRAM_U8 P56C        XRAM_AT_(0x814e);
XRAM_U8 P57C        XRAM_AT_(0x814f);

XRAM_U8 P60C        XRAM_AT_(0x8150);
XRAM_U8 P61C        XRAM_AT_(0x8151);
XRAM_U8 P62C        XRAM_AT_(0x8152);
XRAM_U8 P63C        XRAM_AT_(0x8153);
XRAM_U8 P64C        XRAM_AT_(0x8154);
XRAM_U8 P65C        XRAM_AT_(0x8155);
XRAM_U8 P66C        XRAM_AT_(0x8156);
XRAM_U8 P67C        XRAM_AT_(0x8157);

XRAM_U8 P70C        XRAM_AT_(0x8158);
XRAM_U8 P71C        XRAM_AT_(0x8159);
XRAM_U8 P72C        XRAM_AT_(0x815a);
XRAM_U8 P73C        XRAM_AT_(0x815b);
XRAM_U8 P74C        XRAM_AT_(0x815c);
XRAM_U8 P75C        XRAM_AT_(0x815d);


XRAM_U8 MECON       XRAM_AT_(0xfc00);
XRAM_U8 FSCMD       XRAM_AT_(0xfc01);
XRAM_U8 FSDAT       XRAM_AT_(0xfc02);
XRAM_U8 LOCK        XRAM_AT_(0xfc03);
XRAM_U8 PADRD       XRAM_AT_(0xfc04);
XRAM_U8 PTSL        XRAM_AT_(0xfc05);
XRAM_U8 PTSH        XRAM_AT_(0xfc06);
XRAM_U8 REPSET      XRAM_AT_(0xfc07);



#endif  