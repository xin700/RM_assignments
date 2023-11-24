#pragma once

// ReSharper disable once CppUnusedIncludeDirective
#include <string.h>

#include <boost/asio/buffer.hpp>

struct MemoryView final
{
	using ByteType = unsigned char;
	using HeadType = ByteType*;
	using SizeType = unsigned long long;

	HeadType Head{nullptr};
	SizeType Size{0};

	MemoryView();
	MemoryView(const MemoryView& other);
	MemoryView(MemoryView&& other) noexcept;
	MemoryView& operator=(const MemoryView& other);
	MemoryView& operator=(MemoryView&& other) noexcept;

	template <typename THead>
	MemoryView(THead* head, const SizeType count):
		// ReSharper disable once CppCStyleCast
		Head((HeadType)head),
		Size(sizeof(THead) * count)
	{
	}

	[[nodiscard]] boost::asio::mutable_buffer ToBuffer() const;

	ByteType& operator[](SizeType size) const;

	SizeType CopyTo(void* head) const;

	SizeType CopyTo(const MemoryView& destination) const // NOLINT(modernize-use-nodiscard)
	;

	SizeType ReadFrom(const void* head) const;

	SizeType ReadFrom(const MemoryView& source) const // NOLINT(modernize-use-nodiscard)
	;
};
