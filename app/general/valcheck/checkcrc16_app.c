unsigned int GetCRC16(unsigned int reg_crc,unsigned char* database, unsigned char length) 
{ 
	int j; 
	//unsigned int reg_crc=0; 
	while(length--) 
	{ 
		reg_crc ^= *database++; 
		for (j=0;j<8;j++) 
		{ 
			if (reg_crc & 0x01) reg_crc=(reg_crc>>1) ^ 0Xa001; /* LSB(b0)=1 */ 
			else reg_crc=reg_crc >>1; 
		} 
	} 
	return reg_crc;
} 