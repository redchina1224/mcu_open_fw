unsigned int GetCheckSum(unsigned char* database, unsigned char length) 
{ 
	unsigned int checksum=0; 
	while(length--) 
	{ 
		checksum += *database++; 
	} 
	return checksum;
} 