#pragma once
#include <string>
class Event
{
public:
	Event();
	virtual ~Event();
	using DescriptorType = const char*;
	virtual DescriptorType type() const = 0;
};


