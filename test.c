#include "WavHdr.h"

int main(int argc, char **argv)
{
	FILE *fp	= NULL;
	struct wavhdr	hdr;
	char filepath[64];
	char *gptr	= NULL;
	int i		= 0;
	memset((void *)&filepath, '\0', strlen(filepath));
	
	printf("input .wav file name\n");
	gptr = gets(filepath);
	
	if(strlen(gptr) >60)
	{
		fprintf(stderr, "file name length spillover,limit:60\n");
		exit(0);
	}
	
	for(i = 0; i < strlen(gptr); i++)
	{
		if(gptr[i] == '.')
		{
			if(gptr[i+1] == 'w' && gptr[i+2] == 'a' && gptr[i+3] == 'v')break;	
		}
		
		if( i+1 == strlen(gptr))
		{
			strcpy(filepath,gptr);
			strcat(filepath,".wav");
		}
	}
	
	
	fp = fopen(filepath,"rb");
	if(NULL == fp)
	{
		fprintf(stderr,"file open error.\n");
		exit(0);
	}
	
	
	printf("ret : %d\n",wav_hdr_reader(fp,&hdr));
	
	return 0;
	
}