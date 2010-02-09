#ifndef LG_RENESAS_H
#define LG_RENESAS_H
#include <libmmc/libmmc.h>
#include <stdio.h>

extern char main_pat[72];
extern char core_pat[72];
extern char verify_firmware;

typedef struct firminfo{
  long checksum;
  long reserved[3];
  char devname[16];
  char revlvl[16];
  char romrev[16];
  long firm_start;
  long firm_size;
}firminfo;

enum loc_e{
  LOC_CACHE_SIZE = 0x01, //Location points to the drives cache size
  LOC_CACHE      = 0x02, //location points to the cache
  LOC_MEMORY     = 0x05, //Location points to Absolute memory
  LOC_DEBUG      = 0x06, //Location points to debug info
};

char* lgren_sread(int device,char source,size_t pos,size_t size);
int lgren_diag(int device);
int lgren_read(int device,char source,mmcdata_s* buff,size_t pos,size_t size);
int lgren_write(int device,char source,mmcdata_s* buff,size_t pos,size_t size);
char get_firminfo_drive(int device,char* pattern,size_t patsize,firminfo* fi);
char get_firminfo_buff(char* buff,char* pattern,size_t bsize,size_t patsize,firminfo* fi);
unsigned short firm_chksum_calc(char* buff,size_t size,short key);
int firm_validate(char* buff, size_t size);
char firm_flasher(int device,char* buff,size_t fsize);
char firm_verify(int device,char* buff,size_t firm_start,size_t firm_size);
size_t firm_dumper(int device,char** inbuff,int loc,size_t pos,size_t dsize);
char firm_spliter(char* buff,size_t max_size,const char* outfile);
int firm_demangle(char* buff,char* buff2,size_t firm_start,size_t firm_stop,size_t firm_end);
int get_firmtype(char* buff);
int get_enckeypos(char* buff,int type);
int get_enctype(char* buff);
char firm_decrypter(char* buff,int type,size_t key,size_t size);
size_t find_pattern_drive(int device,int loc,char* pattern,size_t psize);
char firm_ripexe(char* filename);
#endif //LG_RENESAS_H
