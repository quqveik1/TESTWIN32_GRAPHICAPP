#pragma once

#define key(a) txGetAsyncKeyState (a)
#define notKey(a) while (txGetAsyncKeyState (a)) {};
#define endifkey(a) if (key (a)) break;
#define endtillkey(a)           \
{                               \
    if (key (a))                \
    {                           \
        for (;;)                \
        {                       \
            if (!key (a))       \
            {                   \
                break;          \
            }                   \
        }                       \
    }                           \
}

#define addKeyNum(a, anum, num)       \
{                                     \
    if (key(a))                       \
    {                                 \
        num = num * 10 + anum;        \
        for (;;)                      \
        {                             \
            if (!key (a)) break;      \
        }                            \
    }                                 \
}							 

#define stop						\
{									\
	printf ("T\n");	\
	txSleep (0);   		           \
	_getch ();						\
}									\

#define printBlt(image)         \
{                               \
    assert (image);				\
	txSetFillColor (TX_RED);		\
	txRectangle (0, 0, 1000, 1000);	  \
	txSetFillColor (TX_BLACK);    \
	txRectangle(100, 100, 200, 200);									\
	txBitBlt (0, 0, image); 		   \
	txSleep (0);								\
    stop;                 \
    txClear ();                 \
}

#define copyOnDC(x, y, image)	\
{										  \
	txBitBlt (finalDC, x, y, 0,0, image); \
}										  \


#define copyDC(dest, source)                            \
{                                                       \
    txBitBlt (dest, 0, 0, 0, 0, source);                                                   \
}                                                       \



                                                                     
                                                                                               

#define drawOnFinalDC(button)					  \
{												  \
	button.draw ();								  \
	button.app->bitBlt (finalDC, button.rect.pos.x, button.rect.pos.y, button.rect.getSize().x, button.rect.getSize().y, button.finalDC);  \
}