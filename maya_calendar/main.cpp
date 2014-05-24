#include <iostream>
#include <map>
#include <stdio.h>
#include <string>

using namespace std;

#define TZOLKIN_DAYS_NB         13
#define TZOLKIN_DAYS_NAME_NB    20
#define HAAB_MONTH_NB           19
#define HAAB_DAYS_NB            20
#define ROUND_CALENDAR_LENGTH   18980
#define A                       144000
#define B                       7200
#define C                       360
#define D                       20

static string tzolkinDayNames[TZOLKIN_DAYS_NAME_NB] = {"Imix", "Ik", "Akbal", "Kan", "Chikchan", "Kimi",
  "Manik", "Lamat", "Muluk", "Ok", "Chuen", "Eb", "Ben", "Ix", "Men", "Kib",
  "Kaban", "Etznab", "Kawak", "Ajaw"};
map<string, int> dayNames;
static string haabMonthNames[HAAB_MONTH_NB] = {"Pohp", "Wo", "Sip", "Zotz", "Sek", "Xul",
  "Yaxkin", "Mol", "Chen", "Yax", "Sak", "Keh", "Mak", "Kankin", "Muan",
  "Pax", "Kayab", "Kumku", "Wayeb"};
map<string, int> monthNames;

static void find_dates(int tDayNumber, int tDay, int hDayNumber, int hMonth) {
  // Long Date 8.0.0.0.0 corresponds to 9.Ajaw 3.Sip
  int startTDayNumber = 9;
  int startTDay = dayNames["Ajaw"];
  int startHDay = 3;
  int startHMonth = monthNames["Sip"];
  int count = 0;
  // We want to search for the first date after this one which corresponds to
  // our tzolkin dayNumber.dayName and haab dayNumber.monthName.
  // Then, to find all dates until 10.0.0.0.0, we only have to add the
  // round_calendar_length and check that the date is before 10.0.0.0.0
  while ((startTDayNumber != tDayNumber || startTDay != tDay ||
      startHDay != hDayNumber || startHMonth != hMonth) &&
      count < ROUND_CALENDAR_LENGTH) {
    count += 1;
    (startTDayNumber == TZOLKIN_DAYS_NB) ? startTDayNumber = 1 : startTDayNumber += 1;
    (startTDay == TZOLKIN_DAYS_NAME_NB) ? startTDay = 1 : startTDay += 1;
    if (startHMonth == HAAB_MONTH_NB && startHDay == 5) {
      startHDay = 1;
      startHMonth = 1;
    }
    else if (startHDay == HAAB_DAYS_NB) {
      startHDay = 1;
      startHMonth += 1;
    }
    else
      startHDay += 1;
  }

  // If we don't find any date, there is no solution
  if (count == ROUND_CALENDAR_LENGTH) {
    cout << "NO SOLUTION" << endl;
    return;
  }

  // Else we search for all solution and we display them as a.b.c.d.e with :
  // count = a*144000days + b *7200days + c * 360days + d * 20days + e * days
  int a, b, c, d, e;
  count += 8 * A;
  while (count < 10 * A) {
    a = count / A;
    e = count - a * A;
    b = e / B;
    e = e - b * B;
    c = e / C;
    e = e - c * C;
    d = e / D;
    e = e - d * D;
    cout << a << "." << b << "." << c << "." << d << "." << e << endl;
    count += ROUND_CALENDAR_LENGTH;
  }
}

int main() {
  int testcases, tzolkinDayNumber, haabDayNumber;
  char tzolkinDay[10], haabMonth[10];
  for (int i = 0; i < TZOLKIN_DAYS_NAME_NB; i++)
    dayNames.insert(make_pair(tzolkinDayNames[i], i + 1));
  for (int i = 0; i < HAAB_MONTH_NB; i++)
    monthNames.insert(make_pair(haabMonthNames[i], i + 1));

  cin >> testcases;
  while (testcases--) {
    scanf("%d.%s %d.%s", &tzolkinDayNumber, tzolkinDay, &haabDayNumber, haabMonth);
    // Find all corresponding dates
    string str = "Ajaw";
    find_dates(tzolkinDayNumber, dayNames[tzolkinDay], haabDayNumber, monthNames[haabMonth]);
    if (testcases)
      cout << endl;
  }
  return 0;
}
