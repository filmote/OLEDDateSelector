
// -------------------------------------------------------------------------------------------------------
// Render the year selector ..

void renderYearSelector(Selection &selection) {


  // Selected month is (generally) the 3rd row.  Set the top row relative to the third row ..

  int top = year(selection.dateSel) - 2;

  if (year(selection.dateOrig) - CAL_MAX_YEAR_SPAN_NEG - year(selection.dateSel) == -1)   { top = year(selection.dateSel) - 1; }
  if (year(selection.dateOrig) - CAL_MAX_YEAR_SPAN_NEG - year(selection.dateSel) == 0)    { top = year(selection.dateSel); }
  if (year(selection.dateOrig) + CAL_MAX_YEAR_SPAN_POS - year(selection.dateSel) == 1)    { top = year(selection.dateSel) - 3; }
  if (year(selection.dateOrig) + CAL_MAX_YEAR_SPAN_POS - year(selection.dateSel) == 0)    { top = year(selection.dateSel) - 4; }


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

    if (selection.highlightMode == CAL_HIGHLIGHT_MODE_BODY && (top + row == year(selection.dateSel))) {
      display.drawRect(0, CAL_SPACING_Y_TOP + (row * CAL_SPACING_Y_5_ROWS) + 1, 127, CAL_SPACING_Y_5_ROWS);        
    }

    display.drawString(2, CAL_SPACING_Y_TOP + (row * CAL_SPACING_Y_5_ROWS), String(top + row));
  }
  
  display.display();
  
}
