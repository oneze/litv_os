// extern void outb(unsigned short port, unsigned char val);
unsigned char cur_x=0,cur_y=0,attributebyte=(0<<4) |(15 & 0x0F);
unsigned char *videomemory = (unsigned char*)0xB8000;

void outb(unsigned int port, unsigned char val)
{
    asm volatile ( " \
			movb %0, %%al; \
			movw %1, %%dx; \
			outb %%al, %%dx; \
			" : : "m"(val), "m"(port) );
}

void cursormove(int row, int col) {
	unsigned short location=(row*80) + col;

	//Cursor Low port
	outb(0x3D4, 0x0F);//Sending the cursor low byte to the VGA Controller
	outb(0x3D5, (unsigned char)(location&0x00FF));

 	//Cursor High port
	outb(0x3D4, 0x0E);//Sending the cursor high byte to the VGA Controller
	outb(0x3D5, (unsigned char )((location>>8)&0x00FF)); //Char is a 8bit type
}

void scroll() {
	if(cur_y >= 25)
	{
		unsigned short space = 0x20 | (attributebyte << 8);
    //attributebyte must be replaced your attributebyte
    int tmp;
    for (tmp = 0*80; tmp < 24*80; tmp++)
    {
    	videomemory[tmp] = videomemory[tmp+80];//B8000 or B0000 will be location of the buffer
    }
    // Setting the last line
    for (tmp = 24*80; tmp < 25*80; tmp++)
    {
    	videomemory[tmp] = space;//Video memory  is a pointer to the buffer
    }
    // Move the cursor to last line
    cur_y = 24;
	}
}

void print(char chr) {
	unsigned short attribute = attributebyte << 8;
  unsigned short *location;
  // Handle a newline
	if (chr == '\n')
  {	cur_x = 0;
    cur_y++;//Increments cursor's Y axis by 1, i.e; Move's the cursor to the next newline
  }
  // Handle any other printable character.
  else if(chr >=' ')
  {
    location = (unsigned short*)videomemory + (cur_y*80 + cur_x);//Get the  location
    *location = chr | attribute;//Set a element
    cur_x++;//Advance the cursor by 1
  }
  if (cur_x >= 80)//Handles if you are at the end of the line
  {
    cur_x = 0;
    cur_y++;
  }
  // Scroll the screen if needed.
  scroll();
  cursormove(cur_y,cur_x);
}

void printstring(const char* a) {
	while(*a!=0) {
		print(*a++);
	}
}
