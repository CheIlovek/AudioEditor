#include "EffectListBoxModel.h"

EffectListBoxModel::EffectListBoxModel(String name) : name(name)
{
}

EffectListBoxModel::~EffectListBoxModel()
{
}

int EffectListBoxModel::getNumRows()
{
	return list.size();
}

void EffectListBoxModel::paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{
	g.fillAll(ProjectColours::EffectHistory::rowBackground);
}

Component* EffectListBoxModel::refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate)
{
	if (rowNumber < 0 || rowNumber >= list.size())
		return nullptr;
	return list[rowNumber];
}

void EffectListBoxModel::addNewElement(String textForElement)
{
	auto text = std::make_unique<DrawableText>();
	list.add(text.release());
	DrawableText* cur = list[list.size() - 1];
	cur->setText(textForElement);
	cur->setFontHeight(16);
	cur->setColour(ProjectColours::textColour);
	//Rectangle<float> boundingBoxRectangle(5, 0, cur->getWidth() - 5, cur->getHeight());
	//cur->setBoundingBox(Parallelogram<float>(boundingBoxRectangle));
}

void EffectListBoxModel::clear()
{
	list.clear();
}

DrawableText* EffectListBoxModel::getDrawableText(int textId)
{
	return list[textId];
}
