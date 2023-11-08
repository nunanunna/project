#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Data {
    public:
    string date, time, cause, speed, direction, carType;
    int number;
};

class DataManager : public Data {
public:
    void addData(Data data) {
        // csv 파일에 데이터 추가
        // data_insert.cpp에 임시작성
    }

    void deleteData(int number) {
        // csv 파일에서 데이터 삭제
        // data_delete.cpp에 임시작성
    }

    void viewData(string key, string value) {
        // csv 파일에서 데이터 확인
        // data_view.cpp에 임시작성
    }
};

void displayMenu() {
    cout << "1. 데이터 추가" << endl;
    cout << "2. 데이터 삭제" << endl;
    cout << "3. 데이터 확인" << endl;
}

int main() {
    DataManager manager;
    while (true) {
        displayMenu();
        int menu;
        cin >> menu;

        if (menu == 1) {
            Data data;
            cout << "날짜를 입력하세요: ";
            cin >> data.date;
            cout << "시간을 입력하세요: ";
            cin >> data.time;
            cout << "순번을 입력하세요: ";
            cin >> data.number;
            cout << "원인을 입력하세요: ";
            cin >> data.cause;
            cout << "속도를 입력하세요: ";
            cin >> data.speed;
            cout << "방향을 입력하세요: ";
            cin >> data.direction;
            cout << "차종을 입력하세요: ";
            cin >> data.carType;

            manager.addData(data);
        }
        else if (menu == 2) {
            int number;
            cout << "삭제할 데이터의 순번을 입력하세요: ";
            cin >> number;

            manager.deleteData(number);
        }
        else if (menu == 3) {
            string key, value;
            cout << "확인할 데이터의 키(날짜, 순번, 방향, 차종 중 하나)를 입력하세요: ";
            cin >> key;
            cout << "확인할 데이터의 값을 입력하세요: ";
            cin >> value;

            manager.viewData(key, value);
        }
        else {
            cout << "잘못된 입력입니다. 다시 시도해주세요." << endl;
        }
    }

    return 0;
}
