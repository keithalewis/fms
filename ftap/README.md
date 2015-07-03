# ftap - Fundamental Theorem of Asset Pricing

Implementation of models based on [this](http://kalx.net/ftap/xva.html)

types vs objects

atomic instruments: (single currency)
struct LIBOR<3M>, ...
struct AMZN, ...

template<class Instrument>
struct instrument_traits {
	typedef typename Instrument::currency currency;
};
template<class Duration>
struct instrument_traits<LIBOR<Duration>> {
	typedef typename USD currency;
};
