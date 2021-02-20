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

def SOR(A, b, w, e, x2):
    n = 0
    while True:
        n += 1
        row_num = A.shape[1]
        x1 = x2.copy()
        for i in range(row_num):
            temp = 0
            for j in range(row_num):
                if i != j:
                    temp += A[i][j]*x2[j]
            temp = (b[i] - temp)/A[i][i]
            x2[i] = (1-w)*x2[i] + w*temp
        #print(np.max(np.abs(np.subtract(x1, x2))))
        if(n >= 5000):
            break
        if np.max(np.abs(np.subtract(x1, x2))) < e:
            break
    
    return n, x2


def main():
    f = open('out.txt', 'w')
    for i in range(1, 100):
        n, x = SOR(A, b, i/50., 1e-7, np.zeros(b.shape))
        f.write('松弛因子为：{}, 迭代步数：{}\n'.format(i/50., n))
        for i in range(x.shape[0]):
            f.write('x{}={:.15e}\n'.format(i+1, x[i]))



if __name__ == '__main__':
    main()
    

            
                