#include "stdafx.h"
#include "DemoEvent.h"
#include <iostream>

constexpr DemoEvent::DescriptorType DemoEvent::descText;

DemoEvent::DemoEvent()
{
	std::cout << "__PRETTY_FUNCTION__" << std::endl;
}

DemoEvent::~DemoEvent()
{
	std::cout << "__PRETTY_FUNCTION__" << std::endl;
}

Event::DescriptorType;