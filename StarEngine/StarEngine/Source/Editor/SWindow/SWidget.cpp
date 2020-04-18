#include "SWidget.h"
#include <sstream>

int32 SWidget::WidgetIndex = 0;

SWidget::SWidget()
{
	SWidget::WidgetIndex++;
	std::ostringstream WName;
	WName << "Widget" << SWidget::WidgetIndex;
	WidgetName = WName.str();
}

SWidget::~SWidget()
{
}

void SWidget::Draw()
{
}