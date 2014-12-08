#ifndef x86REGISTERS_H
#define x86REGISTERS_H
#define REG_COUNT 34
struct x86Registers
    {
    int Register;
    short int locked;
	int  Rank;
    }x86RegSet[REG_COUNT];
enum memorysize
    {
    none,
    byte,
    word,
    dword
    };
char memorysize_s[4][7]={{""},{"byte "},{"word "},{"dword "}};

char sz386RegName[REG_COUNT][5]={{"NULLR"},{"EAX"},{"EBX"},{"ECX"},{"EDX"},{"ESI"},{"EDI"},{"ESP"},{"EBP"},{"EIP"},{"ax"},{"bx"},{"cx"},{"dx"},{"bp"},{"sp"},{"si"},{"di"},{"cs"},{"ds"},{"es"},{"fs"},"gs","ss","flags","ah","al","bh","bl","ch","cl","dh","dl",{"none"}};
enum int386Register
    {
    NULLR,EAX,EBX,ECX,EDX,ESI,EDI,ESP,EBP,EIP,ax,bx,cx,dx,si,di,bp,sp,cs,ds,es,fs,gs,ss,flags,ah,al,bh,bl,ch,cl,dh,dl,NoRegister
    }i386Register;
/*-------------------------------------------------------------------------------*
 * GetRegisterSize() Gets the Size of Register									 *
 * SourceRegister- Register ID. eg: 1-EAX,2-EBX	                                 *
 * return- Register Size 4-EAX,2-bx				                                 *
 *-------------------------------------------------------------------------------*/
int GetRegisterSize(int SourceRegister)
    {
    if((SourceRegister>=EAX)&&(SourceRegister<=EIP))
        return 4;
    else if((SourceRegister>=ax)&&(SourceRegister<=dx))
        return 2;
    if((SourceRegister>=ah)&&(SourceRegister<=dl))
        return 1;
    }
/*-------------------------------------------------------------------------------*
 * GetRegisterWordSize() Gets the Size of Registaer which can be used for        *
 * Translating to "word" in ASM code                                             *
 * RegisterId- Register ID. eg: 1-EAX,2-EBX	                                     *
 * return- Register Size dword,bye				                                 *
 *-------------------------------------------------------------------------------*/
int GetRegisterWordSize(int RegisterId)
      {
      if((RegisterId>=EAX)&&(RegisterId<=EIP))
          return dword;
      else if((RegisterId>=ax)&&(RegisterId<=dx))
          return word;
      else if((RegisterId>=ah)&&(RegisterId<=dl))
          return byte;
      else 
          return none;

      }
/*
 *IsRegisterLocked() checks whether a particular register is locked by some instruction.
 */
int IsRegisterLocked(int iRegId)
{
	return x86RegSet[iRegId].locked;
}
/*
 *GetSymbolRegister() searches the Register Table to see if iSymId is already stored in the table.
 */
int GetSymbolRegister(int iSymId)
{
	int i;
	if(iSymId==-1)
		return -1;
	for(i=0;i<dl;i++)
	{
		if(x86RegSet[i].Register==iSymId)
		{
			return i;
		}
	}
	return -1;
}


int GetRegisterID(char *LpszRegisterName)
    {
    
    if(strcmpi(LpszRegisterName,"eax")==0)
        return EAX;
    else if(strcmpi(LpszRegisterName,"ebx")==0)
        return EBX;
    else if(strcmpi(LpszRegisterName,"ecx")==0)
        return ECX;
    else if(strcmpi(LpszRegisterName,"edx")==0)
        return EDX;
	else if(strcmpi(LpszRegisterName,"edi")==0)
        return EDI;
	else if(strcmpi(LpszRegisterName,"esi")==0)
        return ESI;
    else if(strcmpi(LpszRegisterName,"ax")==0)
        return ax;
    else if(strcmpi(LpszRegisterName,"bx")==0)
        return bx;
    else if(strcmpi(LpszRegisterName,"cx")==0)
        return cx;
    else if(strcmpi(LpszRegisterName,"dx")==0)
        return dx;
    else if(strcmpi(LpszRegisterName,"ah")==0)
        return ah;
    else if(strcmpi(LpszRegisterName,"bh")==0)
        return bh;
    else if(strcmpi(LpszRegisterName,"ch")==0)
        return ch;
    else if(strcmpi(LpszRegisterName,"dh")==0)
        return dh;
    else if(strcmpi(LpszRegisterName,"al")==0)
        return al;
    else if(strcmpi(LpszRegisterName,"bl")==0)
        return bl;
    else if(strcmpi(LpszRegisterName,"cl")==0)
        return cl;
    else if(strcmpi(LpszRegisterName,"dl")==0)
        return dl; //DL
	else if(strcmpi(LpszRegisterName,"di")==0)
        return di; //di of EDI
	else if(strcmpi(LpszRegisterName,"sl")==0)
        return si;
    else
        return -1;
    }
/*-------------------------------------------------------------------------------*
 * GetRegister() Gets a register from Register Pool whose operand size is iSize  *
 * iSize- Size of variable(in multiple of 8)								     *
 * return- Register of Size iSize				                                 *
 *-------------------------------------------------------------------------------*/
int GetRegister(int iSize)
      {
      int regs;
	  int index;
	  int lowestRank;
	  lowestRank=30000;
	  index=-1;
	  if(iSize==0)
	  {ErrorHandler(ERROR,"VariableSize is 0 GetRegister()");}
      if(iSize==8)
          {
			  
          for(regs=ah;regs<=dl;regs++)
              {
              if(x86RegSet[regs].locked==false)
                  {
					  if(x86RegSet[regs].Rank<lowestRank)
					  {
						  index=regs;
						  lowestRank=x86RegSet[regs].Rank;
					  }
                  //return regs;
                  }
		  }
		  return index;
          }
      else if(iSize==16)
          {
			  
          for(regs=ax;regs<=di;regs++)
              {

              if(x86RegSet[regs].locked==false)
                  {
                  if(x86RegSet[regs].Rank<lowestRank)
				  {
					  index=regs;
					  lowestRank=x86RegSet[regs].Rank;
				  }
                  }
              }
		  return index;
	  }


      else if(iSize==32)
          {
			  
          for(regs=EAX;regs<=EDI;regs++)  
              {
              if(x86RegSet[regs].locked==false)
                  {
                  if(x86RegSet[regs].Rank<lowestRank)
				  {
					  lowestRank=x86RegSet[regs].Rank;
					  index=regs;
				  }
                  }
		  }
		  return index;
          }
      }
void IncreaseRank(int RegisterID,int value)//:TODO have to change it to a macro
{
x86RegSet[RegisterID].Rank=x86RegSet[RegisterID].Rank+value;
}
void  SetCurrentRegisterRank(Optab * LpCurrent)
{
	int Operand1,Operand2,Result,reg;
	Operand1=LpCurrent->Operand1;
	Operand2=LpCurrent->Operand2;
	Result=LpCurrent->Result;
reg=GetSymbolRegister(Operand1);
if(reg!=-1)
IncreaseRank(reg,1);
reg=GetSymbolRegister(Operand2);
if(reg!=-1)
IncreaseRank(reg,1);
reg=GetSymbolRegister(Result);
if(reg!=-1)
IncreaseRank(reg,1);
}
void ClearRegs()
{
	int i;
	i=0;
	for(i=0;i<=dl;i++)
                        {
							if((i!=EBX)&&(i!=bx)&&(i!=bh)&&(i!=bl))
							{
                        x86RegSet[i].Register=-1;
                        x86RegSet[i].locked=false;
						x86RegSet[i].Rank=0;
							}
                        }
}
void  SetNextRegisterRank(Optab * LpCurrent,Optab * LpStart)
{
Optab *LpNext,*LpNextNext;
int i,reg;
int Operand1Next,Operand2Next,ResultNext,Operand1NextNext,Operand2NextNext,ResultNextNext;

LpNext=LpCurrent->next;
if(LpNext!=LpStart)
LpNextNext=LpNext->next;
else
{
	for(i=0;i<dl;i++)
		x86RegSet[i].Rank=0; //clearing rank for next function.
	return;
}

Operand1Next=LpNext->Operand1;
Operand2Next=LpNext->Operand2;
//ResultNext=LpNext->Result;
Operand1NextNext=LpNextNext->Operand1;
Operand2NextNext=LpNextNext->Operand2;
//ResultNextNext=LpNextNext->Result;
reg=GetSymbolRegister(Operand1Next);
if(reg!=-1)
IncreaseRank(reg,3);
reg=GetSymbolRegister(Operand2Next);
if(reg!=-1)
IncreaseRank(reg,3);
reg=GetSymbolRegister(Operand1NextNext);
if(reg!=-1)
IncreaseRank(reg,2);
reg=GetSymbolRegister(Operand2NextNext);
if(reg!=-1)
IncreaseRank(reg,2);
}
char * Getx86RegisterName(int RegisterId)
      {
      return sz386RegName[RegisterId];
      }
void SetRegister(int RegisterId,int Value,int Locked)
      {
      if(Value!=-2) //-2 is for Lock without setting value, 
      x86RegSet[RegisterId].Register=Value;
      if(RegisterId==EAX)
          {
          x86RegSet[ax].locked=Locked;
          x86RegSet[ah].locked=Locked;
          x86RegSet[al].locked=Locked;
          x86RegSet[ax].Register=-1;
          x86RegSet[ah].Register=-1;
          x86RegSet[al].Register=-1;
          }
      if(RegisterId==EBX)
          {
          x86RegSet[bx].locked=Locked;
          x86RegSet[bh].locked=Locked;
          x86RegSet[bl].locked=Locked;
          x86RegSet[bx].Register=-1;
          x86RegSet[bh].Register=-1;
          x86RegSet[bl].Register=-1;
          }
      if(RegisterId==ECX)
          {
          x86RegSet[cx].locked=Locked;
          x86RegSet[ch].locked=Locked;
          x86RegSet[cl].locked=Locked;
          x86RegSet[cx].Register=-1;
          x86RegSet[ch].Register=-1;
          x86RegSet[cl].Register=-1;
          }
      if(RegisterId==EDX)
          {
          x86RegSet[dx].locked=Locked;
          x86RegSet[dh].locked=Locked;
          x86RegSet[dl].locked=Locked;
          x86RegSet[dx].Register=-1;
          x86RegSet[dh].Register=-1;
          x86RegSet[dl].Register=-1;
          }
      if(RegisterId==ax)
          {
          x86RegSet[ah].locked=Locked;
          x86RegSet[al].locked=Locked;
          x86RegSet[ah].Register=-1;
          x86RegSet[EAX].Register=-1;
          x86RegSet[EAX].locked=Locked;
          x86RegSet[al].Register=-1;
          }
      if(RegisterId==bx)
          {
          x86RegSet[bh].locked=Locked;
          x86RegSet[bl].locked=Locked;
          x86RegSet[EBX].Register=-1;
          x86RegSet[EBX].locked=Locked;
          x86RegSet[bh].Register=-1;
          x86RegSet[bl].Register=-1;
          }
      if(RegisterId==cx)
          {
          x86RegSet[ch].locked=Locked;
          x86RegSet[cl].locked=Locked;
          x86RegSet[ECX].Register=-1;
          x86RegSet[ECX].locked=Locked;
          x86RegSet[ch].Register=-1;
          x86RegSet[cl].Register=-1;
          }
      if(RegisterId==dx)
          {
          x86RegSet[dh].locked=Locked;
          x86RegSet[dl].locked=Locked;
          x86RegSet[EDX].Register=-1;
          x86RegSet[EDX].locked=Locked;
          x86RegSet[dh].Register=-1;
          x86RegSet[dl].Register=-1;
          }
      if((RegisterId==ah)||(RegisterId==al))
          {
          x86RegSet[ax].locked=Locked;
          x86RegSet[EAX].locked=Locked;
          x86RegSet[ax].Register=-1;
          x86RegSet[EAX].Register=-1;
          }
      if((RegisterId==bh)||(RegisterId==bl))
          {
          x86RegSet[bx].locked=Locked;
          x86RegSet[EBX].locked=Locked;
          x86RegSet[bx].Register=-1;
          x86RegSet[EBX].Register=-1;
          }
      if((RegisterId==ch)||(RegisterId==cl))
          {
          x86RegSet[cx].locked=Locked;
          x86RegSet[ECX].locked=Locked;
          x86RegSet[cx].Register=-1;
          x86RegSet[ECX].Register=-1;
          }
      if((RegisterId==dh)||(RegisterId==dl))
          {
          x86RegSet[ax].locked=Locked;
          x86RegSet[EAX].locked=Locked;
          x86RegSet[ax].Register=-1;
          x86RegSet[EAX].Register=-1;
          }
      x86RegSet[RegisterId].locked=Locked;

      }
	  void LockRegister(int RegisterId)
      {
      x86RegSet[RegisterId].locked=true;
      }
	  void UnLockRegister(int RegisterId)
      {
      if((RegisterId<0)||(RegisterId>dl))
          return;
      x86RegSet[RegisterId].locked=false;
      if(RegisterId==EAX)
          {
          x86RegSet[ax].locked=false;
          x86RegSet[ah].locked=false;
          x86RegSet[al].locked=false;
          }
      if(RegisterId==EBX)
          {
          x86RegSet[bx].locked=false;
          x86RegSet[bh].locked=false;
          x86RegSet[bl].locked=false;
          
          }
      if(RegisterId==ECX)
          {
          x86RegSet[cx].locked=false;
          x86RegSet[ch].locked=false;
          x86RegSet[cl].locked=false;
 
          }
      if(RegisterId==EDX)
          {
          x86RegSet[dx].locked=false;
          x86RegSet[dh].locked=false;
          x86RegSet[dl].locked=false;

          }
      if(RegisterId==ax)
          {
          x86RegSet[ah].locked=false;
          x86RegSet[al].locked=false;
          
          x86RegSet[EAX].locked=false;
          
          }
      if(RegisterId==bx)
          {
          x86RegSet[bh].locked=false;
          x86RegSet[bl].locked=false;
          
          x86RegSet[EBX].locked=false;
          
          }
      if(RegisterId==cx)
          {
          x86RegSet[ch].locked=false;
          x86RegSet[cl].locked=false;
          
          x86RegSet[ECX].locked=false;
          
          }
      if(RegisterId==dx)
          {
          x86RegSet[dh].locked=false;
          x86RegSet[dl].locked=false;
          
          x86RegSet[EDX].locked=false;
          
          }
      if((RegisterId==ah)||(RegisterId==al))
          {
          x86RegSet[ax].locked=false;
          x86RegSet[EAX].locked=false;
          
          }
      if((RegisterId==bh)||(RegisterId==bl))
          {
          x86RegSet[bx].locked=false;
          x86RegSet[EBX].locked=false;
          
          }
      if((RegisterId==ch)||(RegisterId==cl))
          {
          x86RegSet[cx].locked=false;
          x86RegSet[ECX].locked=false;
          
          }
      if((RegisterId==dh)||(RegisterId==dl))
          {
          x86RegSet[ax].locked=false;
          x86RegSet[EAX].locked=false;
          
          }

      }
	  int GetLowerRegister(int RegisterId)
      {
      if(RegisterId==EAX)
          return ax;
      else if(RegisterId==EBX)
          return bx;
      else if(RegisterId==ECX)
          return cx;
      else if(RegisterId==EDX)
          return dx;
      else if(RegisterId==ax)
          return al;
      else if(RegisterId==bx)
          return bl;
      else if(RegisterId==cx)
          return cl;
      else if(RegisterId==dx)
          return dl;
      else
          {
          return -1;//error handler
          }
      }
#endif