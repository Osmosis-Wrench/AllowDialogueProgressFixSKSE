#include "DialogueMenu.hpp"
#include "Settings.h"

namespace Fix
{
	RE::UI_MESSAGE_RESULTS DialogueMenuEx::ProcessMessageEx(RE::UIMessage& a_message) 
	{
		using Message = RE::UI_MESSAGE_TYPE; // this gives easy access to the message types, like kShow etc.
		static bool allowDialogueProgressionBugfix{ Settings::GetSingleton()->allowDialogueProgressionBugfix };
		static bool instantSkipAllDialogue{ Settings::GetSingleton()->instantSkipAllDialogue };

		if (instantSkipAllDialogue) {
			if (a_message.type == Message::kUpdate) {
				doAllowProgressFix();
			}
		}
		else if (allowDialogueProgressionBugfix) {
			if (a_message.type == Message::kShow) {
				doAllowProgressFix();
			}
		}

		return _ProcessMessageFn(this, a_message);
	}

	void DialogueMenuEx::doAllowProgressFix()
	{
		if (auto ui = RE::UI::GetSingleton(); ui) {
			if (auto menu = ui->GetMenu(RE::DialogueMenu::MENU_NAME); menu) {
				const RE::GFxValue forceTrue = true;
				menu->uiMovie->SetVariable("_root.DialogueMenu_mc.bAllowProgress", true, RE::GFxMovie::SetVarType::kSticky);
			}
		}
	}

	void DialogueMenuEx::Install()
	{
		REL::Relocation<uintptr_t> vtbl(RE::VTABLE_DialogueMenu[0]);
		_ProcessMessageFn = vtbl.write_vfunc(0x4, &ProcessMessageEx);
	}
}
