#include "STabItem.h"
#include "imgui.h"
#include "SLayoutWindow.h"
#include "MainEditorWindow.h"
#include <sstream>

int32 STabItem::STabItemIndex = 0;

STabItem::STabItem()
{
	STabItem::STabItemIndex++;
	std::ostringstream WName;
	WName << "STabItem" << STabItem::STabItemIndex;
	Name = WName.str();
}

STabItem::~STabItem()
{
}

void STabItem::Draw()
{
	SWidget::Draw();
	if (ImGui::BeginTabItem(Name.data()))
	{
		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None | ImGuiDragDropFlags_SourceAllowNullID))
		{
			DragItemData data;
			data.item = this;
			ImGui::SetDragDropPayload("Drag_Tab_Item", &data, sizeof(DragItemData));
			ImGui::EndDragDropSource();
		}
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Drag_Tab_Item"))
			{
				IM_ASSERT(payload->DataSize == sizeof(DragItemData));
				DragItemData payload_n = *(DragItemData*)payload->Data;
				if (payload_n.item && payload_n.item->ParentLayoutWindow && this->ParentLayoutWindow && this->ParentLayoutWindow->mainEditorWindow)
				{
					auto fun = [=]() {
						payload_n.item->ParentLayoutWindow->TabItems.remove(payload_n.item);
						if (payload_n.item->ParentLayoutWindow->TabItems.empty())
						{
							payload_n.item->ParentLayoutWindow->mainEditorWindow->DeleteLayoutWindow(payload_n.item->ParentLayoutWindow);
							payload_n.item->ParentLayoutWindow = nullptr;
						}
						this->ParentLayoutWindow->TabItems.push_front(payload_n.item);
						payload_n.item->ParentLayoutWindow = this->ParentLayoutWindow;
					};
					this->ParentLayoutWindow->mainEditorWindow->ChangeLayoutFunList.push_back(std::bind(fun));
				}
			}
			ImGui::EndDragDropTarget();
		}
		ImGui::TextWrapped("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. ");
		ImGui::Text(Name.data());
		ImGui::EndTabItem();
	}
}