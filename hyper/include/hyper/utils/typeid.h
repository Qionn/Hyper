#ifndef __HYPER_TYPEID_H__
#define __HYPER_TYPEID_H__

namespace hyper
{
	struct TypeInfo final
	{
	public:
		TypeInfo() = delete;

		template<class T>
		static int GetId() noexcept
		{
			static const int id = s_Counter++;
			return id;
		}

	private:
		static inline int s_Counter = 0;
	};

	template<class T>
	static int TypeId() noexcept
	{
		return TypeInfo::GetId<T>();
	}
}

#endif // !__HYPER_TYPEID_H__
