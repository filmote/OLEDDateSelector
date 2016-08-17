// -------------------------------------------------------------------------------------------------------
// Render a calendar ..

void renderDaySelector(Selection &selection) {

  time_t firstOfMonth = firstDayOfMonth(selection.dateSel);
  
  int monthWidth = display.getStringWidth(monthStr(month(firstOfMonth)));
  int monthLeft = 1;
  int yearWidth = display.getStringWidth(String(year(firstOfMonth)));
  int yearLeft = monthLeft + monthWidth + (selection.highlightMode == CAL_HIGHLIGHT_MODE_MONTH ? 15 : 5);
  
  int dayOfMonth = 1;

  int dow = (dayOfWeek(firstOfMonth) == 1 ? 6 : dayOfWeek(firstOfMonth) - 2);
  int maxDays = daysInMonth(firstOfMonth);
  int maxRows = 1 + ((maxDays - (7 - dow)) / 7) + ((maxDays - (7 - dow)) % 7 > 0 ? 1 : 0);
  

  // Render headings in inverse ..
   
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.setColor(WHITE);
  display.fillRect(CAL_HEADING_LEFT, CAL_HEADING_TOP, CAL_HEADING_WIDTH, CAL_HEADING_HEIGHT);
  display.setColor(BLACK);

  
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  
  if (selection.highlightMode == CAL_HIGHLIGHT_MODE_CANCEL) {
    drawLeftArrow(CAL_HEADING_TEXT_BACK_LEFT, 1);
    display.drawString(CAL_HEADING_TEXT_BACK_LEFT + CAL_HEADING_BACK_ARROW_WIDTH + CAL_HEADING_SPACER, CAL_HEADING_TEXT_TOP, "Back");
  }
  else {
    display.drawString(CAL_HEADING_TEXT_BACK_LEFT, CAL_HEADING_TEXT_TOP, "Back");
  }
  
  display.setTextAlignment(TEXT_ALIGN_CENTER);

  if (selection.highlightMode == CAL_HIGHLIGHT_MODE_MONTH) {
    drawDownArrow(64 + (monthWidth + CAL_HEADING_SPACER) / 2, 2);
    display.drawString(64 - ((CAL_HEADING_DOWN_ARROW_WIDTH + CAL_HEADING_SPACER) / 2), CAL_HEADING_TEXT_TOP, monthStr(month(firstOfMonth)));
  }
  else {
    display.drawString(64, CAL_HEADING_TEXT_TOP, monthStr(month(firstOfMonth)));
  }

  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  
  if (selection.highlightMode == CAL_HIGHLIGHT_MODE_YEAR) {

    display.drawString(CAL_HEADING_TEXT_YEAR_RIGHT - CAL_HEADING_DOWN_ARROW_WIDTH - CAL_HEADING_SPACER, CAL_HEADING_TEXT_TOP, String(year(firstOfMonth)));
    drawDownArrow(CAL_HEADING_TEXT_YEAR_RIGHT - CAL_HEADING_DOWN_ARROW_WIDTH, 2);
  }
  else {

    display.drawString(CAL_HEADING_TEXT_YEAR_RIGHT, CAL_HEADING_TEXT_TOP, String(year(firstOfMonth)));

  }


  // Render days headings ..  
  
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  
  display.drawString(0 + CAL_SPACING_X_WIDTH, CAL_SPACING_Y_TOP, "Mo");
  display.drawString((1 * CAL_SPACING_X) + CAL_SPACING_X_WIDTH, CAL_SPACING_Y_TOP, "Tu");
  display.drawString((2 * CAL_SPACING_X) + CAL_SPACING_X_WIDTH, CAL_SPACING_Y_TOP, "We");
  display.drawString((3 * CAL_SPACING_X) + CAL_SPACING_X_WIDTH, CAL_SPACING_Y_TOP, "Th");
  display.drawString((4 * CAL_SPACING_X) + CAL_SPACING_X_WIDTH, CAL_SPACING_Y_TOP, "Fr");
  display.drawString((5 * CAL_SPACING_X) + CAL_SPACING_X_WIDTH, CAL_SPACING_Y_TOP, "Sa");
  display.drawString((6 * CAL_SPACING_X) + CAL_SPACING_X_WIDTH, CAL_SPACING_Y_TOP, "Su");


  // Render first row of days, this may be less than seven days depending on when the first day of the month is ..
  
  for (int col = dow; col < 7; col++) {


    // Render currently highlighted day in reverse ..

    if (selection.highlightMode == CAL_HIGHLIGHT_MODE_BODY && day(selection.dateSel) == dayOfMonth) {
      display.drawRect((col * CAL_SPACING_X), CAL_SPACING_Y_TOP + CAL_SPACING_Y_6_ROWS + 2, (col < 6 ? CAL_SPACING_X_WIDTH : CAL_SPACING_X_WIDTH - 2), CAL_HIGHLIGHT_OUTLINE_HEIGHT);      
    }

    
    // Highlight currently selected day ..
    
    if (day(selection.dateOrig) == dayOfMonth && month(selection.dateOrig) == month(selection.dateSel) && year(selection.dateOrig) == year(selection.dateSel)) {
      display.setColor(WHITE);
      display.fillRect((col * CAL_SPACING_X), CAL_SPACING_Y_TOP + CAL_SPACING_Y_6_ROWS + 2, (col < 6 ? CAL_SPACING_X_WIDTH : CAL_SPACING_X_WIDTH - 2), CAL_HIGHLIGHT_REVERSE_HEIGHT);   
      display.setColor(BLACK);
    }
                  
    display.drawString((col * CAL_SPACING_X) + CAL_SPACING_X_WIDTH, CAL_SPACING_Y_TOP + CAL_SPACING_Y_6_ROWS, String(dayOfMonth));
    display.setColor(WHITE);
  
    dayOfMonth++;
      
  }


  // Render remaining rows.  If the month happens to span 6 rows handle it according to the CAL_SHOW_6_ROWS_OF_DAYS value ..

  for (int row = 2; row <= 6 && dayOfMonth <= maxDays; row++) {

    for (int col = 0; col < 7 && dayOfMonth <= maxDays; col++) {

      
      // Highlight currently highlighted day ..

      if (selection.highlightMode == CAL_HIGHLIGHT_MODE_BODY && day(selection.dateSel) == dayOfMonth) {
        display.drawRect((col * CAL_SPACING_X), CAL_SPACING_Y_TOP + 2 + ((row % 6 == 0 ? 1 : row) * CAL_SPACING_Y_6_ROWS), (col < 6 ? CAL_SPACING_X_WIDTH : CAL_SPACING_X_WIDTH - 2), CAL_HIGHLIGHT_OUTLINE_HEIGHT);   
      }

            
      // Highlight currently selected day ..
      
      if (day(selection.dateOrig) == dayOfMonth && month(selection.dateOrig) == month(selection.dateSel) && year(selection.dateOrig) == year(selection.dateSel)) {
        display.setColor(WHITE);
        display.fillRect((col * CAL_SPACING_X), CAL_SPACING_Y_TOP + 2 + ((row % 6 == 0 ? 1 : row) * CAL_SPACING_Y_6_ROWS), (col < 6 ? CAL_SPACING_X_WIDTH : CAL_SPACING_X_WIDTH - 2), CAL_HIGHLIGHT_REVERSE_HEIGHT);   
        display.setColor(BLACK);
      }

      display.drawString((col * CAL_SPACING_X) + CAL_SPACING_X_WIDTH -1, CAL_SPACING_Y_TOP + ((row % 6 == 0 ? 1 : row) * CAL_SPACING_Y_6_ROWS), String(dayOfMonth));
      display.setColor(WHITE);

      dayOfMonth++;
         
    }

  }

  display.display();
  
}
