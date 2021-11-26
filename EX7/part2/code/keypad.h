sbit R3 = P1^2;
sbit R4 = P1^3;
sbit R2 = P1^1;

sbit C1 = P1^4;
sbit C2 = P1^5;
sbit C3 = P1^6;
sbit C4 = P1^7;



char Read_Keypad()
{
C1=C2=C3=C4=1;

R1=0;
R2=1;
R3=1;
R4=1;
if(C1==0){while(C1==0);return '1';}
if(C2==0){while(C2==0);return '2';}
if(C3==0){while(C3==0);return '3';}
if(C4==0){while(C4==0);return 'A';}
R1=1;
R2=0;
R3=1;
R4=1;
if(C1==0){while(C1==0);return '4';}
if(C2==0){while(C2==0);return '5';}
if(C3==0){while(C3==0);return '6';}
if(C4==0){while(C4==0);return 'B';}
R1=1;
R2=1;
R3=0;
R4=1;
if(C1==0){while(C1==0);return '7';}
if(C2==0){while(C2==0);return '8';}
if(C3==0){while(C3==0);return '9';}
if(C4==0){while(C4==0);return 'C';}
R1=1;
R2=1;
R3=1;
R4=0;
if(C1==0){while(C1==0);return '*';}
if(C2==0){while(C2==0);return '0';}
if(C3==0){while(C3==0);return '#';}
if(C4==0){while(C4==0);return 'D';}
return 0;
}