// -------------------------------------------------------------------------------------------------------
//  Initialise day selector ..
//

int init_day_selector(Selection &selection) {

  #if defined(DEBUG) && defined(DEBUG_DAY_SELECTOR)
    Serial.println("  ");
    Serial.println("init_day_selector()");
    Serial.println("  status = " + renderStatus());
    Serial.println("  selection");
    Serial.println("    dateOrig = " + String(year(selection.dateOrig)) + "-" + String(month(selection.dateOrig)) + "-" + String(day(selection.dateOrig)));
    Serial.println("    dateSel = " + String(year(selection.dateSel)) + "-" + String(month(selection.dateSel)) + "-" + String(day(selection.dateSel)));
    Serial.println("    highlightMode = " + renderCalHighlightMode(selection));
  #endif
  
  renderDaySelector(selection);

  status = STATUS_DAY_SELECTOR_LOOP;
  return loop_day_selector(selection);
  
}


// -------------------------------------------------------------------------------------------------------
//  Process user input ..
//

int loop_day_selector(Selection &selection) {
  
  #if defined(DEBUG) && defined(DEBUG_DAY_SELECTOR)
    Serial.println("  ");
    Serial.println("init_day_selector()");
    Serial.println("  status = " + renderStatus());
    Serial.println("  selection");
    Serial.println("    dateOrig = " + String(year(selection.dateOrig)) + "-" + String(month(selection.dateOrig)) + "-" + String(day(selection.dateOrig)));
    Serial.println("    dateSel = " + String(year(selection.dateSel)) + "-" + String(month(selection.dateSel)) + "-" + String(day(selection.dateSel)));
    Serial.println("    highlightMode = " + renderCalHighlightMode(selection));
  #endif
  
  while (status == STATUS_DAY_SELECTOR_LOOP) {


    // Rotation of encoder ..
  
    long newPosition = myEnc.read();
    
    if (abs(newPosition - oldPosition) >= KY040_MINIMUM_RESOLUTION) {

      if (newPosition > oldPosition)          { status = day_selector_scroll_left(selection); }
      if (newPosition < oldPosition)          { status = day_selector_scroll_right(selection); }
  
      oldPosition = newPosition;

    }


    // Software debounce of button press ..

    if (isButtonPressed && millis() - lastUpdateMillis > 50) {

      delay(KY040_DEBOUNCE_DELAY);

      isButtonPressed = false;
      lastUpdateMillis = millis();              status = day_selector_click(selection);

      myEnc.write(0);    
      newPosition = 0;
      oldPosition = 0;

    }
    
    yield();

  }  
  
  #if defined(DEBUG) && defined(DEBUG_DAY_SELECTOR)
    Serial.println("  ");
    Serial.println("loop_day_selector() - Exit");
    Serial.println("  status = " + renderStatus());
  #endif
  
  return status;
  
}

// -------------------------------------------------------------------------------------------------------
//  Encoder turned left ..
//

int day_selector_scroll_left(Selection &selection) {
        
  #if defined(DEBUG) && defined(DEBUG_DAY_SELECTOR)
    Serial.println("  ");
    Serial.println("day_selector_scroll_left()");
  #endif
  
  if (selection.highlightMode == CAL_HIGHLIGHT_MODE_BODY) {

    if (day(selection.dateSel) > 1) {
      selection.dateSel = addDays(selection.dateSel, -1);
    }
    else {
      selection.highlightMode = CAL_HIGHLIGHT_MODE_YEAR;
    }

  } 
  else if (selection.highlightMode == CAL_HIGHLIGHT_MODE_YEAR) {
    selection.highlightMode = CAL_HIGHLIGHT_MODE_MONTH;
  } 
  else if (selection.highlightMode == CAL_HIGHLIGHT_MODE_MONTH) {
    selection.highlightMode = CAL_HIGHLIGHT_MODE_CANCEL;
  } 
  else if (selection.highlightMode == CAL_HIGHLIGHT_MODE_CANCEL) {
    selection.highlightMode = CAL_HIGHLIGHT_MODE_BODY;
    selection.dateSel = lastDayOfMonth(selection.dateSel);
  }

  renderDaySelector(selection);
  return STATUS_DAY_SELECTOR_LOOP;
  
}


// -------------------------------------------------------------------------------------------------------
//  Encoder turned right ..
//
 
int day_selector_scroll_right(Selection &selection) {
        
  #if defined(DEBUG) && defined(DEBUG_DAY_SELECTOR)
    Serial.println("  ");
    Serial.println("day_selector_scroll_right()");
  #endif
  
  if (selection.highlightMode == CAL_HIGHLIGHT_MODE_BODY) {

    if (day(selection.dateSel) < daysInMonth(selection.dateSel)) {

      selection.dateSel = addDays(selection.dateSel, 1);
    
    }
    else {
      
      selection.highlightMode = CAL_HIGHLIGHT_MODE_CANCEL;

    }    

  }
  else if (selection.highlightMode == CAL_HIGHLIGHT_MODE_CANCEL) {
    selection.highlightMode = CAL_HIGHLIGHT_MODE_MONTH;
  } 
  else if (selection.highlightMode == CAL_HIGHLIGHT_MODE_MONTH) {
    selection.highlightMode = CAL_HIGHLIGHT_MODE_YEAR;
  } 
  else if (selection.highlightMode == CAL_HIGHLIGHT_MODE_YEAR) {
    selection.highlightMode = CAL_HIGHLIGHT_MODE_BODY;
    selection.dateSel = firstDayOfMonth(selection.dateSel);
  }
  
  renderDaySelector(selection);
  return STATUS_DAY_SELECTOR_LOOP;
  
}


// -------------------------------------------------------------------------------------------------------
//  Encoder button clicked ..
//

int day_selector_click(Selection &selection) {
      
  #if defined(DEBUG) && defined(DEBUG_DAY_SELECTOR)
    Serial.println("  ");
    Serial.println("day_selector_click()");
  #endif
  
  if (selection.highlightMode == CAL_HIGHLIGHT_MODE_BODY) {

    return STATUS_EXIT_SELECT;

  }
  else if (selection.highlightMode == CAL_HIGHLIGHT_MODE_MONTH) {

    #if defined(DEBUG) && defined(DEBUG_DAY_SELECTOR)
      Serial.println("  Month menu item selected.");
    #endif

    Selection monthSelection = copySelection(selection);
    monthSelection.highlightMode = CAL_HIGHLIGHT_MODE_BODY;
    
    status = init_month_selector(monthSelection); 

    if (status == STATUS_EXIT_SELECT) { selection = copySelection(monthSelection); }
    selection.highlightMode = CAL_HIGHLIGHT_MODE_MONTH;

    renderDaySelector(selection);
    return STATUS_DAY_SELECTOR_LOOP;

  } 
  else if (selection.highlightMode == CAL_HIGHLIGHT_MODE_YEAR) {

    #if defined(DEBUG) && defined(DEBUG_DAY_SELECTOR)
      Serial.println("  Year menu item selected.");
    #endif

    Selection yearSelection = copySelection(selection);
    yearSelection.highlightMode = CAL_HIGHLIGHT_MODE_BODY;

    status = init_year_selector(yearSelection); 

    if (status == STATUS_EXIT_SELECT) { selection = copySelection(yearSelection); }
    selection.highlightMode = CAL_HIGHLIGHT_MODE_YEAR;

    renderDaySelector(selection);
    return STATUS_DAY_SELECTOR_LOOP;
    
  } 
  else if (selection.highlightMode == CAL_HIGHLIGHT_MODE_CANCEL) {

    #if defined(DEBUG) && defined(DEBUG_DAY_SELECTOR)
      Serial.println("  Cancel menu item selected.");
    #endif
    
    return STATUS_EXIT_CANCEL;
  
  }
  
  
}
