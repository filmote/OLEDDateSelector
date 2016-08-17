
// -------------------------------------------------------------------------------------------------------
// Render the month selector ..

void renderMonthSelector(Selection &selection) {


  // Selected month is (generally) the 3rd row.  Set the top row relative to the third row ..

  int top = 8;
Serial.println(top);
  
  if (month(selection.dateSel) <= 3) { top = 1; }
 Serial.println(top);
 if (month(selection.dateSel) > 3 && month(selection.dateSel) <= 9 ) { top = month(selection.dateSel) - 2; }
Serial.println(top);


  // Render headings in inverse ..
    
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setColor(WHITE);
  display.fillRect(CAL_HEADING_LEFT, CAL_HEADING_TOP, CAL_HEADING_WIDTH, CAL_HEADING_HEIGHT);
  display.setColor(BLACK);
  
  if (selection.highlightMode == CAL_HIGHLIGHT_MODE_CANCEL) {
    drawLeftArrow(CAL_HEADING_TEXT_BACK_LEFT, 1);
    display.drawString(CAL_HEADING_TEXT_BACK_LEFT + CAL_HEADING_BACK_ARROW_WIDTH + CAL_HEADING_SPACER, CAL_HEADING_TEXT_TOP, "Back");
  }
  else {
    display.drawString(CAL_HEADING_TEXT_BACK_LEFT, CAL_HEADING_TEXT_TOP, "Back");
  }


  // Render body with highlighed selection ..
  
  display.setColor(WHITE);
  
  for (int row = 0; row < 5; row++) {

    if (selection.highlightMode == CAL_HIGHLIGHT_MODE_BODY && (top + row == month(selection.dateSel))) {
      display.drawRect(0, CAL_SPACING_Y_TOP + (row * CAL_SPACING_Y_5_ROWS) + 1, 127, CAL_SPACING_Y_5_ROWS);        
    }

    display.drawString(2, CAL_SPACING_Y_TOP + (row * CAL_SPACING_Y_5_ROWS), monthStr(top + row));

  }
  
  display.display();
  
}
