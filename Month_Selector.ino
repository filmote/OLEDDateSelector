// -------------------------------------------------------------------------------------------------------
//  Initialise month selector ..
//

int init_month_selector(Selection &selection) {

  #if defined(DEBUG) && defined(DEBUG_MONTH_SELECTOR)
    Serial.println("  ");
    Serial.println("init_month_selector()");
    Serial.println("  status = " + renderStatus());
    Serial.println("  selection");
    Serial.println("    dateOrig = " + String(year(selection.dateOrig)) + "-" + String(month(selection.dateOrig)) + "-" + String(day(selection.dateOrig)));
    Serial.println("    dateSel = " + String(year(selection.dateSel)) + "-" + String(month(selection.dateSel)) + "-" + String(day(selection.dateSel)));
    Serial.println("    highlightMode = " + renderCalHighlightMode(selection));
  #endif

  renderMonthSelector(selection);

  status = STATUS_MONTH_SELECTOR_LOOP;
  return loop_month_selector(selection);
  
}


// -------------------------------------------------------------------------------------------------------
//  Process user input ..
//

int loop_month_selector(Selection &selection) {

  #if defined(DEBUG) && defined(DEBUG_MONTH_SELECTOR)
    Serial.println("  ");
    Serial.println("loop_month_selector()");
    Serial.println("  status = " + renderStatus());
    Serial.println("  selection");
    Serial.println("    dateOrig = " + String(year(selection.dateOrig)) + "-" + String(month(selection.dateOrig)) + "-" + String(day(selection.dateOrig)));
    Serial.println("    dateSel = " + String(year(selection.dateSel)) + "-" + String(month(selection.dateSel)) + "-" + String(day(selection.dateSel)));
    Serial.println("    highlightMode = " + renderCalHighlightMode(selection));
  #endif

  while (status == STATUS_MONTH_SELECTOR_LOOP) {


    // Rotation of encoder ..
  
    long newPosition = myEnc.read();

    if (abs(newPosition - oldPosition) >= KY040_MINIMUM_RESOLUTION) {

      if (newPosition > oldPosition)          { status = month_selector_scroll_left(selection); }
      if (newPosition < oldPosition)          { status = month_selector_scroll_right(selection); }
  
      oldPosition = newPosition;

    }

    // Software debounce of button press ..
    
    if (isButtonPressed && millis() - lastUpdateMillis > 50) {

      delay(KY040_DEBOUNCE_DELAY);

      isButtonPressed = false;
      lastUpdateMillis = millis();              status = month_selector_click(selection);

      myEnc.write(0);    
      newPosition = 0;
      oldPosition = 0;
      
    }
    
    yield();

  }
  
  #if defined(DEBUG) && defined(DEBUG_MONTH_SELECTOR)
    Serial.println("  ");
    Serial.println("loop_month_selector() - Exit");
    Serial.println("  status = " + renderStatus());
  #endif

  return status;
  
}


// -------------------------------------------------------------------------------------------------------
//  Encoder turned left ..
//

int month_selector_scroll_left(Selection &selection) {
        
  #if defined(DEBUG) && defined(DEBUG_MONTH_SELECTOR)
    Serial.println("  ");
    Serial.println("month_selector_scroll_left()");
  #endif
  
  if (selection.highlightMode == CAL_HIGHLIGHT_MODE_BODY) {

    if (month(selection.dateSel) > 1) {
      selection.dateSel = addMonths(selection.dateSel, -1);
    }
    else {
      selection.highlightMode = CAL_HIGHLIGHT_MODE_CANCEL;
    }

  } 
  else if (selection.highlightMode == CAL_HIGHLIGHT_MODE_CANCEL) {
    selection.highlightMode = CAL_HIGHLIGHT_MODE_BODY;
    selection.dateSel = lastMonthOfYear(selection.dateSel);
  }

  renderMonthSelector(selection);
  return STATUS_MONTH_SELECTOR_LOOP;
  
}


// -------------------------------------------------------------------------------------------------------
//  Encoder turned right ..
//
 
int month_selector_scroll_right(Selection &selection) {
        
  #if defined(DEBUG) && defined(DEBUG_MONTH_SELECTOR)
    Serial.println("  ");
    Serial.println("month_selector_scroll_right()");
  #endif
    
  if (selection.highlightMode == CAL_HIGHLIGHT_MODE_BODY) {

    if (month(selection.dateSel) < 12) {

      selection.dateSel = addMonths(selection.dateSel, 1);
    
    }
    else {
      
      selection.highlightMode = CAL_HIGHLIGHT_MODE_CANCEL;

    }

  }
  else if (selection.highlightMode == CAL_HIGHLIGHT_MODE_CANCEL) {
    selection.highlightMode = CAL_HIGHLIGHT_MODE_BODY;
    selection.dateSel = firstMonthOfYear(selection.dateSel);
  }
  
  renderMonthSelector(selection);
  return STATUS_MONTH_SELECTOR_LOOP;
  
}


// -------------------------------------------------------------------------------------------------------
//  Encoder button clicked ..
//

int month_selector_click(Selection &selection) {

  #if defined(DEBUG) && defined(DEBUG_MONTH_SELECTOR)
    Serial.println("  ");
    Serial.println("month_selector_click()");
  #endif
  
  if (selection.highlightMode == CAL_HIGHLIGHT_MODE_BODY) {

    #if defined(DEBUG) && defined(DEBUG_MONTH_SELECTOR)
      Serial.println("  Select clicked, new date = " + String(year(selection.dateSel)) + "-" + String(month(selection.dateSel)) + "-" + String(day(selection.dateSel)));
    #endif
    
    return STATUS_EXIT_SELECT;

  }
  else if (selection.highlightMode == CAL_HIGHLIGHT_MODE_CANCEL) {

    #if defined(DEBUG) && defined(DEBUG_MONTH_SELECTOR)
      Serial.println("  Cancel mneu item selected, original date returned.");
    #endif  
    
    return STATUS_EXIT_CANCEL;
    
  }
  
}
