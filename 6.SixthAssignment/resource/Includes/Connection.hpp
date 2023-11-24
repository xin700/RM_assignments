#pragma once

#include "MemoryView.hpp"

class Connection
{
public:
	virtual ~Connection();
	virtual void Connect() = 0;
	virtual bool IsConnected() = 0;
	virtual void Disconnect() = 0;
	virtual MemoryView::SizeType Read(const MemoryView& view) = 0;
	virtual MemoryView::SizeType Write(const MemoryView& view) = 0;
};
