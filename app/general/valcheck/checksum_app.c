unsigned int GetCheckSum16(unsigned char* database, unsigned char length,unsigned int checksum) 
{ 
//	unsigned int checksum=0; 
	while(length--) 
	{ 
		checksum += *database++; 
	} 
	return checksum;
} 

unsigned char GetCheckSum8(unsigned char* database, unsigned char length,unsigned char checksum) 
{ 
	//unsigned char checksum=0; 
	while(length--) 
	{ 
		checksum += *database++; 
	} 
	return checksum;
} 


void data_char_fix(unsigned char* database,unsigned char length,unsigned char dat)
{
	while(length--) 
	{ 
		(*database)=dat; 
		database++;
	} 
}