unsigned int GetCheckSum16(unsigned char* database, unsigned char length) 
{ 
	unsigned int checksum=0; 
	while(length--) 
	{ 
		checksum += *database++; 
	} 
	return checksum;
} 

unsigned char GetCheckSum8(unsigned char* database, unsigned char length) 
{ 
	unsigned char checksum=0; 
	while(length--) 
	{ 
		checksum += *database++; 
	} 
	return checksum;
} 