import numpy as np

'''

This file will serve as the skeleton of all the linalg + numerical methods

the battle between np arrays vs lists

'''

testm=[[1,2,3],[4,5,6],[7,8,9]]
trym=[[4,5,6],[7,8,9],[1,2,3]]
testnp= np.arange(1,10).reshape(3,3)
testnpp=np.ones(3)


def printMatrix(matrix):
    ret=''
    for i in matrix:
        lin='['
        for j in i:
            lin+= str(j)+', '
        ret+=lin[:-2]+']\n'
    return ret

def GaussJordan(A,b=None):
    if b!=None:
        solve=augment(A,b)
    else:
        solve=A
    n = len(A) # Columns to solve for -> determined by num of rows, since its redundant to 
    ps=''
    num_col=len(A[0]) 
    
    # Forward elmiminationz
    for i in range(n):
        for j in range(i+1,n):
            factor = solve[j][i]/solve[i][i]
            solve[j] = [k/factor for k in solve[j]]
        ps+="Elimination\n"
        ps+=printMatrix(solve)
    return ps


    pass

def bisectionMethod():
    pass

def augment(A, b)-> list:
    if len(A)!=len(b): raise Exception('Array column lengths do not match')

    aug=[]
    num_rows= len(A) 
    stop=len(A[0])
    num_columns = len(A[0]+b[0])
    for i in range(num_rows):
        line=[]
        for j in range(num_columns):
            if j<stop:
                line.append(A[i][j])
            else:
                line.append(b[i][j-stop])
        aug.append(line)

    return aug

t2=augment(testm,trym)
print(printMatrix(t2))
print(GaussJordan(t2))

