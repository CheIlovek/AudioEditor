#pragma once

// ������� ���� ��� ��������� �������


#include "../JuceLibraryCode/JuceHeader.h"
class DummyComponent : public Component {
public:
    DummyComponent(void);
    ~DummyComponent(void) override;

    void paint(Graphics&) override;
    void resized(void) override;

private:
    juce::Colour colour;
};


