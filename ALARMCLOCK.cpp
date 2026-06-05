#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
using namespace std;
using namespace std::chrono;

const int MAX_ALARM = 10;

class alarm {

private:
	int hour;
	int minute;
	bool isactive;

public:
	alarm();
	void setalarm(int h,int m);
	void displayalarm(int index);
	bool checkalarm(int currenthour,int currentminute);
};

alarm::alarm() {
	 hour = 0;
	 minute = 0;
	 isactive = false;
}

void alarm::setalarm(int h, int m) {
	 hour = h;
	 minute = m;
	 isactive = true;
}
void alarm::displayalarm(int index) {
	if (isactive) {
		cout << " ALARM " << index + 1 << ":";
		if (hour < 10) cout << "0";
		cout << hour << ":";
		if (minute < 10) cout << "0";
		cout << minute << endl;
	}
}

bool alarm::checkalarm(int currenthour, int currentminute) {
	if (isactive && hour==currenthour && minute==currentminute) {
		return true;
	}
	return false;
}


int main() {
	alarm alarms[MAX_ALARM];
	int alarmcount = 0;

	while (true) {
		cout << "/n............alarm clock menu............../n" << endl;
		cout << "1.set alarm" << endl;
		cout << "2.display alarm" << endl;
		cout << "3.alarm started(check alarm)" << endl;
		cout << "4.delete an alarm" << endl;
		cout << "5.exit" << endl;
		cout << "enter your choice" << endl;

		int choice;
		cin >> choice;

		switch(choice){
		case 1: {
			int h, m;
			cout << "enter hour"<< endl;
			cin >> h;
			
			cout << "enter minute"<< endl;
			cin >> m;

			if (h < 0 || h>24 || m < 0 || m>59) {
				cout << "invalid input . try again";
				break;
			}
				

			if (alarmcount < MAX_ALARM) {
				alarms[alarmcount].setalarm(h, m);
				alarmcount++;
				cout << "alarm set successfully" << endl;
			}
			else {
				cout << "maximum limit reached" << endl;
			}

			break;
		}
			

		case 2: {
			if (alarmcount == 0)
				cout << "no alarm set" << endl;
			else {
				for (int i = 0; i < alarmcount; i++) {
					alarms[i].displayalarm(i);
				}
			}
			break;
		}
	case 3: {
		
		cout << "starting alarm clock" << endl;
		while (true) {
			time_t now = time(0);
			tm ltm;
			localtime_s(&ltm, &now);
			int currenthour = ltm.tm_hour;
			int currentminute = ltm.tm_min;

			for (int i = 0; i < alarmcount; i++) {
				if (alarms[i].checkalarm(currenthour, currentminute)) {
					cout << "alarm " << i + 1 << " is ringing!!!!" << endl;

					cout << "snooze or dismiss?" << endl;
					char c = ' ';//s for snooze,d for dismiss
					cin >> c;
					if (c == 's' || c == 'S') {
						int snoozeduration;
						cout << "for how much minute you want to snoooze alarm?" << endl;
						cin >> snoozeduration;

						int newminute = currentminute + snoozeduration;
						int newhour = currenthour + (newminute / 60);
						newminute %= 60;
						newhour %= 24;

						alarms[i].setalarm(newhour, newminute);

						cout << "alarm snooze for " << snoozeduration <<
							". it will ring at:" << endl;
						if (newhour < 10)
							cout << "0";
						cout << newhour <<":";
						if (newminute < 10)
							cout << "0";
						cout << newminute << endl;
					}

					else if (c == 'd' || c == 'D') {
						cout << " alarm dismissed";
					}

					else cout << "alarm continue to ring";
				}
			}
			this_thread::sleep_for(seconds(60));
		}
		break;
		}

	case 4: {
		if (alarmcount == 0)
			cout << "no alarm to delete";
		break;
		for (int i = 0; i < alarmcount; i++) {
			alarms[i].displayalarm(i);
		}
		int indexremove;
		cout << "enter the index to remove" << endl;
		cin >> indexremove;
		if (indexremove<1 || indexremove>alarmcount)
			cout << "invalid alarm number" << endl;
		else {
			alarms[indexremove - 1] = alarms[alarmcount - 1];
			alarmcount--;
			cout << "alarm deleted successfully!";
		}
		break;
	}
	
	case 5: {
		cout << "good bye";
		return 0;

	}
		}
	}
	
}
