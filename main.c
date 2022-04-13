#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

// This program uses the Gregorian calendar to test the validity
//   of dates between the years 1589 and 2999, calculate the day
//   of the week of valid dates, and print out calendars


/////////////////////////////////////////////////////////////////////////////
// PROVIDED FUNCTION and CONSTANTS (DO NOT CHANGE)

// print_header(year, month) prints the calendar "header" 
//   for the given year/month
// notes: if month is invalid, no month line is printed
//        header is aligned for 4-digit years
// effects: produces output
void print_header(const int year, const int month) {
  if (month == 1) {
    printf("====January %d====\n", year);
  } else if (month == 2) {
    printf("===February %d====\n", year);
  } else if (month == 3) {
    printf("=====March %d=====\n", year);
  } else if (month == 4) {
    printf("=====April %d=====\n", year);
  } else if (month == 5) {
    printf("======May %d======\n", year);
  } else if (month == 6) {
    printf("=====June %d======\n", year);
  } else if (month == 7) {
    printf("=====July %d======\n", year);
  }else if (month == 8) {
    printf("====August %d=====\n", year);
  } else if (month == 9) {
    printf("===September %d===\n", year);
  } else if (month == 10) {
    printf("====October %d====\n", year);
  } else if (month == 11) {
    printf("===November %d====\n", year);
  } else if (month == 12) {
    printf("===December %d====\n", year);
  }
  printf("Su Mo Tu We Th Fr Sa\n");
}

// you may use these constants in your code if you wish
// it is not a requirement, but it is strongly recommended
// you may not change their values

const int SUNDAY = 0;
const int base_year = 1589;
const int base_year_jan_1 = SUNDAY;
const int max_year = 2999;
/////////////////////////////////////////////////////////////////////////////

// leap_year (year) returns true if a year is a leap year within
//   Gregorian calendar, and false otherwise
bool leap_year(int year) {
  if (year % 400 == 0) {
    return true;
  } else if (year % 100 == 0) {
    return false;
  } else if (year % 4 == 0) {
    return true;
  } 
  return false;
}

// valid_date (year, month, day) returns true if the given date
//   is valid and between the years 1589 and 2999 (inclusive) and //   is valid, and returns false otherwise
bool valid_date(int year, int month, int day) {
  if (year >= base_year && year <= max_year) {
    if (month >= 1 && month <= 12) {
      if (month == 2) {
       if (leap_year(year)) {
         if (day >= 1 && day <= 29) {
           return true;
         }
         return false;
       } else {
         if (day >= 1 && day <= 28) {
           return true;
         } 
         return false;
       }
      } else if (month == 9 || month == 4 || month == 6 || month == 11) {
        if (day >= 1 && day <= 30) {
          return true;
        } 
        return false;
      } else {
        if (day >= 1 && day <= 31) {
          return true;
        } 
        return false;
      }
    }
    return false;
  }
  return false;
}

// num_days (year, month) returns the number of days in the month
//   the given year according to the Gregorian calendar
// requires: year and month are valid (not asserted)
int num_days(int year, int month) {
  if (month == 2) {
    if (leap_year(year)) {
      return 29;
    }
    return 28;
  } else if (month == 9 || month == 4 || month == 6 || month == 11) {
    return 30;
  }
  return 31;
}

// day_of_the_week (year, month, day) returns the day of the week
//   of a valid date within the Gregorian calendar between the
//   years 1589 and 2999
// requires: assert(valid_date(year, month, day))
int day_of_the_week(int year, int month, int day) {
  // temporary result to pass simple tests
  assert(valid_date(year, month, day));
  
  int total_days = 0;
  int current_year = base_year;
  while (current_year <= year) {
    int current_month = 1;
    while (current_month <= 12) {
      if (current_year == year && current_month == month) {
        break;
      } else {
      total_days += num_days(current_year, current_month);
      ++current_month;
      }
    }
    ++current_year;
  }
  
  total_days += day;
  int week_day = (total_days % 7);
  if (week_day == 0) {
    return 6;
  } else {
    return week_day - 1;
  }
}

// print_calendar (year, month) prints a "pretty" calendar of the
//   month in the given year
// requires: year and month is valid
// effects: produces output
void print_calendar(int year, int month) {
  assert(valid_date(year, month, 1));
  
  print_header(year, month);
  
  int spaces = day_of_the_week(year, month, 1) * 3;
  while (spaces > 0) {
    printf(" ");
    --spaces;
  }
      
  int current_day = 1;
  int number_of_days = num_days(year, month);
  while (current_day <= number_of_days) {
    printf("%2d", current_day);
    ++current_day;

    if (current_day > number_of_days) {
      break;
    } else if (!day_of_the_week(year, month, current_day)) {
      printf("\n");
    } else {
      printf(" ");
    }
  }
  printf("\n");
  return;
}


void assertion_tests(void) {
  // Due date is a valid date and a Friday
  assert(valid_date(2021, 10, 1));
  assert(day_of_the_week(2021, 10, 1) == 5);
  
  // Add your own assertion-based tests below
  assert(valid_date(1588, 12, 31) == false);
  assert(valid_date(3000, 12, 1) == false);
  assert(valid_date(1400, 1, 1) == false);
  assert(valid_date(4000, 5, 8) == false);
  assert(valid_date(2999, 0, 25) == false);
  assert(valid_date(2999, 13, 5) == false);
  assert(valid_date(1900, 2, 29) == false);
  assert(valid_date(2000, 9, 31) == false);
  
  assert(valid_date(2999, 12, 31));
  assert(valid_date(1589, 1, 1));
  assert(valid_date(1600, 2, 29));
  assert(valid_date(1884, 2, 29));
  assert(valid_date(1620, 2, 29));
  assert(valid_date(1589, 1, 1));
  assert(valid_date(2000, 2, 28));
  assert(valid_date(1589, 1, 29));
  
  assert(day_of_the_week(1589, 1, 1) == 0);
  assert(day_of_the_week(1589, 12, 31) == 0);
  assert(day_of_the_week(1589, 7, 1) == 6);
  assert(day_of_the_week(2999, 12, 31) == 2);
  assert(day_of_the_week(2021, 8, 4) == 3);
  assert(day_of_the_week(2021, 11, 2) == 2);
  
  assert(day_of_the_week(2021, 6, 7) == 1);
  assert(day_of_the_week(1974, 3, 7) == 4);
  assert(day_of_the_week(2539, 9, 4) == 5);
}

///////////////////////////////////////////////////////
// You do not need to modify the rest of the program //
///////////////////////////////////////////////////////

int main(void) {
  assertion_tests();
  int year = 0;
  char slash = '/';
  int month = 0;

  while (true) {
    printf("Insert date formatted like YYYY/DD: \n");
    int read_year = scanf("%d", &year);
    char read_slash = scanf("%c", &slash);
    int read_month = scanf("%d", &month);
    
    if (read_year != 1 || read_slash != 1 || slash != '/' || read_month != 1) {
      printf("Invalid date format. Try again! \n");
      continue;
    } else if (month < 1 || month > 12 || year < 1589 || year > 2999) {
      printf("Invalid date. Try again! \n");
      continue;
    }
    break;
  }
  print_calendar(year, month);
}
