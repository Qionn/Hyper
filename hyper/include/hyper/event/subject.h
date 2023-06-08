#ifndef __HYPER_SUBJECT_H__
#define __HYPER_SUBJECT_H__

#include <unordered_set>

#include "hyper/fwd.h"

namespace hyper
{
	class ASubject
	{
	public:
		void AddObserver(IObserver* observer);
		void RemoveObserver(IObserver* observer);

		ASubject(const ASubject&)				= delete;
		ASubject(ASubject&&)					= delete;
		ASubject& operator=(const ASubject&)	= delete;
		ASubject& operator=(ASubject&&)			= delete;

		virtual ~ASubject() = default;

	protected:
		ASubject() = default;

		void NotifyObservers(const AEvent& event) const;

	private:
		std::unordered_set<IObserver*> m_Observer;
	};
}

#endif // !__HYPER_SUBJECT_H__
