#ifndef _WAVHDR_H
#define _WAVHDR_H

#include<stdio.h>
#include<string.h>

typedef unsigned long       SR_DWORD;
typedef unsigned short      SR_WORD;

struct wavhdr{
    char            riff[4];                        // = "RIFF"
    SR_DWORD        size_8;                         // = FileSize - 8
    char            wave[4];                        // = "WAVE"
    char            fmt[4];                         // = "fmt "
    SR_DWORD        dwFmtSize;                      // = 下一个结构体的大小 : 16

    SR_WORD         format_tag;              		// = PCM : 1
    SR_WORD         channels;                		// = 通道数 : 1
    SR_DWORD        samples_per_sec;         		// = 采样率 : 8000 | 6000 | 11025 | 16000
    SR_DWORD        avg_bytes_per_sec;       		// = 每秒字节数 : dwSamplesPerSec * wBitsPerSample / 8
    SR_WORD         block_align;             		// = 每采样点字节数 : wBitsPerSample / 8
    SR_WORD         bits_per_sample;         		// = 量化比特数: 8 | 16

    char            data[4];                 		// = "data";
    SR_DWORD        data_size;               		// = 纯数据长度 : FileSize - 44 
} ;

int wav_hdr_reader(FILE *fp, struct wavhdr	*hdr)
{
	memset((void *)hdr, '0', sizeof(struct wavhdr));
	int len = fread((void *)hdr, 1, sizeof(struct wavhdr),fp);
#ifdef DEBUG
	printf("------------------msg------------------\n\n");
	printf(" read len     :\t%ld\n",	len);
	printf(" riff         :\t%4.4s\n",	hdr->riff);
	printf(" size         :\t%ld\n",	hdr->size_8+8);
	printf(" wave         :\t%4.4s\n",	hdr->wave);
	printf(" fmt          :\t%4.4s\n",	hdr->fmt);
	printf(" nextfmtsize  :\t%ld\n",	hdr->dwFmtSize);
	printf(" format_tag   :\t%d\n",		hdr->format_tag);
	printf(" chanels      :\t%d\n",		hdr->channels);
	printf(" samples/sec  :\t%ld\n",	hdr->samples_per_sec);
	printf(" byte/sec     :\t%ld\n",	hdr->avg_bytes_per_sec);
	printf(" block_align  :\t%d\n",		hdr->block_align);
	printf(" bit/sample   :\t%d\n",		hdr->bits_per_sample);
	printf(" data         :\t%4.4s\n",	hdr->data);
	printf(" datasize     :\t%ld\n",	hdr->data_size);
	printf("\n------------------end------------------\n");	
#endif	
	return len == 44? len:-1;
}

#endif
