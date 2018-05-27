#include <stdio.h>
#include <assert.h>
#include <string.h>

int main(int argc, char *argv[])
{
  FILE *src = fopen(argv[1],"rb");
  char line[9999],m;
  int w,h,f,i,j,x=(argc>2)?2:1;

  assert(src);
  fgets(line, 9999, src); assert(0 == strcmp(line, "P6\n") || 0 == strcmp(line, "P5\n"));
  m=line[1];
  fgets(line, 9999, src); assert(2 == sscanf(line, "%d %d", &w, &h));
  fgets(line, 9999, src); assert(1 == sscanf(line, "%d", &f));
  assert(3*w < 9999);
  assert(9 <= printf("P%c\n%d %d\n%d\n",m,w*x,2*h,f));

  f = (m=='5') ? 1 : 3;

  for(i=0; i<h; ++i)
  {
    assert(f*w == fread(line, 1, f*w, src));
    if (x==2)
    {
      for(j=w-1; j>=0; --j)
      {
        if (f==1) { line[2*j]=line[2*j+1]=line[j]; }
        else
        {
          line[2*j*f+0] = line[(2*j+1)*f+0] = line[j*f+0];
          line[2*j*f+1] = line[(2*j+1)*f+1] = line[j*f+1];
          line[2*j*f+2] = line[(2*j+1)*f+2] = line[j*f+2];
        }
      }
    }
    assert(f*w*x == fwrite(line, 1, f*w*x, stdout));
    assert(f*w*x == fwrite(line, 1, f*w*x, stdout));
  }

  h=ftell(src); fseek(src, 0, SEEK_END); assert(h == ftell(src));

  fclose(src);
  return 0;
}
