#ifndef UICLASSES_H
#define UICLASSES_H


struct Button
{
	int   x;						/* top left x coord of the button */
	int   y;						/* top left y coord of the button */
	int   w;						/* the width of the button */
	int   h;						/* the height of the button */
	char* label;
};
typedef struct Button Button;



const float NEXT[] = {
	0.0, -0.5,
	0.5, -0.5,
	0.5, 0.0,
	0.0, 0.0
};

#endif