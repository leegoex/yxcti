#ifndef kfpc_getmac_h__
#define kfpc_getmac_h__



#define MAXINTERFACES	32
#define MAXMACLEN		32
#define	MAXIPLEN		32
#define	MAXethNameLen	32

int GetLocalMac(char MacList[][MAXMACLEN],char IPlist[][MAXIPLEN],char ethName[][MAXethNameLen],unsigned int* MacCount,bool FilterIP0);
#endif // kfpc_getmac_h__
