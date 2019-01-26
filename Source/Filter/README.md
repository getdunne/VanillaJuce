# Filter
This is a very slightly-modified version of Jordan Harris's implementation of a Virtual Analog _state-variable filter_.

* [Jordan Harris's original GitHub repo](https://github.com/JordanTHarris/VAStateVariableFilter)
* [Michael Donovan's forked version](https://github.com/michaeldonovan/VAStateVariableFilter) (from which this code was adapted).

The only change I made was to add a _cutoff frequency_ argument to the _setFilter()_ member function, to avoid a redundant call to _calcfilter()_.
