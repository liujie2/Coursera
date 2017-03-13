#include <iostream>
#include <iomanip>
using namespace std;
const int WARRIOR_NUM = 5;

class Headquarter;
class Warrior {
private:
    Headquarter * pHeadquarter;
    int kindNo; //??????? 0 dragon 1 ninja 2 iceman 3 lion 4 wolf
    int no;
public:
    static char * product_s[WARRIOR_NUM];
    static int initialLifeValue[WARRIOR_NUM];
    Warrior(Headquarter * p, int no_, int kindNo_);
    void PrintResult(int nTime);
};

class Headquarter {
private:
    int totalLifeValue;
    bool stopped;
    int totalWarriorNum;
    int Color_C;
    int curMakingSeqIdx; //??????????????????
    int warriorNum[WARRIOR_NUM]; //?????????
    Warrior * pWarriors[1000];
public:
    friend class Warrior;
    static int makingSeq[2][WARRIOR_NUM]; //??????
    void Init(int color_, int lifevalue_);
    ~Headquarter();
    int Produce(int nTime);
    char * GetColor();
    static char * color[2];
};

Warrior::Warrior(Headquarter * p, int no_, int kindNo_) {
    no = no_;
    kindNo = kindNo_;
    pHeadquarter = p;
}

void Warrior::PrintResult(int nTime) {
    cout << setfill('0') << setw(3) << nTime << " ";
    cout << pHeadquarter->GetColor() << " " << product_s[kindNo] << " " << no;
    cout << " born with strength " << initialLifeValue[kindNo] << ",";
    cout << pHeadquarter->warriorNum[kindNo] << " " << product_s[kindNo];
    cout << " in " << pHeadquarter->GetColor() << " headquarter" << endl;
}

void Headquarter::Init(int color_, int lifevalue_) {
    Color_C = color_;
    totalLifeValue = lifevalue_;
    totalWarriorNum = 0;
    stopped = false;
    curMakingSeqIdx = 0;
    for (int i = 0; i < WARRIOR_NUM; i++)
        warriorNum[i] = 0;
}

Headquarter::~Headquarter() {
    for (int i = 0; i < totalWarriorNum; i++)
        delete pWarriors[i];
}

int Headquarter::Produce(int nTime) {
    if (stopped)
        return 0;

    int searchingTimes = 0;
    while (Warrior::initialLifeValue[makingSeq[Color_C][curMakingSeqIdx]] > totalLifeValue && searchingTimes < WARRIOR_NUM) {
        curMakingSeqIdx = (curMakingSeqIdx + 1) % WARRIOR_NUM;
        searchingTimes++;
    }

    int kindNo = makingSeq[Color_C][curMakingSeqIdx];

    if (Warrior::initialLifeValue[kindNo] > totalLifeValue) {
        stopped = true;

        cout << setfill('0') << setw(3) << nTime << " ";
        cout << this->GetColor() << " headquarter stops making warriors" << endl;

        return 0;
    }

    //????
    totalLifeValue -= Warrior::initialLifeValue[kindNo];
    curMakingSeqIdx = (curMakingSeqIdx + 1) % WARRIOR_NUM;
    pWarriors[totalWarriorNum] = new Warrior(this, totalWarriorNum + 1, kindNo);
    warriorNum[kindNo]++;
    pWarriors[totalWarriorNum]->PrintResult(nTime);
    totalWarriorNum++;
    return 1;
}

char * Headquarter::GetColor(void) {
    return color[Color_C];
}

char * Warrior::product_s[]{ "dragon", "ninja", "iceman", "lion", "wolf" };
int Warrior::initialLifeValue[WARRIOR_NUM];
int Headquarter::makingSeq[2][WARRIOR_NUM] = { {2,3,4,1,0},{3.0,1,2,4} }; //??????????
char * Headquarter::color[] = { "red", "blue" };

int main() {
    int K, M, casecount = 1;
    Headquarter RedHead, BlueHead;

    cin >> K;

    while (K--) {
        cout << "Case:" << casecount << endl;
        casecount++;

        cin >> M;
        for (int i = 0; i < WARRIOR_NUM; i++)
            cin >> Warrior::initialLifeValue[i];

        RedHead.Init(0, M);
        BlueHead.Init(1, M);
        int nTime = 0;

        while (true) {
            int red = RedHead.Produce(nTime);
            int blue = BlueHead.Produce(nTime);
            if(red == 0 && blue == 0)
                break;
            nTime++;
        }
    }
    return 0;
}