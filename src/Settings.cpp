#include "Settings.h"

bool Settings::Load() {
	constexpr auto path = L"Data/SKSE/Plugins/DialogueMenu_FixesAndTweaks.ini";

	CSimpleIniA ini;
	ini.SetUnicode();

	ini.LoadFile(path);

	const auto get_value = [&]<class T>(T& a_value, const char* a_section, const char* a_key, const char* a_comment) {
		if constexpr (std::is_same_v<bool, T>) {
			a_value = ini.GetBoolValue(a_section, a_key, a_value);
			ini.SetBoolValue(a_section, a_key, a_value, a_comment);
		} else {
			a_value = ini.GetValue(a_section, a_key, a_value.c_str());
			ini.SetValue(a_section, a_key, a_value.c_str(), a_comment);
		}
	};

	get_value(allowDialogueProgressionBugfix, "Bugfixes", "Enable dialogue progression bugfix", "; Prevents you from being stuck in unskippable dialogue.");
	get_value(instantSkipAllDialogue, "Tweaks", "Enable dialogue instant-skip", "; All dialogue can be instantly skipped, with no cooldown.");
	get_value(enableDialogueColor, "Not Working", "Enable dialogue color tweaks", "; Enable custom colors for dialogue.");
	get_value(unreadDialogueColor.nameColor, "Not Working", "Custom unread dialogue color", "; Set the custom color for unread dialogue (Hex).");
	get_value(readDialogueColor.nameColor, "Not Working", "Custom read dialogue color", "; Set the custom color for read dialogue (Hex).");

	ini.SaveFile(path);

	return true;
}
