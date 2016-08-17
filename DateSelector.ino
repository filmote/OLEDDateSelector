// -------------------------------------------------------------------------------------------------------
// Display the date selector dialogue.  
//
// This routine accepts an entry parameter which represents the starting date.  This will be highlighted
// in inverse when visible.  Returns a time_t construct with the selected date.

time_t inputDate(time_t dateOrig) {

  status = STATUS_DAY_SELECTOR_INIT;
  
  #if defined(DEBUG) 
    Serial.println("  ");
    Serial.println("inputDate(dateOrig)");
    Serial.println("  dateOrig = " + String(year(dateOrig)) + "-" + String(month(dateOrig)) + "-" + String(day(dateOrig)));
  #endif
  
  Selection selection; 
  selection.dateOrig = dateOrig;
  selection.dateSel = dateOrig;
  selection.highlightMode = CAL_HIGHLIGHT_MODE_BODY;


  while (status == STATUS_DAY_SELECTOR_INIT) {

    if (status == STATUS_DAY_SELECTOR_INIT)        { status = init_day_selector(selection); }
    if (status == STATUS_EXIT_SELECT)              { return selection.dateSel; }
    if (status == STATUS_EXIT_CANCEL)              { return dateOrig; }

  }

}

  
// -------------------------------------------------------------------------------------------------------
// Determine the number of days in the nominated month ..

int daysInMonth(time_t timeT) {

  int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
  return (month(timeT) == CAL_FEBRUARY ? (year(timeT)%4  == 0 ? (year(timeT)%100 != 0 ? 29 : (year(timeT)%400 == 0 ? 29 : 28)) : 28) : days[month(timeT) - 1]);

}


// -------------------------------------------------------------------------------------------------------
// Copy a selection structure ..

Selection copySelection(Selection selection) {

    Selection newSelection;
    newSelection.dateSel = selection.dateSel;
    newSelection.dateOrig = selection.dateOrig;
    newSelection.highlightMode = selection.highlightMode;  

    return newSelection;
    
}


// -------------------------------------------------------------------------------------------------------
// Calculate a timestamp representing the first day in the month ..

time_t firstDayOfMonth(time_t timeT) {

  tmElements_t tm;
  tm.Hour = hour(timeT);
  tm.Minute = minute(timeT);
  tm.Second = second(timeT);
  tm.Day = 1;
  tm.Month = month(timeT);
  tm.Year = year(timeT) - 1970;

  return makeTime(tm);

}

// -------------------------------------------------------------------------------------------------------
// Calculate a timestamp representing the last day in the month ..

time_t lastDayOfMonth(time_t timeT) {

  tmElements_t tm;
  tm.Hour = hour(timeT);
  tm.Minute = minute(timeT);
  tm.Second = second(timeT);
  tm.Day = daysInMonth(timeT);
  tm.Month = month(timeT);
  tm.Year = year(timeT) - 1970;

  return makeTime(tm);

}


// -------------------------------------------------------------------------------------------------------
// Calculate a timestamp representing the first month in the year ..

time_t firstMonthOfYear(time_t timeT) {

  tmElements_t tm;
  tm.Hour = hour(timeT);
  tm.Minute = minute(timeT);
  tm.Second = second(timeT);
  tm.Day = day(timeT);
  tm.Month = 1;
  tm.Year = year(timeT) - 1970;

  return makeTime(tm);

}


// -------------------------------------------------------------------------------------------------------
// Calculate a timestamp representing the last month in the year ..

time_t lastMonthOfYear(time_t timeT) {

  tmElements_t tm;
  tm.Hour = hour(timeT);
  tm.Minute = minute(timeT);
  tm.Second = second(timeT);
  tm.Day = day(timeT);
  tm.Month = 12;
  tm.Year = year(timeT) - 1970;

  return makeTime(tm);

}


// -------------------------------------------------------------------------------------------------------
// Add / subtract a day to the supplied timestamp.  Note it does not handle going over a month-end!

time_t addDays(time_t timeT, int days) {

//  return adjustTime(time_t, (days * 24 * 60 * 60));

  tmElements_t tm;
  tm.Hour = hour(timeT);
  tm.Minute = minute(timeT);
  tm.Second = second(timeT);
  tm.Day = day(timeT) + days;
  tm.Month = month(timeT);
  tm.Year = year(timeT) - 1970;

  return makeTime(tm);

}


// -------------------------------------------------------------------------------------------------------
// Calculate a timestamp representing the first day in the month ..

time_t addMonths(time_t timeT, int months) {

  tmElements_t tm;

  tm.Hour = hour(timeT);
  tm.Minute = minute(timeT);
  tm.Second = second(timeT);
  tm.Day = day(timeT);
  tm.Month = month(timeT) + (months % 12);
  tm.Year = year(timeT) - 1970 + (months / 12);

  return makeTime(tm);

}


// -------------------------------------------------------------------------------------------------------
// Calculate a timestamp representing the first day in the month ..

time_t addYears(time_t timeT, int years) {

  tmElements_t tm;
  tm.Hour = hour(timeT);
  tm.Minute = minute(timeT);
  tm.Second = second(timeT);
  tm.Day = day(timeT);
  tm.Month = month(timeT);
  tm.Year = year(timeT) - 1970 + years;

  return makeTime(tm);

}


// -------------------------------------------------------------------------------------------------------
// Calculate a timestamp representing the first day in the month ..

time_t setYear(time_t timeT, int year) {

  tmElements_t tm;
  tm.Hour = hour(timeT);
  tm.Minute = minute(timeT);
  tm.Second = second(timeT);
  tm.Day = day(timeT);
  tm.Month = month(timeT);
  tm.Year = year - 1970;

  return makeTime(tm);

}

