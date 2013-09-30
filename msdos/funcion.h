#define VIDEO_INT           0x10      /* the BIOS video interrupt. */
#define VGA_256_COLOR_MODE  0x13      /* use to set 256-color mode. */
#define SET_MODE            0x00      /* BIOS func to set the video mode. */
#define TEXT_MODE           0x03      /* use to set 80x25 text mode. */

#define PALETTE_INDEX       0x03c8
#define PALETTE_DATA        0x03c9
#define INPUT_STATUS        0x03da
#define VRETRACE            0x08

#define SCREEN_WIDTH        320       /* width in pixels of mode 0x13 */
#define SCREEN_HEIGHT       200       /* height in pixels of mode 0x13 */
#define NUM_COLORS          256       /* number of colors in mode 0x13 */


typedef unsigned short word;
typedef unsigned long  dword;
typedef unsigned char  byte;


int xdon,ydon,salir=0,disparo=0,salirgrande=0,bomba=0;
int metele=0;
union REGS entrada, salida;
int puntest=0;
char tecla;

byte *VGA=(byte *)0xA0000000L;
word Vaddr1, Vaddr2;
word *my_clock=(word *)0x0000046C;

typedef struct tagBITMAP
{
	word width;
	word height;
	byte palette[256*3];
	byte *data;
} BITMAP;

typedef struct tagcacho
{
	word x;
	word y;
	byte *trozdat;
} cacho;

typedef struct {int key,mx,my; } mouse;


void fskip(FILE *fp, int num_bytes)
{
	int i;
	for (i=0; i<num_bytes; i++)
		fgetc(fp);
}

void load_bmp(char *file,BITMAP *b)
{
	FILE *fp;
	long index;
	word num_colors;
	int x,c1;
	
	if ((fp = fopen(file,"rb")) == NULL)
	{
    	printf("Error opening file %s.\n",file);
    	getch();
    	exit(1);
	}
	
	if (fgetc(fp)!='B' || fgetc(fp)!='M')
  	{
		fclose(fp);
		printf("%s is not a bitmap file.\n",file);
		exit(1);
	}
	
	fskip(fp,16);
	fread(&b->width, sizeof(word), 1, fp);
	fskip(fp,2);
	fread(&b->height,sizeof(word), 1, fp);
	fskip(fp,22);
	fread(&num_colors,sizeof(word), 1, fp);
	fskip(fp,6);
	
	if (num_colors==0) num_colors=256;
	
	if ((b->data = (byte *) malloc((word)(b->width*b->height))) == NULL)
	{
		fclose(fp);
		printf("Error allocating memory for file %s.\n",file);
		exit(1);
	}
	
	for(index=0;index<num_colors;index++)
	{
		b->palette[(int)(index*3+2)] = fgetc(fp) >> 2;
		b->palette[(int)(index*3+1)] = fgetc(fp) >> 2;
		b->palette[(int)(index*3+0)] = fgetc(fp) >> 2;
		x=fgetc(fp);
	}
	
	for(index=(b->height-1)*b->width;index>=0;index-=b->width)
		for(x=0;x<b->width;x++)
			b->data[(word)(index+x)]=(byte)fgetc(fp);
	fclose(fp);
}

void put_pixel (int x, int y, unsigned char Col, unsigned char *Where)
{
	memset(Where+(x+(y*320)),Col,1);
}

void negro(void)
{
	int x,y;
	
	for (y=0;y<=200;y++) {
		for (x=0;x<=320;x++) {
			put_pixel(x,y,0,VGA);
		}
	}
}

void set_mode(byte mode)
{
	union REGS regs;
	
	regs.h.ah = SET_MODE;
	regs.h.al = mode;
	int86(VIDEO_INT, &regs, &regs);
}

void set_palette(byte *palette)
{
	int i;
	
	outp(PALETTE_INDEX,0);
	for(i=0;i<256*3;i++)
		outp(PALETTE_DATA,palette[i]);
}

void wait(int ticks){
	word start;
	
	start=*my_clock;
	while (*my_clock-start<ticks) {
		*my_clock=*my_clock;
	}
}

void cut2(BITMAP *bmp,cacho *troz,int totx, int toty,int inix)
{
	long index;
	
	troz->x=totx;troz->y=toty;
	if ((troz->trozdat = (byte *) malloc((word)(troz->x*troz->y))) == NULL) {
		printf("Error allocating memory\n");
		exit(1);
	}
	for(index=(troz->y-1)*troz->x;index>=0;index-=troz->x) {
		for(inix=0;inix<troz->x;inix++) {
			troz->trozdat[(word)(index+inix)]=(byte)bmp->data[index+inix];
		}
	}
}

void put(cacho *troz,int inix,int iniy,int itrx,int itry,int finy)
{
	int j;
	word screen_offset = (iniy*320)+inix;
	word offset = (itrx*itry);
	
	for(j=inix;j<finy;j++) {
		memcpy(&VGA[screen_offset],&troz->trozdat[offset],troz->x);
		offset+=troz->x;
		screen_offset+=SCREEN_WIDTH;
	}
}

void put2(cacho *troz,int inix,int iniy)
{
	word offset=0;
	byte data;
	int j,i;
	for (j=0;j<troz->y;j++) {
		for (i=0;i<troz->x;i++,offset++) {
			data=troz->trozdat[offset];
			if (data) put_pixel(inix+i,iniy+j,data,VGA);
		}
	}
	
}

int obtener()
{
	if (kbhit()) {
		tecla=getch();
		switch(tecla) {
			case 75:{if (xdon==0) xdon=xdon;else xdon-=10;break;}
			case 77:{if (xdon==280) xdon=xdon;else xdon+=10;break;}
			case 80:{if (ydon==160) ydon=ydon;else ydon+=10;break;}
			case 72:{if (ydon==0) ydon=ydon;else ydon-=10;break;}
			case 13:disparo=1;break;
			case 98:bomba=1;break;
			case 112: {
				while(!kbhit()) {gotoxy (10,10);printf("PAUSE");}
				entrada.h.ah=0;
				int86(0x16,&entrada,&salida);
				break;
			}
			case 27:{salir=1;salirgrande=1;break;}
		}
	}
	
	return xdon,ydon,salir,salirgrande,bomba;
}

int choque(int xmalo,int ymalo,int xmio,int ymio)
{
	
	if((xmalo+20>=xmio) && (xmalo+20<=xmio+20) && (ymalo+20>=ymio) && (ymalo<=ymio+20)) metele=1;
	if((xmalo<=xmio+20) && (xmalo>=xmio) && (ymalo+20>=ymio) && (ymalo<=ymio+20)) metele=1;
	else metele=0;
	return metele;
}

int initmouse(void)
 {
  int status;
  asm MOV AX, 0x0000
  asm INT 0x33
  asm MOV status, AX
  return(status);
 }

void showpointer(void)
 {
  asm MOV AX, 0x0001
  asm  INT 0x33
 }

void hidepointer(void)
 {
  asm MOV AX, 0x0002
  asm INT 0x33
 }

mouse readmouse(void)
 {
  int k,x,y;
  mouse m;
   asm MOV AX, 0x0003
   asm INT 0x33
   asm MOV k, BX
   asm MOV x, CX
   asm MOV y, DX
  m.key = k;
  m.mx = x;
  m.my = y;
  
  return m;
 }

void rellena(int color,int x1,int y1,int x2,int y2)
{
	int i,j;
	
	for (i=x1;i<=x2;i++) {
		for (j=y1;j<=y2;j++) {
			put_pixel(i,j,color,VGA);
		}
	}
}






