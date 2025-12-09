#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE *f1,*f2,*f3,*f4,*f5;
struct SYMTAB
{
    char label[20];
    int addr;
}ST[100];
struct OPTAB
{
    char opcode[20],hexcode[20];
}OT[100];
int o=-1,s=-1,opd,start,locctr,flag,size=0,len;
char label[20],opcode[20],operand[20],t1[20],t2[20],t3[20];
void read_optab()
{
      while(1)
      {
        o++;
        if(fscanf(f2,"%s%s",OT[o].opcode,OT[o].hexcode)!=2) break;

        //if(feof(f2)) break;
      }
}
void read_line()
{
  strcpy(t1,"");strcpy(t2,"");strcpy(t3,"");
  fscanf(f1,"%s",t1);
  if(getc(f1)!='\n')
  {
     fscanf(f1,"%s",t2);
     if(getc(f1)!='\n')
     {
        fscanf(f1,"%s",t3);
     }
  }
  if(strcmp(t1,"")!=0 && strcmp(t2,"")!=0 && strcmp(t3,"")!=0)
  {
     strcpy(label,t1);strcpy(opcode,t2); strcpy(operand,t3);
  }
  else if(strcmp(t1,"")!=0 && strcmp(t2,"")!=0 && strcmp(t3,"")==0)
  {
     strcpy(label,"");strcpy(opcode,t1); strcpy(operand,t2);
  }
  else if(strcmp(t1,"")!=0 && strcmp(t2,"")==0 && strcmp(t3,"")==0)
  {
     strcpy(label,"");strcpy(opcode,t1); strcpy(operand,"");
  }
}
int main()
{
    f1=fopen("input.txt","r");
    f2=fopen("optab.txt","r");
    f3=fopen("intermediate.txt","w");
    f4=fopen("symtab.txt","w");
    f5=fopen("length.txt","w");
    read_optab();
    fscanf(f1,"%s%s%x",label,opcode,&opd);
    if(strcmp(opcode,"START")==0)
    {
       start=opd;
       locctr=start;
       fprintf(f3,"%s\t%s\t%x\n",label,opcode,opd);
       read_line();
    }
    else
    {
        locctr=0;
    }
    while(strcmp(opcode,"END")!=0)
    {
        fprintf(f3,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        if(strcmp(label,"")!=0)
        {
            for(int i=0;i<=s;i++)
            {
                if(strcmp(ST[i].label,label)==0)
                {
                    printf("error");
                    exit(0);
                }
            }
            s++;
            strcpy(ST[s].label,label);
            ST[s].addr=locctr;
        }
        flag=0;
        for(int i=0;i<=o;i++)
        {
           if(strcmp(opcode,OT[i].opcode)==0)
           {
              locctr+=0x3;
              size+=3;
              flag=1;
              break;
           }
        }
        if(flag==0)
        {
            if(strcmp(opcode,"WORD")==0)
            {
                locctr+=0x3;
                size+=3;
            }
            else if(strcmp(opcode,"RESW")==0)
            {
                locctr+=(0X3*(atoi(operand)));
        
            }
            else if(strcmp(opcode,"RESB")==0)
            {
                locctr+=(atoi(operand));
                
            }
            else if(strcmp(opcode,"BYTE")==0)
            {
                len=strlen(operand);
                if(operand[0]=='c' || operand[0]=='C')
                {
                    len=len-3;
                }
                else
                {
                    len=(len-3)/2;
                }
                locctr+=len;
                size+=len;
            }
        }
        read_line();
    }
        
        fprintf(f3,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        for(int i=0;i<=s;i++)
        {
            fprintf(f4,"%s\t\t%x",ST[i].label,ST[i].addr);
            if(i!=s)
            {
                fprintf(f4,"\n");
            }
        }
        fprintf(f5,"%x\n%x",locctr-start,size);
   fclose(f1);
   fclose(f2);
   fclose(f3);
   fclose(f4);
   fclose(f5);

}