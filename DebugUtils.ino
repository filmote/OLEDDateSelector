
#if defined(DEBUG)

  String renderStatus() {
  
    switch (status) {
  
      case 0: return "STATUS_DAY_SELECTOR_INIT";                        
      case 1: return "STATUS_DAY_SELECTOR_LOOP";                       
      case 2: return "STATUS_MONTH_SELECTOR_INIT";                     
      case 3: return "STATUS_MONTH_SELECTOR_LOOP";                     
      case 4: return "STATUS_YEAR_SELECTOR_INIT";                    
      case 5: return "STATUS_YEAR_SELECTOR_LOOP";                 
      case 6: return "STATUS_EXIT_SELECT";                           
      case 7: return "STATUS_EXIT_CANCEL";                          
  
    }
  
  }

  String renderCalHighlightMode(Selection selection) {

    switch (selection.highlightMode) {

      case 0: return "CAL_HIGHLIGHT_MODE_BODY";  
      case 1: return "CAL_HIGHLIGHT_MODE_MONTH";  
      case 2: return "CAL_HIGHLIGHT_MODE_YEAR";  
      case 3: return "CAL_HIGHLIGHT_MODE_CANCEL";  
    }
    
  }

#endif
