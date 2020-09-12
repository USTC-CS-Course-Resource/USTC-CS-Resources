import numpy as np


def Jacobi(A, e):
    n = A.shape[1]
    Q = np.eye(N=n, M=n, dtype=np.float64)
    while np.sum([A[i][j]**2 for j in range(n) for i in range(n) if i != j]) > e:
    #for t in range(10):
        p = 0
        q = 1
        for i in range(n):
            for j in range(i + 1, n):
                if abs(A[p][q]) < abs(A[i][j]):
                    p, q = i, j
        s = (A[q][q] - A[p][p])/(2*A[p][q])
        if s == 0:
            t = 1
        else:
            t1 = -s-(s*s+1)**0.5
            t2 = -s+(s*s+1)**0.5
            if abs(t1) > abs(t2):
                t = t2
            else:
                t = t1
        c = 1/((t*t+1)**0.5)
        d = t/((t*t+1)**0.5)
        
        # 书上方法 开始
        for i in range(n):
            if i != p and i != q:
                A[i][p] = A[p][i] = c*A[p][i]-d*A[q][i]
                A[i][q] = A[q][i] = d*A[p][i]+c*A[q][i]
        A[p][p] = A[p][p]-t*A[p][q]
        A[q][q] = A[q][q]+t*A[p][q]
        A[p][q] = A[q][p] = 0
        # 书上方法 结束
        
        
        tempQ = np.eye(N=n, M=n, dtype=np.float64)
        tempQ[p][p] = tempQ[q][q] = c
        tempQ[p][q] = d
        tempQ[q][p] = -d
        Q = np.matmul(Q, tempQ)
        
        # 直接乘 开始
        # A = np.matmul(np.matmul(tempQ.T, A), tempQ)
        # 直接乘 结束
        
    eigenvalue = np.diag(A)
    vectors = Q.swapaxes(0, 1)
    return eigenvalue, vectors, Q
    
    
def main():
    A = np.array([[3,2,5,4,6],
                  [2,1,3,-7,8],
                  [5,3,2,5,-4],
                  [4,-7,5,1,3],
                  [6,8,-4,3,8]],dtype=np.float64)
    
    e = 1e-13
    eigenvalue, vectors, Q = Jacobi(A.copy(), e)
    for i in range(A.shape[1]):
        np.set_printoptions(precision=15)
        print('r{}={:.15e},\nv{}=({:.5e}'.format(i+1, eigenvalue[i], i+1, vectors[i][0]), end='')
        for j in range(1, A.shape[1]):
            print(', {:.5e}'.format(vectors[i][j]), end='')
        print(')')
    
        


if __name__ == '__main__':
    main()
