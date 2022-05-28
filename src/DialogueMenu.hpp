#pragma once

namespace Fix
{
	class DialogueMenuEx : public RE::DialogueMenu
	{
	public:
		static void Install();

	public:
		RE::UI_MESSAGE_RESULTS ProcessMessageEx(RE::UIMessage& a_message);

	private:
		using ProcessMessageFn = decltype(&RE::DialogueMenu::ProcessMessage);

		inline static REL::Relocation<ProcessMessageFn> _ProcessMessageFn;

		void doAllowProgressFix();
	};
}
