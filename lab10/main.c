/* main.c --- 
 * 
 * Filename: main.c
 * Description: 
<<<<<<< HEAD
 * Author: 
 * Maintainer: 
 * Created: Thu Jan 10 11:23:43 2013
=======
 * Author: Won Yong Ha, Hanwen Zhang
 * Maintainer: 
 * Created: 7 April 2016
>>>>>>> 1e3d8c03814a9abd99fd80931a73d32545a3ec2d
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */
/* Code: */

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <f3d_rtc.h>
#include <ff.h>
#include <diskio.h>
#include <stdio.h>
<<<<<<< HEAD

void die (FRESULT rc) {
  printf("Failed with rc=%u.\n", rc);
  while (1);
}

FATFS Fatfs;		/* File system object */
FIL Fil;		/* File object */
BYTE Buff[128];		/* File read buffer */

//Formating
struct bmpfile_magic {
  unsigned char magic [2];
};
=======
#include <math.h>
#include <time.h>

/////////////////////////////////////////////////
// Structure 
struct bmpfile_magic {
  unsigned char magic [2];
};

>>>>>>> 1e3d8c03814a9abd99fd80931a73d32545a3ec2d
struct bmpfile_header {
  uint32_t filesz ;
  uint16_t creator1 ;
  uint16_t creator2 ;
  uint32_t bmp_offset ;
};
<<<<<<< HEAD
=======

>>>>>>> 1e3d8c03814a9abd99fd80931a73d32545a3ec2d
typedef struct {
  uint32_t header_sz ;
  int32_t width ;
  int32_t height ;
  uint16_t nplanes ;
  uint16_t bitspp ;
  uint32_t compress_type ;
  uint32_t bmp_bytesz ;
  int32_t hres;
  int32_t vres;
  uint32_t ncolors ;
  uint32_t nimpcolors ;
} BITMAPINFOHEADER ;
<<<<<<< HEAD
=======

>>>>>>> 1e3d8c03814a9abd99fd80931a73d32545a3ec2d
struct bmppixel { // little endian byte order
  uint8_t b;
  uint8_t g;
  uint8_t r;
};
<<<<<<< HEAD


int main(void) { 
  char footer[20];
  int count=0;
  int i;

  char[5

=======
/////////////////////////////////////////////////

//Global variable declaration
FATFS Fatfs;		/* File system object */
FIL Fil;		/* File object */
FIL Fil2;		/* File object */
BYTE Buff[999];		/* File read buffer */
BYTE Buff2[128];		/* File read buffer */
BITMAPINFOHEADER info;
uint16_t rgb[3];
uint16_t pixel_color[128];
double pitch, roll;
int fixing = 1;

//Printf Components
struct bmpfile_magic magic;
struct bmpfile_header header;
struct bmppixel pixel_data[128];


//Die
void die (FRESULT rc) {
  printf("Failed with rc=%u.\n", rc);
  while (1);
}

int check(nunchuk_t * n,int pic){
  //checks to see if the user has changed the image with the joystick/buttons
  if (n->jx < 5 || n->c == 1){
    pic = pic % 3 + 1;//graph 0,1,2
  }
  else if (n->jx > 250 || n->z ==1){
    pic = (pic + 1) % 3 + 1;//graph 1,2,0
  }
  return pic;
}

int main(void) {

  //Variable Declaration
>>>>>>> 1e3d8c03814a9abd99fd80931a73d32545a3ec2d
  FRESULT rc;			/* Result code */
  DIR dir;			/* Directory object */
  FILINFO fno;			/* File information object */
  UINT bw, br;
  unsigned int retval;
<<<<<<< HEAD
=======
  int file_index = 0;
  int file_names[3] = {1, 2, 3};
  char footer[20];
  int count=0;
  int row;
  int col;
  int i;
  float a[3],b[3];
  nunchuk_t n; 
  int graph = 1, direction, lastDirection;
  char name[10] = "1.bmp";

  //Initialization
  f3d_lcd_init();
  f3d_delay_init();
  f3d_rtc_init();
  f3d_i2c1_init();
  f3d_mag_init();
  f3d_accel_init();
  f3d_nunchuk_init();
  f3d_uart_init();
  f3d_gyro_init();
>>>>>>> 1e3d8c03814a9abd99fd80931a73d32545a3ec2d

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

<<<<<<< HEAD
  f3d_uart_init();
  f3d_lcd_init();
  f3d_delay_init();
  f3d_rtc_init();

  f_mount(0, &Fatfs);



	  
  /*while (1) {
    


    }*/
=======


  f_mount(0, &Fatfs);		/* Register volume work area (never fails) */

  while(1) {
    f3d_nunchuk_read(&n);
    /*
    file_index = nunchuk_listener(file_index, nunchuk, &orientation);

    char name[10];
    sprintf(name, "%d.bmp", file_names[file_index]);
    printf("\nOpen an existing file %s.\n", name);
    */
    //f3d_lcd_fillScreen(BLACK);
    graph = check(&n,graph);
    printf("AAA");

    sprintf(name, "%d.bmp", graph);

    f3d_accel_read(a);
    pitch = atan(a[0]/sqrt(pow(a[1],2)+pow(a[2],2)));
    roll = atan(a[1]/sqrt(pow(a[0],2)+pow(a[2],2)));  

    rc = f_open(&Fil, name, FA_READ);
    if (rc) die(rc);

    //Testing
    printf("\nType the file content.\n");
    printf("File name = %s\n", name);
    /*
    if (graph == 1){
      f3d_lcd_fillScreen(BLACK);
      // graph = check(&n,graph);
    }
    else if (graph == 2){
      f3d_lcd_fillScreen(RED);
      //graph = check(&n,graph);
    }
    else {
      f3d_lcd_fillScreen(WHITE);
      //graph = check(&n,graph);
    }
    */

    int pre_fixing = fixing;

    if (pitch < -0.3)
      fixing = 1;
    if (pitch > 0.3)
      fixing = 2;
    if (roll > 0.3)
      fixing = 3;
    if (roll < -0.3)
      fixing = 4;

    if (pre_fixing != fixing)
      f3d_lcd_fillScreen(WHITE);

    while(1) {

      //Storing Buff
      for(i = 0; i < br; i++)
        putchar(Buff[i]);

      //Initialization.
      rc = f_read(&Fil, &magic, sizeof magic, &br);
      if(rc || !br) break;
      rc = f_read(&Fil, &header, sizeof header, &br);
      if(rc || !br) break;
      rc = f_read(&Fil, &info, sizeof info, &br);
      if(rc || !br) break;

      if(fixing == 1) {
	//f3d_lcd_fillScreen(WHITE);
        for (row = 160; row >= 0; row--){
          rc = f_read(&Fil, &pixel_data, sizeof pixel_data, &br);
          if(rc || !br) break;
          for (i = 0; i < 128; i++) {
            rgb[0] = ((uint16_t) (pixel_data[i].b)) >> 3;
            rgb[1] = ((uint16_t) (pixel_data[i].g)) >> 2;
            rgb[2] = ((uint16_t) (pixel_data[i].r)) >> 3;
            pixel_color[i] = (rgb[0] << 11) | (rgb[1] << 5) | rgb[2];
          }

          f3d_lcd_setAddrWindow(0, row, 128, row, MADCTLGRAPHICS);
          f3d_lcd_pushColor(pixel_color, 128);
        }
      } 
      else if (fixing == 2) {
	//f3d_lcd_fillScreen(WHITE);
        for (row = 0; row < 160; row++){
          rc = f_read(&Fil, &pixel_data, sizeof pixel_data, &br);
          if(rc || !br) break;
          for (i = 0; i < 128; i++) {
            rgb[0] = ((uint16_t) (pixel_data[i].b)) >> 3;
            rgb[1] = ((uint16_t) (pixel_data[i].g)) >> 2;
            rgb[2] = ((uint16_t) (pixel_data[i].r)) >> 3;
            pixel_color[i] = (rgb[0] << 11) | (rgb[1] << 5) | rgb[2];
          }

          f3d_lcd_setAddrWindow(0, row, 128, row, MADCTLGRAPHICS);
          f3d_lcd_pushColor(pixel_color, 128);
        }
      }
      else if (fixing == 3) {
	//f3d_lcd_fillScreen(WHITE);
        for (row = 0; row < 160; row++){
          rc = f_read(&Fil, &pixel_data, sizeof pixel_data, &br);
          if(rc || !br) break;
          for (i = 0; i < 128; i++) {
            rgb[0] = ((uint16_t) (pixel_data[i].b)) >> 3;
            rgb[1] = ((uint16_t) (pixel_data[i].g)) >> 2;
            rgb[2] = ((uint16_t) (pixel_data[i].r)) >> 3;
            pixel_color[i] = (rgb[0] << 11) | (rgb[1] << 5) | rgb[2];
          }

          f3d_lcd_setAddrWindow(row, 1, row, 128, MADCTLGRAPHICS);
          f3d_lcd_pushColor(pixel_color, 128);
        }
      }
      else {//4
	//f3d_lcd_fillScreen(WHITE);
        for (row = 160; row >= 0; row--){
          rc = f_read(&Fil, &pixel_data, sizeof pixel_data, &br);
          if(rc || !br) break;
          for (i = 0; i < 128; i++) {
            rgb[0] = ((uint16_t) (pixel_data[i].b)) >> 3;
            rgb[1] = ((uint16_t) (pixel_data[i].g)) >> 2;
            rgb[2] = ((uint16_t) (pixel_data[i].r)) >> 3;
            pixel_color[i] = (rgb[0] << 11) | (rgb[1] << 5) | rgb[2];
          }

          f3d_lcd_setAddrWindow(row, 1, row, 128, MADCTLGRAPHICS);
          f3d_lcd_pushColor(pixel_color, 128);
        }
      }
    }
  }
>>>>>>> 1e3d8c03814a9abd99fd80931a73d32545a3ec2d
}


#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
