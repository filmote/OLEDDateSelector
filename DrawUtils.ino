
// -------------------------------------------------------------------------------------------------------
// Draw a down arrow as part of the scroll bar (7 x 4 pixels) ..

void drawDownArrow(int left, int top) {

  display.drawRect(left, top, 7, 0);
  display.drawRect(left + 1, top + 1, 5, 0);
  display.drawRect(left + 2, top + 2, 3, 0);
  display.setPixel(left + 3, top + 3);

}


// -------------------------------------------------------------------------------------------------------
// Draw a left arrow as part of the scroll bar (4 x 7 pixels) ..

void drawLeftArrow(int left, int top) {

  display.setPixel(left, top + 3);
  display.drawRect(left + 1, top + 2, 0, 3);
  display.drawRect(left + 2, top + 1, 0, 5);
  display.drawRect(left + 3, top, 0, 7);

}
