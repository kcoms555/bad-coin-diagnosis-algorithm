#include <iostream>
#include "Coins.h"
#include <cstring>
using namespace std;
int Coins::num = 0;

//Coins() 은 텅빈 코인 집합 생성
//Coins(0,99) 는 0부터 99 까지의 인덱스를 가진 코인 집합 생성
Coins heavyCoins, lightCoins, tmp1, tmp2, tmp3, unknownCoins(0,99);

void Algorithm_Step();
void Algorithm_Merge();
void Algorithm_Mergev2();
void pickoutNonDominantCoin(Coins& target, bool isHeavyCoinsDominant);

int main(int argc, char * argv[]) {
	if(argc != 3){
		printf("usage : ./main [initialize operand] [merge|step|merge2]");
		exit(1);
	}
	initialize(atoi(argv[1]));
	if(strcmp(argv[2], "step") == 0) Algorithm_Step();
	if(strcmp(argv[2], "merge") == 0) Algorithm_Merge();
	if(strcmp(argv[2], "merge2") == 0) Algorithm_Mergev2();
	cout << "정상[" << heavyCoins.size() << "] : " << heavyCoins << endl;
	cout << "비정상[" << lightCoins.size() << "] : " << lightCoins << endl;
	balance(lightCoins, unknownCoins);
	return 0;
}

//1부터 시작해 2의 지수 수만큼 양쪽에 매달아 계속 저울질 하여 분류하는 알고리즘
void Algorithm_Step() {
	unsigned int stepSize = 1;
	while (1) {
		if (unknownCoins.empty())
			if (tmp3.empty()) break;
			else {
				unknownCoins += tmp3.fetch(ALL);
				stepSize *= 2;
			}
		bool isBalanceableWithStep = (unknownCoins.size() >= stepSize * 2);
		bool isTmp2HeavyCoins;
		if (isBalanceableWithStep) { //두 쌍으로 나누어 저울질 할 수 있을 때
			tmp1 += unknownCoins.fetch(stepSize);
			tmp2 += unknownCoins.fetch(stepSize);
		}
		else { //두 쌍으로 나누어 저울질 못할 때
			cout << "두 쌍으로 나누어 저울질을 못합니다 한쪽은 분류된 곳에서 1개만 빌려와 1개만 저울질 합니다" << endl;
			tmp1 += unknownCoins.fetch(stepSize);
			tmp2 += (isTmp2HeavyCoins = (heavyCoins.size() >= 1)) ? heavyCoins.fetch(1) : lightCoins.fetch(1);
		}
		switch (balanceOnlyOneElement(tmp1, tmp2)) {
		case EQUAL:
			if (isBalanceableWithStep) tmp3 += tmp1.fetch(ALL) + tmp2.fetch(ALL);
			else	if (isTmp2HeavyCoins) heavyCoins += tmp1.fetch(ALL) + tmp2.fetch(ALL);
			else lightCoins += tmp1.fetch(ALL) + tmp2.fetch(ALL);
			break;
		case SMALL:
			heavyCoins += tmp2.fetch(ALL);
			lightCoins += tmp1.fetch(ALL);
			break;
		case LARGE:
			heavyCoins += tmp1.fetch(ALL);
			lightCoins += tmp2.fetch(ALL);
			break;
		default:
			cout << "error!" << endl;
		}
	}
}

//1부터 시작해 동일한 개수 만큼 양쪽에 매달아 양쪽 저울질의 결과가 같으면 한쪽에 몰아넣는 알고리즘
void Algorithm_Merge() {
	unsigned int stepSize = 1;
	bool lastIterationFlag = false;
	bool isTmp2HeavyCoins;
	while (1) {
		if (tmp1.empty()) {
			stepSize = 1;
			tmp1 += unknownCoins.fetch(stepSize);
		}
		if (unknownCoins.empty())
			if (tmp1.empty()) break;
			else {
				lastIterationFlag = true;
				tmp2 += (isTmp2HeavyCoins = (heavyCoins.size() >= 1)) ? heavyCoins.fetch(1) : lightCoins.fetch(1);
			}
		else tmp2 += unknownCoins.fetch(stepSize);

		switch (balanceWithSameAmount(tmp1, tmp2)) {
		case EQUAL:
			tmp1 += tmp2.fetch(ALL);
			stepSize *= 2;
			if (lastIterationFlag)	if (isTmp2HeavyCoins) heavyCoins += tmp1.fetch(ALL);
			else lightCoins += tmp1.fetch(ALL);
			break;
		case SMALL:
			lightCoins += tmp1.fetch(ALL);
			if (stepSize == 1 || lastIterationFlag)	heavyCoins += tmp2.fetch(ALL);
			else									unknownCoins += tmp2.fetch(ALL);
			break;
		case LARGE:
			heavyCoins += tmp1.fetch(ALL);
			if (stepSize == 1 || lastIterationFlag)	lightCoins += tmp2.fetch(ALL);
			else									unknownCoins += tmp2.fetch(ALL);
			break;
		default:
			cout << "error!" << endl;
		}
	}
}
void pickoutNonDominantCoin(Coins& target, bool isHeavyCoinsDominant){
	Coins& dominantCoins = (isHeavyCoinsDominant) ? heavyCoins : lightCoins;
	Coins& nonDominantCoins = (isHeavyCoinsDominant) ? lightCoins : heavyCoins;

	cout<<"PICK"<<endl;
	cout<<target<<endl;
	bool found = false;
	Coins tmpUnknownCoins;
	int fetchsize = (target.size()>2) ? target.size()/2 : 1;
	tmpUnknownCoins += target.fetch(fetchsize);
	cout<<tmpUnknownCoins<<endl;
	switch (balanceWithSameAmount(tmpUnknownCoins, dominantCoins)){
		case EQUAL:
			dominantCoins += tmpUnknownCoins.fetch(ALL);
			if(fetchsize == 1 && target.size() == 1) nonDominantCoins += target.fetch(ALL); //pickoutNonDominantCoin는 최소 1개 이상의 다른 동전이 섞여있다는 것을 알고 있는 상태에서 진행하기에 tmpUnknownCoins가 DominantCoin과 동일하다고 떴고 fetchsize가 1이라면 target에 남아있는 1개의 or 0개의 코인은 nonDominant와 같은 종류일 수 밖에 없다.
			break;
		case SMALL:
			if(tmpUnknownCoins.size() == 1) lightCoins += tmpUnknownCoins.fetch(ALL);
			else pickoutNonDominantCoin(tmpUnknownCoins, isHeavyCoinsDominant); //tmpUnknownCoins에 1개 이상의 다른 동전이 섞여있다는 것을 알게 되었으니 이 해당 코인에게 다시 pickoutNonDominantCoin을 호출한다.
			found = true;
			break;
		case LARGE:
			if(tmpUnknownCoins.size() == 1) heavyCoins += tmpUnknownCoins.fetch(ALL);
			else pickoutNonDominantCoin(tmpUnknownCoins, isHeavyCoinsDominant); //tmpUnknownCoins에 1개 이상의 다른 동전이 섞여있다는 것을 알게 되었으니 이 해당 코인에게 다시 pickoutNonDominantCoin을 호출한다.
			found = true;
			break;
		default:
			cout<<tmpUnknownCoins<<endl;
			cout<<dominantCoins<<endl;
			printf("pickout Error!");
			exit(1);
	}
	if(target.size()>0){
		if(found){ //만약 1개이상 발견되었다면 target에 남아있는 것들은 dominant와 동일할 가능성이 높다.
			switch (balanceWithSameAmount(target, dominantCoins)){
				case EQUAL:
					dominantCoins += target.fetch(ALL);
					break;
				case SMALL:
				case LARGE:
					pickoutNonDominantCoin(target, isHeavyCoinsDominant);
					break;
				default:
					cout<<tmpUnknownCoins<<endl;
					cout<<dominantCoins<<endl;
					printf("pickout Error2!");
					exit(1);
			}
		} else{
			pickoutNonDominantCoin(target, isHeavyCoinsDominant);
		}
	}
	cout<<"PICKEND"<<endl;
}
void Algorithm_Mergev2() {
	unsigned int stepSize = 1;
	bool lastIterationFlag = false;
	bool isTmp2HeavyCoins;
	while (1) {
		if (tmp1.empty()) {
			stepSize = 1;
			tmp1 += unknownCoins.fetch(stepSize);
		}
		if (unknownCoins.empty())
			if (tmp1.empty()) break;
			else {
				lastIterationFlag = true;
				tmp2 += (isTmp2HeavyCoins = (heavyCoins.size() >= 1)) ? heavyCoins.fetch(1) : lightCoins.fetch(1);
			}
		else tmp2 += unknownCoins.fetch(stepSize);

		switch (balanceWithSameAmount(tmp1, tmp2)) {
		case EQUAL:
			tmp1 += tmp2.fetch(ALL);
			stepSize *= 2;
			if (lastIterationFlag)	if (isTmp2HeavyCoins) heavyCoins += tmp1.fetch(ALL);
									else lightCoins += tmp1.fetch(ALL);
			break;
		case SMALL:
			lightCoins += tmp1.fetch(ALL);
			if (stepSize == 1 || lastIterationFlag)	heavyCoins += tmp2.fetch(ALL);
			else	{
				//임시로 stepSize가 16일때로 분기를 나눔
				//if(stepSize < 16) unknownCoins += tmp2.fetch(ALL);
				//else pickoutNonDominantCoin(tmp2, false);
				pickoutNonDominantCoin(tmp2, false);
			}
			break;
		case LARGE:
			heavyCoins += tmp1.fetch(ALL);
			if (stepSize == 1 || lastIterationFlag)	lightCoins += tmp2.fetch(ALL);
			else	{
				//임시로 stepSize가 16일때로 분기를 나눔
				//if(stepSize < 16) unknownCoins += tmp2.fetch(ALL);
				//else pickoutNonDominantCoin(tmp2, true);
				pickoutNonDominantCoin(tmp2, true);
			}
			break;
		default:
			cout << "error!" << endl;
		}
	}
}
