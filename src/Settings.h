#pragma once

class Settings
{
public:
	struct Color
	{
		std::string nameColor;

		explicit Color(std::string a_color) :
			nameColor(std::move(a_color))
		{}
	};

	[[nodiscard]] static Settings* GetSingleton()
	{
		static Settings singleton;
		return std::addressof(singleton);
	}

	[[nodiscard]] bool Load();

	bool allowDialogueProgressionBugfix{ true };
	bool instantSkipAllDialogue{ false };
	bool enableDialogueColor{ false };
	Color unreadDialogueColor{ "0xFFFFFF" };
	Color readDialogueColor{ "0x606060" };

private:
	// stuff idk
};
