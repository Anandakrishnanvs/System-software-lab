#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

FILE *f1,*f2,*f3,*f4,*f5,*f6;
struct SYMTAB
{
    char label[20];
    int addr;
}ST[100];

struct OPTAB
{
    char opcode[20],hexcode[20];
}OT[100];
int o=-1,s=-1,length,size=0;
char opcode[100],label[100],str_addr[20],operand[100],address[100],t1[100],t2[100],t3[100],t4[100],ad[20],a[20];


void read_optab()
{
    while(1)
    {
        o++;
        if(fscanf(f3,"%s%s",OT[o].opcode,OT[o].hexcode) != 2) break;
    }
}
void read_symtab()
{
    while(1)
    {
        s++;
        if(fscanf(f2,"%s%x",ST[s].label,&ST[s].addr) != 2) break;
    }
}
void read_line()
{
    strcpy(t1,"");strcpy(t2,"");strcpy(t3,"");strcpy(t4,"");
    fscanf(f1,"%s",t1);
    if(getc(f1)!='\n')
    {
        fscanf(f1,"%s",t2);
        if(getc(f1)!='\n')
        {
          fscanf(f1,"%s",t3);
          if(getc(f1)!='\n')
          {
             fscanf(f1,"%s",t4);
          }
        }
    }
    if(strcmp(t1,"")!=0 && strcmp(t2,"")!=0 && strcmp(t3,"")!=0 && strcmp(t4,"")!=0 )
    {
       strcpy(address,t1);strcpy(label,t2);strcpy(opcode,t3);strcpy(operand,t4);
    }
    else if(strcmp(t1,"")!=0 && strcmp(t2,"")!=0 && strcmp(t3,"")!=0 && strcmp(t4,"")==0 )
    {
       strcpy(address,t1);strcpy(label,"");strcpy(opcode,t2);strcpy(operand,t3);
    }
    else if(strcmp(t1,"")!=0 && strcmp(t2,"")!=0 && strcmp(t3,"")==0 && strcmp(t4,"")==0 )
    {
        if(strcmp(t1,"END")==0)
        {
             strcpy(address,"");strcpy(label,"");strcpy(opcode,t1);strcpy(operand,t2);
        }
        else
        {
            strcpy(address,"");strcpy(label,"");strcpy(opcode,t1);strcpy(operand,"");
        }
    }
}
int main()
{
    f1=fopen("intermediate.txt","r");
    f2=fopen("symtab.txt","r");
    f3=fopen("optab.txt","r");
    f4=fopen("length.txt","r");
    f5=fopen("assmlist.txt","w");
    f6=fopen("objcode.txt","w");
 

    read_optab();
    read_symtab();
    fscanf(f1,"%s%s%s",label,opcode,operand);
    strcpy(str_addr,operand);
    
    fscanf(f4,"%x%x",&length,&size);
    if(strcmp(opcode,"START")==0)
    {
        fprintf(f5,"\t%s\t%s\t%s\n",label,opcode,operand);
        fprintf(f6,"H^%-6s^00%s^%06x\n",label,operand,length);
        fprintf(f6,"T^00%s^%02x",operand,size);
        read_line();
    }
    while(strcmp(opcode,"END")!=0)
    {
        if(strcmp(opcode,"BYTE")==0)
        {
            fprintf(f5,"%s\t%s\t%s\t%s\t",address,label,opcode,operand);
            if(strlen(operand)>2)
            {
                sprintf(ad,"%02x",(unsigned char)operand[2]);
                fprintf(f5,"%s\n",ad);
                fprintf(f6,"^%s",ad);
            }
            else
            {
                fprintf(f5,"error");
            }
        }
        else if(strcmp(opcode,"WORD")==0)
        {
            fprintf(f5,"%s\t%s\t%s\t%s\n",address,label,opcode,operand);
            sprintf(a,"%x",atoi(operand));
            fprintf(f6,"^00000%s",a);
        }
        else if(strcmp(opcode,"RESW")==0  || strcmp(opcode,"RESB")==0 )
        {
             fprintf(f5,"%s\t%s\t%s\t%s\n",address,label,opcode,operand);   
        }
        else
        {
            int j=0;
            while(j<=o && strcmp(OT[j].opcode,opcode)!=0)
                j++;
             int i=0;
            while(i<=s && strcmp(operand,ST[i].label)!=0)
                i++;
            if(j>o || i>s)
            {
                fprintf(f5,"%s\t%s\t%s\t%s\tERROR\n",address,label,opcode,operand);
                fprintf(f6,"^000000");
            }
            else
            {
                fprintf(f5,"%s\t%s\t%s\t%s\t%s%04x\n",address,label,opcode,operand,OT[j].hexcode,ST[i].addr);
                fprintf(f6,"^%s%04x",OT[j].hexcode,ST[i].addr);
            }
        }
        read_line();
    }
    fprintf(f5,"\t%s\t%s\t%s\n",label,opcode,operand);  // Added newline
    fprintf(f6,"\nE^00%s",str_addr);
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);
    fclose(f6);

    printf("Success\n");  // Fixed typo
    return 0;
}
