#include <MemoryView.hpp>

MemoryView
::MemoryView()
= default;

MemoryView
::MemoryView(const MemoryView& other)
= default;

MemoryView
::MemoryView(MemoryView&& other) noexcept
= default;

MemoryView& 
MemoryView
::operator=(const MemoryView& other)
= default;

MemoryView& 
MemoryView
::operator=(MemoryView&& other) noexcept
= default;

boost::asio::mutable_buffer
MemoryView
::ToBuffer() const
{
	return {Head, Size};
}

MemoryView::ByteType& 
MemoryView::operator[](const SizeType size) const
{
	return Head[size];
}

MemoryView::SizeType
MemoryView
::CopyTo(void* head) const
{
	memcpy(head, Head, Size);
	return Size;
}

MemoryView::SizeType
MemoryView::CopyTo(const MemoryView& destination) const
{
	const SizeType size = Size < destination.Size ? Size : destination.Size;
	memcpy(destination.Head, Head, size);
	return size;
}

MemoryView::SizeType
MemoryView
::ReadFrom(const void* head) const
{
	memcpy(Head, head, Size);
	return Size;
}

MemoryView::SizeType
MemoryView
::ReadFrom(const MemoryView& source) const
{
	const SizeType size = Size < source.Size ? Size : source.Size;
	memcpy(Head, source.Head, size);
	return size;
}
