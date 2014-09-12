#ifndef __DW_OOFPOSITIONEDMGR_HH__
#define __DW_OOFPOSITIONEDMGR_HH__

#include "outofflowmgr.hh"

namespace dw {

namespace oof {

class OOFPositionedMgr: public OutOfFlowMgr
{
protected:
   virtual int containerBoxOffsetX () = 0;
   virtual int containerBoxOffsetY () = 0;
   virtual int containerBoxRestWidth () = 0;
   virtual int containerBoxRestHeight () = 0;

   inline int containerBoxDiffWidth ()
   { return containerBoxOffsetX () + containerBoxRestWidth (); }
   inline int containerBoxDiffHeight ()
   { return containerBoxOffsetY () + containerBoxRestHeight (); }

   OOFAwareWidget *container;
   core::Allocation containerAllocation;

   lout::container::typed::Vector<core::Widget> *children;

   bool doChildrenExceedContainer ();
   bool haveExtremesChanged ();
   void sizeAllocateChildren ();

   inline int getPosLeft (core::Widget *child, int availWidth)
   { return getPosBorder (child->getStyle()->left, availWidth); }
   inline int getPosRight (core::Widget *child, int availWidth)
   { return getPosBorder (child->getStyle()->right, availWidth); }
   inline int getPosTop (core::Widget *child, int availHeight)
   { return getPosBorder (child->getStyle()->top, availHeight); }
   inline int getPosBottom (core::Widget *child, int availHeight)
   { return getPosBorder (child->getStyle()->bottom, availHeight); }

   int getPosBorder (core::style::Length cssValue, int refLength);
   void calcPosAndSizeChildOfChild (core::Widget *child, int refWidth,
                                    int refHeight, int *x, int *y, int *width,
                                    int *ascent, int *descent);

public:
   OOFPositionedMgr (OOFAwareWidget *container);
   ~OOFPositionedMgr ();

   void sizeAllocateStart (OOFAwareWidget *caller,
                           core::Allocation *allocation);
   void sizeAllocateEnd (OOFAwareWidget *caller);
   void containerSizeChangedForChildren ();
   void draw (core::View *view, core::Rectangle *area);

   void markSizeChange (int ref);
   void markExtremesChange (int ref);
   core::Widget *getWidgetAtPoint (int x, int y, int level);

   void addWidgetInFlow (OOFAwareWidget *widget, OOFAwareWidget *parent,
                         int externalIndex);
   int addWidgetOOF (core::Widget *widget, OOFAwareWidget *generator,
                     int externalIndex);
   void moveExternalIndices (OOFAwareWidget *generator, int oldStartIndex,
                             int diff);

   void tellPosition (core::Widget *widget, int yReq);

   void getSize (core::Requisition *containerReq, int *oofWidth,
                 int *oofHeight);
   void getExtremes (core::Extremes *containerExtr,
                     int *oofMinWidth, int *oofMaxWidth);

   int getLeftBorder (OOFAwareWidget *widget, int y, int h,
                      OOFAwareWidget *lastGen, int lastExtIndex);
   int getRightBorder (OOFAwareWidget *widget, int y, int h,
                       OOFAwareWidget *lastGen, int lastExtIndex);

   bool hasFloatLeft (OOFAwareWidget *widget, int y, int h,
                      OOFAwareWidget *lastGen, int lastExtIndex);
   bool hasFloatRight (OOFAwareWidget *widget, int y, int h,
                       OOFAwareWidget *lastGen, int lastExtIndex);

   int getLeftFloatHeight (OOFAwareWidget *widget, int y, int h,
                           OOFAwareWidget *lastGen, int lastExtIndex);
   int getRightFloatHeight (OOFAwareWidget *widget, int y, int h,
                            OOFAwareWidget *lastGen, int lastExtIndex);

   int getClearPosition (OOFAwareWidget *widget);

   bool affectsLeftBorder (core::Widget *widget);
   bool affectsRightBorder (core::Widget *widget);

   bool dealingWithSizeOfChild (core::Widget *child);
   int getAvailWidthOfChild (core::Widget *child, bool forceValue);
   int getAvailHeightOfChild (core::Widget *child, bool forceValue);

   int getNumWidgets ();
   core::Widget *getWidget (int i);
};

} // namespace oof

} // namespace dw

#endif // __DW_OOFPOSITIONEDMGR_HH__