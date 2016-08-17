struct Selection {
  time_t dateOrig; 
  time_t dateSel; 
  int highlightMode;
};

// -- Calendar Configuration ---------------------------------------------------------------------------------------------

#define CAL_SPACING_X                               19
#define CAL_SPACING_Y_TOP                           8
#define CAL_SPACING_Y_6_ROWS                        9
#define CAL_SPACING_Y_5_ROWS                        10
#define CAL_SPACING_X_WIDTH                         15

#define CAL_HIGHLIGHT_OUTLINE_HEIGHT                8            
#define CAL_HIGHLIGHT_REVERSE_HEIGHT                9

#define CAL_HEADING_TOP                             0
#define CAL_HEADING_LEFT                            0
#define CAL_HEADING_WIDTH                           128
#define CAL_HEADING_HEIGHT                          9
#define CAL_HEADING_TEXT_TOP                        -2
#define CAL_HEADING_TEXT_BACK_LEFT                  2
#define CAL_HEADING_TEXT_YEAR_RIGHT                 127
#define CAL_HEADING_BACK_ARROW_WIDTH                4
#define CAL_HEADING_DOWN_ARROW_WIDTH                7
#define CAL_HEADING_SPACER                          1

#define CAL_FEBRUARY                                2
#define CAL_MAX_YEAR_SPAN_NEG                       4
#define CAL_MAX_YEAR_SPAN_POS                       6

#define CAL_HIGHLIGHT_MODE_BODY                     0
#define CAL_HIGHLIGHT_MODE_MONTH                    1
#define CAL_HIGHLIGHT_MODE_YEAR                     2
#define CAL_HIGHLIGHT_MODE_CANCEL                   3


// -- Status Constants -------------------------------------------------------------------------------------------------------
//
// The DateSelecto is essentially a big state machine and is controlled by the following constants.  

#define STATUS_DAY_SELECTOR_INIT                    0
#define STATUS_DAY_SELECTOR_LOOP                    1
#define STATUS_MONTH_SELECTOR_INIT                  2
#define STATUS_MONTH_SELECTOR_LOOP                  3
#define STATUS_YEAR_SELECTOR_INIT                   4
#define STATUS_YEAR_SELECTOR_LOOP                   5
#define STATUS_EXIT_SELECT                          6
#define STATUS_EXIT_CANCEL                          7

int status = STATUS_DAY_SELECTOR_INIT;

