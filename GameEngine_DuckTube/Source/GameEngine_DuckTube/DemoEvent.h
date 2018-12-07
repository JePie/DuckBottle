#pragma once
#include"Event.h"
class DemoEvent : public Event
{
public:
	DemoEvent();
	virtual ~DemoEvent();

	static constexpr DescriptorType descText = "DemoEvent";

	virtual DescriptorType type() const
	{
		return descText;
	};
};

