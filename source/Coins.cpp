#include "Coins.h"
using namespace std;

//private
void Coins::__init() { name = (std::to_string(num++)+"번째로 생성된 코인 객체"); /*std::cout << name; 디버깅 전용*/ }
void Coins::__printName() const { std::cout << name << "[" << coins.size() << "]"; }
void Coins::clear(void) { coins.clear(); }
Coins Coins::get(int num) { return Coins(*this).fetch(num); }
//Coins& Coins::operator=(const Coins& ref) {} //복사대입연산자는 중복방지를 위해 미구현

//public
Coins::Coins() { __init(); }
Coins::Coins(const Coins& ref) :coins(ref.coins) { __init(); }
Coins::Coins(int start, int end) { __init(); for (int i = start; i <= end; i++) coins.push_back(i); }

Coins Coins::fetch(int num) {
	Coins c;
	if (num < 0) num = coins.size() + num + 1; //num이 -1일때는 coins.size() 이다.
	if (num > coins.size()) {
		__printName();  printf(" fetch : %d개 보다 크기에 맞게 %d개 가져옵니다.\n", num, coins.size());
		num = coins.size();
	}
	for (auto i = coins.begin(); i != coins.begin() + num; i++)
		c.coins.push_back(*i);
	coins.erase(coins.begin(), coins.begin() + num); //앞에서 num개 삭제
	return c;
}
unsigned int Coins::size(void) { return coins.size(); }
bool Coins::empty(void) { return coins.empty(); }
void Coins::sort() { std::sort(coins.begin(), coins.end()); }
void Coins::setName(std::string s) { name = name + "_" + s; }

//두 코인 집합간 balance 호출
int balance(Coins A, Coins B) {
	A.coins.push_back(EXITFLAG); B.coins.push_back(EXITFLAG);
	int r = balance(&A.coins[0], &B.coins[0]);
	A.coins.pop_back(); B.coins.pop_back();
	return r;
}

//두 코인 집합 중 수가 더 적은 코인 집합의 갯수에 맞추어 동일한 양만 꺼내 balance 호출
int balanceWithSameAmount(Coins& A, Coins& B) {
	if (A.empty() || B.empty()) return ERROR;
	int size = (A.size() > B.size()) ? B.size() : A.size(); //두 집합 중 작은 집합의 크기
	return balance(A.get(size), B.get(size));
}

//두 코인 집합 중 단 1개만 꺼내서 비교
int balanceOnlyOneElement(Coins& A, Coins& B) {
	if (A.empty() || B.empty()) return ERROR;
	return balance(A.get(1), B.get(1));
}

//중복 코인이 발생할 수 있으니 fetch함수와 같이 쓰는 것을 강하게 권고
Coins& Coins::operator+=(const Coins& ref) {
	for (auto i = ref.coins.begin(); i != ref.coins.end(); i++)
		coins.push_back(*i);
	sort();
	return *this;
}
Coins Coins::operator+(const Coins& ref) { return Coins(*this)+=ref; }
std::ostream& operator<<(std::ostream& os, const Coins& ref) {
	ref.__printName();
	os << "[ ";
	for (auto i = ref.coins.begin(); i != ref.coins.end(); i++)
		if (i != ref.coins.end() - 1) os << *i << ", ";
		else os << *i;
	os << " ]";
	return os;
}
