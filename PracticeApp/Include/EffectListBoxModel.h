#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "ProjectColours.h"

class EffectListBoxModel : public ListBoxModel
{
public:
	EffectListBoxModel(String);
	~EffectListBoxModel();

	int getNumRows() override;
	void paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) override;
	Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate);

	void addNewElement(String textForElement);
	void clear();
	DrawableText* getDrawableText(int textId);

private:
	String name;
	Array<DrawableText*> list;
};