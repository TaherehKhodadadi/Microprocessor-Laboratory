sbit RS=P2^0;
sbit RW=P2^1;
sbit E=P2^2;

char *string;
//LCD 8 Bit Interfacing Functions

void Lcd8_Cmd(unsigned char value)
{
P3=value;
RS=0;
RW=0;
E=1;
delay_msec(1);
E=0;
}


void Lcd8_Init()
{
Lcd8_Cmd(0x38); //function set
Lcd8_Cmd(0x0C); //display on,cursor off,blink off
Lcd8_Cmd(0x01); //clear display
Lcd8_Cmd(0x06); //entry mode, set increment
}

void Lcd8_Write_Char(unsigned char value)
{

P3=value;
RS=1;
RW=0;
E=1;
delay_msec(1);
E=0;
}

void Lcd8_Write_String(char *a)
{
int i;
string=a;
for(i=0;a[i]!='';i++)
Lcd8_Write_Char(a[i]);
}

void Lcd8_Shift_Right()
{ int j;
for(j=0;j{Lcd8_Cmd(0x1C);delay_msec(100);}
}

void Lcd8_Shift_Left()
{ int k;
for(k=0;k{Lcd8_Cmd(0x18);delay_msec(100);}
}

 