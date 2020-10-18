#ifndef __COINS__
#define __COINS__
#include <vector>
#include <string>
#include "balance.h"
#include <iostream>
#include <algorithm>
constexpr int ALL = -1;
class Coins {
private:
	static int num;
	std::string name;
	std::vector<int> coins;

	void __init();
	void __printName() const;
	void clear(void);			//텅빈 코인 집합으로 만들기 : 일부 코인을 누락할 가능성이 매우 높은 함수, 사용 제한
	Coins get(int num);		//num개 만큼 꺼내서 return : 중복 코인을 생성할 가능성 매우 높은 함수, 사용 제한
	Coins& operator=(const Coins& ref); //복사대입연산자 : 중복 코인을 생성할 가능성이 매우 높은 함수, 사용 제한
public:
	Coins();					//텅빈 코인 집합 생성자
	Coins(const Coins& ref);//복사대입생성자 : 중복 코인을 생성할 가능성이 매우 높은 생성자, 사용 제한
	Coins(int start, int end);//start부터 end까지의 코인 인덱스를 가진 집합 생성자

	Coins fetch(int num);		//코인 집합에서 앞에서부터 num개 코인 빼내기
	unsigned int size(void);	//집합 원소 수
	bool empty(void);			//텅빈 코인 집합이면 true 반환
	void sort();				//코인 집합 오름차순 정렬
	void setName(std::string s);//디버깅용 이름 설정

	//두 코인 집합간 balance 호출
	friend int balance(Coins A, Coins B);

	//두 코인 집합간 작은 코인 집합에 맞추어 코인을 동일한 갯수만 꺼내 balance 호출
	friend int balanceWithSameAmount(Coins& A, Coins& B);

	//두 코인 집합간 오직 1개의 원소만 꺼내 balance 호출
	friend int balanceOnlyOneElement(Coins& A, Coins& B);

	//+=, +, << 연산자 오버로딩

	//복합 대입 연산자 함수로 중복 코인이 발생할 수 있으니 fetch함수와 같이 쓰는 것을 강하게 권고
	Coins& operator+=(const Coins& ref);
	Coins operator+(const Coins& ref);
	friend std::ostream& operator<<(std::ostream& os, const Coins& ref);
};
#endif
