#include <cassert>

template<typename T, std::size_t N>
VectorArray<T, N>::VectorArray(void)
:
        size_(0)
{
        assert(invariant());
}

template<typename T, std::size_t N>
VectorArray<T, N>::VectorArray(size_type s)
:
        size_(s)
{
        assert(invariant());
}

template<typename T, std::size_t N>
typename VectorArray<T, N>::iterator VectorArray<T, N>::begin(void)
{
        return array_.begin();
}

template<typename T, std::size_t N>
typename VectorArray<T, N>::const_iterator VectorArray<T, N>::begin(void) const
{
        return array_.begin();
}

template<typename T, std::size_t N>
typename VectorArray<T, N>::iterator VectorArray<T, N>::end(void)
{
        return begin() + size();
}

template<typename T, std::size_t N>
typename VectorArray<T, N>::const_iterator VectorArray<T, N>::end(void) const
{
        return begin() + size();
}

template<typename T, std::size_t N>
typename VectorArray<T, N>::reverse_iterator VectorArray<T, N>::rbegin(void)
{
        return reverse_iterator(end());
}

template<typename T, std::size_t N>
typename VectorArray<T, N>::const_reverse_iterator VectorArray<T, N>::rbegin(void) const
{
        return const_reverse_iterator(end());
}

template<typename T, std::size_t N>
typename VectorArray<T, N>::reverse_iterator VectorArray<T, N>::rend(void)
{
        return array_.rend();
}

template<typename T, std::size_t N>
typename VectorArray<T, N>::const_reverse_iterator VectorArray<T, N>::rend(void) const
{
        return array_.rend();
}

template<typename T, std::size_t N>
typename VectorArray<T, N>::size_type VectorArray<T, N>::size(void) const
{
        return size_;
}

template<typename T, std::size_t N>
typename VectorArray<T, N>::size_type VectorArray<T, N>::max_size(void) const
{
        return N;
}
template<typename T, std::size_t N>
void VectorArray<T, N>::resize(size_type s)
{
        assert(within_bounds(s));
        size_ = s;
        assert(invariant());
}

template<typename T, std::size_t N>
typename VectorArray<T, N>::size_type VectorArray<T, N>::capacity(void) const
{
        return size();
}

template<typename T, std::size_t N>
bool VectorArray<T, N>::empty(void) const
{
        return begin() == end();
}

template<typename T, std::size_t N>
bool VectorArray<T, N>::full(void) const
{
        return size() == max_size();
}

template<typename T, std::size_t N>
typename VectorArray<T, N>::reference VectorArray<T, N>::operator[](size_type i)
{
        assert(within_range(i));
        return array_[i];
}

template<typename T, std::size_t N>
typename VectorArray<T, N>::const_reference VectorArray<T, N>::operator[](size_type i) const
{
        assert(within_range(i));
        return array_[i];
}

template<typename T, std::size_t N>
typename VectorArray<T, N>::reference VectorArray<T, N>::front(void)
{
        return *begin();
}

template<typename T, std::size_t N>
typename VectorArray<T, N>::const_reference VectorArray<T, N>::front(void) const
{
        return *begin();
}

template<typename T, std::size_t N>
typename VectorArray<T, N>::reference VectorArray<T, N>::back(void)
{
        return *(end() - 1);
}

template<typename T, std::size_t N>
typename VectorArray<T, N>::const_reference VectorArray<T, N>::back(void) const
{
        return *(end() - 1);
}

template<typename T, std::size_t N>
void VectorArray<T, N>::push_back(const_reference t)
{
        increment_size();
        back() = t;
}

template<typename T, std::size_t N>
void VectorArray<T, N>::pop_back(void)
{
        decrement_size();
}

template<typename T, std::size_t N>
void VectorArray<T, N>::increment_size(void)
{
        assert(!full());
        ++size_;
        assert(invariant());
}

template<typename T, std::size_t N>
void VectorArray<T, N>::decrement_size(void)
{
        assert(!empty());
        --size_;
        assert(invariant());
}

template<typename T, std::size_t N>
void VectorArray<T, N>::clear(void)
{
        size_ = 0;
        assert(invariant());
}

template<typename T, std::size_t N>
bool VectorArray<T, N>::invariant(void) const
{
        return size() <= max_size();
}

template<typename T, std::size_t N>
bool VectorArray<T, N>::within_range(size_type i) const
{
        return i < size();
}

template<typename T, std::size_t N>
bool VectorArray<T, N>::within_bounds(size_type i) const
{
        return i < max_size();
}
