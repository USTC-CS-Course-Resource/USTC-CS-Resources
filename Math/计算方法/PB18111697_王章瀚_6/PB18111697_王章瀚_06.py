import numpy as np

# 一些初值
A = np.array([[31,-13,0,0,0,-10,0,0,0],
     [-13,35,-9,0,-11,0,0,0,0],
     [0,-9,31,-10,0,0,0,0,0],
     [0,0,-10,79,-30,0,0,0,-9],
     [0,0,0,-30,57,-7,0,-5,0],
     [0,0,0,0,-7,47,-30,0,0],
     [0,0,0,0,0,-30,41,0,0],
     [0,0,0,0,-5,0,0,27,-2],
     [0,0,0,-9,0,0,0,-2,29]], dtype=np.float64)

b = np.array([-15,27,-23,0,-20,12,-7,7,10], dtype=np.float64)

def GaussEliminationWithPartialPivoting(A, b):
    col_num, row_num = A.shape
    for i in range(row_num):
        # 找到列主元所在行
        maxarg = np.argmax(np.abs(A[i:, [i]]), axis=0)[0]+i
        # 交换
        A[[maxarg, i], :] = A[[i, maxarg], :]
        b[maxarg], b[i] = b[i], b[maxarg]
        if(A[i][i] != 0):
            for j in range(i+1, row_num):
                b[j] = np.subtract(b[j], A[j][i]/A[i][i]*b[i])
                A[j] = np.subtract(A[j], A[j][i]/A[i][i]*A[i])

    for i in range(row_num-1, -1, -1):
        for j in range(i+1, row_num):
            b[i] = b[i] - A[i][j]*b[j]
        b[i] = b[i]/A[i][i]
            
    return b
    
x = GaussEliminationWithPartialPivoting(A.copy(), b.copy())
for i in range(A.shape[1]):
    print('x{}={:.15e}'.format(i+1, x[i]))

