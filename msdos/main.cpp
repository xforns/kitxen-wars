#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <iostream.h>
#include "funcion.h"

#define VIDEO_INT           0x10      /* the BIOS video interrupt. */
#define VGA_256_COLOR_MODE  0x13      /* use to set 256-color mode. */
#define SET_MODE            0x00      /* BIOS func to set the video mode. */
#define TEXT_MODE           0x03      /* use to set 80x25 text mode. */

#define PALETTE_INDEX       0x03c8
#define PALETTE_DATA        0x03c9
#define INPUT_STATUS        0x03da
#define VRETRACE            0x08

#define xdisp 60
#define sul 60

#define SCREEN_WIDTH        320       /* width in pixels of mode 0x13 */
#define SCREEN_HEIGHT       200       /* height in pixels of mode 0x13 */
#define NUM_COLORS          256       /* number of colors in mode 0x13 */

typedef unsigned short word;
typedef unsigned long  dword;
typedef unsigned char  byte;


int initmouse(void);
void showpointer(void);
void hidepointer(void);
mouse readmouse(void);
void put_pixel (int x, int y, unsigned char Col, unsigned char *Where);
void negro();
void set_mode(byte mode);
void fskip(FILE *fp, int num_bytes);
void load_bmp(char *file,BITMAP *b);
void set_palette(byte *palette);
void wait(int ticks);
void cut(cacho *troz,int totx, int toty,int inix);
void cut2(BITMAP *bmp,cacho *troz,int totx, int toty,int inix);
void put(cacho *troz,int inix,int iniy,int itrx,int itry,int finy);
void put2(cacho *troz,int inix,int iniy);
int obtener();
int choque(int xmalo,int ymalo,int xmio,int ymio);
void rellena(int color,int x1,int y1,int x2,int y2);

void main(void)
{
	BITMAP bmp,bmp2,bmp3,bmp4;
	mouse mouze;
	int i;
	union REGS entrada,salida;
	char fichero[20],tecla;
	char *elmio;
	int cont,c1,c2,c3;
	int est_img=0;
	int sux[sul],suy[sul],su=0;
	cacho troz,troz2,troz3,troz4,troz5,troz6,troz7,troz8,troz9,troz10,troz11;
	int disx[xdisp],disy[xdisp],disp=0,contdisp=-1,nodizp[xdisp];
	int zino=0,loko=0,lives=5,maxpermitido=10;
	int muerto[sul];
	int salirmenu=0;
	long int poin=0;
	int ponermenu=1;
	int rex,bombest,bx,by,hazlo,iniciobomb,final;
	
	randomize();
 	set_mode(VGA_256_COLOR_MODE);
 	load_bmp("ok52.bmp",&bmp);
 	set_palette(bmp.palette);
 	cut2(&bmp,&troz,bmp.width,bmp.height,0);
 	put2(&troz,0,0);
 	wait(40);
 	free(troz.trozdat);
 	negro();
 	load_bmp("presents.bmp",&bmp);
 	cut2(&bmp,&troz,bmp.width,bmp.height,0);
 	put2(&troz,10,0);
 	wait(30);
 	free(troz.trozdat);
 	negro();
 	load_bmp("portada.bmp",&bmp);
 	cut2(&bmp,&troz,bmp.width,bmp.height,0);
 	put2(&troz,10,0);
 	wait(40);
 	free(bmp.data);
 	free(troz.trozdat);
 	load_bmp("coc1.bmp",&bmp);
 	load_bmp("coc2.bmp",&bmp2);
 	load_bmp("mio.bmp",&bmp3);
 	load_bmp("disp.bmp",&bmp4);
 	cut2(&bmp,&troz,bmp.width,bmp.height,0);
 	cut2(&bmp2,&troz2,bmp2.width,bmp2.height,0);
 	cut2(&bmp3,&troz3,bmp3.width,bmp3.height,0);
 	cut2(&bmp4,&troz4,bmp4.width,bmp4.height,0);
 	free(bmp.data);
 	free(bmp2.data);
 	free(bmp3.data);
 	free(bmp4.data);
 	load_bmp("malo.bmp",&bmp);
 	load_bmp("explos.bmp",&bmp2);
 	cut2(&bmp,&troz5,bmp.width,bmp.height,0);
 	cut2(&bmp2,&troz6,bmp2.width,bmp2.height,0);
 	free(bmp.data);
 	free(bmp2.data);
 	load_bmp("menu2.bmp",&bmp);
 	cut2(&bmp,&troz8,bmp.width,bmp.height,0);
 	load_bmp("gran.bmp",&bmp2);
 	cut2(&bmp2,&troz9,bmp2.width,bmp2.height,0);
 	load_bmp("energy.bmp",&bmp3);
 	cut2(&bmp3,&troz10,bmp3.width,bmp3.height,0);
 	free(bmp.data);
 	free(bmp2.data);
 	free(bmp3.data);
 	initmouse();
 	while(salirmenu!=1) {
 	if(ponermenu==1) {
		
		negro();
 	 	put2(&troz8,10,0);
 	 	ponermenu=0;
	}
	poin=0;
	showpointer();
	mouze=readmouse();
	salirmenu=0;salirgrande=1;
	if((mouze.mx>=240)&&(mouze.mx<=310)&& (mouze.my>=49)&&(mouze.my<=64)&&(mouze.key==1)) {
		
		salirgrande=0;salirmenu=0;hidepointer();
	}
	if((mouze.mx>=240)&&(mouze.mx<=310)&&(mouze.my>=126)&& (mouze.my<=141) && (mouze.key==1)) {
		
		hidepointer();
		salirmenu=1;
		final=2;
	}
	if ((mouze.mx>=240) && (mouze.mx<=310) && (mouze.my>=87)&& (mouze.my<=102) && (mouze.key==1)) {
		
		hidepointer();
	 	negro();
	 	load_bmp("help.bmp",&bmp);
	 	cut2(&bmp,&troz11,bmp.width,bmp.height,0);
	 	put2(&troz11,0,0);
	 	while(!kbhit()) {}
		free(bmp.data);
		free(troz11.trozdat);
		ponermenu=1;
	}
	if (lives==0) salirmenu=1;
	
	while(salirgrande!=1) {
		
		negro();
		xdon=(320/2)-40;ydon=160;
		cont=0;c1=200;
		for (su=0;su<=10;su++) {suy[su]=0;}
		for (disp=0;disp<=60;disp++) {nodizp[disp]=0;}
		gotoxy (15,10);
		printf("READY!!!");
		getch();
		salir=0;
		contdisp=-1;zino=0;loko=0;metele=0;
		est_img=0;
		rex=238;bombest=0;hazlo=0;iniciobomb=0;
		while(salir!=1) {
			
			gotoxy (1,1);printf("Lives: %d  Score: %d",lives,poin);
			if (lives==0) {salir=1;salirgrande=1;salirmenu=1;final=1;}
			if (poin==1000) maxpermitido=15;
			if (poin==2000) maxpermitido=20;
			if (poin==6000) maxpermitido=25;
			if (poin==8000) maxpermitido=30;
			if (poin==10000) maxpermitido=35;
			if (poin==20000) maxpermitido=40;
			put2(&troz10,200,180);
			if (rex>=318) bombest=1;
			else if (rex<318) bomba=0;
			
			if (zino==0) {cont++;c1--;}
			if ((cont==201) && (c1==-1))
			{
				if (est_img==0) est_img=1;
				else if (est_img==1) est_img=0;
				cont=0; c1=200;
			}
			if ((est_img==0) && (zino==0))
			{
				put(&troz,0,cont,320,0,200-cont);
				put(&troz2,0,0,320,c1,cont);
			}
			if ((est_img==1) && (zino==0))
			{
				put(&troz,0,0,320,c1,cont);
				put(&troz2,0,cont,320,0,200-cont);
			}
			rellena(40,238,181,rex,198);
			zino+=1;
			if (zino==5) zino=0;
			
			loko+=1;
			if (loko==3) loko=0;
			if (loko==0) {
				
				obtener();put2(&troz3,xdon,ydon);
				if ((bomba==1) && (bombest==1)) {
					if (iniciobomb==0) {bx=xdon;by=ydon;iniciobomb=1;}
					if ((bx==160) && (by==100)) hazlo=1;
					if (bx<=160) bx++;
					else if (bx>=160) bx--;
					if (by<=100) by++;
					else if (by>=100) by--;
					put2(&troz9,bx,by);
					if (hazlo==1) {
						for (su=0;su<=maxpermitido;su++) put2(&troz6,sux[su],suy[su]);
						wait(5);
						for (su=0;su<=maxpermitido;su++) {sux[su]=rand()%160;suy[su]=0;poin+=10;}
						bomba=0;bombest=0;rex=237;hazlo=0;iniciobomb=0;}
					}
					
					if (disparo==1) {
						contdisp+=1;
						if (contdisp==60) {
							for (disp=0;disp<60;disp++) {nodizp[disp]=0;}
							contdisp=0;
						}
						disx[contdisp]=xdon+17;disy[contdisp]=ydon;
						disp=contdisp;
						nodizp[disp]=0;
						disparo=0;
					}
					
					for (su=0;su<maxpermitido;su++)
					{
						if (suy[su]==170) {
							while (1) {
								sux[su]=rand()%160;suy[su]=0;
								if ((sux[su]<=sux[su-1]-40) || (sux[su]>=sux[su-1]+40)) break;
							}
						}
						else if (suy[su]<170) { suy[su]+=1;put2(&troz5,sux[su],suy[su]); }
						
						choque(sux[su],suy[su],xdon,ydon);
						if (metele==1) {
							put2(&troz6,sux[su],suy[su]);put2(&troz6,xdon,ydon);
							lives-=1;salir=1;metele=0;break;
						}
						for (disp=0;disp<=contdisp;disp++) {
							if (nodizp[disp]==0) {
								if ((disx[disp]>=sux[su]) && (disx[disp]<=sux[su]+40) &&
								(disy[disp]<=suy[su]+40) && (disy[disp]>=suy[su])) {
									put2(&troz6,sux[su],suy[su]);
									sux[su]=rand()%160;suy[su]=0;nodizp[disp]=1;poin+=10;
									if (bombest==0) rex+=1;
								}
							}
						}
					}
					for (disp=0;disp<=contdisp;disp++) {
						if (nodizp[disp]==0) {
							if (disy[disp]==0) nodizp[disp]=1;
							else if (disy[disp]>0) {
								disy[disp]-=1;put2(&troz4,disx[disp],disy[disp]);
							}
						}
					}
				}
				if (salir==1) break;
			}
			if (salirgrande==1) {ponermenu=1;break;}
		}
	}
	free(troz.trozdat);
	free(troz2.trozdat);
	free(troz3.trozdat);
	free(troz4.trozdat);
	free(troz5.trozdat);
	free(troz6.trozdat);
	free(troz7.trozdat);
	free(troz8.trozdat);
	free(troz9.trozdat);
	free(troz10.trozdat);
	free(troz11.trozdat);
	if(final==1){
		load_bmp("pilla1.bmp",&bmp);
		cut2(&bmp,&troz11,bmp.width,bmp.height,0);
		negro();
		put2(&troz11,0,0);
		wait(100);
		free(bmp.data);
	}
	else if (final==2) {
		load_bmp("end.bmp",&bmp);
		cut2(&bmp,&troz11,bmp.width,bmp.height,0);
		negro();
		put2(&troz11,0,0);
		wait(100);
		free(bmp.data);
	}
	free(troz11.trozdat);
	set_mode(TEXT_MODE);
	entrada.h.ah=0;
	int86(0x16,&entrada,&salida);
}

