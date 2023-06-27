#include "../Include/MainComponent.h"
//
MainComponent::MainComponent(void)
{
    setOpaque(true);
    setSize(800, 800);
}
//
MainComponent::~MainComponent(void)
{
}
//
void MainComponent::paint(Graphics& g)
{
    g.fillAll(Colours::powderblue);
}
//
void MainComponent::resized(void)
{
}