import os
import random


def init():
    B=[]
    dim=int(input("dim...."))
    nop=int(input("nop...."))

    for r in range(0,dim):
        arow=[]
        for c in range(0,dim):
            arow.append('-')
        B.append(arow)

    sym=[]
    pnames=[]
    for i in range(0,nop):
        pnames.append(input(f"player {i+1}'s name: "))
        sym.append(input(f"player {i+1}'s symbol: "))

    
    turn = random.randint(0,nop-1)
    return B, dim,nop,sym,pnames,turn
def printBoard (B,dim):
    os.system('cls')
    for r in range(0,dim):
        for c in range (0,dim):
            print(B[r][c],end="")
        print()
def turnmsg(harami):
    print(f"{harami}'s turn: ")
def slcpos(dim):
 
    while(1):
    
        pr = int(input(f"select row number(0...{dim}) ... "))
        if(pr<=dim and pr>=1):
            pr-=1
            break
        else:
            print("wrong coordinates, enter again: ")
    
    while(1):
    
        pc = int(input(f"select column number(0...{dim}) ... "))
        if(pc<=dim and pc>=1):
            pc-=1
            break
        else:
            print("wrong coordinates, enter again: ")
    for i in range(0,dim):
        if(B[pr][pc]!='-' or pr<0 or pr>dim or pc <0 or pc > dim):
            print("wrong coordinates, enter again: ")
            pr = int(input(f"select row number(0...{dim}) ... "))
            pc = int(input(f"select column number(0...{dim}) ... "))
            pr-=1
            pc-=1
    return pr, pc
def plcmov(B,pr,pc,haramisym):
    B[pr][pc]=haramisym
def trnchng(turn,nop):
    turn=(turn+1)%nop
    return turn

def isValidMove(pr,pc,dim,B):
    if ((pr >= 0 and pr < dim) and (pc >= 0 and pc < dim) and (B[pr][pc] == '-')):
         return True
    else:
         return False

def horiz(B,r,c,dim,wincount,sym):
    count = 0
    if (c + wincount - 1 >= dim):
        return False
    for i in range(0,wincount):
        if(B[r][c+i]==sym):
            count+=1
    if(count == wincount):
        return True
    else:
        return False
def vert(B,r,c,dim,wincount,sym):
    count = 0
    if (r + wincount - 1 >= dim):
        return False
    for i in range(0,wincount):
        if(B[r+i][c]==sym):
            count+=1
    if(count == wincount):
        return True
    else:
        return False
def diag_left(B,r,c,dim,wincount,sym):
    count = 0
    if (r + wincount - 1 >= dim or c + wincount - 1 >= dim):
        return False
    for i in range(0,wincount):
        if(B[r+i][c+i]==sym):
            count+=1
    if(count == wincount):
        return True
    else:
        return False
def diag_rig(B,r,c,dim,wincount,sym):
    count = 0
    if (r + wincount - 1 >= dim or c -(wincount - 1) < 0):
        return False
    for i in range(0,wincount):
        if(B[r+i][c-i]==sym):
            count+=1
    if(count == wincount):
        return True
    else:
        return False
def iswin(B,dim,sym,wincount):
    for r in range(0,dim):
        for c in range(0,dim):
            if(horiz(B, r, c, dim, wincount, sym) or
				vert(B, r, c, dim, wincount, sym) or
				diag_left(B, r, c, dim, wincount, sym) or
				diag_rig(B, r, c, dim, wincount, sym)):
                return True 
            
    return False
def game_over(B,dim):
    if(draw(B,dim)==0):
        return True
    return False
def draw(B,dim):
    count = 0
    for r in range(0,dim):
        for c in range (0,dim):
            if(B[r][c] == "-"):
              count+=1
    return count
def computerMove(B,dim,sym,wincount,human,computer):
    wc=0
    for wc in range(wincount,wc>1,-1):
        for r in range(0,dim):
            for c in range(0,dim):
                row=r
                col=c
                if(isValidMove(row,col,dim,B)):
                    B[r][c] = sym[computer]
                    if(iswin(B,dim,sym[computer],wc)):
                        B[r][c]='-'
                        return row,col
                    B[r][c]='-'
        for r in range(0,dim):
            for c in range(0,dim):
                row = r
                col = c
                if(isValidMove(row,col,dim,B)):
                    B[r][c] = sym[human]
                    if(iswin(B,dim,sym[human],wc)):
                        B[r][c]='-'
                        return row,col
                    B[r][c]='-'
    row = random.randint(0,dim-1)
    col = random.randint(0,dim-1)
    while(not isValidMove(row,col,dim,B)):
        row = random.randint(0,dim-1)
        col = random.randint(0,dim-1)
    return row,col
##########################################################################
human=1
computer=0
B,dim,nop,sym,pname,turn = init()
wincount = int(input("Enter winner count : "))
printBoard(B,dim)
while (True):
    turnmsg(pname[turn])
   
    if(turn==human):
         pr,pc = slcpos(dim)
      
    else:
        pr,pc = computerMove(B,dim,sym,wincount,human,computer)
    plcmov(B,pr,pc,sym[turn])
    printBoard(B,dim)
    if(iswin(B,dim,sym[turn],wincount)):
         print(f"{pname[turn]} is the winner")
         break
    if(game_over(B,dim)):
          print("Game draw")
          break
    turn = trnchng(turn,nop)
print("Game over!!!")

############################################################
