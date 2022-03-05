#pragma once

#include <Merlin/Scene/Wizard.h>

#include <vector>

namespace Merlin
{
	class WizardStack
	{
	public:
		WizardStack();
		~WizardStack();

		void PushWizard(Wizard* wizard);
		void PopWizard(Wizard* wizard);

		std::vector<Wizard*>::iterator begin() { return m_Wizards.begin(); }
		std::vector<Wizard*>::iterator end() { return m_Wizards.end(); }
	private:
		std::vector<Wizard*> m_Wizards;
		std::vector<Wizard*>::iterator m_WizardInsert;
	};
}