# bad-coin-diagnosis-algorithm
Implementation for bad coin diagnosis algorithm  
불량 코인 분류 알고리즘  

# 개요
`100개`의 코인들 중 일부는 `보통 코인`보다 살짝 가벼운 `불량 코인`입니다.  
이 `불량 코인`들을 솎아내기 위해 `하나의 저울`을 사용할 수 있습니다.  
`불량 코인`의 `비율`은 알려져있지 않습니다.  
`저울질`을 최소화 하면서 모든 `불량 코인`을 솎아내봅시다.

# 다운로드 및 실행
1. 다운로드 또는 git clone
```
git clone https://github.com/kcoms555/bad-coin-diagnosis-algorithm
```
2. 디렉토리 이동
```
cd bad-coin-diagnosis-algorithm
```
3. 컴파일
```
make
```
또는
```
g++ source/main.cpp source/Coins.cpp source/balance.c -o bin/main
```
4. 실행
```
bin/main [발생확률] [merge|step|merge2]
```

# 참고자료 : 문제의 종류
![image](https://user-images.githubusercontent.com/48780754/96365701-78311980-117d-11eb-83ee-a3f6ce8efc45.png)  
-- 회의발표자료/02_문기의분석.pdf 중 1page


### 참고문헌
E. Purdy(2011), Lower Bounds for Coin-Weighing Problems, ACM Transactions on Computation Theory, 2(2):3, 1-12.
