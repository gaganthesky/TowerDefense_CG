//Functions used for debugging in various files


#include "project.h"

void setFont(char* name, int size)
{
  if(strcmp(name,"helvetica") == 0) {
    if (size == 10) fontStyle = GLUT_BITMAP_HELVETICA_10;
    else if (size == 12) fontStyle = GLUT_BITMAP_HELVETICA_12;
    else if (size == 18) fontStyle = GLUT_BITMAP_HELVETICA_18;
  } else if (strcmp(name, "times roman") == 0) {
    if (size == 24) fontStyle = GLUT_BITMAP_TIMES_ROMAN_24;
  }
}

#define LEN 8192
void printv(va_list args, const char* format)
{
  char    buf[LEN];
  char*   ch=buf;

  vsnprintf(buf,LEN,format,args);

  while (*ch)
    glutBitmapCharacter(fontStyle,*ch++);
}

void print(const char* format , ...)
{
  va_list args;
  va_start(args,format);
  printv(args,format);
  va_end(args);
}

void printAt(int x, int y, const char* format, ...)
{
  va_list args;
  glWindowPos2i(x, y);
  va_start(args,format);
  printv(args,format);
  va_end(args);
}

void errCheck(char* where)
{
   int err = glGetError();
   if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}

void fatal(const char* format , ...)
{
   va_list args;
   va_start(args,format);
   vfprintf(stderr,format,args);
   va_end(args);
   exit(1);
}
