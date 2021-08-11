// CommandLineCalendar.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

// via http://truelogic.org/wordpress/2015/09/12/generate-yearly-calendar-in-c/

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Cal {

public:
	Cal(void);
	void getYearly(int year);

protected:
	int mYear;
	string mMonths[13];
	string mWeekDays[8];
	int mDays[13];
	int firstDayOfMonth(int month, int year);

	static const int YEAR_ROW_WIDTH = 35; // width of a row in yearly display

};

/**
 * Constructor - initialize data
 *
 */
Cal::Cal(void) {
	mMonths[0] = "";	// month starts from 1
	mMonths[1] = "January";
	mMonths[2] = "February";
	mMonths[3] = "March";
	mMonths[4] = "April";
	mMonths[5] = "May";
	mMonths[6] = "June";
	mMonths[7] = "July";
	mMonths[8] = "August";
	mMonths[9] = "September";
	mMonths[10] = "October";
	mMonths[11] = "November";
	mMonths[12] = "December";

	mDays[0] = 0;
	mDays[1] = 31;
	mDays[2] = 28;
	mDays[3] = 31;
	mDays[4] = 30;
	mDays[5] = 31;
	mDays[6] = 30;
	mDays[7] = 31;
	mDays[8] = 31;
	mDays[9] = 30;
	mDays[10] = 31;
	mDays[11] = 30;
	mDays[12] = 31;

	mWeekDays[0] = "";
	mWeekDays[1] = "Sun";
	mWeekDays[2] = "Mon";
	mWeekDays[3] = "Tue";
	mWeekDays[4] = "Wed";
	mWeekDays[5] = "Thu";
	mWeekDays[6] = "Fri";
	mWeekDays[7] = "Sat";


}

/**
 * Using a standard c++ algorithm to find day of week for a date
 * Parameters:
 *  month - month number
 *  year - year
 * Returns:
 *	dow = day of week, sun =0, mon=1 etc.
 */
int Cal::firstDayOfMonth(int month, int year) {
	int dow = 0;
	int day = 1;

	int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	year -= month < 3;
	dow = (year + year / 4 - year / 100 + year / 400 + t[month - 1] + day) % 7;

	return dow;
}

/**
 * Print yearly calendar
 * Parameters:
 *  year - year to print for
 */
void Cal::getYearly(int year) {

	mYear = year;
	if (mYear < 1900 || mYear > 2100) {
		std::cout << "Year must be between 1900 and 2100" << endl;
		return;
	}

	// check for leap year
	if ((mYear % 4 == 0 && mYear % 100 != 0) || (mYear % 400 == 0))
		mDays[2] = 29;

	int leftPadding = 0;
	for (int i = 1; i <= 12; i++) {

		// center month label
		leftPadding = (YEAR_ROW_WIDTH - mMonths[i].size()) / 2;
		for (int x = 0; x < leftPadding; x++) {
			cout << "  ";
		}
		cout << mMonths[i] << endl;

		//print weekday labels
		for (int j = 1; j <= 7; j++) {
			cout << setw(5) << mWeekDays[j] << setw(2) << "   ";
		}
		cout << endl;

		// print days
		int daysPrinted = 0;
		for (int j = 1; j <= mDays[i]; j++) {
			// move display head to the correct day of week for 1st
			if (j == 1) {
				int dow = firstDayOfMonth(i, mYear);
				for (int spaces = 0; spaces < dow; spaces++) {
					cout << setw(5) << " " << setw(2) << "   ";
					daysPrinted++;
				}
			}

			cout << setw(5) << j << setw(2) << "   ";
			daysPrinted++;
			if (daysPrinted % 7 == 0) {
				cout << endl;
				daysPrinted = 0;
			}
		}
		cout << endl << setw(35) << "----------------------------------------------------------------" << endl;
	}
}

int main()
{
	Cal cal;
	cal.getYearly(2015);
}
