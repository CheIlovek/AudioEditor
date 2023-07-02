#include "../Include/MainComponent.h"
#include "../Include/Menubar.h"
//
MainComponent::MainComponent(void)
{
    setOpaque(true);
    setSize(800, 800);
    MenuBar mb = MenuBar();
    menuBarComp.setModel(&mb);
    addAndMakeVisible(&menuBarComp);
    menuBarComp.setBounds(0, 0, proportionOfWidth(1.0f), 20);
}
//
MainComponent::~MainComponent(void)
{
}
//
void MainComponent::paint(Graphics& g)
{
    g.fillAll(Colours::hotpink);
}
//
void MainComponent::resized(void)
{
    menuBarComp.setBounds(0, 0, proportionOfWidth(1.0f), 20);
}