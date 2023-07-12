#include "../JuceLibraryCode/JuceHeader.h"
#include "../Include/MainFrame.h"
#include "../Include/Application.h"
//
MainFrame::MainFrame(const String& name)
   : DocumentWindow(name, Desktop::getInstance().getDefaultLookAndFeel()
      .findColour(ResizableWindow::backgroundColourId),
      DocumentWindow::allButtons)
{
   setUsingNativeTitleBar(true);
   setResizable(true, false);
   setResizeLimits(1000, 600, 2000, 2000);
   setFullScreen(true);
   //
   setContentOwned (new MainComponent(), false);
   setVisible(true);
}