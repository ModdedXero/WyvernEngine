#include "wvpch.h"
#include "WizardStack.h"

namespace Wyvern
{
	WizardStack::WizardStack()
	{
		m_WizardInsert = m_Wizards.begin();
	}

	WizardStack::~WizardStack()
	{
		for (Wizard* layer : m_Wizards)
			delete layer;
	}

	void WizardStack::PushWizard(Wizard* wizard)
	{
		m_WizardInsert = m_Wizards.emplace(m_WizardInsert, wizard);
	}

	void WizardStack::PopWizard(Wizard* wizard)
	{
		auto it = std::find(m_Wizards.begin(), m_Wizards.end(), wizard);
		if (it != m_Wizards.end())
		{
			m_Wizards.erase(it);
			m_WizardInsert++;
		}
	}
}