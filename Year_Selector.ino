// -------------------------------------------------------------------------------------------------------
//  Initialise year selector ..
//

int init_year_selector(Selection &selection) {

  #if defined(DEBUG) && defined(DEBUG_YEAR_SELECTOR)
    Serial.println("  ");
    Serial.println("init_year_selector()");
    Serial.println("  status = " + renderStatus());
    Serial.println("  selection");
    Serial.println("    dateOrig = " + String(year(selection.dateOrig)) + "-" + String(month(selection.dateOrig)) + "-" + String(day(selection.dateOrig)));
    Serial.println("    dateSel = " + String(year(selection.dateSel)) + "-" + String(month(selection.dateSel)) + "-" + String(day(selection.dateSel)));
    Serial.println("    highlightMode = " + renderCalHighlightMode(selection));
  #endif
  
  renderYearSelector(selection);

  status = STATUS_YEAR_SELECTOR_LOOP;
  return loop_year_selector(selection);
  
}


// -------------------------------------------------------------------------------------------------------
//  Process user input ..
//

int loop_year_selector(Selection &selection) {

  #if defined(DEBUG) && defined(DEBUG_YEAR_SELECTOR)
    Serial.println("  ");
    Serial.println("loop_year_selector()");
    Serial.println("  status = " + renderStatus());
    Serial.println("  selection");
    Serial.println("    dateOrig = " + String(year(selection.dateOrig)) + "-" + String(month(selection.dateOrig)) + "-" + String(day(selection.dateOrig)));
    Serial.println("    dateSel = " + String(year(selection.dateSel)) + "-" + String(month(selection.dateSel)) + "-" + String(day(selection.dateSel)));
    Serial.println("    highlightMode = " + renderCalHighlightMode(selection));
  #endif
  
  while (status == STATUS_YEAR_SELECTOR_LOOP) {
  

    // Rotation of encoder ..

    long newPosition = myEnc.read();
    
    if (abs(newPosition - oldPosition) >= KY040_MINIMUM_RESOLUTION) {

      if (newPosition > oldPosition)                                                                  { status = year_selector_scroll_left(selection); }
      if (newPosition < oldPosition)                                                                  { status = year_selector_scroll_right(selection); }
  
      oldPosition = newPosition;

    }


    // Software debounce of button press ..
    
    if (isButtonPressed && millis() - lastUpdateMillis > 50) {

      delay(KY040_DEBOUNCE_DELAY);

      isButtonPressed = false;
      lastUpdateMillis = millis();                                                                      status = year_selector_click(selection);

      myEnc.write(0);    
      newPosition = 0;
      oldPosition = 0;

    }
    
    yield();

  }
  
  #if defined(DEBUG) && defined(DEBUG_YEAR_SELECTOR)
    Serial.println("  ");
    Serial.println("loop_year_selector() - Exit");
    Serial.println("  status = " + renderStatus());
  #endif
  
  return status;

}

// -------------------------------------------------------------------------------------------------------
//  Encoder turned left ..
//

int year_selector_scroll_left(Selection &selection) {
  
  #if defined(DEBUG) && defined(DEBUG_YEAR_SELECTOR)
    Serial.println("  ");
    Serial.println("year_selector_scroll_left()");
  #endif
  
  if (selection.highlightMode == CAL_HIGHLIGHT_MODE_BODY) {

    if (year(selection.dateSel) > year(selection.dateOrig) - CAL_MAX_YEAR_SPAN_NEG) {
      selection.dateSel = addYears(selection.dateSel, -1);
    }
    else {
      selection.highlightMode = CAL_HIGHLIGHT_MODE_CANCEL;
    }

  } 
  else if (selection.highlightMode == CAL_HIGHLIGHT_MODE_CANCEL) {
    selection.highlightMode = CAL_HIGHLIGHT_MODE_BODY;
    selection.dateSel = setYear(selection.dateOrig, year(selection.dateOrig) + CAL_MAX_YEAR_SPAN_POS);
  }

  renderYearSelector(selection);
  return STATUS_YEAR_SELECTOR_LOOP;
  
}


// -------------------------------------------------------------------------------------------------------
//  Encoder turned right ..
//
 
int year_selector_scroll_right(Selection &selection) {
  
  #if defined(DEBUG) && defined(DEBUG_YEAR_SELECTOR)
    Serial.println("  ");
    Serial.println("year_selector_scroll_right()");
  #endif
  
  if (selection.highlightMode == CAL_HIGHLIGHT_MODE_BODY) {

    if (year(selection.dateSel) < year(selection.dateOrig) + CAL_MAX_YEAR_SPAN_POS) {

      selection.dateSel = addYears(selection.dateSel, 1);
    
    }
    else {
      
      selection.highlightMode = CAL_HIGHLIGHT_MODE_CANCEL;

    }

  }
  else if (selection.highlightMode == CAL_HIGHLIGHT_MODE_CANCEL) {
    selection.highlightMode = CAL_HIGHLIGHT_MODE_BODY;
    selection.dateSel = setYear(selection.dateOrig, year(selection.dateOrig) - CAL_MAX_YEAR_SPAN_NEG);
  }
  
  renderYearSelector(selection);
  return STATUS_YEAR_SELECTOR_LOOP;
  
}


// -------------------------------------------------------------------------------------------------------
//  Encoder button clicked ..
//

int year_selector_click(Selection &selection) {
    
  #if defined(DEBUG) && defined(DEBUG_YEAR_SELECTOR)
    Serial.println("  ");
    Serial.println("year_selector_click()");
  #endif

  if (selection.highlightMode == CAL_HIGHLIGHT_MODE_BODY) {

    #if defined(DEBUG) && defined(DEBUG_YEAR_SELECTOR)
      Serial.println("  Select clicked, new date = " + String(year(selection.dateSel)) + "-" + String(month(selection.dateSel)) + "-" + String(day(selection.dateSel)));
    #endif

    return STATUS_EXIT_SELECT;

  }
  else if (selection.highlightMode == CAL_HIGHLIGHT_MODE_CANCEL) {

    #if defined(DEBUG) && defined(DEBUG_YEAR_SELECTOR)
      Serial.println("  Cancel mneu item selected, original date returned.");
    #endif  

    return STATUS_EXIT_CANCEL;
    
  }
  
}
