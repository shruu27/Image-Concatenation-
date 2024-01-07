#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"
int main(void)
{
    int w1,h1,ch1,w2,h2,ch2;
    unsigned char *img1=stbi_load("trial8.png",&w1,&h1,&ch1,0);
    unsigned char *img2=stbi_load("trial9.png",&w2,&h2,&ch2,0);

    printf("%d w1  %d h1  %d chn1  ///  %d w2  %d h2  %d chn2",w1,h1,ch1,w2,h2,ch2);
    size_t imgsz1 = w1*h1*ch1;
    size_t imgsz2 = w2*h2*ch2;
    size_t nimgsize = (w1>w2?w1:w2)*(h1+h2)*(ch1+ch2);
    unsigned char *nimg=malloc(nimgsize);
    unsigned char *a1=img1,*a2=img2;

    unsigned char *b=nimg;
    int i,j;
    for(i=0;i<h1;i++)
    {
        b=nimg+(i*(w1>w2?w1:w2)*(ch1+ch2));
        for(j=0;j<w1;j++)
        {
                *b=*a1;
                *(b+1)=*(a1+1);
                *(b+2)=*(a1+2);
                if(ch1==4)
                {
                    *(b+3)=*(a1+3);

                }
                a1+=ch1;
                b+=ch1;

        }
        if(w1<w2)
        {
            b=nimg+(i*(w1>w2?w1:w2)*(ch1+ch2))+w1*ch1;
            for(j=0;j<w2-w1;j++)
            {
                *b=0;
                *(b+1)=0;
                *(b+2)=0;
                if(ch1==4)
                {
                    *(b+3)=0;
                }
                b+=ch1;
            }
        }
    }

for(i=h1;i<h1+h2;i++)
    {
        b=nimg+(i*(w1>w2?w1:w2)*(ch1+ch2))+(w1>w2?w1-w2:0)*ch1;
        for(j=0;j<w2;j++)
        {
                *b=*a2;
                *(b+1)=*(a2+1);
                *(b+2)=*(a2+2);
                if(ch2==4)
                {
                    *(b+3)=*(a2+3);

                }
                a2+=ch2;
                b+=ch2;

        }
        if(w2<w1)
        {
            b=nimg+(i*(w1>w2?w1:w2)*(ch1+ch2))+w2*ch2;
            for(j=0;j<w1-w2;j++)
            {
                *b=0;
                *(b+1)=0;
                *(b+2)=0;
                if(ch2==4)
                {
                    *(b+3)=0;
                }
                b+=ch2;
            }
        }
    }


    stbi_write_png("concat.png",w1>w2?w1:w2,h1+h2,ch2,nimg,(w1>w2?w1:w2)*(ch1+ch2));
    stbi_image_free(img1);
    stbi_image_free(img2);
    free(nimg);
}
