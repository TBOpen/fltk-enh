//
// "$Id: Fl_Checkbox_Browser.cxx 8354 2011-02-01 15:41:04Z manolo $"
//
// Fl_Checkbox_Browser header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

#include <stdio.h>
#include <stdlib.h>
#include "flstring.h"
#include <FL/fl_draw.H>
#include <FL/Fl_Checkbox_Browser.H>

Fl_Checkbox_Browser::Fl_Checkbox_Browser(int X,int Y,int W,int H,const char *L)
                    : Fl_Browser(X,Y,W,H,L)
{
  nchecked_=0;
  type(FL_CHECKBOX_BROWSER);
}


/** Gets the current status of item item. */
int Fl_Checkbox_Browser::checked(int i) const {
	FL_BLINE *p = find_line(i);

	if (p) return (p->flags & CHECKED)!=0;
	return 0;
}

/** Sets the check status of item item to b. */
void Fl_Checkbox_Browser::checked(int i, int b) {
  checked(find_line(i), b);
}

/**  Sets all the items checked.*/
void Fl_Checkbox_Browser::check_all() {
	FL_BLINE *p;

	nchecked_ = size();
	for (p = (FL_BLINE*)item_first(); p; p = p->next) {
		p->flags |= CHECKED;
	}
	redraw();
}

/**  Sets all the items unchecked.*/
void Fl_Checkbox_Browser::check_none() {
	FL_BLINE *p;

	nchecked_ = 0;
	for (p = (FL_BLINE*)item_first(); p; p = p->next) {
		p->flags &= ~CHECKED;
	}
	redraw();
}

/**
  change the checked status of item

  \param[in] item The item whose checked state is to be changed
  \param[in] val The new checked state (1=checked, 0=not checked, -1=toggle)
*/
void Fl_Checkbox_Browser::checked(void *item,int val)
{
  FL_BLINE *p=(FL_BLINE*) item;

	if (p) {
	  int updated=0;
	  if (val<0) {
	    updated=1;
	    if (p->flags & CHECKED) {
	      p->flags&=~CHECKED;
	      nchecked_--;
	    }
	    else {
	      p->flags|=CHECKED;
	      nchecked_++;
	    }
	  }
	  else if (val>0 && (p->flags & CHECKED)==0) {
	    updated=1;
	    p->flags |= CHECKED;
	    nchecked_++;
	  }
	  else if (val==0 && (p->flags & CHECKED)) {
	    updated=1;
	    p->flags &= ~CHECKED;
	    nchecked_--;
	  }
	  if (updated) {
		  redraw();
      set_check_changed();
		  if (when() & FL_WHEN_CHANGED) {
		    do_callback();
		  }
	  }
	}
}

//
// End of "$Id: Fl_Checkbox_Browser.cxx 8354 2011-02-01 15:41:04Z manolo $".
//
