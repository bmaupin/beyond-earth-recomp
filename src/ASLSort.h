#pragma once

namespace ASL { namespace StdLib { namespace Sort {

// TODO(Phase1): _Sort implementation requires independent native reconstruction.
template<class RandomAccessIterator, class Difference>
void _Sort(RandomAccessIterator first, RandomAccessIterator last, Difference count);

} } }
