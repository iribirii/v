#include "v.h"
#include "x.h"

extern Display * dis;
extern int       screen;
extern Window    win;
extern GC        gc_white, gc_black, gc_red, gc_dot[2], gcc[NCOLORS];
extern Pixmap    px;
extern Drawable  canv;
extern XFontStruct * fontInfo;

extern int W,H;

void close_x(void) {
  XFreeGC(dis, gc_red);
  XFreeGC(dis, gc_black);
  XFreeGC(dis, gc_white);
  XFreeGC(dis, gc_dot[0]);
  XFreeGC(dis, gc_dot[1]);
  for(int i=0; i<NCOLORS; i++){
    XFreeGC(dis, gcc[i]);
  }
  XDestroyWindow (dis, win);
  XFreePixmap    (dis, px);
  if(fontInfo){
    XFreeFont    (dis, fontInfo);
  }
  XCloseDisplay  (dis);
};

static void setcolors(){
  XColor
  col[NCOLORS]={
    [   0] .red = 0x9999, [   0] .green = 0x9999, [   0] .blue = 0x9999,
    [   1] .red = 0xBFFF, [   1] .green = 0xBFFF, [   1] .blue = 0xBFFF, /* H  */
    [   2] .red = 0xD9D9, [   2] .green = 0xFFFF, [   2] .blue = 0xFFFF, /* He */
  [3] .red = 0xCCCC, [ 3] .green = 0x8080, [ 3] .blue = 0xFFFF, /* Li */
  [4] .red = 0xC2C2, [ 4] .green = 0xFFFF, [ 4] .blue = 0x0000, /* Be */
  [5] .red = 0xFFFF, [ 5] .green = 0xB5B5, [ 5] .blue = 0xB5B5, /* B */
    [   6] .red = 0x5FFF, [   6] .green = 0x5FFF, [   6] .blue = 0x5FFF, /* C  */
    [   7] .red = 0x1FFF, [   7] .green = 0x1FFF, [   7] .blue = 0xBFFF, /* N  */
    [   8] .red = 0xBFFF, [   8] .green = 0x1FFF, [   8] .blue = 0x1FFF, /* O  */
    [   9] .red = 0xF500, [   9] .green = 0xFFFF, [   9] .blue = 0x8500, /* F  */
    [  10] .red = 0xAAAA, [  10] .green = 0xFFFF, [  10] .blue = 0xFFFF, /* Ne */
  [11] .red = 0xABAB, [ 11] .green = 0x5C5C, [ 11] .blue = 0xF2F2, /* Na */
  [12] .red = 0x8A8A, [ 12] .green = 0xFFFF, [ 12] .blue = 0x0000, /* Mg */
  [13] .red = 0xBFBF, [ 13] .green = 0xA6A6, [ 13] .blue = 0xA6A6, /* Al */
    [  14] .red = 0x5FFF, [  14] .green = 0x5FFF, [  14] .blue = 0x5FFF, /* Si */
    [  15] .red = 0xFFFF, [  15] .green = 0xCCCC, [  15] .blue = 0x9999, /* P  */
    [  16] .red = 0xFFFF, [  16] .green = 0xEEEE, [  16] .blue = 0x1111, /* S  */
    [  17] .red = 0xCCCC, [  17] .green = 0xFFFF, [  17] .blue = 0x9999, /* Cl */
    [  18] .red = 0xAAAA, [  18] .green = 0xFFFF, [  18] .blue = 0xFFFF, /* Ar */
  [19] .red = 0x8F8F, [ 19] .green = 0x4040, [ 19] .blue = 0xD4D4, /* K */
  [20] .red = 0x3D3D, [ 20] .green = 0xFFFF, [ 20] .blue = 0x0000, /* Ca */
  [21] .red = 0xE6E6, [ 21] .green = 0xE6E6, [ 21] .blue = 0xE6E6, /* Sc */
  [22] .red = 0xBFBF, [ 22] .green = 0xC2C2, [ 22] .blue = 0xC7C7, /* Ti */
  [23] .red = 0xA6A6, [ 23] .green = 0xA6A6, [ 23] .blue = 0xABAB, /* V */
  [24] .red = 0x8A8A, [ 24] .green = 0x9999, [ 24] .blue = 0xC7C7, /* Cr */
  [25] .red = 0x9C9C, [ 25] .green = 0x7A7A, [ 25] .blue = 0xC7C7, /* Mn */
    [  26] .red = 0xDDDD, [  26] .green = 0x6666, [  26] .blue = 0x3333, /* Fe */
    [  27] .red = 0xEEEE, [  27] .green = 0x8888, [  27] .blue = 0x9999, /* Co */
    [  28] .red = 0x5050, [  28] .green = 0xD0D0, [  28] .blue = 0x5050, /* Ni */
    [  29] .red = 0xBBBB, [  29] .green = 0x7777, [  29] .blue = 0x3333, /* Cu */
  [30] .red = 0x7D7D, [ 30] .green = 0x8080, [ 30] .blue = 0xB0B0, /* Zn */
  [31] .red = 0xC2C2, [ 31] .green = 0x8F8F, [ 31] .blue = 0x8F8F, /* Ga */
  [32] .red = 0x6666, [ 32] .green = 0x8F8F, [ 32] .blue = 0x8F8F, /* Ge */
  [33] .red = 0xBDBD, [ 33] .green = 0x8080, [ 33] .blue = 0xE3E3, /* As */
    [  34] .red = 0xFFFF, [  34] .green = 0xAAAA, [  34] .blue = 0x1111, /* Se */
    [  35] .red = 0xAAAA, [  35] .green = 0x4444, [  35] .blue = 0x0000, /* Br */
    [  36] .red = 0xAAAA, [  36] .green = 0xFFFF, [  36] .blue = 0xFFFF, /* Kr */
  [37] .red = 0x7070, [ 37] .green = 0x2E2E, [ 37] .blue = 0xB0B0, /* Rb */
  [38] .red = 0x0000, [ 38] .green = 0xFFFF, [ 38] .blue = 0x0000, /* Sr */
  [39] .red = 0x9494, [ 39] .green = 0xFFFF, [ 39] .blue = 0xFFFF, /* Y */
  [40] .red = 0x9494, [ 40] .green = 0xE0E0, [ 40] .blue = 0xE0E0, /* Zr */
  [41] .red = 0x7373, [ 41] .green = 0xC2C2, [ 41] .blue = 0xC9C9, /* Nb */
  [42] .red = 0x5454, [ 42] .green = 0xB5B5, [ 42] .blue = 0xB5B5, /* Mo */
  [43] .red = 0x3B3B, [ 43] .green = 0x9E9E, [ 43] .blue = 0x9E9E, /* Tc */
  [44] .red = 0x2424, [ 44] .green = 0x8F8F, [ 44] .blue = 0x8F8F, /* Ru */
  [45] .red = 0x0A0A, [ 45] .green = 0x7D7D, [ 45] .blue = 0x8C8C, /* Rh */
  [46] .red = 0x0000, [ 46] .green = 0x6969, [ 46] .blue = 0x8585, /* Pd */
  [47] .red = 0xC0C0, [ 47] .green = 0xC0C0, [ 47] .blue = 0xC0C0, /* Ag */
  [48] .red = 0xFFFF, [ 48] .green = 0xD9D9, [ 48] .blue = 0x8F8F, /* Cd */
  [49] .red = 0xA6A6, [ 49] .green = 0x7575, [ 49] .blue = 0x7373, /* In */
  [50] .red = 0x6666, [ 50] .green = 0x8080, [ 50] .blue = 0x8080, /* Sn */
  [51] .red = 0x9E9E, [ 51] .green = 0x6363, [ 51] .blue = 0xB5B5, /* Sb */
  [52] .red = 0xD4D4, [ 52] .green = 0x7A7A, [ 52] .blue = 0x0000, /* Te */
  [53] .red = 0x9494, [ 53] .green = 0x0000, [ 53] .blue = 0x9494, /* I */
  [54] .red = 0x4242, [ 54] .green = 0x9E9E, [ 54] .blue = 0xB0B0, /* Xe */
  [55] .red = 0x5757, [ 55] .green = 0x1717, [ 55] .blue = 0x8F8F, /* Cs */
  [56] .red = 0x0000, [ 56] .green = 0xC9C9, [ 56] .blue = 0x0000, /* Ba */
  [57] .red = 0x7070, [ 57] .green = 0xD4D4, [ 57] .blue = 0xFFFF, /* La */
  [58] .red = 0xFFFF, [ 58] .green = 0xFFFF, [ 58] .blue = 0xC7C7, /* Ce */
  [59] .red = 0xD9D9, [ 59] .green = 0xFFFF, [ 59] .blue = 0xC7C7, /* Pr */
  [60] .red = 0xC7C7, [ 60] .green = 0xFFFF, [ 60] .blue = 0xC7C7, /* Nd */
  [61] .red = 0xA3A3, [ 61] .green = 0xFFFF, [ 61] .blue = 0xC7C7, /* Pm */
  [62] .red = 0x8F8F, [ 62] .green = 0xFFFF, [ 62] .blue = 0xC7C7, /* Sm */
  [63] .red = 0x6161, [ 63] .green = 0xFFFF, [ 63] .blue = 0xC7C7, /* Eu */
  [64] .red = 0x4545, [ 64] .green = 0xFFFF, [ 64] .blue = 0xC7C7, /* Gd */
  [65] .red = 0x3030, [ 65] .green = 0xFFFF, [ 65] .blue = 0xC7C7, /* Tb */
  [66] .red = 0x1F1F, [ 66] .green = 0xFFFF, [ 66] .blue = 0xC7C7, /* Dy */
  [67] .red = 0x0000, [ 67] .green = 0xFFFF, [ 67] .blue = 0x9C9C, /* Ho */
  [68] .red = 0x0000, [ 68] .green = 0xE6E6, [ 68] .blue = 0x7575, /* Er */
  [69] .red = 0x0000, [ 69] .green = 0xD4D4, [ 69] .blue = 0x5252, /* Tm */
  [70] .red = 0x0000, [ 70] .green = 0xBFBF, [ 70] .blue = 0x3838, /* Yb */
  [71] .red = 0x0000, [ 71] .green = 0xABAB, [ 71] .blue = 0x2424, /* Lu */
  [72] .red = 0x4D4D, [ 72] .green = 0xC2C2, [ 72] .blue = 0xFFFF, /* Hf */
  [73] .red = 0x4D4D, [ 73] .green = 0xA6A6, [ 73] .blue = 0xFFFF, /* Ta */
  [74] .red = 0x2121, [ 74] .green = 0x9494, [ 74] .blue = 0xD6D6, /* W */
  [75] .red = 0x2626, [ 75] .green = 0x7D7D, [ 75] .blue = 0xABAB, /* Re */
  [76] .red = 0x2626, [ 76] .green = 0x6666, [ 76] .blue = 0x9696, /* Os */
  [77] .red = 0x1717, [ 77] .green = 0x5454, [ 77] .blue = 0x8787, /* Ir */
  [78] .red = 0xD0D0, [ 78] .green = 0xD0D0, [ 78] .blue = 0xE0E0, /* Pt */
  [79] .red = 0xFFFF, [ 79] .green = 0xD1D1, [ 79] .blue = 0x2323, /* Au */
  [80] .red = 0xB8B8, [ 80] .green = 0xB8B8, [ 80] .blue = 0xD0D0, /* Hg */
  [81] .red = 0xA6A6, [ 81] .green = 0x5454, [ 81] .blue = 0x4D4D, /* Tl */
  [82] .red = 0x5757, [ 82] .green = 0x5959, [ 82] .blue = 0x6161, /* Pb */
  [83] .red = 0x9E9E, [ 83] .green = 0x4F4F, [ 83] .blue = 0xB5B5, /* Bi */
  [84] .red = 0xABAB, [ 84] .green = 0x5C5C, [ 84] .blue = 0x0000, /* Po */
  [85] .red = 0x7575, [ 85] .green = 0x4F4F, [ 85] .blue = 0x4545, /* At */
  [86] .red = 0x4242, [ 86] .green = 0x8282, [ 86] .blue = 0x9696, /* Rn */
  [87] .red = 0x4242, [ 87] .green = 0x0000, [ 87] .blue = 0x6666, /* Fr */
  [88] .red = 0x0000, [ 88] .green = 0x7D7D, [ 88] .blue = 0x0000, /* Ra */
  [89] .red = 0x7070, [ 89] .green = 0xABAB, [ 89] .blue = 0xFAFA, /* Ac */
  [90] .red = 0x0000, [ 90] .green = 0xBABA, [ 90] .blue = 0xFFFF, /* Th */
  [91] .red = 0x0000, [ 91] .green = 0xA1A1, [ 91] .blue = 0xFFFF, /* Pa */
  [92] .red = 0x0000, [ 92] .green = 0x8F8F, [ 92] .blue = 0xFFFF, /* U */
  [93] .red = 0x0000, [ 93] .green = 0x8080, [ 93] .blue = 0xFFFF, /* Np */
  [94] .red = 0x0000, [ 94] .green = 0x6B6B, [ 94] .blue = 0xFFFF, /* Pu */
  [95] .red = 0x5454, [ 95] .green = 0x5C5C, [ 95] .blue = 0xF2F2, /* Am */
  [96] .red = 0x7878, [ 96] .green = 0x5C5C, [ 96] .blue = 0xE3E3, /* Cm */
  [97] .red = 0x8A8A, [ 97] .green = 0x4F4F, [ 97] .blue = 0xE3E3, /* Bk */
  [98] .red = 0xA1A1, [ 98] .green = 0x3636, [ 98] .blue = 0xD4D4, /* Cf */
  [99] .red = 0xB3B3, [ 99] .green = 0x1F1F, [ 99] .blue = 0xD4D4, /* Es */
  [100] .red = 0xB3B3, [100] .green = 0x1F1F, [100] .blue = 0xBABA, /* Fm */
  [101] .red = 0xB3B3, [101] .green = 0x0D0D, [101] .blue = 0xA6A6, /* Md */
  [102] .red = 0xBDBD, [102] .green = 0x0D0D, [102] .blue = 0x8787, /* No */
  [103] .red = 0xC7C7, [103] .green = 0x0000, [103] .blue = 0x6666, /* Lr */
  [104] .red = 0xCCCC, [104] .green = 0x0000, [104] .blue = 0x5959, /* Rf */
  [105] .red = 0xD1D1, [105] .green = 0x0000, [105] .blue = 0x4F4F, /* Db */
  [106] .red = 0xD9D9, [106] .green = 0x0000, [106] .blue = 0x4545, /* Sg */
  [107] .red = 0xE0E0, [107] .green = 0x0000, [107] .blue = 0x3838, /* Bh */
  [108] .red = 0xE6E6, [108] .green = 0x0000, [108] .blue = 0x2E2E, /* Hs */
  // [109] .red = 0xEBEB, [109] .green = 0x0000, [109] .blue = 0x2626, /* Mt */ 
  };

  // for(int i=3;  i<5;  i++){ col[i] = col[0]; }
  // for(int i=11; i<14; i++){ col[i] = col[0]; }
  // for(int i=19; i<26; i++){ col[i] = col[0]; }
  // for(int i=30; i<34; i++){ col[i] = col[0]; }
  // for(int i=37; i<46; i++){ col[i] = col[0]; }
  // for(int i=48; i<53; i++){ col[i] = col[0]; }
  // for(int i=55; i<78; i++){ col[i] = col[0]; }

  Colormap colmap = DefaultColormap(dis, DefaultScreen(dis));
  for(int i=0; i<NCOLORS; i++){
    gcc[i] = XCreateGC (dis, win, 0, 0);
    XAllocColor(dis, colmap, col+i);
    XSetForeground (dis, gcc[i], col[i].pixel);
  }
  return;
}

void init_x(const char * const capt){

  dis    = XOpenDisplay((char *)0);
  screen = DefaultScreen(dis);
  W = DisplayWidth  (dis, screen);
  H = DisplayHeight (dis, screen);

  unsigned long bp = BlackPixel (dis, screen);
  unsigned long wp = WhitePixel (dis, screen);
  unsigned long red_pixel = 0xff0000;

  win = XCreateSimpleWindow(dis, DefaultRootWindow(dis),
      0, 0, W, H, 0, bp, wp);

  XSetStandardProperties(dis, win, capt, "icon", None, NULL, 0, NULL);
  XSelectInput   (dis, win, ExposureMask|KeyPressMask|StructureNotifyMask   |ButtonPressMask|ButtonReleaseMask|PointerMotionMask	  );

  gc_white = XCreateGC (dis, win, 0, 0);
  XSetBackground (dis, gc_white, wp);
  XSetForeground (dis, gc_white, wp);

  gc_black = XCreateGC (dis, win, 0, 0);
  XSetBackground (dis, gc_black, wp);
  XSetForeground (dis, gc_black, bp);
  XSetLineAttributes(dis, gc_black, 2, 0, 0, 0);

  gc_red = XCreateGC (dis, win, 0, 0);
  XSetBackground (dis, gc_red, wp);
  XSetForeground (dis, gc_red, red_pixel);

  gc_dot[0] = XCreateGC (dis, win, 0, 0);
  XSetBackground (dis, gc_black, wp);
  XSetForeground (dis, gc_black, bp);
  XSetLineAttributes(dis, gc_dot[0], 2, 1, 0, 0);

  gc_dot[1] = XCreateGC (dis, win, 0, 0);
  XSetBackground (dis, gc_black, wp);
  XSetForeground (dis, gc_black, bp);
  XSetLineAttributes(dis, gc_dot[1], 0, 1, 0, 0);

  setcolors();

  XClearWindow   (dis, win);
  XMapRaised     (dis, win);

  px = XCreatePixmap(dis, win, W, H, DefaultDepth(dis, 0));
  return;
};

static void autosize_font(char * fontname){
  const int screen_sizes[] = {1200, 1080, 960, 900, 840, 768};
  const int font_sizes[]   = {  24,   20,  18,  16,  15,  14}; //  font_size='ceil'(screen_size) / 60
  int font_size = 13;
  int screen_size = MIN(W, H);
  for(int i=0; i<sizeof(screen_sizes)/sizeof(screen_sizes[0]); i++){
    if(screen_size>screen_sizes[i]){
      font_size = font_sizes[i];
      break;
    }
  }
  sprintf(fontname, "*x%d", font_size);
  return;
}

void init_font(char * fontname){
  if(!fontname[0]){
    autosize_font(fontname);
  }
  fontInfo = XLoadQueryFont(dis, fontname);
  if(fontInfo){
    XSetFont (dis, gc_black, fontInfo->fid);
  }
  else{
    PRINT_WARN("cannot load font '%s'\n", fontname);
  }
  return;
}

void textincorner(const char * const text1, const char * const text2){
  int voffset = fontInfo ? (fontInfo->ascent + fontInfo->descent + 5) : 20;
  XDrawString(dis, win, gc_black, 10, voffset, text1, strlen(text1));
  if(text2){
    XDrawString(dis, win, gc_black, 10, voffset*2, text2, strlen(text2));
  }
  return;
}

void textincorner2(const char * const text1){
  int voffset = fontInfo ? (fontInfo->ascent + fontInfo->descent + 5) : 20;
  XDrawString(dis, win, gc_red, 10, voffset*3, text1, strlen(text1));
  return;
}

void setcaption(const char * const capt){
  XStoreName(dis, win, capt);
}

void drawvertices(double * v, double scale, double xy0[2]){
  double d = MIN(H, W)*scale;
  int iw;
#define LINE(I,J) \
  iw=( v[(I)*3+2]>0.0 || v[(J)*3+2]>0.0) ? 0 : 1; \
  XDrawLine(dis, win, gc_dot[iw],\
      W/2+d*(xy0[0]+v[(I)*3]), H/2-d*(xy0[1]+v[(I)*3+1]),\
      W/2+d*(xy0[0]+v[(J)*3]), H/2-d*(xy0[1]+v[(J)*3+1]));
  LINE(0,1);
  LINE(0,2);
  LINE(0,3);
  LINE(1,4);
  LINE(1,5);
  LINE(2,4);
  LINE(2,6);
  LINE(3,5);
  LINE(3,6);
  LINE(4,7);
  LINE(5,7);
  LINE(6,7);
#undef LINE
  return;
}

void drawshell(double rmin, double rmax, double scale, double xy0[2]){
  double d = MIN(H,W)*scale;
  rmax *= d;
  rmin *= d;
  int x = W/2+d*xy0[0];
  int y = H/2-d*xy0[1];
  XDrawArc(dis, win, gc_dot[0], x-rmax, y-rmax, 2*rmax, 2*rmax, 0, 360*64);
  XDrawArc(dis, win, gc_dot[1], x-rmin, y-rmin, 2*rmin, 2*rmin, 0, 360*64);
  return;
}

int savepic(char * s){
  XpmAttributes a;
  a.valuemask = (0 | XpmSize) ;
  a.width     = W;
  a.height    = H;
  XCopyArea (dis, win, px, gc_white, 0, 0, W, H, 0, 0);   /* with text */
  return XpmWriteFileFromPixmap(dis, s, px, 0, &a);
}

